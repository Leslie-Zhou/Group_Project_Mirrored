#ifndef FILTERS_H_INCLUDED
#define FILTERS_H_INCLUDED

/** @file
 * This file contains the declarations for all the VTK filters to be used in the main program
 */
#include <vtkSmartPointer.h>
// For shrink filter
#include <vtkShrinkFilter.h>
// For clip filter
#include <vtkClipDataSet.h>
#include <vtkPlane.h>
// For smooth filter
#include <vtkSmoothPolyDataFilter.h>
#include <vtkPolyDataNormals.h>
// For slice filter
#include <vtkNamedColors.h>
#include <vtkCutter.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
// For elevation fitler
#include <vtkActor.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkXMLPolyDataWriter.h>
#include <vtkLookupTable.h>
#include <vtkFloatArray.h>
#include <vtkElevationFilter.h>
#include <vtkUnsignedCharArray.h>
// For source
#include <vtkAlgorithm.h>
#include <vtkAlgorithmOutput.h>


/** Clips the given source model based on the provided X, Y, Z coordinates for the clipping plane normal and its origin point
 */
vtkSmartPointer<vtkClipDataSet> clip(vtkSmartPointer<vtkAlgorithm> source, double xOrigin, double yOrigin, double zOrigin, double xNormal, double yNormal, double zNormal);
/** Shrinks the given source model by a factor determined by the given shrinking factor
 */
vtkSmartPointer<vtkShrinkFilter> shrink(vtkSmartPointer<vtkAlgorithm> source, double shrinkFactor);
/** Smooths the given source model by smoothing out all of its edges into curves
 */
vtkSmartPointer<vtkPolyDataNormals> smooth(vtkSmartPointer<vtkAlgorithm> source);
/** Slices the current model based on the provided X, Y, Z coordinates for the slicing plane normal and its origin point
 */
vtkSmartPointer<vtkActor> slice(vtkSmartPointer<vtkAlgorithm> source, double xOrigin, double yOrigin, double zOrigin, double xNormal, double yNormal, double zNormal);
/** Visualizes the elevation througout the model by using a rainbow colour gradient.
 * The 'bluer' an area is, the higher it is relative to the rest of the model
 */
vtkSmartPointer<vtkPolyData> elevation(vtkSmartPointer<vtkAlgorithm> source, vtkSmartPointer<vtkActor> actor);
/** Visualizes the contours of the model
 */
vtkSmartPointer<vtkActor> contours(vtkSmartPointer<vtkAlgorithm> source, vtkSmartPointer<vtkActor> actor);
#endif // FILTERS_H_INCLUDED
