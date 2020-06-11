#include "Cell.h"

Cell::Cell()
{
    //ctor
}

Cell::~Cell()
{
    //dtor
}

//set everything of the cell
void Cell::setCell(int ID, char Shape, int Mat, vectorClass *vectors)
{
    id = ID;
    shape = Shape;

    if(shape == 't')
        vectorNum = 4;
    if(shape == 'p')
        vectorNum = 5;
    if(shape == 'h')
        vectorNum = 8;

    mat = Mat;
    v = new vectorClass[vectorNum];
    v = vectors;
}

void Cell::setShape(char Shape)
{
    shape = Shape;
    //also set the number of vectors here
    if(shape == 't')
        vectorNum = 4;
    if(shape == 'p')
        vectorNum = 5;
    if(shape == 'h')
        vectorNum = 8;
}

//set the vectors of the cell
void Cell::setVector(vectorClass *vectors)
{
    v = new vectorClass[vectorNum];
    v = vectors;
}

void Cell::calVolume()
{
    //volume calculation for tetrahedron
    //volume = 1/6*|(v[1]-v[0]),(v[2]-v[0]),(v[3]-v[0])|
    if(vectorNum == 4)
    {
        x1 = v[1]-v[0];
        x2 = v[2]-v[0];
        x3 = v[3]-v[0];
        x4 = x4.vectorProduct(x2, x3);//x4 = (v[2]-v[0]) cross (v[3]-v[0])
        x5 = x5.scalarProduct(x1, x4);//x5 = (v[1]-v[0]) dot x4
        volume = fabs(x5.getScalarProduct())/6;
    }

    //volume calculation for pyramid
    //volume = 1/6*(|(v[1]-v[0]),(v[2]-v[0]),(v[4]-v[0])| +
    //              |(v[3]-v[0]),(v[2]-v[0]),(v[4]-v[0])|)
    if(vectorNum == 5)
    {
        x1 = v[1]-v[0];
        x2 = v[2]-v[0];
        x3 = v[3]-v[0];
        x4 = v[4]-v[0];
        x5 = x5.vectorProduct(x2, x4);//x5 = (v[2]-v[0]) cross (v[4]-v[0])
        x6 = x6.scalarProduct(x1, x5);//x6 = (v[1]-v[0]) dot x5
        x7 = x7.scalarProduct(x3, x5);//x7 = (v[3]-v[0]) dot x5
        volume = fabs(x6.getScalarProduct())/6+fabs(x7.getScalarProduct())/6;
    }

    //volume calculation for hexahedron
    //volume = 1/6*(|(v[6]-v[0]),(v[1]-v[0]),(v[2]-v[5])| +
    //         |(v[6]-v[0]),(v[4]-v[0]),(v[5]-v[7])| +
    //         |(v[6]-v[0]),(v[3]-v[0]),(v[7]-v[2])|)
    if(vectorNum == 8)
    {
        x1 = v[1]-v[0];
        x2 = v[3]-v[0];
        x3 = v[2]-v[5];
        x4 = v[4]-v[0];
        x5 = v[5]-v[7];
        x6 = v[7]-v[2];
        x7 = v[6]-v[0];
        x8 = x8.vectorProduct(x1, x3);//x8 = (v[1]-v[0]) cross (v[2]-v[0])
        x9 = x9.vectorProduct(x4, x5);//x9 = (v[4]-v[0]) cross (v[5]-v[0])
        x10 = x10.vectorProduct(x2, x6);//x10 = (v[3]-v[0]) cross (v[7]-v[0])
        x11 = x11.scalarProduct(x7, x8);//x11 = (v[6]-v[0]) dot x8
        x12 = x12.scalarProduct(x7, x9);//x12 = (v[6]-v[0]) dot x9
        x13 = x13.scalarProduct(x7, x10);//x13 = (v[6]-v[0]) dot x10

        volume = fabs(x11.getScalarProduct())+fabs(x12.getScalarProduct())+fabs(x13.getScalarProduct());
        volume = volume/6;
    }

}

//calculate the gravity centre
//gravity centre = (v[0]+v[1]+v[2]+...+v[n])/n
void Cell::calGravityCentre()
{
    gravityCentre = v[0];
    for(int i=1;i<vectorNum;i++)
    {
        gravityCentre = gravityCentre + v[i];
    }

    gravityCentre = gravityCentre/vectorNum;

}

float Cell::getVolume()
{
    return volume;
}

int Cell::getVectorNum()
{
    return vectorNum;
}

vectorClass Cell::getGravityCentre()
{
    return gravityCentre;
}

int Cell::getId()
{
    return id;
}

int Cell::getMat()
{
    return mat;
}

char Cell::getShape()
{
    return shape;
}

vectorClass* Cell::getVector()
{
    return v;
}

//calculate and return the weight of the cell
float Cell::getWeight(float Density)
{
    density = Density;
    return density* volume;
}
