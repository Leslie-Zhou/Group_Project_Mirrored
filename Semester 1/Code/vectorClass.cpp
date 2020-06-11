#include <iostream>
#include "vectorClass.h"
#include <math.h>

vectorClass::vectorClass(){
}

vectorClass::~vectorClass(){
}

vectorClass::vectorClass(int id, float x, float y, float z)   // Constructor
{
    // Store values in respective indexes
    this->x = x;
    this->y = y;
    this->z = z;
    this->id = id;
}

void vectorClass::setVector(int id, float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->id = id;
}

void vectorClass::getVector(int id, float *x, float *y, float *z) // Function to get values of a vector
{
    *x = this->x;    // Assign stored values of vector to variables
    *y = this->y;
    *z = this->z;

    cout << "v " << id << " "<< *x << ". " << *y << ". " << *z << "."<< endl;   // Output vector in required format
}

float vectorClass::getID()
{
    id = this->id;
    return id;
}

float vectorClass::getX()   // Function to get x value of vector
{
    x = this->x;
    return x;
}

float vectorClass::getY()   // Function to get y value of vector
{
    y = this->y;
    return y;
}

float vectorClass::getZ()   // Function to get z value of vector
{
    z = this->z;
    return z;
}

void vectorClass::setX(float x) // Function to set x value of vector
{
    this->x = x;
}

void vectorClass::setY(float y) // Function to set y value of vector
{
    this->y = y;
}

void vectorClass::setZ(float z) // Function to set z value of vector
{
    this->z = z;
}

vectorClass::vectorClass(vectorClass &v1)   // Copy constructor
{
    this->x = v1.getX();     //Must copy each coordinate from v1
    this->y = v1.getY();
    this->z = v1.getZ();
}

vectorClass operator +(vectorClass &v1, vectorClass &v2)    // '+' operator overload
{
    vectorClass result;     // Create vector to store result
    result.setX(v1.getX() + v2.getX());     // Set x value of result to total of x values
    result.setY(v1.getY() + v2.getY());     // Set y value of result to total of y values
    result.setZ(v1.getZ() + v2.getZ());     // Set z value of result to total of z values
    return result;          // Return result vector
}

vectorClass operator -(vectorClass &v1, vectorClass &v2)    // '-' operator overload
{
    vectorClass result;     // Create vector to store result
    result.setX(v1.getX() - v2.getX());     // Set x value of result to total of x values
    result.setY(v1.getY() - v2.getY());     // Set y value of result to total of y values
    result.setZ(v1.getZ() - v2.getZ());     // Set z value of result to total of z values
    return result;          // Return result vector
}

vectorClass operator *(vectorClass& v1, float val)          // '*' operator overload
{
    vectorClass result;     // Create vector to store result
    result.setX(v1.getX()*val);             // Set x value of result to total of x values
    result.setY(v1.getY()*val);             // Set y value of result to total of y values
    result.setZ(v1.getZ()*val);             // Set z value of result to total of z values
    return result;          // Return result vector
}

vectorClass operator /(vectorClass& v1, float val)          // '/' operator overload
{
    vectorClass result;     // Create vector to store result
    result.setX(v1.getX()/val);     // Set x value of result to x value divided by 'val'
    result.setY(v1.getY()/val);     // Set y value of result to y value divided by 'val'
    result.setZ(v1.getZ()/val);     // Set z value of result to z value divided by 'val'
    return result;          // Return result vector
}

vectorClass vectorClass::scalarProduct(vectorClass v1, vectorClass v2)  // Function to perform scalar product calculation
{
    vectorClass result;     // Create vector to store result
    result.setX(v1.getX()*v2.getX());   // Set x value of result to product of x values
    result.setY(v1.getY()*v2.getY());   // Set y value of result to product of y values
    result.setZ(v1.getZ()*v2.getZ());   // Set z value of result to product of z values
    return result;          // Return result vector
}

float vectorClass::getScalarProduct()   // Function to return scalar product total
{
    float result;   // Create variable to store result
    result = this->x + this->y + this->z;  // Calculate total of all coordinates
    return result;  // Return calculated value
}

