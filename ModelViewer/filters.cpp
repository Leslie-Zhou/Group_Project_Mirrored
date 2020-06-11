#include <filters.h>

/** @file
 * This file contains the code for all the VTK filters to be used in the main program.
 */

vtkSmartPointer<vtkClipDataSet> clip(vtkSmartPointer<vtkAlgorithm> source, double xOrigin, double yOrigin, double zOrigin, double xNormal, double yNormal, double zNormal)
{
  vtkSmartPointer<vtkClipDataSet> clippedSource = vtkSmartPointer<vtkClipDataSet>::New();
  vtkSmartPointer<vtkPlane> clipPlane = vtkSmartPointer<vtkPlane>::New();

  clippedSource->SetInputConnection( source->GetOutputPort() ) ;
  // Setup clipping plane
  // this will apply a clipping plane
  clipPlane->SetOrigin(xOrigin, yOrigin, zOrigin); // origin point
  clipPlane->SetNormal(xNormal, yNormal, zNormal); // clipping plane (normal axis)
  clippedSource->SetClipFunction( clipPlane.Get() );

  // Return the filtered source
  return clippedSource;
}

vtkSmartPointer<vtkShrinkFilter> shrink(vtkSmartPointer<vtkAlgorithm> source, double shrinkFactor)
{
  vtkSmartPointer<vtkShrinkFilter> shrinkedSource = vtkSmartPointer<vtkShrinkFilter>::New();

  shrinkedSource->SetInputConnection( source->GetOutputPort() );

  // Apply shrink filter
  shrinkedSource->SetShrinkFactor(shrinkFactor*0.01); // Scale down the shrink factor by a factor of 100
                                                      // From 0 - 100 of the slider value to 0.00 - 1.00
  shrinkedSource->Update();

  // Return the filtered source
  return shrinkedSource;
}

vtkSmartPointer<vtkPolyDataNormals> smooth(vtkSmartPointer<vtkAlgorithm> source)
{
  // To create a smoothed model
  vtkSmartPointer<vtkSmoothPolyDataFilter> smoothSource = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
  smoothSource->SetInputConnection( source->GetOutputPort() );
  smoothSource->SetNumberOfIterations(15);
  smoothSource->SetRelaxationFactor(0.1);
  smoothSource->FeatureEdgeSmoothingOff();
  smoothSource->BoundarySmoothingOn();
  smoothSource->Update();

  // To scale the smoothed model correctly to the Polygon's "normals", resulting in the final smoothed model
  vtkSmartPointer<vtkPolyDataNormals> normalSource = vtkSmartPointer<vtkPolyDataNormals>::New();
  normalSource->SetInputConnection( smoothSource->GetOutputPort() );
  normalSource->ComputePointNormalsOn();
  normalSource->ComputeCellNormalsOn();
  normalSource->Update();

  // Return the filtered source
  return normalSource;
}

vtkSmartPointer<vtkActor> slice(vtkSmartPointer<vtkAlgorithm> source, double xOrigin, double yOrigin, double zOrigin, double xNormal, double yNormal, double zNormal)
{
  vtkSmartPointer<vtkPlane> slicePlane = vtkSmartPointer<vtkPlane>::New();
  slicePlane->SetOrigin(xOrigin, yOrigin, zOrigin);
  slicePlane->SetNormal(xNormal, yNormal, zNormal);

  // Create cutter
  vtkSmartPointer<vtkCutter> slicer =  vtkSmartPointer<vtkCutter>::New();
  slicer->SetCutFunction(slicePlane);
  slicer->SetInputConnection( source->GetOutputPort() );

  vtkSmartPointer<vtkPolyDataMapper> slicerMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  slicerMapper->SetInputConnection( slicer->GetOutputPort());
  slicerMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkNamedColors> colors =  vtkSmartPointer<vtkNamedColors>::New();

  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor = vtkSmartPointer<vtkActor>::New();

  planeActor->GetProperty()->SetColor(colors->GetColor3d("pink").GetData());
  planeActor->GetProperty()->SetLineWidth(5);
  planeActor->SetMapper(slicerMapper);

  return planeActor;
}

