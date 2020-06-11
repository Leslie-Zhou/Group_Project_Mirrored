#include "model.h"
using namespace std;

int main()
{
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

    vectorClass centre;  // initialize vector used to store the centre of gravity of the model

    ifstream modelFile1 ("ExampleModel1.mod");  // Input the model file (change the name of the file to open different files)
                                                // Ensure that the file exists within the same directory with the code
                                                // Otherwise provide the directory path instead of only the file name of the model
                                                // Ensure to put path or filename within the " " marks
    ifstream modelFile2 ("ExampleModel2.mod");
    ifstream modelFile3 ("ExampleModel3.mod");

    model1.readModel(modelFile1);  // read the model file
    model2.readModel(modelFile2);
    model3.readModel(modelFile3);



    // MODEL 1 EXAMPLE //
    // Set and calculate the test variables
    cout << "\nEXAMPLE MODEL 1" << endl;
    num_of_mats     = model1.countObjectsFromClass('m');  // amount of materials
    num_of_vertices = model1.countObjectsFromClass('v');  // amt of vectors
    num_of_cells    = model1.countObjectsFromClass('c');  // amt of cells

    volume = model1.getVolume();  //  calculate volume of model
    weight = model1.getWeight();  //  calculate weight of model
    centre = model1.getCentre();  // calculate centre of gravity of the model
    model1.getDimensions(length, width, height); // calculate dimensions of the model

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

    // MODEL 2  EXAMPLE //
    cout << "\nEXAMPLE MODEL 2" << endl;
    num_of_mats     = model2.countObjectsFromClass('m');  // amount of materials
    num_of_vertices = model2.countObjectsFromClass('v');  // amt of vectors
    num_of_cells    = model2.countObjectsFromClass('c');  // amt of cells

    volume = model2.getVolume();  //  calculate volume of model
    weight = model2.getWeight();  //  calculate weight of model
    centre = model2.getCentre();  // calculate centre of gravity of the model
    model2.getDimensions(length, width, height); // calculate dimensions of the model

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
    ofstream model2Output ("testModel2.mod");
    model2.saveModel (model2Output);

    // MODEL 3 EXAMPLE //
    cout << "\nEXAMPLE MODEL 3" << endl;
    num_of_mats     = model3.countObjectsFromClass('m');  // amount of materials
    num_of_vertices = model3.countObjectsFromClass('v');  // amt of vectors
    num_of_cells    = model3.countObjectsFromClass('c');  // amt of cells

    volume = model3.getVolume();  //  calculate volume of model
    weight = model3.getWeight();  //  calculate weight of model
    centre = model3.getCentre();  // calculate centre of gravity of the model
    model3.getDimensions(length, width, height); // calculate dimensions of the model

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
    model3.saveModel (model3Output);

    return(0);
}
