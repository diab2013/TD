/*
* Programme qui remplace toutes les occurences d'un caractere choisie d'un mot par un
* autre caractere. 
* \file Ex_3.cpp
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
	//Mot et caractère choisis par l'utilisateur
	string chaine; 
	char carARemplace, carRemplace;
	cout << "Entrer une chaine de caracteres: ";
	cin >> chaine;
	cout << "Entrer un caractere a remplacer: ";
	cin >> carARemplace;
	cout << "Entrer le caractere par lequel on remplace: ";
	cin >> carRemplace;

	//On passe un caractere à la fois et il est remplacé si bien 
	//le caractere choisi
	for (int i = 0; i < chaine.length(); i++) {
		if (chaine[i] == carARemplace) {
			chaine[i] = carRemplace;
		}
	}
	cout << "Le mot est maintenant " << chaine << endl;
}