vtkSmartPointer<vtkPolyData> elevation(vtkSmartPointer<vtkAlgorithm> source, vtkSmartPointer<vtkActor> actor)
{
    double bounds[6];
    actor->GetBounds(bounds); // Gets the dimensions of the model

    vtkSmartPointer<vtkElevationFilter> elevationFilter = vtkSmartPointer<vtkElevationFilter>::New();
    elevationFilter->SetInputConnection(source->GetOutputPort());
    elevationFilter->SetLowPoint(0.0, 0.0, bounds[4]);  // Set the lowest Z value as the lower point
    elevationFilter->SetHighPoint(0.0, 0.0, bounds[5]); // Set the highest Z value as the upper point
    elevationFilter->Update();

    vtkSmartPointer<vtkPolyData> output = vtkSmartPointer<vtkPolyData>::New();
    output->ShallowCopy(vtkPolyData::SafeDownCast(elevationFilter->GetOutput()));

    vtkFloatArray* elevation = vtkFloatArray::SafeDownCast(output->GetPointData()->GetArray("Elevation"));

    // Create the color map
    vtkSmartPointer<vtkLookupTable> colorLookupTable = vtkSmartPointer<vtkLookupTable>::New();
    colorLookupTable->SetTableRange(bounds[4], bounds[5]);
    colorLookupTable->Build();

    // Generate the colors for each point based on the color map
    vtkSmartPointer<vtkUnsignedCharArray> colors = vtkSmartPointer<vtkUnsignedCharArray>::New();
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");

    // Generate the gradient of colors that will visualize the elevation throughout the model
    for(vtkIdType i = 0; i < output->GetNumberOfPoints(); i++)
    {
      double val = elevation->GetValue(i);
      double dcolor[3];
      colorLookupTable->GetColor(val, dcolor);
      unsigned char color[3];
      for(unsigned int j = 0; j < 3; j++)
      {
        color[j] = 255 * dcolor[j]/1.0;
      }
      colors->InsertNextTypedTuple(color);
    }

    output->GetPointData()->AddArray(colors);
    return output;
}

vtkSmartPointer<vtkActor> contours(vtkSmartPointer<vtkAlgorithm> source, vtkSmartPointer<vtkActor> actor)
{
  // Create a plane
  vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
  plane->SetOrigin(actor->GetCenter());
  plane->SetNormal(1,1,1);

  // Get the minimum bounds (X, Y, Z) of the model
  double minBound[3];
  minBound[0] = actor->GetBounds()[0];
  minBound[1] = actor->GetBounds()[2];
  minBound[2] = actor->GetBounds()[4];

  // Get the maximum bounds (X, Y, Z) of the model
  double maxBound[3];
  maxBound[0] = actor->GetBounds()[1];
  maxBound[1] = actor->GetBounds()[3];
  maxBound[2] = actor->GetBounds()[5];

  // Get the center of the model (X, Y, Z)
  double center[3];
  center[0] = actor->GetCenter()[0];
  center[1] = actor->GetCenter()[1];
  center[2] = actor->GetCenter()[2];

  // Find the minimum and maximum distance by calculating the distance between the bounds and the center
  double distanceMin = sqrt(vtkMath::Distance2BetweenPoints(minBound, center));
  double distanceMax = sqrt(vtkMath::Distance2BetweenPoints(maxBound, center));

  // Create cutter
  vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
  cutter->SetCutFunction(plane);
  cutter->SetInputConnection(source->GetOutputPort());


  // Generate 20 contours in the model
  cutter->GenerateValues(20, -distanceMin, distanceMax);
  vtkSmartPointer<vtkPolyDataMapper> cutterMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  cutterMapper->SetInputConnection( cutter->GetOutputPort());
  cutterMapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

  // Create plane actor
  vtkSmartPointer<vtkActor> planeActor = vtkSmartPointer<vtkActor>::New();
  planeActor->GetProperty()->SetColor(colors->GetColor3d("pink").GetData());  // Set contours to deep pink
  planeActor->GetProperty()->SetLineWidth(5);
  planeActor->SetMapper(cutterMapper);

  return planeActor;
}
