#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;

class Material
{
private:


	int ID;
	float Density;
	std::string Colour;
	std::string Name;

public:

//Constructors

	Material();
	Material(int ID, float Density, const std::string& Colour, const std::string& Name); //Constructor receiving all members for Material

//Destructors
	~Material();

	//Set Function

	void SetID(int ID);
	void SetDensity(float Density);
	void SetColour(const std::string& Colour);
	void SetName(const std::string& Name);
	void SetMaterial(int ID, float Density, const std::string& Colour, const std::string& Name);

	//Get Function

	int GetID();
	float GetDensity();
	std::string GetColour();
	std::string GetName();

	friend std::ostream& operator<< (std::ostream&, const Material& Material);
};

#endif // MATERIAL_H_INCLUDED
