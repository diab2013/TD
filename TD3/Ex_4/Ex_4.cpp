/*
* Programme qui lit un fichier dont le nom est donnée pas l'utilisateur. Par la suite,
* il afficher un histogramme des longeurs de mots contenu dans le fichier s'il existe.
* \file Ex_4.cpp
* \author Diab et Abdelrahman
* \date 16 octobre 2018
* Crée le 3 octobre 2018
*/
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	const int NBR_CHAR_MAX = 30;
	int longeurMots[NBR_CHAR_MAX] = {};
	string nomFichier;

	cout << "Entrer le nom du fichier à lire: ";
	cin >> nomFichier;
	ifstream source(nomFichier + ".txt");
	
	//Vérification de l'existence du fichier, si non, le programme se ferme
	if (source.fail()) {
		cout << "Echec de lecture, verifier le fichier!" << endl;
		return 0;
	} else {
		string motLu;
		while (!ws(source).eof()) {
			source >> motLu;
			longeurMots[motLu.size()]++; //À chaque mot d''un certain nombre de caractere, on augmente le counter
		}
		for (int i = 0; i < NBR_CHAR_MAX; i++) {
			cout << "Mot a " << i << " lettre(s): " << longeurMots[i] << endl;
		}
	}
}