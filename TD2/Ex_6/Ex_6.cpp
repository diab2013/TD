/**
* Programme qui détermine le centre de trois points
* \file   Ex_6.cpp
* \author Diab et Abdelrahman
* \date   23 septembre 2018
* Créé le 12 septembre 2018
*/

#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream file("res.txt");
	ofstream newFile("vainqueur.txt");
	if (file.fail()) {
		cout << "Probleme de fichier!";
		return 1;
	}

	file.getline
}