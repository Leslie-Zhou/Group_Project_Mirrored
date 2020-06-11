#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <iostream> // cin and cout
#include <fstream>  // file reading (i.e. ifstream)
#include <string>   // string variable
#include <sstream>  // use of stringstreams to read of the file
#include <stdint.h> // allow the use of uint16_t vars
#include <stdlib.h> // allow the use of exit()

// Class includes
#include "vectorClass.h"
#include "Material.h"
#include "Cell.h"

using namespace std;

class model
{
public:
    model(); // Initialize Constructor

    ~model();  // Destructor

    model(const model& toBeCopied);   // Copying a model object to another (new) model object via Copy Constructor (i.e. model model2 = model1;)

    model& operator=(const model& toBeCopied);  // Equaling two model objects together (i.e. model2 = model1;)

    void readModel(ifstream &modelFile);        // Reads a mod file and set vector/cell/mat variables accordingly
    void saveModel(ofstream &modelFile);        // Saves model information into a file

    int countObjectsFromClass(char type);  // Counts the amount of objects of the given class (m, v, c) and outputs it

    // Functions to retrieve properties about the modelFile
    float getVolume();
    float getWeight();
    vectorClass getCentre();  // returns a vector of the centre of gravity of the model
    void getDimensions(float &x, float &y, float &z); // gets the overall dimension of the model (length, width, height). sets values via reference

private:
    vectorClass* vectorObjects;  // A pointer to an array of vector objects
    Material* materialObjects;   // A pointer to an array of material objects
    Cell* cellObjects;           // A pointer to an array of cell objects

    void createObjectsFromFile(ifstream &modelFile); // Counts number of mat/cell/vector objects to make, and creates them

    // Exporting class's data from the file to their respective object variables
    // Polymorphism to allow of the same function name with different input vars
    void exportDataToObj(int id, float density, string colour, string name); // mat
    void exportDataToObj(int id, float x, float y, float z);                 // vector
    void exportDataToObj(int id, char type, int mat, int cell_vertices[8]);  // cell

};
#endif // MODEL_H_INCLUDED
