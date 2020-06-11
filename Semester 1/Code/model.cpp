#include "model.h"

// constructor
model::model()
{}

// destructor
model::~model()
{}

// copy constructor
model::model(const model& toBeCopied)
{
  materialObjects = toBeCopied.materialObjects;
  vectorObjects = toBeCopied.vectorObjects;
  cellObjects = toBeCopied.cellObjects;
}

// '=' operator overload to equal a model with another model
model& model::operator=(const model& toBeCopied)
{
  if (this == &toBeCopied) return(*this);
  materialObjects = toBeCopied.materialObjects;
  vectorObjects = toBeCopied.vectorObjects;
  cellObjects = toBeCopied.cellObjects;
  return(*this);
}

int model::countObjectsFromClass(char type)
{
    int counter = 0;

    if (type != 'm' && type != 'v' && type != 'c')      // error check: if type input is incorrect, return.
        return(0);

    // Loop over a large number of iterations
    // This loop counts how many objects a certain class has
    for (int i = 0 ; i < 100000000 ; i++)
    {
        // Once the last object is reached, break from the for loop. //
        if (type == 'm' && materialObjects[i].GetID() != i)
            break;
        if (type == 'v' && vectorObjects[i].getID() != i)
            break;
        if (type == 'c' && cellObjects[i].getId() != i)
            break;
        counter++;  // count how many objects there are
    }
    return(counter); // return amount of objects for a given class
}

void model::createObjectsFromFile(ifstream &modelFile)
{
    // Variables to store number of materials, vectors and cells presented in the file
    uint16_t num_mat = 0;
    uint16_t num_vctr = 0;
    uint16_t num_cell = 0;

    string line;  // string variable to store each line from reading the file

    // loop through every line
    while( getline (modelFile, line) )
    {
        // Depending on the class indicator infront of each line within the mod file, count up the corresponding counter variable
        if (line[0] == 'm')
            num_mat++;
        if (line[0] == 'v')
            num_vctr++;
        if (line[0] == 'c')
            num_cell++;
    }

    // If there's more than one object, then create an array of objects, otherwise, create a single variable //
    if (num_mat > 1)
        materialObjects = new Material[num_mat];
    else
        materialObjects = new Material;

    if (num_vctr > 1)
        vectorObjects = new vectorClass[num_vctr];
    else
        vectorObjects = new vectorClass;

    if (num_cell > 1)
        cellObjects = new Cell[num_cell];
    else
        cellObjects = new Cell;

    // Test print the number of objects created for each class
    /*cout << "# Mats: " << num_mat << endl;
    cout << "# Vectors: " << num_vctr << endl;
    cout << "# Cells: " << num_cell << endl;*/

    // Resets the file seeking; puts the 'cursor' back to the beginning of the file
    modelFile.clear();
    modelFile.seekg (0, ios::beg);
}

// Export material input data to the material object
void model::exportDataToObj(int id, float density, string colour, string name)
{
    materialObjects[id].SetMaterial(id, density, colour, name);
}


// Export vector input data to the vector object
void model::exportDataToObj(int id, float x, float y, float z)
{
    vectorObjects[id].setVector(float(id), x, y, z);
}

// Export input data to the cell object
void model::exportDataToObj(int id, char type, int mat, int cell_vertices[8])
{
    uint16_t num_vctr = 0;

    // Determine the shape of the cell to determine how many vertices it contains
    if (type != 't' && type != 'p' && type != 'h')
        exit(1);
    if (type == 't')
        num_vctr = 4;
    if (type == 'p')
        num_vctr = 5;
    if (type == 'h')
        num_vctr = 8;

    // Create the appropiate sized vector object to store the vertices
     vectorClass* cellVectors = new vectorClass[num_vctr];

    // Find the actual vectors associated with the vector ID provided by the
    // cell_vertices IDs and set it equal to the vector "cellVectors"
    for (int i = 0 ; i < num_vctr ; i++)
    {
        cellVectors[i].setVector(float(vectorObjects[cell_vertices[i]].getID()),
                                       vectorObjects[cell_vertices[i]].getX(),
                                       vectorObjects[cell_vertices[i]].getY(),
                                       vectorObjects[cell_vertices[i]].getZ());
    }

    // Export cell data to the cell object
    cellObjects[id].setCell(id, type, mat, cellVectors);
}


// Function to calculate total volume of a model
float model::getVolume()
{
    uint16_t num_cell = countObjectsFromClass('c');
    if (num_cell <= 0) // error check
    {
      cout << "getVolume() function failed: number of cells cannot not determined" << endl;
      exit(1);
    }

    float volume = 0;

    // Loop through all the cells in the model
    for (int i = 0 ; i < num_cell ; i++)
    {
        cellObjects[i].calVolume();     // calculate the volume of the ith cell
        volume += cellObjects[i].getVolume();  // total up the volumes of each individual cell
    }
    return volume;  // return the total sum of all the volumes of each cells in the model
}

