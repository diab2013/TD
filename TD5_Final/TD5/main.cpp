////////////////////////////////////////////////////////////////////////////////
/// VOTRE ENTÊTE ICI
////////////////////////////////////////////////////////////////////////////////

#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "CodeDemande.hpp"
#include "CodeFourni.hpp"

using namespace std;

#pragma endregion //}

void tests_partie1() {
	// Dans la partie 1, on déclare une liste de cibles avec un tableau statique, puisque l'allocation dynamique est vue en classe seulement la semaine suivante.
	//	--DONE
	Cible tableauCibles[3] = {};
	ListeCibles cibles = { tableauCibles, 0, size(tableauCibles) };

	//TODO: Ajouter 3 fois une cible (ajouterCible) à la cibles, chacun avec un ID différent (les autres valeurs ne sont pas importantes);
	//TODO: après chaque ajout vérifier que le nombre de cibles est bon (i.e. 1 après le premier ajout, 2 après le deuxième), et que les données de la cible sont dans la liste (vérifiez uniquement l'ID).
	//TODO: Ajouter une autre cible, le nombre d'éléments devrait être encore 3 puisque c'est la capacité de la liste. -- DONE
	
	for (uint32_t i = 1; i <= 4; i++) {
		Cible cible = { i, 0, '0', '0'};
		ajouterCible(cibles, cible);
		cout << " le nombre de cibles est : " << cibles.nbElements << endl;
	}
	for (uint32_t i = 0; i < 3; i++) {
		cout << " id cible :  " << cibles.elements[i].id << endl;
	}
	
	//TODO: Retirer la cible (retirerCible) ayant l'ID que vous avez mis en 2e, vérifier qu'il reste 2 éléments aux indices 0 et 1 dont les ID sont les bons.
	cout << "cible de ID = 2 a ete enleve!" << endl;
	retirerCible(cibles, 2);
	for (uint32_t i = 0; i < cibles.nbElements; i++) {
		cout << " id cible :  " << cibles.elements[i].id << endl;
	}

	//TODO: Écrire les cibles (ecrireCibles) dans le fichier fichierTestCibles. Vérifier que la tête d'écriture est rendue au bon endroit.
	fstream fichierTestCibles("fichierTestCibles.bin", ios::in | ios::out | ios::trunc | ios::binary);
	ecrireCibles(fichierTestCibles, cibles);
	cout << fichierTestCibles.tellp() << endl;

	//TODO: Remettre la tête de lecture au début du fichier puis lire les cibles (lireCibles) dans cibles2. Vérifier que les 2 bonnes cibles y sont.
	fichierTestCibles.seekg(0, ios::beg);
	Cible tableauCibles2[3] = {};
	ListeCibles cibles2 = { tableauCibles2, 0, size(tableauCibles2) };
	lireCibles(fichierTestCibles, cibles2);
	for (uint32_t i = 0; i < cibles2.nbElements; i++) {
		cout << " id cible :  " << cibles2.elements[i].id << endl;
	}

	//TODO: Créer une variable de type JournalDetection avec des valeurs quelconques et une ListeCibles déjà créé ci-dessus.
	string nomDuFichier = "FichierTest.bin";
	JournalDetection journal = { {"Diab", "Notes inutiles", 0}, cibles };
	//TODO: Écrire ce journal (ecrireJournalDetection) dans un nouveau fichier binaire.
	bool ok;
	ecrireJournalDetection(nomDuFichier, journal, ok);
	//TODO: Vérifier que ok est vrai.
	if (ok) {
		cout << "Le journal a ete ecrit!" << endl;
	}
	//NOTE: La relecture du fichier pour vérifier qu'il est bon se fera seulement dans la partie 2.  Vous pouvez pour l'instant vérifier que la taille du fichier est bonne (propriétés du fichier dans Windows; la "taille" en octets devrait être une taille d'entête plus le bon nombre de cibles; attention de ne pas regarder la "taille sur disque" qui peut être différente de la "taille" dans les propriétés du fichier).  Vous pouvez aussi ouvrir le fichier binaire avec un éditeur binaire (par exemple celui de VisualStudio) pour voir si les ID sont bien dans le fichier.

	//TODO: Ajouter une observation (ecrireObservation) au fichier créé ci-dessus à l'indice 1 (deuxième cible).
	ecrireObservation(nomDuFichier,(size_t) 1, "Une observation"); //REVOIR!!!!
	//NOTE: Même chose que ci-dessus: la taille du fichier ne devrait pas avoir changée, et dans l'éditeur binaire vous devriez voir le texte après le deuxième ID.

}

