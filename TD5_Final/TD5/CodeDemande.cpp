////////////////////////////////////////////////////////////////////////////////
/// \file    CodeDemande.cpp
/// \author  Diab Khanafer et Abdelrahman Bassiouni
/// \version 2018-11-20
///
/// Contient les fonctions qui nous sont demandées d'écrire et d'utiliser dans main.cpp
////////////////////////////////////////////////////////////////////////////////

#pragma region "Inclusions" //{

#include "CodeFourni.hpp"
#include "CodeDemande.hpp"

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

#pragma endregion //}

#pragma region "Globaux" //{

#pragma region "Fonctions" //{

/*
* ajouterCible: fonction qui ajoute une cible dans une liste de cible s'il y a de la place
*  \param [IN] liste  la liste qui va contenir l'élément cible
*  \param [IN] element	la cible que la methode ajoute dans la liste
*/
void ajouterCible(ListeCibles& liste, const Cible& element) {
	// TODO: S'il reste de la place, ajouter l'élément à la fin. --DONE
	if (liste.nbElements < liste.capacite) {
		liste.elements[liste.nbElements] = element;
		liste.nbElements++;
	}
}

/*
* retirerCible: fonction qui retire une certaine cible selon son ID
*  \param [IN] liste	la liste qui contient toutes les cibles
*  \param [IN] id	le ID qu'il faudra chercher est retirer de la liste
*/
void retirerCible(ListeCibles& liste, uint32_t id) {
	// TODO: Rechercher la cible avec le même ID et le retirer de la liste si	
	//       présent. ATTENTION! On parle bien de Cible::id, pas de l'index
	//       dans le tableau.	--DONE
	for (size_t i = 0; i < liste.nbElements; i++) {
		if (liste.elements[i].id == id) {
			for (size_t j = i; j < liste.nbElements; j++) {
				liste.elements[j] = liste.elements[j + 1];
			}
			liste.nbElements--;
		}
	}
}

/*
* lireCibles: fonction qui lit toutes les cibles présentes dans un fichier
*  \param [IN] fichier	le nom du fichier à acceder
*  \param [IN] cibles	la liste de cibles qui contiendra toutes les cibles qui viennent du fichier
*/
void lireCibles(istream& fichier, ListeCibles& cibles) {
	// TODO: Tant que la fin de fichier n'est pas atteinte :
	// TODO: Lire une 'Cible' à partir du ficher à la position
	//       courante et l'ajouter à la liste.	--DONE
	fichier.seekg(0, ios::cur);
	while (fichier.peek() != EOF) {
		Cible temporaire;
		fichier.read((char*)&temporaire, sizeof(temporaire)); 
		ajouterCible(cibles, temporaire);
	}
}

/*
* ecrireCibles: fonction qui ecrit toutes les cibles d'une liste dans un fichier
*  \param [IN] fichier	le nom du fichier à acceder
*  \param [IN] cibles	la liste de cibles qui contient toutes les cibles à écrire dans le fichier
*/
void ecrireCibles(ostream& fichier, const ListeCibles& cibles) {
	// TODO: Écrire tous les éléments de la liste dans le fichier à partir de la position courante.
	// --DONE
	fichier.seekp(0, ios::cur);
	for (uint32_t i = 0; i < cibles.nbElements; i++) {
		fichier.write((char*)&cibles.elements[i], sizeof(cibles.elements[i]));
	}
}

/*
* ecrireJournalDetection: fonction qui ecrit le journal dans un fichier
*  \param [IN] nomFichier	le nom du fichier dans lequel on écrit
*  \param [IN] journal	le journal qui contient l'information et qui sera écrit dans le fichier<
*  \param [OUT] ok		un booléen qui sort true si l'ouverture du fichier a marcher et false si non.
*/
void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok) {
	// TODO: Ouvrir un fichier en écriture binaire.	--DONE
	fstream destination;
	destination.open(nomFichier, ios::binary | ios::out);

	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'. 
	if (destination.fail()) {
		ok = false;
	}
	// TODO: Écrire les paramètres de mission dans le fichier.
	else {
		ok = true;
		destination.write((char*)&journal.parametres, sizeof(&journal.parametres));

		// TODO: Écrire les cibles dans le fichier.
		ecrireCibles(destination, journal.cibles);
	}
}

