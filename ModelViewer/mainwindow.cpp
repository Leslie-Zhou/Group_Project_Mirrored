// mainwindow.cpp
#include <array>
#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/** @file
 * This file contains all the code of all functions utilised for the display of a model in the user interface,
 * as well as all of the functionality of the buttons and other input widgets.
 */

// Menu functions ----------------------------------------------------------- //
void MainWindow::handleOpenButton()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model File"), "./", tr("Model Files(*.stl *.mod)"));

  // If the user opens a file
  // This if statement prevents crashing when the user clicks the open button but doesn't select any files to be opened
  if (fileName.endsWith(".stl", Qt::CaseSensitive))
    {
      reader = vtkSmartPointer<vtkSTLReader>::New();  // Create vtkSTLReader variable that will store the STL file

      reader->SetFileName(fileName.toStdString().c_str());  // Converts file name to standard c string
      reader->Update();

      renderer->RemoveAllViewProps(); // Remove everything from the renderer

      // Update Statistics Section
      ui->numPieces->display( int( reader->GetOutput()->GetNumberOfPieces() ) );
      ui->numPoints->display( int( reader->GetOutput()->GetNumberOfPoints() ) );
      ui->numPolys->display(  int( reader->GetOutput()->GetNumberOfPolys() ) );

      // Visualize
      mapper->SetInputConnection(reader->GetOutputPort());    // Set imported model to the mapper
    }

  if (fileName.endsWith(".mod", Qt::CaseSensitive))
    {
      mapper->SetInputData(readModFile(fileName));  // Read the mod file and set the output to the mapper

      // Update Statistics Section
      ui->numPieces->display( getNumberOfMaterials() );
      ui->numPoints->display( getNumberOfVertices() );
      ui->numPolys->display( getNumberOfCells() );
    }

  // After file had been processed, render it
  if (fileName.endsWith(".mod", Qt::CaseSensitive) || fileName.endsWith(".stl", Qt::CaseSensitive))
    {
      actor->SetMapper(mapper);
      source = actor->GetMapper()->GetInputConnection(0, 0)->GetProducer(); // Update the "original" unfiltered source to the opened file
      renderer->AddActor(actor);
      handleResetViewButton();  // To reset all the settings (turn off filters, reset camera, etc.)
    }
}

void MainWindow::handleSaveButton()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Model File"), "./", tr("Image (*.png);;STL File (*.stl)"));

    // Save as png
    if (fileName.endsWith(".png", Qt::CaseSensitive))
    {
      // Take model displayed in window and converts to image
      vtkWindowToImageFilter* filter = vtkWindowToImageFilter::New();
      filter->Modified();
      filter->SetInput(ui->qvtkWidget->GetRenderWindow());
      filter->SetInputBufferTypeToRGBA();
      filter->Update();

      vtkImageData* data = filter->GetOutput();   // Gets image data

      // Writes image to png by name of 'image.png'. File is saved in build folder currently
      vtkPNGWriter* writer = vtkPNGWriter::New();
      writer->SetFileName(fileName.toStdString().c_str());
      writer->SetInputData(data);
      writer->Write();
      writer->Delete();
    }
    // Save as STL
    // Works to convert mod files to stl files
    if (fileName.endsWith(".stl", Qt::CaseSensitive))
    {
      vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
      stlWriter->SetFileName(fileName.toStdString().c_str());
      stlWriter->SetInputConnection(source->GetOutputPort());
      stlWriter->Write();
    }
}

