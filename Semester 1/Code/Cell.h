/*
This header file enables the user to set a cell
and calculate its volume and gravity centre
*/

#ifndef CELL_H
#define CELL_H
#include "vectorClass.h"
#include <vector>
#include <math.h>


class Cell
{
    public:
        Cell();
        void setShape(char);
        void setVector(vectorClass*);//here the address of vector object should be passed
        void calVolume();//use calVolume to calculate the volume of the cell
        void calGravityCentre();//use calGravityCentre to calculate the gravity centre of the cell
        void setCell(int, char, int, vectorClass*);//here pass the ID, shape, material and vectors of the cell
        float getVolume();//return the volume of the cell
        float getWeight(float);//calculate and return the weight of the cell; pass the density here
        int getVectorNum();//return the number of vectors
        vectorClass getGravityCentre();//return a vector class, which is the gravity centre
        int getId();//return id
        int getMat();//return material
        char getShape();//return shape, 't' = tetrahedron, 'p' = pyramid, 'h' = hexahedron
        vectorClass* getVector();//return a vectorClass object
        virtual ~Cell();

    protected:


    private:
        int id, mat;
        char shape;
        int vectorNum;
        float volume;
        float density;
        vectorClass *v;//vector of the points of the cell
        vectorClass x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13;//these are variables to store temporary calculation results to avoid the rvalue error
        vectorClass gravityCentre;
};



#endif // CELL_H
