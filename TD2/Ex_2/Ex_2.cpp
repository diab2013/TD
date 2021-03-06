/**
* Programme qui donne 2 points x pour un point y
* \file   Ex_2.cpp
* \author Diab et Abdelrahman
* \date   23 septembre 2018
* Créé le 12 septembre 2018
*/

#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std; 

int main()
{
	int a = 0, c = 0, y = 0;
	double b = 0;
	cout << "Entrer a, b et c : ";
	cin >> a >> b >> c;
	cout << "Entrer y : ";
	cin >> y; 

	c = c - y; //enlever y à c
	double discriminant = pow(b, 2) - 4 * a * c;
	bool estMauvaise = discriminant < 0;

	float x1 = (-b + sqrt(discriminant)) / (2 * a);
	float x2 = (-b - sqrt(discriminant)) / (2 * a);

	cout << "Les 2 valeurs de x pour ce y sont : " << x1 << " et " << x2
		<< endl << boolalpha << !estMauvaise;
}