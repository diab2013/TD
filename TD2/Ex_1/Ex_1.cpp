/**
* Programme qui détermine le centre de trois points
* \file   Ex_1.cpp
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
	cout << "Entrer les coordonnées en X des trois points : ";
	double pointX1 = 0, pointX2 = 0, pointX3 = 0;
	cin >> pointX1 >> pointX2 >> pointX3;

	cout << "Entrer les coordonnées en Y des trois points : ";
	double pointY1 = 0, pointY2 = 0, pointY3 = 0;
	cin >> pointY1 >> pointY2 >> pointY3;

	double coordX = (pointX1 + pointX2 + pointX3) / 3;
	double coordY = (pointY1 + pointY2 + pointY3) / 3;

	cout << "Les coordonnees du centre de gravite du triangles sont (" << coordX << ";" << coordY << ").";
}