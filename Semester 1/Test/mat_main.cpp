#include <iostream>
#include "Material.h"

using namespace std;

int main()
{
	cout << "Testing ID, Density, Colour, and Name Constructor" << endl;
	Material test(5, 8960, "b87373", "Copper");
	cout << test << endl;

	cout << "Testing Set Functions" << endl;
	test.SetID(4);
	test.SetDensity(7654);
	test.SetColour("FFD700");
	test.SetName("GOLD");
	cout << test << endl;

	int ID = 0;
	float Density = 0;
	string Colour = "Unknow";
	string Name = "Unknow";

	cout << "Get Functions Pull From Material with Members:" << endl;
	cout << test << endl;

	ID = test.GetID();
	Density = test.GetDensity();
	Colour = test.GetColour();
	Name = test.GetName();
	cout << "After Get Functions Variable are : " << endl;
	cout << "ID = " << ID << " Density = " << Density << " Colour = " << Colour << " Name = " << Name << endl;

	return 0;
}