#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp"      // Structures de données pour la collection de films en mémoire.

#include "debogageMemoire.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "unicode.hpp"         // Nos fonctions pour l'utilisation d'Unicode sur wcin/wcout.

#include <iostream>
#include <fstream>
#include <string>
#include <cwchar>
#include <limits>
#include <algorithm>
using namespace std;

#pragma endregion//}

//TODO: Mettre les bons types pour le fichier binaire.
typedef unsigned char UInt8;   //DONE both verified online through sizes explanation
typedef unsigned short UInt16;   ///DONE

#pragma region "Fonctions de base pour lire le fichier binaire"//{

UInt8 lireUint8(istream& fichier)  {
	UInt8 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)  {
	UInt16 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}

wstring lireWstring(istream& fichier){
	wstring texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], sizeof(texte[0]) * texte.length());
	return texte;
}

#pragma endregion//}

//TODO: Une fonction pour ajouter un Film à une ListeFilms, le film existant déjà; on veut uniquement 
//ajouter le pointeur vers le film existant.  Vous pouvez vous inspirer de votre fonction du TD5.  
//Cette fonction ne doit copier aucun Film ni Acteur, elle doit copier uniquement des pointeurs.
void ajouterFilm(ListeFilms& liste, Film* film){
	if (liste.capacite == 0) {
		liste.capacite++;
	}
	if (liste.capacite == liste.nElements) {
		liste.capacite *= 2;
		Film** temporaire = liste.elements;
		liste.elements = new Film*[liste.capacite];
		for (int i = 0; i < liste.nElements; i++) {
			liste.elements[i] = temporaire[i];
		}
		delete[] temporaire;
	}
	liste.nElements++;
	*liste.elements[liste.nElements] = film;
	
}
	
void ajouterActeur(ListeActeurs& liste, Acteur* acteur){ //// fonction que j ai fait pr faciliter le TD	
	if (liste.capacite == 0) {
		liste.capacite++;
	}
	if (liste.capacite == liste.nElements) {
		liste.capacite *= 2;
		Acteur** temporaire = liste.elements;
		liste.elements = new Acteur*[liste.capacite];
		for (int i = 0; i < liste.nElements; i++) {
			liste.elements[i] = temporaire[i];
		}
		delete[] temporaire;
	}
	liste.elements[liste.nElements++] = acteur;
	liste.nElements++;
}

//TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film; la fonction prenant en paramètre un pointeur vers le film à enlever.  L'ordre des films dans la liste n'a pas à être conservé.  Encore une fois, vous pouvez vous inspirer de votre fonction du TD5.
void retirerFilm(ListeFilms& liste, Film* film){
	for (int i = 0; i < liste.nElements; i++){
		if (film == liste.elements[i]) {
			for (int j = 0; j < liste.nElements; j++) {
				liste.elements[j] = liste.elements[j + 1];
			}
		}
	}
	liste.nElements--;
}

//TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms, qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.
Acteur* trouverActeur(ListeFilms& liste, wstring nomActeur){
	for (int i = 0; i < liste.nElements; i++) {
		for (int j = 0; j < liste.elements[i]->acteurs.nElements; j++) {
			if (liste.elements[i]->acteurs.elements[j]->nom == nomActeur) {
				return liste.elements[i]->acteurs.elements[j];
			}
		}
	}
	return nullptr;
}

//TODO: Compléter les fonctions pour lire le fichier et créer/allouer une ListeFilms.  
//La ListeFilms devra être passée entre les fonctions, pour vérifier l'existence d'un Acteur avant 
//de l'allouer à nouveau (cherché par nom en utilisant la fonction ci-dessus).
Acteur* lireActeur(istream& fichier, ListeFilms& liste){
	Acteur acteur = {};
	acteur.nom = lireWstring(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);
	Acteur* ptrActeurExistant = trouverActeur(liste, acteur.nom);
	if (ptrActeurExistant == nullptr) {
		return  { &acteur };
	}
	else {
	//TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations, selon si l'acteur 
	//existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées; vous ne devriez pas voir le même nom d'acteur affiché 
	//deux fois pour la création.
		return { ptrActeurExistant };
	}
}

