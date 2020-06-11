// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/** @file
 * This file contains the declarations for the Program's Main Window.
 */

// Qt Libraries used
#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QColorDialog>
#include <QColor>
#include <QButtonGroup>

// VTK libraries used
// For main program
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkLight.h>
#include <vtkLegendScaleActor.h>
#include <vtkRotationalExtrusionFilter.h>
#include <vtkCubeAxesActor.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkLegendScaleActor.h>  // For Scale Legend
#include <vtkCubeAxesActor.h> // For Axes Display

// To read/write STL files
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>

// To save model into an image file
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkImageData.h>

// For storing source
#include <vtkAlgorithm.h>
#include <vtkAlgorithmOutput.h>

// For box widget
#include <vtkBoxWidget2.h>
#include <vtkTransform.h>
#include <vtkCommand.h>
#include <vtkBoxCallback.h>
#include <vtkBoxRepresentation.h>

// For filters
#include "filters.h"
// To read mod files
#include "readMod.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Constructor function to initialize the program
    */
    explicit MainWindow(QWidget *parent = 0);
    /** Destructor function to exit the program
     */
    ~MainWindow();

// Slots for the button actions
    public slots:
      /** A function to open MOD and STL file.
       * Utilizes QFileDialog to open the native OS file explorer,
       * allowing only MOD/STL files to be opened and read by the program.
       */
      void handleOpenButton();
      /** A function to save an image of the model.
       * Saves a screenshot of what is currently displayed in the QtVTKWidget.
       */
      void handleSaveButton();
      /** A function to reset the Model View.
       * Resets Model's filters, rotation, properties, and camera.
       */
      void handleResetViewButton();
      /** Function to change the colour of the model.
       * Uses QColorDialog to allow the user to select any RGB colour and apply it to the model.
       */
      void handleChangeColorButton();
      /** Function to change the colour of the background.
       * Uses QColorDialog to allow the user to select any RGB colour and apply it to the background.
       */
      void handleBackgroundColor();
      /** Function to apply clip filter to the model.
        * User can specify the clipping axis and origin point (X, Y, Z) via a spinbox.
        */
      void handleClipFilter();
      /** Function to apply shrink filter to the model.
       * User can specify the shrinking factor via a slider.
       * The lower the slider, the lower the shrink factor (the more the model will shrink).
       */
      void handleShrinkFilter();
      /** Function to apply smooth filter to the model.
       */
      void handleSmoothFilter();
      /** Function to apply slice filter to the model
       */
      void handleSliceFilter();
      /** Function to apply elevation filter to the model.
       */
      void handleElevationFilter();
      /** Function to apply contours filter to the model.
       */
      void handleContoursFilter();
      /** Function to apply a scale legend to the model.
       */
      void handlelegendScaleActor();
      /** Function to show or hide the axes of the model
       */
      void handleAxes();
	    /** Function to switch representation of the actor.
	     */
	    void handleRepresentation();
      /** Function to turn on box widget
      */
      void handleBoxWidget();
      /** Update the model when clip filter's X origin point is changed.
       */
      void on_xClipOrigin_valueChanged(double value);
      /** Update the model when clip filter's Y origin point is changed.
       */
      void on_yClipOrigin_valueChanged(double value);
      /** Update the model when clip filter's Z origin point is changed.
       */
      void on_zClipOrigin_valueChanged(double value);
      /** Update the model when clip filter's X normal point is changed.
       */
      void on_xClipValue_valueChanged(double value);
      /** Update the model when clip filter's Y normal point is changed.
       */
      void on_yClipValue_valueChanged(double value);
      /** Update the model when clip filter's Z normal point is changed.
       */
      void on_zClipValue_valueChanged(double value);
      /** Update the model when shrink filter's shrink factor is changed.
       */
      void on_shrinkSlider_sliderMoved(int position);
      /** Update the model when clip filter's X origin point is changed.
       */
      void on_xSliceOrigin_valueChanged(double value);
      /** Update the model when clip filter's Y origin point is changed.
       */
      void on_ySliceOrigin_valueChanged(double value);
      /** Update the model when clip filter's Z origin point is changed.
       */
      void on_zSliceOrigin_valueChanged(double value);
      /** Update the model when slice filter's X value is changed.
       */
      void on_xSliceValue_valueChanged(double value);
      /** Update the model when slice filter's Y value is changed.
       */
      void on_ySliceValue_valueChanged(double value);
      /** Update the model when slice filter's Z value is changed.
       */
      void on_zSliceValue_valueChanged(double value);
      /** Function for changing the brightness of the model via slider.
       */
      void on_lightSlider_sliderMoved(int position);
      /** Function for changing the opacity of the model via slider.
       */
      void on_opacitySlider_sliderMoved(int position);
      /** Function for zooming in the model.
       */
      void handleZoomInButton();
      /** Function for zooming out the model.
       */
      void handleZoomOutButton();
      /** Function for changing the Pitch/Azimuth of the model.
       */
	    void on_X_Camera_Pos_valueChanged(int value);
      /** Function for changing the Roll of the model.
       */
	    void on_Y_Camera_Pos_valueChanged(int value);
      /** Function for changing the Yaw/Elevation of the model.
       */
	    void on_Z_Camera_Pos_valueChanged(int value);

private:
    Ui::MainWindow *ui; /**< Qt UI variable */

    // Main components of a vtk model renderer
    vtkSmartPointer<vtkActor> actor;
    vtkSmartPointer<vtkNamedColors> colors;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkDataSetMapper> mapper;
    vtkSmartPointer<vtkLight> light;
    vtkSmartPointer<vtkSTLReader> reader;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow; // The VTK Render Window
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkAlgorithm> source; // To store the "original" source of the model

    QButtonGroup *repGroupButton;  /**< To store group buttons of representation */

    vtkSmartPointer<vtkLegendScaleActor> legendScaleActor; /**< Actor for Scale Legend */
    // For showing axes
    vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor;  /**< Store the axes actor */
    // For box widget
    vtkSmartPointer<vtkRenderWindowInteractor> interactor; /**< Interactor for box widget */
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style; /**< Style of the interactor */
    vtkSmartPointer<vtkBoxWidget2> boxWidget; /**< Box Widget object */
    vtkSmartPointer<vtkBoxCallback> callback; /**< Callback class to be used for box widget */

    // To keep track of rotation of the model
    double Last_Value_Pitch; /**< To keep track of the model's pitch */
    double Last_Value_Roll; /**< To keep track of the model's roll */
    double Last_Value_Yaw; /**< To keep track of the model's yaw */
};

#endif // MAINWINDOW_H
