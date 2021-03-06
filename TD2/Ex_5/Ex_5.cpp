/**
* Programme qui montre le nombre de billets de 100, 20, 10, 5 et 1 dollar(s)
* à retourner après un achat
* \file   Ex_5.cpp
* \author Diab et Abdelrahman
* \date   23 septembre 2018
* Créé le 12 septembre 2018
*/

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string article;
	int prix, argent_a_rendre, entree, nb_billets;
	const int BILLET100 = 100, BILLET20 = 20, BILLET10 = 10, BILLET5 = 5, BILLET1 = 1;

	cout << "Entrer le nom de votre article : ";
	cin >> article;
	cout << "Entrer le prix de votre article : ";
	cin >> prix;
	cout << "Entrer le montant d'argent donnee par le client : ";
	cin >> entree;

	argent_a_rendre = entree - prix;

	nb_billets = argent_a_rendre / BILLET100;
	cout << "Billet(s) de 100$ : " << nb_billets << endl;
	argent_a_rendre = argent_a_rendre - (nb_billets * BILLET100);
	
	nb_billets = argent_a_rendre / BILLET20;
	cout << "Billet(s) de 20$  : " << nb_billets << endl;
	argent_a_rendre = argent_a_rendre - (nb_billets * BILLET20);
	
	nb_billets = argent_a_rendre / BILLET10;
	cout << "Billet(s) de 10$  : " << nb_billets << endl;
	argent_a_rendre = argent_a_rendre - (nb_billets * BILLET10);

	nb_billets = argent_a_rendre / BILLET5;
	cout << "Billet(s) de 5$   : " << nb_billets << endl;
	argent_a_rendre = argent_a_rendre - (nb_billets * BILLET5);

	nb_billets = argent_a_rendre / BILLET1;
	cout << "Billet(s) de 1$   : " << nb_billets << endl;
	argent_a_rendre = argent_a_rendre - (nb_billets * BILLET1);
}