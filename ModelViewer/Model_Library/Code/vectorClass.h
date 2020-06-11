#ifndef VECTORCLASS_H
#define VECTORCLASS_H

using namespace std;

#ifndef MATRIXCLASS_H
#define MATRIXCLASS_H

#define M_PI 3.1415926536

/** @file
 * This file contains all the declarations for the matrix and vector classes.
 */

class matrixClass {
friend class vectorClass;
private:
    // Create variables - layout of matrix (m11 m12 m13)
    //                                     (m21 m22 m23)
    //                                     (m31 m32 m33)
    float m11; /**< Stores the first number in matrix */
    float m12; /**< Stores the second number in matrix */
    float m13; /**< Stores the third number in matrix */
    float m21; /**< Stores the fourth number in matrix */
    float m22; /**< Stores the fifth number in matrix */
    float m23; /**< Stores the sixth number in matrix */
    float m31; /**< Stores the seventh number in matrix */
    float m32; /**< Stores the eighth number in matrix */
    float m33; /**< Stores the ninth number in matrix */

public:
   // Constructors
   /**
    * Constructor function to create an empty matrix
    */
   matrixClass();
   /**
    * Constructor function to create a matrix with values
    */
   matrixClass(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);

   // Destructor
   /**
    * Destructor function
    */
   ~matrixClass();

   // Functions
   /**
    * Function to output matrix to user
    */
   void getMatrix();
   /**
    * Function to create an identity matrix
    */
   void identityMatrix();
   /**
    * Function to create a rotation matrix for rotation in the x direction.
    * Takes the angle of rotation as a parameter
    */
   void xRotationMatrix(double angle);
   /**
    * Function to create a rotation matrix for rotation in the y direction.
    * Takes the angle of rotation as a parameter
    */
   void yRotationMatrix(double angle);
   /**
    * Function to create a rotation matrix for rotation in the z direction.
    * Takes the angle of rotation as a parameter
    */
   void zRotationMatrix(double angle);
   /**
    * Function to calculate the determinant of a matrix
    */
   float calcDeterminant(matrixClass m1);

   /**
    * Function to return the 1st item in a matrix
    */
   float getM11();
   /**
    * Function to return the 2nd item in a matrix
    */
   float getM12();
   /**
    * Function to return the 3rd item in a matrix
    */
   float getM13();
   /**
    * Function to return the 4th item in a matrix
    */
   float getM21();
   /**
    * Function to return the 5th item in a matrix
    */
   float getM22();
   /**
    * Function to return the 6th item in a matrix
    */
   float getM23();
   /**
    * Function to return the 7th item in a matrix
    */
   float getM31();
   /**
    * Function to return the 8th item in a matrix
    */
   float getM32();
   /**
    * Function to return the 9th item in a matrix
    */
   float getM33();

   /**
    * Function to invert a matrix
    */
   matrixClass invert(matrixClass m1);
   /**
    * Function to transpose a matrix
    */
   matrixClass transpose(matrixClass m1);
   /**
    * Function to find the adjugate of a matrix
    */
   matrixClass adjugate(matrixClass m1);

   /**
    * Copy constructor for matrix
    */
   matrixClass(matrixClass &m1);
   /**
    * '/' operator overload to allow a matrix to be divided by a float
    */
   friend matrixClass operator /(matrixClass& m1, float val );  // Operator overload
};

#endif // MATRIXCLASS_H



class vectorClass {
private:

    float x; /**< Stores the x value of the vector */
    float y; /**< Stores the y value of the vector */
    float z; /**< Stores the z value of the vector */

    int id; /**< Stores the id of the vector */


public:
    // Constructor
    /**
     * Constructor function to create an empty vector
     */
    vectorClass();
    /**
     * Constructor function to create a vector with values and an ID
     */
    vectorClass(int id, float x, float y, float z);

    // Destructor
    /**
     * Destructor function
     */
    ~vectorClass();

    /**
     * Function to set a vector's values and ID
     */
    void setVector(int id, float x, float y, float z);      // Create a vector with values
    /**
     * Function to get a vector's x, y and z values by providing ID
     */
    void getVector(int id, float *x, float *y, float *z);   // Request vector output by providing ID
    /**
     * Function to get ID of a vector
     */
    float getID();  // Get ID of a vector
    /**
     * Function to get x value of a vector
     */
    float getX();   // Get x value of a vector
    /**
     * Function to get y value of a vector
     */
    float getY();   // Get y value of a vector
    /**
     * Function to get z value of a vector
     */
    float getZ();   // Get z value of a vector
    /**
     * Function to get the total of coordinates from scalar product calculation
     */
    float getScalarProduct();   // Get total of coordinates resulting from scalar product calculation
    /**
     * Function to set the x value of a vector
     */
    void setX(float x); // Set the x value of a vector
    /**
     * Function to set the y value of a vector
     */
    void setY(float y); // Set the y value of a vector
    /**
     * Function to set the z value of a vector
     */
    void setZ(float z); // Set the z value of a vector

    /**
     * Function to calculate scalar product of two vectors
     */
    vectorClass scalarProduct(vectorClass v1, vectorClass v2);  // Function to calculate scalar product of two vectors
    /**
     * Function to calculate vector product of two vectors
     */
    vectorClass vectorProduct(vectorClass v1, vectorClass v2);  // Function to calculate vector product of two vectors

    /**
     * Function to rotate a vector around the x axis by a specified angle
     */
    vectorClass rotateX(vectorClass v1, double angle);
    /**
     * Function to rotate a vector around the y axis by a specified angle
     */
    vectorClass rotateY(vectorClass v1, double angle);
    /**
     * Function to rotate a vector around the z axis by a specified angle
     */
    vectorClass rotateZ(vectorClass v1, double angle);

    /**
     * Copy constructor for vector
     */
    vectorClass(vectorClass &v1);   // Copy constructor
    /**
     * '+' operator overload for addition of two vectors
     */
    friend vectorClass operator +(vectorClass& v1, vectorClass& v2);    // '+' operator overload
    /**
     * '-' operator overload for subtraction of one vector from another
     */
    friend vectorClass operator -(vectorClass& v1, vectorClass& v2);    // '-' operator overload
    /**
     * '*' operator overload for multiplication of a vector by a float
     */
    friend vectorClass operator *(vectorClass& v1, float val);          // '*' operator overload
    /**
     * '/' operator overload for division of a vector by a float
     */
    friend vectorClass operator /(vectorClass& v1, float val);          // '/' operator overload
    /**
     * '*' operator overload for multiplicaton of a matrix by a vector
     */
    friend vectorClass operator *(matrixClass& m1, vectorClass& v1);     // '*' operator overload

};


#endif // VECTORCLASS_H
