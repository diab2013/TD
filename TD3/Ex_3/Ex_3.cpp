// Ex_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string chaine;
	char carARemplace, carRemplace;
	cout << "Entrer une chaine de caracteres: ";
	cin >> chaine;
	cout << "Entrer un caractere a remplacer: ";
	cin >> carARemplace;
	cout << "Entrer le caractere par lequel on remplace: ";
	cin >> carRemplace;
	for (int i = 0; i < chaine.length(); i++) {
		if (chaine[i] == carARemplace) {
			chaine[i] = carRemplace;
		}
	}
	cout << "Le mot est maintenant " << chaine << endl;
}