/*
* ecrireObservation: fonction qui une nouvelle observation dans un fichier
*  \param [IN] nomFichier	le nom du fichier dans lequel on écrit
*  \param [IN] index	l'index de la cible où il faut modifier l'observation
*  \param [IN] observation	la nouvelle observation qu'il faut écrire
*/
void ecrireObservation(const string& nomFichier, size_t index, const string& observation) {
	// TODO: Ouvrir un fichier en lecture/écriture binaire.
	fstream fichier;
	fichier.open(nomFichier, ios::in | ios::out | ios::binary);
	// TODO: Se positionner (têtes de lecture et d'écriture) au début de la cible 
	//       à l'index donné. On parle ici de l'index dans le fichier, donc 0 est
	//       la première cible dans le fichier, etc.
	

	// TODO: Lire cette cible.
	//       ATTENTION! Vous ne devez lire que cette cible isolée, pas tout le
	//       tableau.
	Cible cibleALire;
	
	fichier.seekg(index * sizeof(cibleALire) + sizeof(ParametresMission), ios::beg);
	fichier.seekp(index * sizeof(cibleALire) + sizeof(ParametresMission), ios::beg);
	
	fichier.read((char*)&cibleALire, sizeof(cibleALire));

	// TODO: Copier l'observation donnée en paramètre dans la cible.
	//       Astuce : strcpy()
	strcpy_s(cibleALire.observation, observation.c_str());

	// TODO: Réécrire la cible (et seulement celle-là) dans le fichier.
	fichier.seekp(index * sizeof(cibleALire) + sizeof(ParametresMission), ios::beg);
	fichier.write((char*)&cibleALire, sizeof(cibleALire));
}

/*
* allouerListe: fonction qui alloue une capacité a une liste et la retourne
*  \param [IN] capacite	la capacite de la liste a allouer
*  \return ListeCibles	variable qui contient un certain nombre de cibles
*/
ListeCibles allouerListe(size_t capacite) {
	// TODO: Créer une 'ListeDonnee' vide (nbElements = 0) avec la capacité donnée.

	ListeCibles ListeDonnee;
	ListeDonnee.nbElements = 0;
	ListeDonnee.capacite = capacite;

	// TODO: Allouer un tableau de 'Cible' de la taille demandée.

	Cible* Tableau; ///initialisation
	Tableau = new Cible[capacite];
	ListeDonnee.elements = Tableau;

	return { ListeDonnee };
}

/*
* desallouerListe: fonction qui desalloue une liste
*  \param [IN] cibles	la liste que l'on desalloue et enleve tout l'information dedans
*/
void desallouerListe(ListeCibles& cibles) {
	// TODO: Désallouer le tableau d'élément.

	delete[] cibles.elements;

	// TODO: Remettre les membres à zéro.
	cibles.elements = 0;
	cibles.nbElements = 0;
	cibles.capacite = 0;
}

/*
* lireJournalDetection: fonction qui lit un journal dans un fichier et stock l'information
*  \param [IN] nomFichier	le nom du fichier dans lequel on écrit
*  \param [IN] ok			un booléen qui sort true si l'ouverture du fichier a marcher et false si non.<
*  \return	JournalDetection	variable qui contient les parametres de mission et la liste de cibles
*/
JournalDetection lireJournalDetection(const string& nomFichier, bool& ok) {
	// TODO: Ouvrir un fichier en lecture binaire.
	ifstream source;
	source.open(nomFichier, ios::binary);

	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	if (source.fail()) {
		ok = false;
	} else {
		ok = true;
		// TODO: Lire les paramètres de mission

		JournalDetection journal;
		source.seekg(0, ios::beg);
		source.read((char*)&journal.parametres, sizeof(ParametresMission));

		// TODO: Compter le nombre de cibles dans le fichier.
		Cible cible;
		int nombreCibles = 0;
		while (source.peek() != EOF) {
			source.read((char*)&cible, sizeof(cible));
			nombreCibles++;
		}

		source.seekg(sizeof(journal.parametres), ios::beg);
		// TODO: Allouer la liste de cibles avec la bonne capacité.
		ListeCibles nouvelleListe = allouerListe(nombreCibles);
		
		// TODO: Lire les cibles.
		source.seekg(sizeof(journal.parametres), ios::beg);
		lireCibles(source, nouvelleListe);
		journal.cibles = nouvelleListe;
		return { journal };
	}
	return { NULL };
}

#pragma endregion //}

#pragma endregion //}