// Function to calculate total weight of the model
// NOTE: Weight here refers to the mass of the model, so it should be expressed as units of mass (e.g. kg, g, lb) instead of units of force (e.g. Newtons)                          //
// To convert mass into weight, multiply the return data from this function with the gravitational acceleration experienced by the model (i,e, On Earth it will be about 9.81 m/s2) //
float model::getWeight()
{
    uint16_t num_cell = countObjectsFromClass('c');
    uint16_t num_mat  = countObjectsFromClass('m');
    if (num_cell <= 0 || num_mat <= 0) // error check
    {
      cout << "getWeight() function failed: number of cells or materials cannot not determined" << endl;
      exit(1);
    }

    float weight = 0;

    int current_cell_mat = 0;  // will store the total number of cells that had been processed

    // Calculate the weight of the entire model by summing the weights of each cells according to the material's density and the cell's volume
    // NOTE: weight = density * volume
    for (int i = 0 ; i < num_mat ; i++) // Loop through all the materials (to account for different density materials)
    {
        for (int j = 0 ; j < num_cell ; j++)    // Loop through all the cells associated with ONE of the material (i signifies the material)
        {
            current_cell_mat = cellObjects[j].getMat();  // find the current material the jth cell has
            if (i == current_cell_mat)  // only sum up the weights of cells of the current material being processed
            {
            // Weight calculations
            cellObjects[j].calVolume();  // get volume
            weight += (materialObjects[i].GetDensity() * cellObjects[j].getVolume());  // multiply volume by density and total up the weights of all the cells
            }
        }
    }
    return(weight);  // return total weight of the model
}

// Function to get the centre of gravity of the model
vectorClass model::getCentre()
{
    uint16_t num_cell = countObjectsFromClass('c');
    if (num_cell <= 0) // error check
    {
      cout << "getCentre() function failed: number of cells cannot not determined" << endl;
      exit(1);
    }
    float density = 0;

    // vector objects to use for calculations (to avoid rvalue errors)
    vectorClass centre;
    vectorClass weightedCentre;
    vectorClass gravityCentre;

    // Loop through all the cells
    for (int i = 0 ; i < num_cell ; i++)
    {
        cellObjects[i].calGravityCentre();  // Calculate gravity

        density = materialObjects[cellObjects[i].getMat()].GetDensity();  // Retrieve the density of the material that the given cell is made of
        gravityCentre = cellObjects[i].getGravityCentre();                // Calculate the centre of gravity of the cell
        weightedCentre = gravityCentre*cellObjects[i].getWeight(density); // Multiply the centre of gravity of the cell with the weight of the cell
        centre = centre + weightedCentre;                                 // Sum it up
    }

    centre = centre/num_cell;  // divide centre by number of cells
    centre = centre/getWeight(); //  then divide it by the weight of the entire model
    return(centre);  // return the centre of gravity of the entire model
}

// Function to get the dimensions of the model
// Assume that x = length, y = width, z = height of the model
void model::getDimensions(float &x, float &y, float &z)
{
    uint16_t num_vctr = countObjectsFromClass('v');
    if (num_vctr <= 0)  // error check
    {
      cout << "getDimensions() function failed: number of vectors cannot not determined" << endl;
      exit(1);
    }

    // Initialize min values for length, width, height
    float minX = vectorObjects[0].getX();
    float minY = vectorObjects[0].getY();
    float minZ = vectorObjects[0].getZ();

    // Initialize max values for L, W, H
    float maxX = minX;
    float maxY = minY;
    float maxZ = minZ;

    for (int i = 1 ; i < num_vctr ; i++)  // loop through all the vectors
    {
        // Finding the minimum value for x, y, z
        if(minX > vectorObjects[i].getX())
            minX = vectorObjects[i].getX();
        if(minY > vectorObjects[i].getY())
            minY = vectorObjects[i].getY();
        if(minZ > vectorObjects[i].getZ())
            minZ = vectorObjects[i].getZ();

        // Finding the maximum value for x, y, z
        if(maxX < vectorObjects[i].getX())
            maxX = vectorObjects[i].getX();
        if(maxY < vectorObjects[i].getY())
            maxY = vectorObjects[i].getY();
        if(maxZ < vectorObjects[i].getZ())
            maxZ = vectorObjects[i].getZ();
    }

  // L, W, H calculations by finding the difference between the max val and min val of each of the three dimensions
  // Values are passed as references so it does not need to be returned
  x = maxX - minX;
  y = maxY - minY;
  z = maxZ - minZ;

  return;
}

