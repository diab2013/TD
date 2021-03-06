/**
* Programme qui lit un fichier et détermine le meilleur joueur
* en comparant leurs scores
* \file   Ex_6.cpp
* \author Diab et Abdelrahman
* \date   23 septembre 2018
* Créé le 12 septembre 2018
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	string city, name1, name2;
	int points1, points2, points3;
	ifstream resFile("res.txt");
	ofstream winFile("vainqueur.txt");

	if (resFile.fail()) {
		cout << "Probleme de fichier!";
		return 1;
	}
	
	getline(resFile, city);
	winFile << city << endl;

	getline(resFile, name1);
	resFile >> points1 >> points2 >> points3 >> ws;
	double result1 = (points1 + points2 + points3) / 3;
	winFile << name1 << " " << round(result1) << endl;

	getline(resFile, name2);
	resFile >> points1 >> points2 >> points3 >> ws;
	double result2 = (points1 + points2 + points3) / 3;
	winFile << name2 << " " << round(result2) << endl;

	bool isBetter = result1 < result2;
	winFile << name1 << " est meilleur que " << name2 << "? " << boolalpha << isBetter << endl;
}