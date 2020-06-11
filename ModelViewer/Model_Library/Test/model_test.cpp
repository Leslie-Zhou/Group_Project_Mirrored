#include "model.h"
using namespace std;

// This file contains the code to test the model class via CTest to ensure it is working as intended.


int main(int argc, char *argv[])
{
    // This test will import three model files via the model class functions.
    // All the relevant information (values) of the properties of each model file is known
    // and can be used to compare with the output from running the model functions.

    // When the outputs from the model functions matches with known data, it passes and returns a 0 (success).
    // However if only one of the outputs doesn't match, then it returns a 1 (fail).
    model model1; // create model
    model model2;
    model model3;

    int num_of_mats = 0; // create variables
    int num_of_vertices = 0;
    int num_of_cells = 0;
    float volume = 0;
    float weight = 0;  // NOTE: weight here refers to mass of the model (i.e. it is expressed in units of mass).
                       // getWeight() function returns the mass only, so to find the true weight, multiply it by the gravitational acceleration
                       // experienced by the model

    float length = 0;
    float width = 0;
    float height = 0;

    // Import the sample model files
    // Found in Model_Library/Example_Mod_Files
    ifstream modelFile1 ("ExampleModel1.mod");  // Input the model file (change the name of the file to open different files)
                                                // Ensure that the file exists within the same directory with the code
                                                // Otherwise provide the directory path instead of only the file name of the model
                                                // Ensure to put path or filename within the " " marks
    ifstream modelFile2 ("ExampleModel2.mod");
    ifstream modelFile3 ("ExampleModel3.mod");

    model1.readModel(modelFile1);  // read the model file
    model2.readModel(modelFile2);
    model3.readModel(modelFile3);

    // MODEL 1 //
    // Set and calculate the test variables
    cout << "\nEXAMPLE MODEL 1" << endl;
    num_of_mats     = model1.countObjectsFromClass('m');  // amount of materials
    num_of_vertices = model1.countObjectsFromClass('v');  // amt of vectors
    num_of_cells    = model1.countObjectsFromClass('c');  // amt of cells

    volume = model1.getVolume();  //  calculate volume of model
    weight = model1.getWeight();  //  calculate weight of model

    model1.getDimensions(length, width, height); // calculate dimensions of the model

    // Test for model file #1
    // If any of the output is incorrect, return a 1 (fail)
    if (num_of_mats != 2) return(1);
    if (num_of_vertices != 12) return(1);
    if (num_of_cells != 2) return(1);
    // Due to the use of floats, where the exact value cannot be compared,
    // check that the output value lies within a small range where the correct value lies in.
    if (weight > 10085.01 || weight < 10084.99) return(1);
    if (volume > 1.41668 || volume < 1.41666) return(1);
    if (length > 6.01 || length < 5.99) return(1);
    if (width > 6.51 || width < 6.49) return(1);
    if (height > 1.01 || height < 0.99) return(1);
/*
    // Print out the results onto the console
    cout << "------------------------------------\n";
    cout << "# Mats: " << num_of_mats << endl;
    cout << "# of vertices: " << num_of_vertices << endl;
    cout << "# of cells: " << num_of_cells << endl;
    cout << "Weight: " << weight << endl;
    cout << "Volume: " << volume << endl;
    cout << "Centre of Gravity: " << "X: " << centre.getX() << " Y: " << centre.getY() << " Z: " << centre.getZ() << endl;
    cout << "Overall Dimensions: " << "Length: " << length << " Width: " <<  width << " Height: " << height << endl;

    // Export the model class to a mod file that will be created on the same folder of the code
    ofstream model1Output ("testModel1.mod");
    model1.saveModel (model1Output);
*/
    // MODEL 2  EXAMPLE //
    cout << "\nEXAMPLE MODEL 2" << endl;
    num_of_mats     = model2.countObjectsFromClass('m');  // amount of materials
    num_of_vertices = model2.countObjectsFromClass('v');  // amt of vectors
    num_of_cells    = model2.countObjectsFromClass('c');  // amt of cells

    volume = model2.getVolume();  //  calculate volume of model
    weight = model2.getWeight();  //  calculate weight of model
    model2.getDimensions(length, width, height); // calculate dimensions of the model

    // Test for model file #2
    // If any of the output is incorrect, return a 1 (fail)
    if (num_of_mats != 2) return(1);
    if (num_of_vertices != 301) return(1);
    if (num_of_cells != 129) return(1);
    // Due to the use of floats, where the exact value cannot be compared,
    // check that the output value lies within a small range where the correct value lies in.
    if (volume > 5.392e-007 || volume < 5.390e-007) return(1);
    if (weight > 0.00228160 || weight < 0.00228158) return(1);
    if (length > 0.02 || length < 0.00) return(1);
    if (width > 0.0047 || width < 0.0045) return(1);
    if (height > 0.0326 || height < 0.0324) return(1);

/*    // Print out the results onto the console
    cout << "------------------------------------\n";
    cout << "# Mats: " << num_of_mats << endl;
    cout << "# of vertices: " << num_of_vertices << endl;
    cout << "# of cells: " << num_of_cells << endl;
    cout << "Weight: " << weight << endl;
    cout << "Volume: " << volume << endl;
    cout << "Centre of Gravity: " << "X: " << centre.getX() << " Y: " << centre.getY() << " Z: " << centre.getZ() << endl;
    cout << "Overall Dimensions: " << "Length: " << length << " Width: " <<  width << " Height: " << height << endl;

    // Export the model class to a mod file that will be created on the same folder of the code
    ofstream model2Output ("testModel2.mod");
    model2.saveModel (model2Output);
*/
    // MODEL 3 EXAMPLE //
    cout << "\nEXAMPLE MODEL 3" << endl;
    num_of_mats     = model3.countObjectsFromClass('m');  // amount of materials
    num_of_vertices = model3.countObjectsFromClass('v');  // amt of vectors
    num_of_cells    = model3.countObjectsFromClass('c');  // amt of cells

    volume = model3.getVolume();  //  calculate volume of model
    weight = model3.getWeight();  //  calculate weight of model
    model3.getDimensions(length, width, height); // calculate dimensions of the model

    // Test for model file #3
    // If any of the output is incorrect, return a 1 (fail)
    if (num_of_mats != 1) return(1);
    if (num_of_vertices != 220) return(1);
    if (num_of_cells != 100) return(1);
    // Due to the use of floats, where the exact value cannot be compared,
    // check that the output value lies within a small range where the correct value lies in.
    if (weight > 1839.19 || weight < 1839.17) return(1);
    if (volume > 0.205726 || volume < 0.205724) return(1);
    if (length > 1.01 || length < 0.99) return(1);
    if (width > 0.81 || width < 0.79) return(1);
    if (height > 0.760847 || height < 0.760845) return(1);

/*
    // Print out the results onto the console
    cout << "------------------------------------\n";
    cout << "# Mats: " << num_of_mats << endl;
    cout << "# of vertices: " << num_of_vertices << endl;
    cout << "# of cells: " << num_of_cells << endl;
    cout << "Weight: " << weight << endl;
    cout << "Volume: " << volume << endl;
    cout << "Centre of Gravity: " << "X: " << centre.getX() << " Y: " << centre.getY() << " Z: " << centre.getZ() << endl;
    cout << "Overall Dimensions: " << "Length: " << length << " Width: " <<  width << " Height: " << height << endl;

    // Export the model class to a mod file that will be created on the same folder of the code
    ofstream model3Output ("testModel3.mod");
    model3.saveModel (model3Output); */

    // If all the tests passes, then return a 0 (success)
    return(0);
}
