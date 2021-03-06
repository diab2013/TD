/* Programmae qui permet de lire un fichier et de déssiner une image fractale
*  par IFS selon les informations inscrites dans le fichier et ensuite de dessiner le résultat
*  de l'image dans un fichier sorti.
* \file TD4Finale.cpp
* \author Diab et Abdelrahman
* \date 30 octobre 2018
* Crée le 17 octobre 2018
*/
#include "pch.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
using namespace std;

//Liste des constantes
using Pixel = uint8_t;
static constexpr unsigned tailleX = 500, tailleY = 500;
//Liste de Structures
struct Point2d {
	double x, y;
};
struct Intervalle {
	int sup, inf;
};

// Fonction fournie, elle permet d'écrire le résultat des transformations fait à la matrice
// dans le fichier envoyé comme paramètre 
// IN : image[tailleY][tailleX] contient les points de type Pixel de l'image
//		nomFichier est le nom du fichier où l'image sera écrite
// OUT : retourne false si l'écriture du fichier ne marche pas
//		 et true lorsque la méthode fonctionne
inline bool ecrireImage(const Pixel image[tailleY][tailleX], const std::string& nomFichier) {
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

// Une fonction qui permet de savoir si la valeur donné en paramètre et dans l'intervalle aussi donné
// donné comme paramètre.
// IN : valeurBorne est la valeur que l'on vérifie si elle se situe dans l'intervalle
//      intervalle est l'intervalle dans lequel on vérifie s'il contient la valeur
// OUT: retourne la borne inférieur si la valeur est inférieure à celle ci
//		retourne la borne inférieur si la valeur est supérieure à celle ci
//		retourne la valeur si elle se situe dans l'intervalle
int borneDansIntervalle(int valeurBorner, Intervalle intervalle) {
	if (valeurBorner < intervalle.inf) {
		return{ intervalle.inf };
	} else if (valeurBorner > intervalle.sup) {
		return{ intervalle.sup };
	} else {
		return { valeurBorner };
	}
}

// Une fonction qui permet de savoir si la valeur se situe dans l'intervalle passé en paramètre
// IN : valeurBorne est la valeur que l'on vérifie si elle se situe dans l'intervalle
//      intervalle est l'intervalle dans lequel on vérifie s'il contient la valeur
// OUT: retourne false si la valeur n'est pas située dans l'intervalle
//		retourne true si la valeur est située dans l'intervalle
bool estDansIntervalle(double valeurBorner, Intervalle intervalle) {
	bool isIn = false;
	if (intervalle.inf <= valeurBorner && valeurBorner <= intervalle.sup) {
		isIn = true;
	}
	return { isIn };
}

// Une fonction qui modifie l'intensité d'un certain point dans le tableau de l'image
// IN : point est la structure Point2d que le modifie
//		intensité est la valeur qu'on soustrait de l'intensité original de 255
//		image est le tableau contenant tout les points de l'image
// OUT: aucun
void dessinePoint(Point2d point, int intensite, Pixel image[tailleX][tailleY]) {
	Intervalle intervalleImage, intervalleIntensite;
	intervalleImage.inf = 0;
	intervalleImage.sup = 500;
	intervalleIntensite.sup = 255;
	intervalleIntensite.inf = 0;
	bool estPointPossible = estDansIntervalle(point.x, intervalleImage) && estDansIntervalle(point.y, intervalleImage);
	bool estIntensitePossible = estDansIntervalle(image[(int)point.y][(int)point.x] -= intensite, intervalleIntensite);
	if (estPointPossible && estIntensitePossible) {
		image[(int)point.y][(int)point.x] -= intensite;
	} else if (estPointPossible && !estIntensitePossible){
		if (image[(int)point.x][(int)point.y] -= intensite < 0){
			image[(int)point.x][(int)point.y] = 0;
		}
		else{
			image[(int)point.x][(int)point.y] = 255;
		}
	}
}

// Une fonction qui génére un nombre aléatoire entre [0,1[
// IN : aucun
// OUT: retourne le nombre aléatoire généré
double aleatoireZeroUn() {
	double r = rand() / (double)RAND_MAX;
	return { r };
}

// Une fonction qui utilise un nombre généré alératoirement pour décider l'indice de transformation
// IN : probabilitesCumulatives est un tableau de probabilités que la méthode parcours venant des fichiers txt
//		contenants les valeurs
// OUT: retourne l'indice selon le nombre aléatoire généré
int aleatoireSelonDistribution(double probabilitesCumulatives[]) {
	double random;
	random = aleatoireZeroUn();
	if (probabilitesCumulatives[0] > random) {
		return { 0 };
	}
	for (int i = 1; i < 5; i++) {
		if (probabilitesCumulatives[i] > random && probabilitesCumulatives[i - 1] <= random) {
			return { i };
		}
	}
	return{  };
}

// Une fonction qui modifie, en utilisant la transformation donnée, les coordonnées x et y  d'un point et le renvois
// IN : pointX est la coordonnée en x du point
//		pointY est la coordonnée en y du point
//		transformation est le tableau contenant les valeurs pour faire la transformation
// OUT: retourne une structure Point2d après avoir fait la transformation
Point2d transformePoint(double pointX, double pointY, double transformation[3][2]) {
	Point2d point;
	point.x = transformation[0][0] * pointX + transformation[0][1] * pointY + transformation[2][0];
	point.y = transformation[1][0] * pointX + transformation[1][1] * pointY + transformation[2][1];
	return { point };
}

// Fonction qui lit une fichier, en extrait les données, et traverse l'algorithme finale pour faire l'image fractale
// IN : nomFichierEntree est le nom du fichier dont la méthode extrait les données
//		nomFichierSortie est le nom du fichier où le resultat sera affiché
// OUT: aucun
void calculerImage(string nomFichierEntree, string nomFichierSortie) {
	ifstream source(nomFichierEntree);
	struct Transformation {
		double transfo[3][2];
	};
	struct Informations {
		int nbrPoints, nbrTransformations, nbrTransfAvant, intensite;
		double transformationAff[3][2], probabiliteCumulative[5];
		Transformation transformation[4];
	};

	Informations infos;
	source >> infos.nbrPoints >> infos.nbrTransformations >> infos.nbrTransfAvant >> infos.intensite;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			source >> infos.transformationAff[i][j];
		}
	}

	int nbrLigne = 0;
	while (!ws(source).eof()) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				source >> infos.transformation[nbrLigne].transfo[i][j];
			}
		}
		source >> infos.probabiliteCumulative[nbrLigne];
		infos.probabiliteCumulative[nbrLigne] = infos.probabiliteCumulative[nbrLigne] / 100;
		nbrLigne++;
	}
	
	Pixel image[tailleX][tailleY] = { };
	Point2d point;
	for (int i = 0; i < tailleX; i++) {
		for (int j = 0; j < tailleY; j++) {
			image[i][j] = 255;
		}
	}

	//Début de l'algo finale
	for (int i = 0; i < infos.nbrPoints; i++) {
		point.x = aleatoireZeroUn();
		point.y = aleatoireZeroUn();
		for (int j = 0; j < infos.nbrTransformations; j++) {
			int indiceTransfo = aleatoireSelonDistribution(infos.probabiliteCumulative);
			point = transformePoint(point.x, point.y, infos.transformation[indiceTransfo].transfo);
			if (j > infos.nbrTransfAvant) {
				Point2d pointTemp = point;
				pointTemp = transformePoint(pointTemp.x, pointTemp.y, infos.transformationAff);
				dessinePoint(pointTemp, infos.intensite, image);
			}
		}
	}
	ecrireImage(image, nomFichierSortie);
}

