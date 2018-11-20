////////////////////////////////////////////////////////////////////////////////
/// VOTRE ENT�TE ICI
////////////////////////////////////////////////////////////////////////////////

#pragma region "Inclusions" //{

#include "CodeFourni.hpp"
#include "CodeDemande.hpp"
#include "pch.h"

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

void ajouterCible(ListeCibles& liste, const Cible& element){
	if (liste.nbElements < liste.capacite){
		liste.elements[liste.nbElements-1] = element;
		liste.nbElements += 1;
	}
	// TODO: S'il reste de la place, ajouter l'�l�ment � la fin.
}


void retirerCible(ListeCibles& liste, uint32_t id){
	for (size_t i = 0; i <liste.nbElements; i++){
		if ( id == liste.elements[i].id){
			delete &liste.elements[i];
			i = liste.nbElements;/// Pour sortir de ma boucle
		}
	}

	// TODO: Rechercher la cible avec le m�me ID et le retirer de la liste si
	//       pr�sent. ATTENTION! On parle bien de Cible::id, pas de l'index
	//       dans le tableau.
}


void lireCibles(istream& fichier, ListeCibles& cibles){
	// TODO: Tant que la fin de fichier n'est pas atteinte :
	// TODO: Lire une 'Cible' � partir du ficher � la position
	//       courante et l'ajouter � la liste.
	while (fichier.peek() != EOF){
		Cible temporaire;
		fichier.read((char*)&temporaire, sizeof(temporaire));
		ajouterCible(cibles, temporaire);

	}
}


void ecrireCibles(ostream& fichier, const ListeCibles& cibles){
	fichier.seekp(0, ios::cur);
	fichier.write((char*)&cibles.elements, sizeof(cibles.elements));
	
	// TODO: �crire tous les �l�ments de la liste dans le fichier � partir de la position courante.
}


void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok){
	// TODO: Ouvrir un fichier en �criture binaire.

	ofstream destination(nomFichier, ios::binary);
	destination.open(nomFichier, ios::binary | ios::in);

	// TODO: Indiquer la r�ussite ou l'�chec de l'ouverture dans 'ok'.
	
	if (destination.fail){
		ok = false;
	}
	// TODO: �crire les param�tres de mission dans le fichier.
	else{
		destination.write((char*)&journal.parametres, sizeof(&journal.parametres));
	
		// TODO: �crire les cibles dans le fichier.
		ecrireCibles(destination, journal.cibles);
	}
}


void ecrireObservation(const string& nomFichier, size_t index, const string& observation){
	// TODO: Ouvrir un fichier en lecture/�criture binaire.
	fstream fichier(nomFichier, ios::in | ios::out | ios::binary);
	// TODO: Se positionner (t�tes de lecture et d'�criture) au d�but de la cible 
	//       � l'index donn�. On parle ici de l'index dans le fichier, donc 0 est
	//       la premi�re cible dans le fichier, etc.
	fichier.seekg(index, ios::beg);

	// TODO: Lire cette cible.
	//       ATTENTION! Vous ne devez lire que cette cible isol�e, pas tout le
	//       tableau.
	Cible cibleALire;
	fichier.read((char*)&cibleALire, sizeof(cibleALire));

	// TODO: Copier l'observation donn�e en param�tre dans la cible.
	//       Astuce : strcpy()

	strcpy(cibleALire.observation, observation[observation.length]);
	
	// TODO: R��crire la cible (et seulement celle-l�) dans le fichier.

	fichier.write((char*)&cibleALire, sizeof(cibleALire));
}


ListeCibles allouerListe(size_t capacite){
	// TODO: Cr�er une 'ListeDonnee' vide (nbElements = 0) avec la capacit� donn�e.
	
	ListeCibles ListeDonnee;
	ListeDonnee.nbElements = 0;
	ListeDonnee.capacite = capacite;

	// TODO: Allouer un tableau de 'Cible' de la taille demand�e.

	Cible* Tableau; ///initialisation
	Tableau = new Cible[capacite];

	return {ListeDonnee};
}


void desallouerListe(ListeCibles& cibles){
	// TODO: D�sallouer le tableau d'�l�ment.

	delete cibles.elements;

	// TODO: Remettre les membres � z�ro.
	cibles.elements = 0;
}


JournalDetection lireJournalDetection(const string& nomFichier, bool& ok){
	// TODO: Ouvrir un fichier en lecture binaire.

	ifstream source;
	source.open(nomFichier, ios::binary);

	// TODO: Indiquer la r�ussite ou l'�chec de l'ouverture dans 'ok'.

	if (source.fail){
		ok = false;
	} else {
		ok = true;
	// TODO: Lire les param�tres de mission

		JournalDetection journal;
		source.read((char*)&journal.parametres, sizeof(journal.parametres));

		// TODO: Compter le nombre de cibles dans le fichier.
		source.seekg(0, ios::end);
		int nombreCibles;
		nombreCibles = (source.tellg - sizeof(ParametresMission) / sizeof (Cible));
		///// maybe its just nombreCibles = (source.tellg - sizeof(journal.parametres)/ sizeof(journal.cibles);

		// TODO: Allouer la liste de cibles avec la bonne capacit�.

		ListeCibles nouvelleListe = allouerListe(nombreCibles);
		// TODO: Lire les cibles.

		lireCibles(source, nouvelleListe);
	}
	return {};
}

#pragma endregion //}

#pragma endregion //}

