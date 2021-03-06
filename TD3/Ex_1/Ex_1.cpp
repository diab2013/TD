/*
* Programme qui calcule le binôme de Newton selon une formule founie et avec les deux
* entrées entrés par l'utilisateur
* \file Ex_1.cpp
* \author Diab et Abdelrahman
* \date 16 octobre 2018
* Crée le 3 octobre 2018
*/
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	double n, k;
	double resultat = 1.0;
	cout << "Entrer une valeur de n: ";
	cin >> n;
	cout << "E ntrer une valeur de k (inferieur a n): ";
	cin >> k;

	//vérification des entrées de l'utilisateur
	while (k > n) {
		cout << "La valeur de k ne peut etre plus grande que n!" << endl;
		cout << "Entrer une valeur de k (inferieur a n): ";
		cin >> k;
	}

	//Tant que la variable 'k' n'est pas égale a 'n', on applique l'operation
	if (k != n) {
		while (k < n) {
			resultat = resultat * ((k + 1.0) / (n - k));
			k++;
		}
	}
	cout << "Le resultat est " << resultat;
}