vectorClass vectorClass::vectorProduct(vectorClass v1, vectorClass v2)  // Function to perform vector product calculation
{
    vectorClass result;     // Create vector to store result
    // Calculate result coordinates using vector product formula
    result.setX( (v1.getY()*v2.getZ()) - (v1.getZ()*v2.getY()) );
    result.setY( (v1.getZ()*v2.getX()) - (v1.getX()*v2.getZ()) );
    result.setZ( (v1.getX()*v2.getY()) - (v1.getY()*v2.getX()) );
    return result;          // Return result vector
}

// Functions to rotate vectors
vectorClass vectorClass::rotateX(vectorClass v1, double angle)
{
    vectorClass result;
    matrixClass rX;
    rX.xRotationMatrix(angle);
    result = rX*v1;
    return result;
}
vectorClass vectorClass::rotateY(vectorClass v1, double angle)
{
    vectorClass result;
    matrixClass rY;
    rY.yRotationMatrix(angle);
    result = rY*v1;
    return result;
}
vectorClass vectorClass::rotateZ(vectorClass v1, double angle)
{
    vectorClass result;
    matrixClass rZ;
    rZ.zRotationMatrix(angle);
    result = rZ*v1;
    return result;
}

// Operator overload for multiplying matrix by vector
vectorClass operator *(matrixClass& m1, vectorClass& v1)
{
    vectorClass result;
    result.setX((m1.getM11()*v1.getX())+(m1.getM12()*v1.getY())+(m1.getM13()*v1.getZ()));
    result.setY((m1.getM21()*v1.getX())+(m1.getM22()*v1.getY())+(m1.getM23()*v1.getZ()));
    result.setZ((m1.getM31()*v1.getX())+(m1.getM32()*v1.getY())+(m1.getM33()*v1.getZ()));
    return result;
}

//----Matrix functions-----------------------------------------------------------

// Constructor
matrixClass::matrixClass(){
}

matrixClass::matrixClass(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;
}

// Destructor
matrixClass::~matrixClass(){
}

// Function to output matrix
void matrixClass::getMatrix()
{
    cout << m11 << " " << m12 << " " << m13 << endl;
    cout << m21 << " " << m22 << " " << m23 << endl;
    cout << m31 << " " << m32 << " " << m33 << endl;
}

// Get individual matrix values
float matrixClass::getM11()
{
    m11 = this->m11;
    return m11;
}
float matrixClass::getM12()
{
    m12 = this->m12;
    return m12;
}
float matrixClass::getM13()
{
    m13 = this->m13;
    return m13;
}
float matrixClass::getM21()
{
    m21 = this->m21;
    return m21;
}
float matrixClass::getM22()
{
    m22 = this->m22;
    return m22;
}
float matrixClass::getM23()
{
    m23 = this->m23;
    return m23;
}
float matrixClass::getM31()
{
    m31 = this->m31;
    return m31;
}
float matrixClass::getM32()
{
    m32 = this->m32;
    return m32;
}
float matrixClass::getM33()
{
    m33 = this->m33;
    return m33;
}

// Function to create an identity matrix
void matrixClass::identityMatrix()
{
    this->m11 = 1;
    this->m12 = 0;
    this->m13 = 0;
    this->m21 = 0;
    this->m22 = 1;
    this->m23 = 0;
    this->m31 = 0;
    this->m32 = 0;
    this->m33 = 1;
}

// Function to create rotation matrix with angle given
void matrixClass::xRotationMatrix(double angle)
{
    this->m11 = 1;
    this->m12 = 0;
    this->m13 = 0;
    this->m21 = 0;
    this->m22 = float(cos((angle*M_PI)/180));
    this->m23 = float(-sin((angle*M_PI)/180));
    this->m31 = 0;
    this->m32 = float(sin((angle*M_PI)/180));
    this->m33 = float(cos((angle*M_PI)/180));
}

// Function to create rotation matrix with angle given
void matrixClass::yRotationMatrix(double angle)
{
    this->m11 = float(cos((angle*M_PI)/180));
    this->m12 = 0;
    this->m13 = float(sin((angle*M_PI)/180));
    this->m21 = 0;
    this->m22 = 1;
    this->m23 = 0;
    this->m31 = float(-sin((angle*M_PI)/180));
    this->m32 = 0;
    this->m33 = float(cos((angle*M_PI)/180));
}

