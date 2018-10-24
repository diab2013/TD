// TD4'.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip>
#include<cmath>
#include <cstdint>

static constexpr unsigned tailleX = 500, tailleY = 500;

using namespace std;

struct Intervalle
{
	int inf, sup;
};
struct Point2D
{
	double x, y;
};

void dessinePoint(Point2D coordonnees, uint8_t intensite, int image[tailleX][tailleY]) 
{

	image[tailleX][tailleY] = { 255 };
}


int borneDansIntervalle(int valeurABorner, Intervalle intervalle)
{
	if (valeurABorner >= intervalle.inf && valeurABorner <= intervalle.sup)
	{
		return { valeurABorner };
	}

	else  if (valeurABorner > intervalle.sup)
	{
		return { intervalle.sup };
	}
	else
		return (intervalle.inf);
}
bool estDansIntervalle(int valeurABorner, Intervalle intervalle)
{
	bool status = false;
	if (valeurABorner >= intervalle.inf && valeurABorner <= intervalle.sup)
	{
		status = true;
	}
	return { status };
}

/////////////////////// ces fonctions ont été testées et marche/////////////////




void tests()
{
	for (int i = -1; i <= 4; i++)
	{
		Intervalle intervalle;
		intervalle.inf = 1;
		intervalle.sup = 3;
		cout << borneDansIntervalle(i, intervalle) << setw(2);
	}
	cout << endl << endl << endl;

	for (int i = -1; i <= 4; i++)
	{
		Intervalle intervalle;
		intervalle.inf = 1;
		intervalle.sup = 3;
		cout << estDansIntervalle(i, intervalle) << setw(2);
	}

}

int main()
{
	tests();




}




