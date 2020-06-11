//Material.cpp
//Computing Project

#include <iostream>
#include "Material.h"

/** @file
 * This file contains the code for Material that includes ID, Density, Colour, and Name.
 */

using namespace std;

//Constructors
Material::Material() {}

//Constructors and Destructor
Material::Material(int ID, float Density, const std::string& Colour, const std::string& Name)
{
	this->ID = ID;
	this->Density = Density;
	this->Colour = Colour;
	this->Name = Name;
}

//Destructors
Material::~Material() {}

//Set Functions of ID, Density, Colour, and Name
void Material::SetID(int ID)
{
	this->ID = ID;
}

void Material::SetDensity(float Density)
{
	this->Density = Density;
}

void Material::SetColour(const std::string& Colour)
{
	this->Colour = Colour;
}

void Material::SetName(const std::string& Name)
{
	this->Name = Name;
}

void Material::SetMaterial(int ID, float Density, const std::string& Colour, const std::string& Name)
{
	this->ID = ID;
	this->Density = Density;
	this->Colour = Colour;
	this->Name = Name;
}

//Get Functions
int Material::GetID()
{
	return (ID);
}

float Material::GetDensity()
{
	return (Density);
}

string Material::GetColour()
{
	return (Colour);
}

string Material::GetName()
{
	return (Name);
}

//Friend Functions
std::ostream& operator<< (std::ostream&, const Material& aMaterial)
{
	std::cout << "ID = " << aMaterial.ID;
	std::cout << " Density = " << aMaterial.Density;
	std::cout << " Colour = " << aMaterial.Colour;
	std::cout << " Name = " << aMaterial.Name << std::endl;

	return std::cout;
}