// Fonction qui nous permets de tester nos autres fonctions
// IN : aucun
// OUT: aucun
void tests() {
	/////Test de borneDansIntervalle
	for (int i = -1; i <= 4; i++) {
		Intervalle intervalle;
		intervalle.inf = 1, intervalle.sup = 3;
		cout << borneDansIntervalle(i, intervalle) << setw(2);
	}
	cout << "\n" << endl;

	/////Test de estDansIntervalle
	for (int i = -1; i <= 4; i++) {
		Intervalle intervalle;
		intervalle.inf = 1, intervalle.sup = 3;
		cout << estDansIntervalle(i, intervalle) << setw(2);
	}
	cout << "\n" << endl;

	/////Test de dessinePoint
	Pixel Image[tailleX][tailleY] = {};
	for (int i = 0; i < tailleX; i++) {
		for (int j = 0; j < tailleX; j++) {
			Image[i][j] = 255;
		}
	};

	Point2d point1, point2, point3, point4, point5, point6, point7, point8;
	point1.x = 10, point2.x = 20, point3.x = 30, point4.x = -1, point5.x = 500, point6.x = 1, point7.x = 1, point8.x = 30;
	point1.y = 10, point2.y = 15, point3.y = 20, point4.y = 1, point5.y = 1, point6.y = -1, point7.y = 500, point8.y = 20;
	dessinePoint(point1, 255, Image);
	dessinePoint(point2, 100, Image);
	dessinePoint(point3, 128, Image);
	dessinePoint(point4, 255, Image);
	dessinePoint(point5, 255, Image);
	dessinePoint(point6, 255, Image);
	dessinePoint(point7, 255, Image);
	dessinePoint(point8, 128, Image);
	ecrireImage(Image, "imageTestFinal.bmp");

	/////Test de Aleatoire Selon Distribution
	int counter1 = 0;
	for (int i = 0; i < 1000; i++) {
		double probabilite[3] = { 0.1, 0.35, 1.0 };
		if (aleatoireSelonDistribution(probabilite) == 1) {
			counter1++;
		}
	}
	cout << "counter1 = " << counter1 << endl;

	/////Test Transformation
	double transformation[3][2] = { {0.5, -0.5}, {0.25, 0.75}, {2.0, 3.0} };
	Point2d point = transformePoint(0.2, 0.7, transformation);
	cout << "(" << point.x << " , " << point.y << ")" << endl;
};

int main() {
	
	tests();
	calculerImage("Heighway dragon.txt", "Heighway dragon.bmp"); //MARCHE
	calculerImage("Barnsley fern.txt", "Barnsley fern.bmp");	//MARCHE
	calculerImage("Golden dragon agrandi.txt", "Golden dragon agrandi.bmp");	//ERREUR
	calculerImage("Goldendragon.txt", "Goldendragon.bmp");	//MARCHE
	calculerImage("Sierpensky triangle.txt", "Sierpensky triangle.bmp");	//MARCHE
}