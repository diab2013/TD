/*
* Programme qui montre les nombres qui respectent la règle de la somme des cubes entre 100 et 500 inclusivement
* \file Ex_2.cpp
* \author Diab et Abdelrahman
* \date 16 octobre 2018
* Crée le 3 octobre 2018
*/
#include "pch.h"
#include <iostream>
#include <string>
#include <clocale>
using namespace std;

int main()
{
	int numb = 100;
	int total = 0;
	cout << "Il existe des nobres a 3 chiffres tels que la somme des cubes des chiffres qui compesent un nombre est egale au nombre lui-meme." << endl;
	cout << "Les nombres satisfaisant la regle sont les suivants : ";
	
	while (numb <= 500) {
		double chiffre1 = numb/ 100, chiffre2 = (numb%100)/10, chiffre3 = numb%10;  /*trouver les chiffres qui compose le nombre*/
		total = pow(chiffre1, 3.0) + pow(chiffre2, 3.0) + pow(chiffre3, 3.0); /*calcul du total de chaque nombre exposant 3*/
		
		if (total == numb) {
			cout << numb << ", ";
		}
		numb++;
	}
	cout << endl;
}