// Function to import a model from a mod file
void model::readModel(ifstream &modelFile)
{
    // Temporary Variables to store the model information extracted from the file //
    // Material variables
    int mat_id = 0;
    float mat_density = 0;
    string mat_colour;
    string mat_name;

    // Vector variables
    int vctr_id = 0;
    float vctr_x = 0.;
    float vctr_y = 0.;
    float vctr_z = 0.;

    // Cell variables
    int cell_id = 0;
    char cell_type = 0;  // p, t, h
    int cell_mat = 0;   // material the cell is made of
    int cell_vertices[8] = {0, 0, 0, 0, 0, 0, 0, 0};   // max number of vertices is 8 (hexahedron). 5 for pyramid, 4 for tetrahedron

    string line;  // string variable to store each line from reading the file
    // ----------------------------------------------------------------------------------- //

    if (modelFile.is_open())  // check if the file is opened
    {
        createObjectsFromFile(modelFile);  // create the vector, cell and material class objects of the appropiate size (given by the mod file)
        while ( getline (modelFile,line) ) // while loop that runs through each line of the file
        {
            if(line[0] != '#' && line.length() != 0)  // Ignore blank lines and lines that start with the '#'
            {
                if (line[0] == 'm')  // if the line has a material identifier
                {
                    stringstream str_line(line); // convert the line into a stringstream
                    str_line.ignore(1);  // ignore the "m"
                    str_line >> mat_id >> mat_density >> mat_colour >> mat_name; // stream the contents of the line to the appropiate variables

                    /*cout << "Mat ID: " << mat_id << endl;
                    cout << "Density: " << mat_density << endl;
                    cout << "Colour: " << mat_colour << endl;
                    cout << "Material: " << mat_name << endl;*/

                    exportDataToObj(mat_id, mat_density, mat_colour, mat_name);  // import the data into the object
                }

                if (line[0] == 'v')
                {
                    stringstream str_line(line);
                    str_line.ignore(1);  // ignore "v"
                    str_line >> vctr_id >> vctr_x >> vctr_y >> vctr_z;

                    /*cout << "Vector ID: " << vctr_id << endl;
                    cout << "Vector x: " << vctr_x << endl;
                    cout << "Vector y: " << vctr_y << endl;
                    cout << "Vector z: " << vctr_z << endl; */

                    exportDataToObj(vctr_id, vctr_x, vctr_y, vctr_z);
                }


                if (line[0] == 'c')
                {
                    stringstream str_line(line);
                    str_line.ignore(1);  // ignore "c"
                    str_line >> cell_id >> cell_type >> cell_mat
                             >> cell_vertices[0] >> cell_vertices[1]
                             >> cell_vertices[2] >> cell_vertices[3]
                             >> cell_vertices[4] >> cell_vertices[5]
                             >> cell_vertices[6] >> cell_vertices[7];  // maximum amount of vertex IDs is 8, so attempt to stream 8 vertices into the array variable

                    /*cout << "Cell ID: " << cell_id << endl;
                    cout << "Cell Type: " << cell_type << endl;
                    cout << "Cell Mat: " << cell_mat << endl;
                    cout << "Cell Vertices: ";
                    for (int i = 0 ; i < 8 ; i++)
                    {
                        cout << cell_vertices[i] << " ";
                    }
                    cout << '\n'; */

                    exportDataToObj(cell_id, cell_type, cell_mat, cell_vertices);

                    // reset the cell_vertices array to be used for the next line
                    for (int i = 0 ; i < 8 ; i++)
                        cell_vertices[i] = 0;
                }
            }
        }
        modelFile.close();  //  close the file once it has been fully read
        cout << "Model file loaded successfully" << endl;
    }
    else    // if file isn't opened
        cout << "File cannot be opened" << endl;
}

// Function to export model into a mod/txt file
void model::saveModel(ofstream &modelFile)
{
    // Count the amount of objects for each class //
    uint16_t num_mat = countObjectsFromClass('m');
    uint16_t num_vctr = countObjectsFromClass('v');
    uint16_t num_cell = countObjectsFromClass('c');

    // Export the material content line by line (guided by the for loop)
    for (int i = 0 ; i < num_mat ; i++)
    {
        // stream material data on a line in the file
        modelFile << "m "
                  << materialObjects[i].GetID() << " "
                  << materialObjects[i].GetDensity() << " "
                  << materialObjects[i].GetColour() << " "
                  << materialObjects[i].GetName() << '\n';
    }
    modelFile << '\n'; // skip line to indicate that all materials had been completed

    // Export the vector content
    for (int i = 0 ; i < num_vctr ; i++)
    {
        // stream vector data on a line in the file
        modelFile << "v "
                  << vectorObjects[i].getID() << " "
                  << vectorObjects[i].getX() << " "
                  << vectorObjects[i].getY() << " "
                  << vectorObjects[i].getZ() << '\n';
    }
    modelFile << '\n';

    // Export the cell content
    for (int i = 0 ; i < num_cell ; i++)
    {
        // Export the cell data on the line up to the 4th vertex ID
        modelFile << "c "
                  << cellObjects[i].getId() << " "
                  << cellObjects[i].getShape() << " "
                  << cellObjects[i].getMat() << " ";

        for (int j = 0 ; j < 8 ; j++)  // loop through all the vertices of the cell
        {
            if (j == 4 && cellObjects[i].getShape() == 't')   // if the shape is a tetrahedron, then stop after the 4th vertex had been exported
                break;
            if (j == 5 && cellObjects[i].getShape() == 'p')   // if the shape is a pyramid, then stop at 5th vertex
                break;
            modelFile << cellObjects[i].getVector()[j].getID() << " ";
        }

        modelFile << "\n";  // skip a line after each cell exported

    }
    modelFile.close();  // close the file after all the data has been exported
    cout << "Model has been exported and saved as a file" << endl;
}
