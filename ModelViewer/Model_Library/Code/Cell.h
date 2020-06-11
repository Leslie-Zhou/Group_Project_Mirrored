#ifndef CELL_H
#define CELL_H

/** @file
 * This contains the declarations for the cell class
 * that enables the user to calculate the volume, weight
 * and gravity centre of the model.
 */



#include "vectorClass.h" // include operators that calculate vectors
#include <vector> // use vector to store data
#include <math.h>


class Cell
{
    public:
        /** Construstor.
        */
        Cell();
        /** Set up the shape of the model. 't' = tetrahedron, 'p' = pyramid, 'h' = hexahedron
        */
        void setShape(char);
        /** Set the vector of the model.
        * address of vector object is passed.
        */
        void setVector(vectorClass*);
        /** Function to calculate the volume of the model.
        */
        void calVolume();
        /** Function to calculate the gravity centre of the model.
        */
        void calGravityCentre();
        /** Function to set the ID, shape, material and vectors of the cell.
        */
        void setCell(int, char, int, vectorClass*, int*); 
        /** Function to get the volume of the cell.
        */
        float getVolume();
        /** Function to calculate and get the weight of the cell. A float that represents density is input.
        */
        float getWeight(float);
        /** Get the number of vectors
        */
        int getVectorNum();
        /** Function to get the gravity centre of the cell.
        */
        vectorClass getGravityCentre();
        /** Function to get ID
        */
        int getId();
        /** Function to get material
        */
        int getMat();
        /** Function to get shape. 't' = tetrahedron, 'p' = pyramid, 'h' = hexahedron.
        */
        char getShape();
        /** Function to get the vector.
        */
        vectorClass* getVector();
        /** Function to get the number of vertices of the cell.
        */
        int* getCellVertices();
        /** Destructor
        */
        virtual ~Cell();

    protected:


    private:
        int id, mat; /**< ID and material ID of the cell */
        char shape; /**< Shape of the cell */
        int vectorNum; /**< Number of vectors */
        float volume; /**< Volume of the cell */
        float density; /**< Density of the model */
        vectorClass *v; /**< Vector of vertex of the cell */
        int *cellVertices; /**< A pointer to the vector of the cell */
        vectorClass x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13; /**< Variables to store temporary calculation results to avoid the rvalue error */
        vectorClass gravityCentre; /**< Gravity centre of the cell */
};



#endif // CELL_H
