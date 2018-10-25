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


////////////////////////////// Liste des fonctions//////////////////////////

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
}
bool estDansIntervalle(int valeurABorner, Intervalle intervalle) {
	bool status = false;
	if (valeurABorner >= intervalle.inf && valeurABorner <= intervalle.sup) {
		status = true;
	}
	return { status };
}
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
double aleatoireZeroUn() {
	double  random;
	random = (rand() / (double)RAND_MAX);
	return { random };
}
int aleatoireSelonDistribution(double probabilitesCumulatives[]) {
	double random;
	random = aleatoireZeroUn();
	if (probabilitesCumulatives[0] > random && random > 0) {
		return { 0 };
	}
	for (int i = 1; i < sizeof(probabilitesCumulatives); i++) {
		if (probabilitesCumulatives[i] > random && probabilitesCumulatives[i - 1] <= random) {
			return { i };
		}
	}
	return{};
}
Point2d transformePoint(double PointX, double PointY, double transformation[3][3]) {
	Point2d point;
	point.x = transformation[0][0] * PointX + transformation[0][1] * PointY + transformation[2][0];
	point.y = transformation[1][0] * PointX + transformation[1][1] * PointY + transformation[2][1];
	return { point };
}



void tests() {

	for (int i = -1; i <= 4; i++) {
		Intervalle intervalle;
		intervalle.inf = 1;
		intervalle.sup = 3;
		cout << borneDansIntervalle(i, intervalle) << setw(2);
	}
	cout << endl << endl << endl;

	/////////// cette boucle est repetitive et peut etre remplacé par une fonction 
	for (int i = -1; i <= 4; i++) {
		Intervalle intervalle;
		intervalle.inf = 1;
		intervalle.sup = 3;
		cout << estDansIntervalle(i, intervalle) << setw(2);
	} 
	cout << endl;
	////Initialisation du tableau

	Pixel image[tailleY][tailleX] = {};
	for (int i = 0; i < tailleX; i++) {
		for (int j = 0; j < tailleY; j++) {
			image[i][j] = 255;
		}
	}

	//Test de la méthode dessinePoint et ecrireImage avec des points prédéfinis
	Point2d coord1, coord2, coord3, coord4, coord5, coord6, coord7, coord8;
	coord1.x = 10; coord1.y = 10; dessinePoint(coord1, 255, image);
	coord2.x = 20; coord2.y = 15; dessinePoint(coord2, 100, image);
	coord3.x = 30; coord3.y = 20; dessinePoint(coord3, 128, image);
	coord4.x = -1; coord4.y = 1; dessinePoint(coord4, 255, image);
	coord5.x = 500; coord5.y = 1; dessinePoint(coord5, 256, image);
	coord6.x = 1; coord6.y = -1; dessinePoint(coord6, 255, image);
	coord7.x = 1; coord7.y = 500; dessinePoint(coord7, 255, image);
	coord8.x = 30; coord8.y = 20; dessinePoint(coord8, 128, image);
	ecrireImage(image, "imageTest.bmp");

	//Test de la méthode aleatoireSelonDistribution qui utilise la méthode aleatoireZeroUn
	int counter1 = 0;
	double probabilité[3] = { 0.1, 0.35, 1.0 };
	for (int x = 0; x < 1000; x++) {
		if (aleatoireSelonDistribution(probabilité) == 1) {
			counter1++;
		}
		//cout << "prob " << i << " : " <<aleatoireSelonDistribution(probabilité) << endl;
	}
	cout << "counter1 = " << counter1 << endl;

	//Test de la méthode transformePoint
	double transformation[3][3] = { {0.5, -0.5}, {0.25, 0.75}, {2.0, 3.0} };
	Point2d point = transformePoint(0.2, 0.7, transformation);
	cout << "(" << point.x << " , " << point.y << ")" << endl;
}

void CalculerImage()
{

	/////ouverture et lecture du fichier d'infos
	ifstream source("Golden dragon.txt");

	struct Information{
	int nbrPts, nbrT, nbrTAvant, intensite;
	double transformationAff[3][3], transformationIFS1[3][3], transformationIFS2[3][3];
	int probabiliteCumulative1, probabiliteCumulative2;
	};

	Information infos;
	
	source >> (infos.nbrPts)>> infos.nbrT>> infos.nbrTAvant>> infos.intensite ;
	source >> infos.transformationAff[0][0] >> infos.transformationAff[0][1] >> infos.transformationAff[1][0] >> infos.transformationAff[1][1] >> infos.transformationAff[2][0] >> infos.transformationAff[2][1];
	source >> infos.transformationIFS1[0][0] >> infos.transformationIFS1[0][1] >> infos.transformationIFS1[1][0] >> infos.transformationIFS1[1][1] >> infos.transformationIFS1[2][0] >> infos.transformationIFS1[2][1];
	source >> infos.probabiliteCumulative1;
	source >> infos.transformationIFS2[0][0] >> infos.transformationIFS2[0][1] >> infos.transformationIFS2[1][0] >> infos.transformationIFS2[1][1] >> infos.transformationIFS2[2][0] >> infos.transformationIFS2[2][1];
	source >> infos.probabiliteCumulative2;

	//////initialisation image
	Pixel image[tailleY][tailleX] = {};
	for (int i = 0; i < tailleX; i++) {
		for (int j = 0; j < tailleY; j++) {
			image[i][j] = 255;
		}
	}
	Point2d point;
	{
		double x, y;
	}
	for (int i = 0; i < infos.nbrPts; i++)
	{
		point.x = aleatoireZeroUn();
		point.y = aleatoireZeroUn();
		for (int j = 0; j < infos.nbrT; j++)
		{
			aleatoireSelonDistribution();
		}

	}
	

}

int main()
{
	
	tests();
}

