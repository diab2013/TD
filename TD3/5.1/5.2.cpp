// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	
	double dcalculee = 0, ptsprocheX = 0, ptsprocheY = 0, ptsloinX = 0, ptsloinY = 0 , dproche = 0, dloin = 0  ; 
	struct point
	{
		double X;
		double Y;
		char couleur;
	};

	point tableau[6], pts_usager;

	ifstream source("points.txt");
	
	if (source.fail()) {

		cout << "Echec de lecture du fichier" << "\n" <<endl;
	}

	else
	{
		for (int t = 0; t < 6; t++)

		{
			source >> tableau[t].X >> tableau[t].Y >> tableau[t].couleur;

		}


		/////////////////// Partie qui interragit avec l'usager

		cout << "Donnez les coordonnes d'un point (abscicsse, ordonnee, puis couleur V R ou B : " << endl;
		cout << "abscisse : ";
		cin >> pts_usager.X;
		cout << "\n" << "ordonnee : ";
		cin >> pts_usager.Y;
		cout << "couleur R( rouge ) V( vert ) ou B( bleu ) :  ";
		cin >> pts_usager.couleur;

		////////////////// Traitement

		if (pts_usager.couleur == tableau->couleur)
		{


			for (int ligne = 0; ligne < 6; ligne++)
			{
				dcalculee = sqrt(pow(pts_usager.X - tableau[ligne].X, 2) + pow(pts_usager.Y - tableau[ligne].Y, 2));

				if (ligne == 0)
				{
					dproche = dcalculee;
					ptsprocheX = tableau[ligne].X;
					ptsprocheY = tableau[ligne].Y;
					dloin = dcalculee;
					ptsloinX = tableau[ligne].X;
					ptsloinY = tableau[ligne].Y;
				}
				if (dcalculee < dproche)
				{
					dproche = dcalculee;
					ptsprocheX = tableau[ligne].X;
					ptsprocheY = tableau[ligne].Y;
				}

				if (dcalculee > dloin)
				{
					dloin = dcalculee;
					ptsloinX = tableau[ligne].X;
					ptsloinY = tableau[ligne].Y;
				}


			}
		}
		else
		{
			cout << "Il n'existe pas de points de cette couleur dans le fichier . ";
		}




		cout << " coordonnees du point le plus proche : " << ptsprocheX << " , " << ptsprocheY << " . " << endl;
		cout << " coordonnees du point le plus distant : " << ptsloinX << " , " << ptsloinY << " . " << endl;

	}
}



