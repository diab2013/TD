// Ex_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
	while (k > n) {
		cout << "La valeur de k ne peut etre plus grande que n!" << endl;
		cout << "Entrer une valeur de k (inferieur a n): ";
		cin >> k;
	}
	if (k != n) {
		while (k < n) {
			resultat = resultat * ((k + 1.0) / (n - k));
			k++;
		}
	}
	cout << "Le resultat est " << resultat;
}