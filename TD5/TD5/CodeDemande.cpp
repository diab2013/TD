////////////////////////////////////////////////////////////////////////////////
/// VOTRE ENTÊTE ICI
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

void ajouterCible(ListeCibles& liste, const Cible& element)
{
	if (liste.nbElements < liste.capacite)
	{
		liste.elements[liste.nbElements] = element;
		liste.nbElements += 1;
	}
	// TODO: S'il reste de la place, ajouter l'élément à la fin.
}


void retirerCible(ListeCibles& liste, uint32_t id)
{
	for (size_t i = 0; i <liste.nbElements; i++)
	{
		if ( id == liste.elements[i].id)
		{
			delete &liste.elements[i];
			i = liste.nbElements;/// Pour sortir de ma boucle
		}

	}


	// TODO: Rechercher la cible avec le même ID et le retirer de la liste si
	//       présent. ATTENTION! On parle bien de Cible::id, pas de l'index
	//       dans le tableau.
}


void lireCibles(istream& fichier, ListeCibles& cibles)
// TODO: Tant que la fin de fichier n'est pas atteinte :
		// TODO: Lire une 'Cible' à partir du ficher à la position
		//       courante et l'ajouter à la liste.
{
	while (fichier.peek() != EOF)
	{
		Cible temporaire;
		fichier.read((char*)&temporaire, sizeof(temporaire));
		ajouterCible(cibles, temporaire);


	}
	
}


void ecrireCibles(ostream& fichier, const ListeCibles& cibles)
{

	fichier.seekp(0, ios::cur);
	
	
	fichier.write((char*)&cibles.elements, sizeof(cibles.elements));
	
	
	// TODO: Écrire tous les éléments de la liste dans le fichier à partir de la position courante.
}


void ecrireJournalDetection(const string& nomFichier, const JournalDetection& journal, bool& ok)
{
	// TODO: Ouvrir un fichier en écriture binaire.

	ofstream destination(nomFichier, ios::binary);
	destination.open(nomFichier, ios::binary | ios::in);

	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	
	if (destination.fail)
	{
		ok = false;
	}

	// TODO: Écrire les paramètres de mission dans le fichier.
	else
	{
		destination.write((char*)&journal.parametres, sizeof(&journal.parametres));
	
		// TODO: Écrire les cibles dans le fichier.

		ecrireCibles(destination, journal.cibles);
	
	
	}
	
	

}


void ecrireObservation(const string& nomFichier, size_t index, const string& observation)
{
	// TODO: Ouvrir un fichier en lecture/écriture binaire.
	fstream fichier(nomFichier, ios::in | ios::out | ios::binary);
	// TODO: Se positionner (têtes de lecture et d'écriture) au début de la cible 
	//       à l'index donné. On parle ici de l'index dans le fichier, donc 0 est
	//       la première cible dans le fichier, etc.
	fichier.seekg(index, ios::beg);

	// TODO: Lire cette cible.
	//       ATTENTION! Vous ne devez lire que cette cible isolée, pas tout le
	//       tableau.
	Cible cibleALire;
	fichier.read((char*)&cibleALire, sizeof(cibleALire));



	// TODO: Copier l'observation donnée en paramètre dans la cible.
	//       Astuce : strcpy()

	strcpy(cibleALire.observation, observation[observation.length]);
	
	// TODO: Réécrire la cible (et seulement celle-là) dans le fichier.

	fichier.write((char*)&cibleALire, sizeof(cibleALire));
}


ListeCibles allouerListe(size_t capacite)
{
	// TODO: Créer une 'ListeDonnee' vide (nbElements = 0) avec la capacité donnée.
	
	// TODO: Allouer un tableau de 'Cible' de la taille demandée.
	return {};
}


void desallouerListe(ListeCibles& cibles)
{
	// TODO: Désallouer le tableau d'élément.
	// TODO: Remettre les membres à zéro.
}


JournalDetection lireJournalDetection(const string& nomFichier, bool& ok)
{
	// TODO: Ouvrir un fichier en lecture binaire.
	
	// TODO: Indiquer la réussite ou l'échec de l'ouverture dans 'ok'.
	
	// TODO: Lire les paramètres de mission
	
	// TODO: Compter le nombre de cibles dans le fichier.
	
	// TODO: Allouer la liste de cibles avec la bonne capacité.
	
	// TODO: Lire les cibles.
	return {};
}

#pragma endregion //}

#pragma endregion //}

