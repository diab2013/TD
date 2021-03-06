/*
* Programme qui lit un fichier et compare les coordonnées entrées avec ceux écrit dans le fichier
* pour ensuite s'il existe un point proche et un point loin selon la couleur du point entré
* \file Ex_5.2.cpp
* \author Diab et Abdelrahman
* \date 16 octobre 2018
* Crée le 3 octobre 2018
*/
#include "pch.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	double dcalculee = 0, ptsprocheX = 0, ptsprocheY = 0, ptsloinX = 0, ptsloinY = 0, dproche = 0, dloin = 0;
	struct point {
		double X;
		double Y;
		char couleur;
	};

	point tableau[6], pts_usager;
	ifstream source("points.txt");

	//Le programme arrete si le fichier n'est pas présent
	if (source.fail()) {
		cout << "Echec de lecture du fichier" << endl;
		return 1;
	}
	else {
		for (int t = 0; t < 6; t++) {
			source >> tableau[t].X >> tableau[t].Y >> tableau[t].couleur;
		}
		// Partie qui interragit avec l'usager
		cout << "Donnez les coordonnes d'un point (abscicsse, ordonnee, puis couleur V R ou B : " << endl;
		cout << "Abscisse (x): ";
		cin >> pts_usager.X;
		cout << "Ordonnee (y): ";
		cin >> pts_usager.Y;
		cout << "Couleur R(rouge), V(vert) ou B(bleu):  ";
		cin >> pts_usager.couleur;

		// Traitement des données pour trouver le point le plus proche et le point le plus loin
		if (pts_usager.couleur == tableau->couleur) {
			for (int ligne = 0; ligne < 6; ligne++) {
				dcalculee = sqrt(pow(pts_usager.X - tableau[ligne].X, 2) + pow(pts_usager.Y - tableau[ligne].Y, 2));
				if (ligne == 0) {
					dproche = dcalculee;
					ptsprocheX = tableau[ligne].X;
					ptsprocheY = tableau[ligne].Y;
					dloin = dcalculee;
					ptsloinX = tableau[ligne].X;
					ptsloinY = tableau[ligne].Y;
				}
				if (dcalculee < dproche) {
					dproche = dcalculee;
					ptsprocheX = tableau[ligne].X;
					ptsprocheY = tableau[ligne].Y;
				}
				if (dcalculee > dloin) {
					dloin = dcalculee;
					ptsloinX = tableau[ligne].X;
					ptsloinY = tableau[ligne].Y;
				}
			}
			//Dans le cas où avec la même couleur
		}
		else {
			cout << "Il n'existe pas de points de cette couleur dans le fichier." << endl;
		}
		cout << "Coordonnees du point le plus proche : (" << ptsprocheX << " , " << ptsprocheY << "). " << endl;
		cout << "Coordonnees du point le plus distant : (" << ptsloinX << " , " << ptsloinY << "). " << endl;
	}
}