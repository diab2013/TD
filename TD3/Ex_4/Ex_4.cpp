// Ex_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	string fileName;
	cout << "Entrer le nom du fichier: ";
	cin >> fileName;
	ifstream file(fileName+".txt");
	if (file.fail()) {
		cout << "Probleme de fichier, le fichier n'existe pas!";
		return 1;
	}

}