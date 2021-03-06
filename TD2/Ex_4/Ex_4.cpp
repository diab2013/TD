/**
* Programme qui détermine la distance d'un projectile à un certain degrée
* \file   Ex_4.cpp
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
	double distance, temps, vitesse_initiale, angle;
	double const GRAVITY = 9.8, CONVERSION = 0.0174533;

	cout << "Entrer l'angle et la vitesse en m/s du projectile : ";
	cin >> angle >> vitesse_initiale;
	angle = angle * CONVERSION; //conersion de l'angle en radian

	temps = (2 * vitesse_initiale * sin(angle)) / GRAVITY;
	distance = vitesse_initiale * cos(angle) * temps;

	cout << "La distance maximale parcourure est de " << distance << " metres." << endl;
}