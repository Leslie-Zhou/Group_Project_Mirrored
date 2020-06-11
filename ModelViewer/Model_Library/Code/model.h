#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

/** @file
 * This contains the declarations for the model class.
 */

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
    /** Initialize Model Constructor.
     */
    model();
    /** Model Destructor.
     */
    ~model();
    /** Copying a model object to another (new) model object via Copy Constructor.
     * @param toBeCopied model object to be copied.
     */
    model(const model& toBeCopied);   // (i.e. model model2 = model1;)
    /** Equaling two model objects together.
     */
    model& operator=(const model& toBeCopied);  // (i.e. model2 = model1;)
    /** Reads a mod file and set vector/cell/mat variables accordingly.
     * @param modelFile Contains the ifstream path of the model file to be read
     */
    void readModel(ifstream &modelFile);
    /** Saves model information into a file.
     * @param modelFile Contains the ofstream path of where the model file should be saved at
     */
    void saveModel(ofstream &modelFile);
    /** Counts the amount of objects of the given class (m, v, c) and outputs it.
     * @param type M, V, C (Materials, Vertices, Cells)
     */
    int countObjectsFromClass(char type);

    // Functions to retrieve vector information
    /** Gets the X value of the vertex given its ID.
     * @param id ID of the vector
     */
    float getX(int id);
    /** Gets the Y value of the vertex given its ID.
     * @param id ID of the vector
     */
    float getY(int id);
    /** Gets the Z value of the vertex given its ID.
     * @param id ID of the vector
     */
    float getZ(int id);
    /** Gets the Cell's vertices IDs given the cell ID.
     * @param id ID of the cell
     */
    int* getCellVertices(int id);
    /** Gets the Cell's shape given the cell ID.
     * @param id ID of the cell
     */
    char getCellType(int id);
    /** Gets the Cell's colour given the cell ID.
     * @param id ID of the cell
     */
    string getCellColour(int id);

    // Functions to retrieve properties about the modelFile
    /** Gets the model's volume.
     */
    float getVolume();
    /** Gets the model's mass (not accounting for the gravitational acceleration experienced by the model).
     */
    float getWeight();
    /** Gets a vector of the centre of gravity of the model.
     */
    vectorClass getCentre();
    /** Gets the overall dimension of the model (length, width, height).
     * @param x length
     * @param y width
     * @param z height
     */
    void getDimensions(float &x, float &y, float &z); //  L, W, H values inputted via reference
private:
    vectorClass* vectorObjects;  /**< A pointer to an array of vector objects */
    Material* materialObjects;   /**< A pointer to an array of material objects */
    Cell* cellObjects;           /**< A pointer to an array of cell objects */

    /** Function to initialize all the m, v, c objects from the inputted model file
     * @param modelFile Model file ifstream path to be read
     */
    void createObjectsFromFile(ifstream &modelFile);

    // Polymorphism to allow of the same function name with different input vars
    // Exporting class's data from the file to their respective object variables
    /** Function to export data from the model file to the materialObjects array
     * @param id Material ID
     * @param density Material Density
     * @param colour Material Colour in hex
     * @param name Material Name/type
     */
    void exportDataToObj(int id, float density, string colour, string name);
    /** Function to export data from the model file to the vectorObjects array
     * @param id Vector ID
     * @param x Vector X coordinate
     * @param y Vector Y coordinate
     * @param z Vector Z coordinate
     */
    void exportDataToObj(int id, float x, float y, float z);
    /** Function to export data from the model file to the cellObjects array
     * @param id Cell ID
     * @param type Cell Type (t: tetrahedron, p: pyramid, h: hexahedron)
     * @param mat Cell's Material ID
     * @param cell_vertices[8] Cell's vertices
     */
    void exportDataToObj(int id, char type, int mat, int cell_vertices[8]);
};
#endif // MODEL_H_INCLUDED
