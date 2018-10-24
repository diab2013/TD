// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <fstream>

using namespace std;

const int tailleX(255), tailleY(255);






double borneDansIntervalle(double ValeurABorner, double BorneInferieure, double BorneSuperieure, static double intervalle[1][2])
{

	if (estDansIntervalle(ValeurABorner, BorneInferieure, BorneSuperieure) == 1)
	{
		intervalle[1][1] = BorneInferieure;

		return (intervalle[1][2]);
	}
	else
	{
		if (ValeurABorner < BorneInferieure)
		{
			return (BorneInferieure);
		}
		if (ValeurABorner > BorneSuperieure)
		{
			return (BorneSuperieure);
		}
	}

}


bool estDansIntervalle(double ValeurABorner, double BorneInferieure, double BorneSuperieure)
{
	bool status = false;
	if (ValeurABorner >= BorneInferieure && ValeurABorner <= BorneSuperieure)
	{
		status = true;
	}

	return{ status };
}
void dessinePoint(double PointX, double PointY, int intensite, uint8_t image[tailleX][tailleY])
{
	struct Point
	{
		double PointX;
		double PointY;
	};

	for (int i = 0; i <= tailleX; i++)
	{
		for (int j = 0; j <= tailleY; j++)
		{
			image[i][j] =


		}


	}

}
double aleatoireZeroUn()
{
	double min = 0.0, max = 1.0, random;

	random = rand() / (float)RAND_MAX;
	return { random
	};
}
int aleatoireSelonDistribution(double probabilitesCumulatives[])
{
	return{};
}
void  transformePoint(double PointX, double PointY, double transformation[2][1], double& PointXT, double& PointYT)
{
	PointXT = transformation[0][0] * PointX + transformation[0][1] * PointY + transformation[2][0];
	PointYT = transformation[1][0] * PointX + transformation[1][1] * PointY + transformation[2][1];

}
void calculerImage(string nomFichierEntree, string nomFichierSortie)
{
	ifstream source(nomFichierEntree + ".txt");

	int nbrPtsAleatoire;
	source >> cin.get(nbrPtsAleatoire);


}
void tests()
{
	double ValeurABorner, BorneInferieure, BorneSuperieure;
	borneDansIntervalle(ValeurABorner, BorneInferieure, BorneSuperieure);

	for (int i = -1; i <= 4; ++i)
	{
		ValeurABorner = i;
		BorneInferieure = -1;
		BorneSuperieure = 3;
		cout << borneDansIntervalle << setw(1);
	}
	for (int i = -1; i <= 4; ++i)
	{
		ValeurABorner = i;
		BorneInferieure = -1;
		BorneSuperieure = 3;
		cout << estDansIntervalle << setw(1);
	}

	uint8_t image[tailleX][tailleY] = { 255 };


}




int main()
{
	tests();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