// Function to create rotation matrix with angle given
void matrixClass::zRotationMatrix(double angle)
{
    this->m11 = float(cos((angle*M_PI)/180));
    this->m12 = float(-sin((angle*M_PI)/180));
    this->m13 = 0;
    this->m21 = float(sin((angle*M_PI)/180));
    this->m22 = float(cos((angle*M_PI)/180));
    this->m23 = 0;
    this->m31 = 0;
    this->m32 = 0;
    this->m33 = 1;
}

// Function to calculate determinant of 3x3 matrix
float matrixClass::calcDeterminant(matrixClass m1)
{
    float a11 = m1.m11*((m1.m22 * m1.m33) - (m1.m32 * m1.m23));
    float a12 = -m1.m12*((m1.m22 * m1.m33) - (m1.m31 * m1.m23));
    float a13 = m1.m13*((m1.m21 * m1.m32) - (m1.m31 * m1.m22));
    float result = a11 + a12 + a13;
    return result;
}

// Function to transpose 3x3 matrix
matrixClass matrixClass::transpose(matrixClass m1)
{
    matrixClass mT;
    mT.m11 = m1.m11;
    mT.m12 = m1.m21;
    mT.m13 = m1.m31;
    mT.m21 = m1.m12;
    mT.m22 = m1.m22;
    mT.m23 = m1.m32;
    mT.m31 = m1.m13;
    mT.m32 = m1.m23;
    mT.m33 = m1.m33;
    return mT;
}

// Function to create adjugate matrix
matrixClass matrixClass::adjugate(matrixClass m1)
{
    matrixClass adjM;
    adjM.m11 = ((m1.m22*m1.m33) - (m1.m32*m1.m23));
    adjM.m12 = -1*((m1.m21*m1.m33) - (m1.m31*m1.m23));
    adjM.m13 = ((m1.m21*m1.m32) - (m1.m31*m1.m22));
    adjM.m21 = -1*((m1.m12*m1.m33) - (m1.m32*m1.m13));
    adjM.m22 = ((m1.m11*m1.m33) - (m1.m31*m1.m13));
    adjM.m23 = -1*((m1.m11*m1.m32) - (m1.m31*m1.m12));
    adjM.m31 = ((m1.m12*m1.m23) - (m1.m22*m1.m13));
    adjM.m32 = -1*((m1.m11*m1.m23) - (m1.m21*m1.m13));
    adjM.m33 = ((m1.m11*m1.m22) - (m1.m21*m1.m12));
    return adjM;
}

// Function to invert 3x3 matrix
matrixClass matrixClass::invert(matrixClass m1)
{
    matrixClass m, mT, adjM, inverseM;
    float determinant = calcDeterminant(m1);
    cout << "Determinant: " << determinant << endl;
    if (determinant == 0) {
        cout << "Matrix has no inverse" << endl;
    }
    else {
        mT = m.transpose(m1);
        adjM = m.adjugate(mT);
        inverseM = adjM / determinant;
        return inverseM;
    }
}

// Copy constructor
matrixClass::matrixClass(matrixClass &m1)
{
    this->m11 = m1.m11;
    this->m12 = m1.m12;
    this->m13 = m1.m13;
    this->m21 = m1.m21;
    this->m22 = m1.m22;
    this->m23 = m1.m23;
    this->m31 = m1.m31;
    this->m32 = m1.m32;
    this->m33 = m1.m33;
}

// Function to divide a matrix by a value
matrixClass operator /(matrixClass& m1, float val )
{
    matrixClass result;
    result.m11 = m1.m11/val;
    result.m12 = m1.m12/val;
    result.m13 = m1.m13/val;
    result.m21 = m1.m21/val;
    result.m22 = m1.m22/val;
    result.m23 = m1.m23/val;
    result.m31 = m1.m31/val;
    result.m32 = m1.m32/val;
    result.m33 = m1.m33/val;
    return result;
}