void tests_partie2() {
	cout << endl;
	cout << "------TEST PARTIE 2------" << endl;
	//TODO: Allouer une liste de cibles (allouerListe) de capacité 2; vérifier que la capacité est la bonne et que le nombre d'éléments est zéro.
	ListeCibles liste =  allouerListe((size_t) 2);
	cout << liste.capacite << endl;

	//TODO: Ajouter une cible la liste; ça devrait fonctionner.
	Cible cible = {123, 0, 'Test', 'A'};
	ajouterCible(liste, cible);
	for (uint32_t i = 0; i < liste.nbElements; i++) {
		cout << " id cible :  " << liste.elements[i].id << endl;
	}
	//TODO: Conserver le pointeur vers le tableau de cibles dans une variable.
	Cible** pointeurTemp = &liste.elements;
	//TODO: Désallouer la liste (desallouerListe); vérifier que les valeurs sont à zéro.
	desallouerListe(liste);
	//TODO: Allouer une nouvelle liste de cibles de capacité 2; vérifier que son pointeur est le même que celui conservé ci-dessus.  NOTE: Il n'y a pas de manière dans le standard ISO C++ pour vérifier que la mémoire a bien été désallouée.  Ce test n'est donc pas standard et pourrait échouer même si le programme est correct, mais on a la garantie qu'il peut réussir uniquement si la désallocation est faite.
	ListeCibles liste2 = allouerListe((size_t)2);
	cout << liste2.capacite << endl;
	if (pointeurTemp == &liste2.elements) {
		cout << "les pointeurs sont similaires!" << endl;
	}
	//TODO: Désallouer cette deuxième liste.
	desallouerListe(liste2);
	//NOTE: lireJournalDetection est directement testé par ce qu'il y a à faire dans le main.
	
	cout << "------FIN DES TEST------" << endl << endl;
}

int main() {
	tests_partie1();
	tests_partie2();

	const string nomFichierCibles = "Cibles.data";
	const string nomFichierCiblesFinal = "Cibles_final.data";

	string observation = "Cercle noir, E rouge";

	Cible c11 = { 11, {38.140728, -76.426494}, "Triangle gris, O orange", "cible_11.jpg" };

	// TODO: Lire le journal de détection "Cibles.data".<
	bool ok;
	JournalDetection journal = lireJournalDetection(nomFichierCibles, ok);
	// TODO: Faire la vérification d'erreur et terminer le programme avec un
	//       message s'il y a erreur.
	if (!ok) {
		cout << "Erreur de lecture du journal!" << endl;
	}
	else {
		// TODO: Afficher le journal.  (Devrait afficher un journal avec 10 cibles ayant des données valides.)
		afficherJournal(journal);
		// TODO: Retirer la cible 5 de la liste du journal.
		// TODO: Ajouter la cible 11 (variable 'c11' ci-dessus) à la liste du journal.
		// TODO: Afficher les cibles pour vérifier que les opérations ci-dessus ont bien fonctionnées.

		// TODO: Écrire le journal de détection dans "Cibles_final.data".

		// TODO: Écrire l'observation (variable 'observation' ci-dessus) dans la
		//       deuxième cible du fichier créé ci-dessus.

		// TODO: Lire ce nouveau journal et l'afficher.  Toutes les cibles (autre que la 5 qu'on a enlevée) devrait y être, et la nouvelle observation devrait être sur la deuxième cible (qui a aussi l'ID 2, mais c'est une coïncidence).

		// TODO: Désallouer les deux listes de cibles.

		// TODO: Faire la vérification d'erreur et terminer le programme avec un
		//       message s'il y a erreur.
	}
}