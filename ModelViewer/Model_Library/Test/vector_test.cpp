//test_vectorClass.cpp
#include "vectorClass.h"
#include <iostream>

int main(int argc, char *argv[])
{
    //Create vectors
    vectorClass v1(1,3,3,3);
    vectorClass v2(2,2,3,4);

    //Create vectors to store results
    vectorClass add, sub, mult, div, scalarP, vectorP, x_rotate, y_rotate, z_rotate;

    //Test basic mathematical functions
    add = v1 + v2;
    sub = v1 - v2;
    mult = v1 * 4;
    div = v1 / 2;
    scalarP = scalarP.scalarProduct(v1,v2);
    float scalarP_total = scalarP.getScalarProduct();
    vectorP = vectorP.vectorProduct(v1,v2);

    //Test rotation functions
    x_rotate = x_rotate.rotateX(v1,90);
    y_rotate = y_rotate.rotateY(v1,90);
    z_rotate = z_rotate.rotateZ(v1,90);

    //Create matrix
    matrixClass m1(1,2,3,4,5,6,7,8,9);

    //Create variables to store results
    vectorClass vec_mat_mult;
    matrixClass divMat;

    //Test matrix maths functions
    vec_mat_mult = m1 * v1; //Matrix multiplied by vector
    divMat = m1 / 2;    //Matrix divided by float

    //Check results of calculations
    if(add.getX() != 5 || add.getY() != 6 || add.getZ() != 7) return 1;
    if(sub.getX() != 1 || sub.getY() != 0 || sub.getZ() != -1) return 1;
    if(mult.getX() != 12 || mult.getY() != 12 || mult.getZ() != 12) return 1;
    if(div.getX() != 1.5 || div.getY() != 1.5 || div.getZ() != 1.5) return 1;
    if(scalarP.getX() != 6 || scalarP.getY() != 9 || scalarP.getZ() != 12) return 1;
    if(scalarP_total != 27) return 1;
    if(vectorP.getX() != 3 || vectorP.getY() != -6 || vectorP.getZ() != 3) return 1;
    if(x_rotate.getX() != 3 || x_rotate.getY() != -3 || x_rotate.getZ() != 3) return 1;
    if(y_rotate.getX() != 3 || y_rotate.getY() != 3 || y_rotate.getZ() != -3) return 1;
    if(z_rotate.getX() != -3 || z_rotate.getY() != 3 || z_rotate.getZ() != 3) return 1;

    //Check matrix and vector multiplication
    if(vec_mat_mult.getX() != 18 || vec_mat_mult.getY() != 45 || vec_mat_mult.getZ() != 72) return 1;

    //Check matrix division
    if(divMat.getM11() != 0.5 || divMat.getM12() != 1 || divMat.getM13() != 1.5 ||
       divMat.getM21() != 2 || divMat.getM22() != 2.5 || divMat.getM23() != 3   ||
       divMat.getM31() != 3.5 || divMat.getM32() != 4 || divMat.getM33() != 4.5) return 1;


    else return 0;



    //(3x4 - 3x3)
    //(3x2 - 3x4)
    //(3x3 - 3x2)
}