Film* lireFilm(istream& fichier, ListeFilms& liste){
	Acteur* ptrActeur;
	Film film = {};
	film.titre = lireWstring(fichier);
	film.realisateur = lireWstring(fichier);
	film.anneeSortie = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	film.acteurs.nElements = lireUint8(fichier); 
	//NOTE: Vous avez le droit d'allouer d'un coup le tableau pour les acteurs, sans faire de réallocation comme pour ListeFilms.  
	//Vous pouvez aussi copier-coller les fonctions d'allocation de ListeFilms ci-dessus dans des nouvelles fonctions et faire un remplacement 
	//de Film par Acteur, pour réutiliser cette réallocation.
	//TODO: Placer l'acteur au bon endroit dans les acteurs du film.
	ajouterFilm(liste, &film);
	for (int i = 0; i < film.acteurs.nElements; i++) {
		ptrActeur = trouverActeur(liste, film.acteurs.elements[i]->nom);
		if (ptrActeur != nullptr) {
			//TODO: Ajouter le film aux films dans lesquels l'acteur joue.
			ajouterFilm(ptrActeur->joueDans, &film);
			ajouterActeur(film.acteurs, ptrActeur);
		}
	}
	return { liste.elements[liste.nElements] }; //TODO: Retourner le pointeur vers le nouveau film.
}

ListeFilms creerListe(const string& nomFichier){
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	int nElements = lireUint16(fichier);
	//TODO: Créer une liste de films vide.
	ListeFilms liste = {};
	liste.capacite = nElements;
	//TODO: Ajouter le film à la liste.
	for (int i = 0; i < nElements; i++) {
		Film* film = lireFilm(fichier, liste);
		ajouterFilm(liste, film);
	}
	return { liste }; //TODO: Retourner la liste de films.
}

//TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film, 
//et les acteurs qui ne jouent plus dans aucun films de la collection).  Noter qu'il faut enleve le film détruit 
//des films dans lesquels jouent les acteurs.  Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.
void detruireFilm(ListeFilms& Liste, Film* film){	
	for (int i = 0; i < film->acteurs.nElements; i++) {
		if (film->acteurs.elements[i]->joueDans.nElements == 1) {
			delete[] film->acteurs.elements[i]->joueDans.elements;
			delete film->acteurs.elements[i];
		} else {
			retirerFilm(film->acteurs.elements[i]->joueDans, film);
		}
	}
	delete[] film->acteurs.elements;
	delete film;

	/*
	bool vide = true;
	bool fini = false;
	for (size_t i = 0; i < Liste.nElements; i++){
		if (Liste.elements[i] == film){
			delete[] Liste.elements[i];
			for (size_t j = 0; j < film->acteurs.nElements; j++) {
				for (size_t k = 0; j < film->acteurs.elements[j]->joueDans.nElements; k++){
					if (film->acteurs.elements[j]->joueDans.elements[k] != nullptr) {
						vide = false;
						break;
					}
					if (vide == true&& fini == true) {
						delete[] film->acteurs.elements[j];
					}
					if (k == film->acteurs.elements[j]->joueDans.nElements){
						fini = true;
					}
				}
			}
			break;
		}
		break;
	}
	*/
}

//TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.
void detruireListeFilms(ListeFilms liste){
	for (int i = 0; i < liste.nElements; i++){
		detruireFilm(liste, liste.elements[i]);
	}
	delete[] liste.elements;
}