// -------------------------------------------------------------------------- //
// RESET function ----------------------------------------------------------- //
void MainWindow::handleResetViewButton()
{
  camera = vtkSmartPointer<vtkCamera>::New();  // Create new camera variable to work with

  boxWidget->Off();

  // Resets model to original source
  mapper->SetInputConnection( source->GetOutputPort() );

  // Ensure filters are unchecked when view is being resetted
  ui->clipFilter->setChecked(false);
  ui->shrinkFilter->setChecked(false);
  ui->smoothFilter->setChecked(false);
  ui->sliceFilter->setChecked(false);
  ui->elevationFilter->setChecked(false);
  ui->contoursFilter->setChecked(false);
  ui->axes->setChecked(false);
  ui->legendScaleActor->setChecked(false);
  ui->boxWidget->setChecked(false);
  ui->solidActor->setChecked(true);

  // Reset filter paramaters
  ui->xClipOrigin->setValue(0);
  ui->yClipOrigin->setValue(0);
  ui->zClipOrigin->setValue(0);
  ui->xClipValue->setValue(1);
  ui->yClipValue->setValue(0);
  ui->zClipValue->setValue(0);
  ui->shrinkSlider->setValue(80);
  ui->xSliceOrigin->setValue(0);
  ui->ySliceOrigin->setValue(0);
  ui->zSliceOrigin->setValue(0);
  ui->xSliceValue->setValue(1);
  ui->ySliceValue->setValue(0);
  ui->zSliceValue->setValue(0);

  //To reset the surface
  actor->GetProperty()->SetRepresentationToSurface();

  // To reset the rotation setting //
  Last_Value_Pitch = 0.0;
  Last_Value_Roll = 0.0;
  Last_Value_Yaw = 0.0;
  ui->X_Camera_Pos->setValue(0);
  ui->Y_Camera_Pos->setValue(0);
  ui->Z_Camera_Pos->setValue(0);
  // ----------------------------- //

  // Reset Opacity and Brightness
  ui->opacitySlider->setValue(100);
  ui->lightSlider->setValue(100);
  actor->GetProperty()->SetOpacity(1);
  light->SetIntensity(1);

  // Reset the camera
  camera->SetFocalPoint(30, 0, 30);  // Point the camera to 30, 0, 30
  renderer->SetActiveCamera(camera);  //  Sets the camera to the renderer's camera
  renderer->ResetCamera();
  renderer->ResetCameraClippingRange();

  // Reset renderer and then render
  renderer->RemoveAllViewProps();
  actor->SetMapper(mapper);
  renderer->AddActor(actor);
  renderWindow->Render(); // update renderer
}

// -------------------------------------------------------------------------- //
// Filter & Widget Functions ------------------------------------------------ //
void MainWindow::handleClipFilter()
{
  // Disable all filters
  ui->shrinkFilter->setChecked(false);
  ui->smoothFilter->setChecked(false);
  ui->elevationFilter->setChecked(false);

  // If its applied
  if (ui->clipFilter->isChecked())
  {
    // Run the clip function, providing the origin and normal points via the spinbox as the input,
    // and set the output port of the function as the new input connection to the mapper
    mapper->SetInputConnection( clip(source, ui->xClipOrigin->value(),
                                             ui->yClipOrigin->value(),
                                             ui->zClipOrigin->value(),
                                             ui->xClipValue->value(),
                                             ui->yClipValue->value(),
                                             ui->zClipValue->value())->GetOutputPort() );
  }
  // If it's unchecked
  if (!ui->clipFilter->isChecked())
    mapper->SetInputConnection( source->GetOutputPort() );    // Set back to the original source

  // Render it
  renderWindow->Render();
}

void MainWindow::handleShrinkFilter()
{
  // Disable all filters
  ui->clipFilter->setChecked(false);
  ui->smoothFilter->setChecked(false);
  ui->elevationFilter->setChecked(false);
  ui->solidActor->setChecked(true);

  // If it's applied
  // Apply shrink filter to the mapper, providing the shrink factor via shrinkSlider as the input
  if (ui->shrinkFilter->isChecked())
    mapper->SetInputConnection( shrink(source, ui->shrinkSlider->value())->GetOutputPort() );
  // If unchecked
  if (!ui->shrinkFilter->isChecked())
    mapper->SetInputConnection( source->GetOutputPort() );  // Set back to original source

  // Render
  renderWindow->Render();
}

