#ifndef VECTORCLASS_H
#define VECTORCLASS_H

using namespace std;

#ifndef MATRIXCLASS_H
#define MATRIXCLASS_H

#define M_PI 3.1415926536

class matrixClass {
friend class vectorClass;
private:
   float m11, m12, m13; // Create variables (layout of matrix variables can be seen)
   float m21, m22, m23;
   float m31, m32, m33;

public:
   // Constructor
   matrixClass();
   matrixClass(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

   // Destructor
   ~matrixClass();

   // Functions
   void getMatrix();
   void identityMatrix();
   void xRotationMatrix(double angle);
   void yRotationMatrix(double angle);
   void zRotationMatrix(double angle);
   float calcDeterminant(matrixClass m1);

   float getM11();
   float getM12();
   float getM13();
   float getM21();
   float getM22();
   float getM23();
   float getM31();
   float getM32();
   float getM33();

   matrixClass invert(matrixClass m1);
   matrixClass transpose(matrixClass m1);
   matrixClass adjugate(matrixClass m1);

   matrixClass(matrixClass &m1);
   friend matrixClass operator /(matrixClass& m1, float val );  // Operator overload
};

#endif // MATRIXCLASS_H



class vectorClass {
private:
    float x, y, z;      // Create variables
    int id;

public:
    // Constructor
    vectorClass();
    vectorClass(int id, float x, float y, float z);

    // Destructor
    ~vectorClass();

    void setVector(int id, float x, float y, float z);      // Create a vector with values
    void getVector(int id, float *x, float *y, float *z);   // Request vector output by providing ID
    float getID();  // Get ID of a vector
    float getX();   // Get x value of a vector
    float getY();   // Get y value of a vector
    float getZ();   // Get z value of a vector
    float getScalarProduct();   // Get total of coordinates resulting from scalar product calculation
    void setX(float x); // Set the x value of a vector
    void setY(float y); // Set the y value of a vector
    void setZ(float z); // Set the z value of a vector

    vectorClass scalarProduct(vectorClass v1, vectorClass v2);  // Function to calculate scalar product of two vectors
    vectorClass vectorProduct(vectorClass v1, vectorClass v2);  // Function to calculate vector product of two vectors

    vectorClass rotateX(vectorClass v1, double angle);
    vectorClass rotateY(vectorClass v1, double angle);
    vectorClass rotateZ(vectorClass v1, double angle);

    vectorClass(vectorClass &v1);   // Copy constructor
    friend vectorClass operator +(vectorClass& v1, vectorClass& v2);    // '+' operator overload
    friend vectorClass operator -(vectorClass& v1, vectorClass& v2);    // '-' operator overload
    friend vectorClass operator *(vectorClass& v1, float val);          // '*' operator overload
    friend vectorClass operator /(vectorClass& v1, float val);          // '/' operator overload
    friend vectorClass operator *(matrixClass& m1, vectorClass& v1);     // '*' operator overload

};


#endif // VECTORCLASS_H
