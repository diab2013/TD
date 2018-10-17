/*
* Programme qui invite l'utilisateur a entré un nombre de point et calcule le centre 
* de gravité de ces points ainsi que le point le plus proche et le plus loin de ce dernier
* \file Ex_5.1.cpp
* \author Diab et Abdelrahman
* \date 16 octobre 2018
* Crée le 3 octobre 2018
*/
#include "pch.h"
#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <vector>
#include <array>
using namespace std;

int main()
{
	double moyenneX = 0, moyenneY = 0, dproche = 0, dloin = 0, dcalculee = 0, 
			ptsprocheX = 0, ptsloinX = 0, ptsprocheY = 0, ptsloinY = 0;
	int nbrPoints;

	//saisie du nombre de points et initialisation des variables urtilisés pour le traiteemnt
	cout << "Saisir un entier entre 1 et 10 designant le nombre de points : ";
	cin >> nbrPoints;
	while (nbrPoints < 1 || nbrPoints > 10) {
		cout << "L'entier doit être entre 1 et 10 inclusivement." << endl;
		cout << "Saisir un entier entre 1 et 10 designant le nombre de points : ";
		cin >> nbrPoints;
	}

	//remplissage du tableau des points entré par l'utilisateur
	double tableau[10][2];
	for (int ligne = 0; ligne < nbrPoints; ligne++){
		for (int colone = 0; colone < 2; colone++){
			cout << "Veuillez entrer les coordonnees x puis y du point " << ligne + 1 << ": ";
			cin >> tableau[ligne][colone];
		}
	}

	//Calcule de la moyenne des points entrés
	for (int ligne = 0; ligne < nbrPoints; ligne++)
	{
		moyenneX += tableau[ligne][0];
		moyenneY += tableau[ligne][1];
	}

	moyenneX = moyenneX / nbrPoints;
	moyenneY = moyenneY / nbrPoints;

	cout << endl;
	cout << "Les coordonnes du centre de gravite sont : (" << moyenneX << " ; " << moyenneY << ")" << endl;

	//Calcule pour trouver le point le plus proche et celui le plus loin du centre de gravité
	for (int ligne = 0; ligne < nbrPoints; ligne++)
	{
		dcalculee = sqrt(pow(moyenneX - tableau[ligne][0], 2) + pow(moyenneY - tableau[ligne][1], 2));
		if (ligne == 0)
		{
			dproche = dcalculee;
			ptsprocheX = tableau[ligne][0];
			ptsprocheY = tableau[ligne][1];
			dloin = dcalculee;
			ptsloinX = tableau[ligne][0];
			ptsloinY = tableau[ligne][1];
		}
		if (dcalculee < dproche)
		{
			dproche = dcalculee;
			ptsprocheX = tableau[ligne][0];
			ptsprocheY = tableau[ligne][1];
		}
		if (dcalculee > dloin)
		{
			dloin = dcalculee;
			ptsloinX = tableau[ligne][0];
			ptsloinY = tableau[ligne][1];
		}
	}
	cout << "Les coordonnees du point le plus proche du centre de gravite sont (" << ptsprocheX << " , " << ptsprocheY << ")" << endl;
	cout << "Les coordonnees du point le plus loin du centre de gravite sont (" << ptsloinX << " , " << ptsloinY << ")" << endl;
}