void MainWindow::handleSmoothFilter()
{
  // Disable all filters
  ui->shrinkFilter->setChecked(false);
  ui->clipFilter->setChecked(false);
  ui->elevationFilter->setChecked(false);

  // If it's applied
  // Apply smooth filter to the mapper via 'smooth' function
  if (ui->smoothFilter->isChecked())
    mapper->SetInputConnection( (smooth(source))->GetOutputPort() );
  // If unchecked
  if (!ui->smoothFilter->isChecked())
    mapper->SetInputConnection( source->GetOutputPort() );

  // Render
  renderWindow->Render();
}

void MainWindow::handleSliceFilter()
{
  // Disable contour filter
  ui->contoursFilter->setChecked(false);
  // If it's applied
  // Apply slice filter and add the new actor to the renderer via 'slice' function
  if (ui->sliceFilter->isChecked())
  {
    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);  // Reset renderer to only include source actor
    // Add additional slice actor to overlay on top of the source actor
    renderer->AddActor( slice( source,
                               ui->xSliceOrigin->value(),
                               ui->ySliceOrigin->value(),
                               ui->zSliceOrigin->value(),
                               ui->xSliceValue->value(),
                               ui->ySliceValue->value(),
                               ui->zSliceValue->value() ) );
  }
  // If unchecked
  if (!ui->sliceFilter->isChecked())
  {
    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);  // Only include the source actor in the renderer
  }
  // Render
  renderWindow->Render();
}

void MainWindow::handleElevationFilter()
{
  // Disable all filters
  ui->shrinkFilter->setChecked(false);
  ui->clipFilter->setChecked(false);
  ui->smoothFilter->setChecked(false);

  if (ui->elevationFilter->isChecked())
    mapper->SetInputData(elevation(source, actor));
  // If unchecked
  if (!ui->elevationFilter->isChecked())
    mapper->SetInputConnection( source->GetOutputPort() );

  // Render
  renderWindow->Render();
}

void MainWindow::handleContoursFilter()
{
  // Disable slice filter
  ui->sliceFilter->setChecked(false);

  // If it's applied
  // Apply contours filter and add the new actor to the renderer via 'contours' function
  if (ui->contoursFilter->isChecked())
  {
    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);  // Reset renderer to only include source actor
    // Add additional contours actor to overlay on top of the source actor
    renderer->AddActor( contours(source, actor) );
  }
  // If unchecked
  if (!ui->contoursFilter->isChecked())
  {
    renderer->RemoveAllViewProps();
    renderer->AddActor(actor);  // Only include the source actor in the renderer
  }
  // Render
  renderWindow->Render();
}

void MainWindow::handleBoxWidget()
{
    if (ui->boxWidget->isChecked())
    {
        callback = vtkSmartPointer<vtkBoxCallback>::New();
        boxWidget = vtkSmartPointer<vtkBoxWidget2>::New();
        // Initialize the interactor
        interactor->SetRenderWindow(renderWindow);
        interactor->SetInteractorStyle(style);

        boxWidget->SetInteractor(interactor);
        boxWidget->GetRepresentation()->SetPlaceFactor(1);
        boxWidget->GetRepresentation()->PlaceWidget(actor->GetBounds());

        callback->SetActor(actor);
        boxWidget->AddObserver(vtkCommand::InteractionEvent, callback);
        boxWidget->On();
    }
    else
    {
      boxWidget->Off();
    }

    renderWindow->Render();
}

// -------------------------------------------------------------------------- //
// FILTER PARAMETERS FUNCTIONS ---------------------------------------------- //
// These functions run as soon as any of the filter's parameters changes to
// to update the model in real-time
void MainWindow::on_xClipOrigin_valueChanged(double value)
{
  if (ui->clipFilter->isChecked())
    handleClipFilter();
}
void MainWindow::on_yClipOrigin_valueChanged(double value)
{
  if (ui->clipFilter->isChecked())
    handleClipFilter();
}
void MainWindow::on_zClipOrigin_valueChanged(double value)
{
  if (ui->clipFilter->isChecked())
    handleClipFilter();
}

