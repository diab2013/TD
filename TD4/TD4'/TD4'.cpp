// TD4'.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include<cmath>
#include <vector>
#include <array>


using namespace std;
using Pixel = uint8_t;
static constexpr unsigned tailleX = 500, tailleY = 500;
struct Point2d {
	double x, y;
};
struct Intervalle{
	int inf, sup;
};



inline bool ecrireImage(const Pixel image[tailleY][tailleX], const std::string& nomFichier)
{
	ofstream fichier(nomFichier, ios::binary);
	if (fichier.fail())
		return false;
	uint32_t tailleImageEnOctets = tailleX * tailleY;
	uint32_t resolutionImage = 72 * 10000 / 254;  // En pixels par mètre.
	static const char nombreMagique[] = { 'B', 'M' };
	uint32_t entete[3 + 10] = {
		0,0,0,
		40,
		tailleX, tailleY,
		0x080001, 0,
		tailleImageEnOctets,
		resolutionImage, resolutionImage
	};
	uint32_t tableCouleur[256];

	entete[2] = sizeof(nombreMagique) + sizeof(entete) + sizeof(tableCouleur);
	entete[0] = entete[2] + tailleImageEnOctets;

	for (unsigned i = 0; i < 256; i++)
		tableCouleur[i] = i * 0x010101;

	fichier.write(nombreMagique, sizeof(nombreMagique));
	fichier.write((char*)entete, sizeof(entete));
	fichier.write((char*)tableCouleur, sizeof(tableCouleur));
	fichier.write((char*)image, tailleImageEnOctets);
	return !fichier.fail();
}

int borneDansIntervalle(int valeurABorner, Intervalle intervalle) {
	if (valeurABorner > intervalle.sup) {
		return { intervalle.sup };
	}
	else if (valeurABorner < intervalle.inf) {
		return { intervalle.inf };
	}
	else {
		return (valeurABorner);
	}
}////////
///
bool estDansIntervalle(int valeurABorner, Intervalle intervalle) {
	bool status = false;
	if (valeurABorner >= intervalle.inf && valeurABorner <= intervalle.sup) {
		status = true;
	}
	return { status };
}
///

void dessinePoint(Point2d coord, Pixel intensite, Pixel image[tailleX][tailleY])
{
	Intervalle intervalleImage, Intensite;
	intervalleImage.inf = 0;
	intervalleImage.sup = 500;
	Intensite.sup = 255;
	Intensite.inf = 0;
	bool possiblePoint = estDansIntervalle(coord.x, intervalleImage) && estDansIntervalle(coord.y, intervalleImage);
	bool possibleIntensite = estDansIntervalle(image[(uint8_t)coord.y][(uint8_t)coord.x] -= intensite, Intensite);
	if (possiblePoint && possibleIntensite) {
		image[(uint8_t)coord.y][(uint8_t)coord.x] -= intensite;
	}
	else if (possiblePoint && !possibleIntensite)
	{
		if (image[(uint8_t)coord.y][(uint8_t)coord.x] -= intensite < 0)
		{
			image[(uint8_t)coord.y][(uint8_t)coord.x] = 0;
		}
		else
		{
			image[(uint8_t)coord.y][(uint8_t)coord.x] = 255;
		}




	}
}

void tests() {
	for (int i = -1; i <= 4; i++) {
		Intervalle intervalle;
		intervalle.inf = 1;
		intervalle.sup = 3;
		cout << borneDansIntervalle(i, intervalle) << setw(2);
	}
	cout << endl << endl << endl;

	for (int i = -1; i <= 4; i++) {
		Intervalle intervalle;
		intervalle.inf = 1;
		intervalle.sup = 3;
		cout << estDansIntervalle(i, intervalle) << setw(2);
	}

	Pixel image[tailleY][tailleX] = {};
	for (int i = 0; i < tailleX; i++) {
		for (int j = 0; j < tailleY; j++) {
			image[i][j] = 255;
		}
	}

	Point2d coord1, coord2, coord3, coord4, coord5, coord6, coord7, coord8;
	coord1.x = 10; coord1.y = 10;
	coord2.x = 20; coord2.y = 15;
	coord3.x = 30; coord3.y = 20;
	coord4.x = -1; coord4.y = 1;
	coord5.x = 500; coord5.y = 1;
	coord6.x = 1; coord6.y = -1;
	coord7.x = 1; coord7.y = 500;
	coord8.x = 30; coord8.y = 20;

	dessinePoint(coord1, 255, image);
	dessinePoint(coord2, 100, image);
	dessinePoint(coord3, 128, image);
	dessinePoint(coord4, 255, image);
	dessinePoint(coord5, 255, image);
	dessinePoint(coord6, 255, image);
	dessinePoint(coord7, 255, image);
	dessinePoint(coord8, 128, image);

	ecrireImage(image, "imageTest.bmp");





}

int main()
{
	
	tests();
}

