#ifndef READMOD_H_INCLUDED
#define READMOD_H_INCLUDED

/** @file
 * This file contains the declarations for loading in MOD files and render them in the main program.
 */

#include <QString>

#include <vtkSmartPointer.h>

#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnsignedCharArray.h>
#include <vtkCellData.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkPolyData.h>

#include "model.h"

/** Function to convert hex string into an rgb array.
 * @param hex 6-character colour string.
 */
int* hex_to_rgb(string hex);
/** Function to read mod files and output vtk-compatible polydata.
 * @param fileName Contains the Qstring path of the model file.
 */
vtkSmartPointer<vtkPolyData> readModFile(QString fileName);

/** Function to get the number of cells/polys of the current model.
 */
int getNumberOfCells();
/** Function to get the number of vertices/points of the current model.
 */
int getNumberOfVertices();
/** Function to get the number of materials/pieces of the current model.
 */
int getNumberOfMaterials();

#endif // READMOD_H_INCLUDED