void MainWindow::on_xClipValue_valueChanged(double value)
{
  if (ui->clipFilter->isChecked())
    handleClipFilter();
}
void MainWindow::on_yClipValue_valueChanged(double value)
{
  if (ui->clipFilter->isChecked())
    handleClipFilter();
}
void MainWindow::on_zClipValue_valueChanged(double value)
{
  if (ui->clipFilter->isChecked())
    handleClipFilter();
}

void MainWindow::on_shrinkSlider_sliderMoved(int position)
{
  if (ui->shrinkFilter->isChecked())
    handleShrinkFilter();
}

void MainWindow::on_xSliceOrigin_valueChanged(double value)
{
  if (ui->sliceFilter->isChecked())
    handleSliceFilter();
}
void MainWindow::on_ySliceOrigin_valueChanged(double value)
{
  if (ui->sliceFilter->isChecked())
    handleSliceFilter();
}
void MainWindow::on_zSliceOrigin_valueChanged(double value)
{
  if (ui->sliceFilter->isChecked())
    handleSliceFilter();
}

void MainWindow::on_xSliceValue_valueChanged(double value)
{
  if (ui->sliceFilter->isChecked())
    handleSliceFilter();
}
void MainWindow::on_ySliceValue_valueChanged(double value)
{
  if (ui->sliceFilter->isChecked())
    handleSliceFilter();
}
void MainWindow::on_zSliceValue_valueChanged(double value)
{
  if (ui->sliceFilter->isChecked())
    handleSliceFilter();
}
// -------------------------------------------------------------------------- //
// Properties Functions ----------------------------------------------------- //
void MainWindow::handleChangeColorButton()
{
  // Retrieve RGB data from the user-selected colour via a QColorDialog window
  QColor QTcolor = QColorDialog::getColor(Qt::white, this);
	if (QTcolor.isValid())
	{
     // change the actor to that colour
    actor->GetProperty()->SetColor(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
		renderWindow->Render();
	}
}

void MainWindow::handleBackgroundColor()
{
  // Retrieve RGB data from the user-selected colour via a QColorDialog window
  QColor QTcolor = QColorDialog::getColor(Qt::white, this);
	if (QTcolor.isValid())
	{
    // change the background of the renderer to that colour
    renderer->SetBackground(QTcolor.redF(), QTcolor.greenF(), QTcolor.blueF());
		renderWindow->Render();
	}
}

// Brightness slider
void MainWindow::on_lightSlider_sliderMoved(int position)
{
		light->SetIntensity(float(position) / 100); // Change brightness of light as slider is moved
    renderWindow->Render();
}
// Opacity slider
void MainWindow::on_opacitySlider_sliderMoved(int position)
{
	actor->GetProperty()->SetOpacity(float(position) / 100); // Change opacity of actor as slider is moved
	renderWindow->Render();
}

// -------------------------------------------------------------------------- //
// Perspective Functions ---------------------------------------------------- //
void MainWindow::handleZoomInButton()
{
    camera->Zoom(1.1); //zoom in
    renderWindow->Render();
}

void MainWindow::handleZoomOutButton()
{
    camera->Zoom(0.9); //zoom out
    renderWindow->Render();
}

void MainWindow::on_X_Camera_Pos_valueChanged(int value)
{
	int Temp = value;
	value = value - Last_Value_Pitch;
	renderer->GetActiveCamera()->Azimuth(double(value));
	Last_Value_Pitch = Temp;
	renderWindow->Render();
}

void MainWindow::on_Y_Camera_Pos_valueChanged(int value)
{
	int Temp = value;
	value = value - Last_Value_Roll;
	renderer->GetActiveCamera()->Roll(double(value));
	Last_Value_Roll = Temp;
	renderWindow->Render();
}

void MainWindow::on_Z_Camera_Pos_valueChanged(int value)
{
	int Temp = value;
	value = value - Last_Value_Yaw;
  renderer->GetActiveCamera()->OrthogonalizeViewUp();     // Prevents glitches
	renderer->GetActiveCamera()->Elevation(double(value));
	Last_Value_Yaw = Temp;
	renderWindow->Render();
}

// -------------------------------------------------------------------------- //
// Representation Functions ------------------------------------------------- //
void MainWindow::handleAxes()
{
    if (ui->axes->isChecked())
      {
          //set bounds and camera
          cubeAxesActor->SetBounds(actor->GetBounds());
          cubeAxesActor->SetCamera(renderer->GetActiveCamera());

          //set color of title, label and grid

          cubeAxesActor->GetXAxesGridlinesProperty()->SetColor(0.5, 0.5, 0.5);
          cubeAxesActor->GetYAxesGridlinesProperty()->SetColor(0.5, 0.5, 0.5);
          cubeAxesActor->GetZAxesGridlinesProperty()->SetColor(0.5, 0.5, 0.5);

          //show gridlines
          cubeAxesActor->DrawXGridlinesOn();
          cubeAxesActor->DrawYGridlinesOn();
          cubeAxesActor->DrawZGridlinesOn();

          cubeAxesActor->SetGridLineLocation(2);
          cubeAxesActor->XAxisMinorTickVisibilityOff();
          cubeAxesActor->YAxisMinorTickVisibilityOff();
          cubeAxesActor->ZAxisMinorTickVisibilityOff();
          cubeAxesActor->SetLabelScaling(true, 0, 0, 0);
          cubeAxesActor->SetTickLocation(1);

          renderer->AddActor(cubeAxesActor);
          renderWindow->Render();
      }
    else
      {
          renderer->RemoveActor(cubeAxesActor);
          renderWindow->Render();
      }
}

void MainWindow::handlelegendScaleActor()
{
  //if checked this function
	if (ui->legendScaleActor->isChecked())
		renderer->AddActor(legendScaleActor);   // to add the scale legend actor to renderer
	// If  unchecked this function
	if (!ui->legendScaleActor->isChecked())
    renderer->RemoveActor(legendScaleActor);  // Remove scale actor props

  renderWindow->Render();
}

void MainWindow::handleRepresentation()
{
    switch(repGroupButton->checkedId())
    {
    case 0:
        actor->GetProperty()->SetRepresentationToSurface();
        break;

    case 1:
        actor->GetProperty()->SetRepresentationToWireframe();
        break;

    case 2:
        actor->GetProperty()->SetRepresentationToPoints();
        break;
    }
    renderWindow->Render();
}
// -------------------------------------------------------------------------- //
// Main Function ------------------------------------------------------------ //
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
  // standard call to setup Qt UI
  ui->setupUi( this );
  //showMaximized(); // NOTE: Maximizing doesn't work on Mac

  //create a button group of representation buttons
  repGroupButton = new QButtonGroup(this);
  repGroupButton -> addButton(ui->solidActor, 0);
  repGroupButton -> addButton(ui->wireFrameActor, 1);
  repGroupButton -> addButton(ui->vertexActor, 2);
  ui->solidActor->setChecked(true); // set default to solid actor

  // Connecting qt buttons/actions to their appropiate function.
  // Opening and Saving
  connect( ui->actionFileOpen, &QAction::triggered, this, &MainWindow::handleOpenButton );
  connect( ui->actionFileSave, &QAction::triggered, this, &MainWindow::handleSaveButton );
  // Reset
  connect( ui->buttonResetView, &QPushButton::released, this, &MainWindow::handleResetViewButton );
  // Filters & Widgets
  connect( ui->clipFilter, &QCheckBox::released, this, &MainWindow::handleClipFilter );
  connect( ui->shrinkFilter, &QCheckBox::released, this, &MainWindow::handleShrinkFilter );
  connect( ui->smoothFilter, &QCheckBox::released, this, &MainWindow::handleSmoothFilter );
  connect( ui->sliceFilter, &QCheckBox::released, this, &MainWindow::handleSliceFilter );
  connect( ui->elevationFilter, &QCheckBox::released, this, &MainWindow::handleElevationFilter );
  connect( ui->contoursFilter, &QCheckBox::released, this, &MainWindow::handleContoursFilter );
  connect( ui->boxWidget, &QCheckBox::released, this, &MainWindow::handleBoxWidget);
  // Properties
  connect( ui->buttonColor, &QPushButton::released, this, &MainWindow::handleChangeColorButton );
  connect( ui->buttonBgColor, &QPushButton::released, this, &MainWindow::handleBackgroundColor );
  // Perspective
  connect( ui->zoomInButton, &QPushButton::released, this, &MainWindow::handleZoomInButton);
  connect( ui->zoomOutButton, &QPushButton::released, this, &MainWindow::handleZoomOutButton);
  // Representation
  connect( ui->axes, &QCheckBox::released, this, &MainWindow::handleAxes );
  connect( ui->legendScaleActor, &QCheckBox::released, this, &MainWindow::handlelegendScaleActor);
  connect( ui->solidActor, &QCheckBox::released, this, &MainWindow::handleRepresentation);
  connect( ui->wireFrameActor, &QCheckBox::released, this, &MainWindow::handleRepresentation);
  connect( ui->vertexActor, &QCheckBox::released, this, &MainWindow::handleRepresentation);

  // Initialize the variables that will be used throughout the program
  actor = vtkSmartPointer<vtkActor>::New();
  renderer = vtkSmartPointer<vtkRenderer>::New();
  mapper = vtkSmartPointer<vtkDataSetMapper>::New();
  camera = vtkSmartPointer<vtkCamera>::New();
  legendScaleActor = vtkSmartPointer<vtkLegendScaleActor>::New();

  // Initialize the source to be used to save the original model details
  source = vtkSmartPointer<vtkAlgorithm>::New();
  // Initialize the axes actor
  cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();

  // Initialize vars to be used for the box widget
  interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
  style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
  callback = vtkSmartPointer<vtkBoxCallback>::New();
  boxWidget = vtkSmartPointer<vtkBoxWidget2>::New();

  // Set default rotation values
  Last_Value_Pitch = 0.0;
  Last_Value_Roll = 0.0;
  Last_Value_Yaw = 0.0;

  //  Initialize light with default settings
  light = vtkSmartPointer<vtkLight>::New();
  light->SetLightTypeToHeadlight();
  light->SetPositional(false);
  light->SetFocalPoint(0, 0, 0);
  light->SetDiffuseColor(1, 1, 1);
  light->SetAmbientColor(1, 1, 1);
  light->SetSpecularColor(1, 1, 1);
  light->SetIntensity(1);

  // Setup the renderers's camera
  // This changes the default focal point
  camera->SetFocalPoint(30, 0, 30);  // Point the camera to 30, 0, 30
  renderer->SetActiveCamera(camera);
  renderer->AddLight( light );

  // Set default color of actor to red and background to silver
  vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
  actor->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );
  renderer->SetBackground( colors->GetColor3d("Silver").GetData() );

  // Now need to create a VTK render window and link it to the QtVTK widget
  ui->qvtkWidget->SetRenderWindow( renderWindow );
  ui->qvtkWidget->GetRenderWindow()->AddRenderer( renderer );	  // ask the QtVTKOpenGLWidget for its renderWindow and add it to the renderer

  //Must create the window initially
  renderWindow->Render();

  // Prompt the user to open a model file
  handleOpenButton();
}

MainWindow::~MainWindow()
{
    delete ui;
}
