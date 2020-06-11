// Material.h
// Computing Project

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include <iostream>

/** @file
 * This file contains the declarations for the Material that this class has the members of
 * Color, ID, Name, and Density.
 */

using namespace std;

class Material
{
public:
	// Constructors
	/** @brief Blank constructor that assigns ID to 0; Density to 0; Colour to "N/A"; and Name to "N/A".
	 */
	Material();

	/** @brief Full constructor
	*  @param ID is the identification number for the material
	*  @param Density is the density of the Material
	*  @param Colour is the colour of the material
	*  @param Name is the name of the material
	*/
	Material(int ID, float Density, const std::string& Colour, const std::string& Name); //Constructor receiving all members for Material

	//Destructors
	/** @brief Blank destructor (empty)
	 */
	~Material();


	//Set Functions
	/** Sets the identification number of the material
	 */
	void SetID(int ID);

	/** Sets the density of the material
	 */
	void SetDensity(float Density);

	/** Sets the colour of the material
	 */
	void SetColour(const std::string& Colour);

	/** Sets the name of the material
	 */
	void SetName(const std::string& Name);

	/** Sets all member variables of the material
	 */
	void SetMaterial(int ID, float Density, const std::string& Colour, const std::string& Name);

	//Get Functions
	/** Returns the identification number of the material
	 */
	int GetID();

	/** Returns the density of the material
	 */
	float GetDensity();

	/** Returns colour of the materials
	 */
	std::string GetColour();

	/** Returns the name of the material
	 */
	std::string GetName();

	//Friend Functions
	/** Displays the values of all member variables of the material
	 */
	friend std::ostream& operator<< (std::ostream&, const Material& Material);

private:
	int ID; /**< Material ID */
	float Density; /**< Material Density */
	std::string Colour; /**< Material Colour in hex string */
	std::string Name; /**< Name of the Material */
};

#endif // MATERIAL_H_INCLUDED
