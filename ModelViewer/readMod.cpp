#include <readMod.h>

/** @file
 * This file contains the code for loading in MOD files and render them in the main program.
 */

 model model; // Create model object

// Function to convert hex string into an rgb array
 int* hex_to_rgb(string hex)
 {
 	int* rgb = new int[3];
 	stringstream ss;
 	string str;

 	int size = hex.size();

 	for (int i = 0; i < 3; i++)
  {
 	  if (size == 6)  // Check that there are 6 characters in the string
      str = hex.substr(i * 2, 2);
 		else
      break;

 		ss << std::hex << str;
 		ss >> rgb[i];
 		ss.clear();
 	}
 	return rgb;
 }

// Function to convert a mod file to a vtkPolyData that can be rendered
// Input the fileName QString retrieved via QFileDialog in the mainwindow
vtkSmartPointer<vtkPolyData> readModFile(QString fileName)
{
  std::ifstream modelFile(fileName.toStdString().c_str());  // Convert QString to ifstream
  model.readModel(modelFile); // Pass modelFile to the readModel function found in the model class

  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  int num_vctr = model.countObjectsFromClass('v');
  int num_cell = model.countObjectsFromClass('c');

  // Create a 2D point array
  // Outcome: point[num_vctr][3]
  float** point = new float*[ num_vctr ];
  for (int i = 0 ; i < num_vctr ; i++)
    point[i] = new float[3];

  // Fill in the point array with all the points/vertices of the model
  for (int i = 0 ; i < num_vctr ; i++)
  {
      point[i][0] = model.getX(i);
      point[i][1] = model.getY(i);
      point[i][2] = model.getZ(i);
  }

  // Import all the points into vtkPoint variable
  for (int i = 0; i < num_vctr; i++)
    points->InsertPoint(i,point[i]);

  // Create vertices array
  // Outcome: vertices[num_cell][8]
  vtkIdType** vertices = new vtkIdType*[ num_cell ];
  for (int i = 0 ; i < num_cell ; i++)
    vertices[i] = new vtkIdType[8];

  // Fill in the vertices array with the vertices corresponding to each cell
  for (int i = 0 ; i < num_cell ; i++)
  {
    for (int j = 0 ; j < 8 ; j ++)
      vertices[i][j] = model.getCellVertices(i)[j];
  }

  vtkSmartPointer<vtkUnstructuredGrid> ugrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
  ugrid->Allocate( num_cell );  // Allocate the total number of cells to the ugrid

  // Input all of the cell data into the ugrid
  for (int i = 0 ; i < num_cell ; i++)
  {
    if (model.getCellType(i) == 't')  // If tetrahedron
      ugrid->InsertNextCell(VTK_TETRA, 4, vertices[i]);
    if (model.getCellType(i) == 'p')  // If pyramid
      ugrid->InsertNextCell(VTK_PYRAMID, 5, vertices[i]);
    if (model.getCellType(i) == 'h')  // If hexahedron
      ugrid->InsertNextCell(VTK_HEXAHEDRON, 8, vertices[i]);
  }

  ugrid->SetPoints(points); // Input all points data into ugrid

  vtkSmartPointer<vtkUnsignedCharArray> cellData = vtkSmartPointer<vtkUnsignedCharArray>::New();
  cellData->SetNumberOfComponents(3);   // To store R, G, B values
  cellData->SetNumberOfTuples(num_cell);  // To store the rgb values for all the model cells

  // Set the colour of each cell into cellData
  for (int i = 0; i < num_cell ; i++)
  {
    string hex = model.getCellColour(i);  // Outputs a hex string
    int* rgbPtr = hex_to_rgb(hex);  // Convert hex string to rgb array
    float rgb[3];
    rgb[0] = rgbPtr[0]; // R
    rgb[1] = rgbPtr[1]; // G
    rgb[2] = rgbPtr[2]; // B

    cellData->InsertTuple(i, rgb);  // Update cellData
  }
  ugrid->GetCellData()->SetScalars(cellData); // Update ugrid with the colours for each cell

  // To convert Ugrid into vtkPolyData
  // This has to be done for filters/features that requires polydata to work
  vtkSmartPointer<vtkDataSetSurfaceFilter> filter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
  filter->SetInputData(ugrid);
  filter->Update();

  vtkSmartPointer<vtkPolyData> output = filter->GetOutput();

  return output;  // Return polydata output

  // https://lorensen.github.io/VTKExamples/site/Cxx/UnstructuredGrid/UGrid/
  // https://lorensen.github.io/VTKExamples/site/Cxx/PolyData/ColorCellsWithRGB/
  // http://vtk.1045678.n5.nabble.com/vtkUnstructuredGrid-to-vtkPolyData-td5722890.html#a5722901
}

// Functions to retrieve the CURRENT model's total number of mats, vertices and cells
// Used to retrieve data for statistics
int getNumberOfMaterials() { return model.countObjectsFromClass('m'); }
int getNumberOfCells() { return model.countObjectsFromClass('c'); }
int getNumberOfVertices() { return model.countObjectsFromClass('v'); }