void afficherActeur(const Acteur& acteur){
	wcout << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

//TODO: Une fonction pour afficher un film avec tous ces acteurs (en utilisant la fonction afficherActeur ci-dessus).
void afficherFilm(Film& film) {
	for (int i = 0; i < film.acteurs.nElements; i++) {
		afficherActeur(*(film.acteurs.elements[i]));
	}
}

//TODO: Une fonction pour afficher tous les films d'une ListeFilms.
void afficherToutFilm(ListeFilms& liste){
	for (int i = 0; i < liste.nElements; i++){
		afficherFilm(*(liste.elements[i]));
	}
}

//TODO: Une fonction pour afficher tous les films dans lesquels un acteur joue, prenant en paramètre le nom de l'acteur.  Cette fonction devrait presque uniquement faire des appels aux autres fonctions écrites.  Elle doit se comporter correctement si l'acteur n'existe pas.
void afficherFilmActeur(ListeFilms& liste, wstring nomActeur)
{
	afficherToutFilm((trouverActeur(liste, nomActeur)->joueDans));
}

///////////////////////////////////////DOOOOOOOONNNNNNEEEE///////////////////////////
void exempleAffichageUnicode()
{
	// Après avoir initialisé Unicode, vous devez absolument utiliser wcin/wcout au lieu de cin/cout.  L'utilisation de cin/cout vous donnera une erreur de "symbole ambigu".
	// Vous pouvez tout de même utiliser des chaînes de caractères non Unicode et les afficher sur wcout.

	// Exemples de chaînes C non Unicode:
	static const char texteNonUnicode[] = "Un texte pas Unicode permet l'affichage des caractères Latin-1, àâéèêïùç...\n";
	wcout << "Une chaine de 'char' est considérée en Latin-1 (pas Unicode):" << endl
		<< texteNonUnicode << endl;
	
	// Exemples de chaînes C Unicode, noter l'utilisation de wchar_t (un caractère Unicode sur 16 bits) au lieu de char (un caractère sur 8 bits), et l'utilisation du L devant les guillemets:
	// (si vous oubliez le L et que vous utilisez des caractères spéciaux, vous aurez l'avertissement "le caractère ... ne peut pas être représenté dans la page de codes actuelle")
	static const wchar_t texteUnicode[] = L"Russe: Добрый день\nGrec: Γεια σας\nTeintes de gris: ░▒▓█\n";
	wcout << L"Une chaine de 'wchar_t' est Unicode et permet les caractères plus spéciaux ♪♫:" << endl
		<< texteUnicode << endl;
	
	// Exemple de string (pas Unicode) et wstring (Unicode):
	static const string stringNonUnicode = "Une string avec caractères Latin-1.";
	static const wstring stringUnicode = L"Une string Unicode ░▒▓█♪♫.";
	wcout << stringNonUnicode << endl // Nous avons fourni une fonction qui permet d'afficher des 'string' sur wcout.
		<< stringUnicode << endl;
	
	/*
	// On ne demande pas de faire de lecture dans ce programme, mais vous pouvez si vous voulez.
	// Exemple de lecture:
	// On peut lire des valeurs comme on est habitué:
	wcout << "Entrer un entier: ";
	int x;
	wcin >> x;
	wcout << "Vous avez entré " << x << endl;
	// Pour les textes, il faut lire des wstring:
	wcout << "Entrer un mot: ";
	wstring chaineUnicode;
	wcin >> chaineUnicode;
	wcout << "Vous avec entré " << chaineUnicode << endl;

	wcout << "Entrer une phrase: ";
	wcin.ignore(numeric_limits<streamsize>::max(), '\n'); // On ignore jusqu'à la fin de la ligne avant de faire le getline.
	getline(wcin, chaineUnicode);
	wcout << "Vous avec entré " << chaineUnicode << endl;
	
	// Il n'est pas possible de lire des 'string' directement (vous pouvez écrire une fonction pour le faire), mais nous fournissons les fonctions versString et versWstring pour faire la conversion.
	string chaineNonUnicode = versString(chaineUnicode);
	wcout << "Sans caractères Unicode: " << chaineNonUnicode << endl;
	
	wchar_t tableauWchar[40] = {};
	wcsncpy(tableauWchar, chaineUnicode.c_str(), 39); // L'équivalent de strncpy mais pour les chaines C Unicode.
	wcout << "En chaine C: " << tableauWchar << endl;
	*/
}

int main()
{
	initDebogageMemoire(); // Affichera dans la "Sortie" de VisualStudio les fuites de mémoire, si exécuté avec débogage.
	initUnicode(); // Permet d'afficher des caractères Unicode (pas seulement les accents latin).
	int* fuite = new int; //TODO: Enlever cette ligne après avoir vérifié qu'il y a bien un "Detected memory leak" de "4 bytes" affiché dans la "Sortie", qui réfère à cette ligne du programme.

	//exempleAffichageUnicode(); //TODO: Juste un exemple; pas à garder dans la version finale.
	
	static const wstring LIGNE_DE_SEPARATION = L"\n════════════════════════════════════════\n";

	//TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

	//TODO: Lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms liste = creerListe("films.bin");
	
	wcout << LIGNE_DE_SEPARATION << L"Le premier film de la liste est:" << endl;
	//TODO: Afficher le premier film de la liste.  Devrait être Alien.
	afficherFilm(*liste.elements[0]);
	
	wcout << LIGNE_DE_SEPARATION << L"Les films sont:" << endl;
	//TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	afficherToutFilm(liste);
	
	//TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).
	wstring nomActeur;
	nomActeur.resize(UInt16("Benedict Cumberbatch"));
	Acteur* ptrActeur = trouverActeur(liste, nomActeur);
	ptrActeur->anneeNaissance = 1976;

	wcout << LIGNE_DE_SEPARATION << L"Liste des films où Benedict Cumberbatch joue sont:" << endl;
	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	afficherFilmActeur(liste, nomActeur);
	
	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	Film* filmDetruire;
	detruireFilm(liste, filmDetruire);

	wcout << LIGNE_DE_SEPARATION << L"Les films sont maintenant:" << endl;
	//TODO: Afficher la liste des films.
	afficherToutFilm(liste);
	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; 
	//c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, 
	//si finalement vous pensez qu'elle ne sont pas utiles.
	
	//TODO: Détruire tout avant de terminer le programme.  Il ne devrait y avoir aucun message "Detected memory leaks!" dans la fenêtre de Sortie de VisualStudio.
	detruireListeFilms(liste);
	}
