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
	ListeCibles listeCibles = { tableauCibles, 0, size(tableauCibles) };

	//TODO: Ajouter 3 fois une cible (ajouterCible) à la cibles, chacun avec un ID différent (les autres valeurs ne sont pas importantes);
	//TODO: après chaque ajout vérifier que le nombre de cibles est bon (i.e. 1 après le premier ajout, 2 après le deuxième), et que les données de la cible sont dans la liste (vérifiez uniquement l'ID).
	//TODO: Ajouter une autre cible, le nombre d'éléments devrait être encore 3 puisque c'est la capacité de la liste. -- DONE
	
	for (uint32_t i = 1; i <= 3; i++) {
		Cible cible = { i, 0, '0', '0'};
		ajouterCible(listeCibles, cible);
		cout << " le nombre de cibles est : " << listeCibles.nbElements << endl;
	}
	for (uint32_t i = 0; i < 3; i++) {
		cout << " id cible :  " << listeCibles.elements[i].id << endl;
	}
	
	//TODO: Retirer la cible (retirerCible) ayant l'ID que vous avez mis en 2e, vérifier qu'il reste 2 éléments aux indices 0 et 1 dont les ID sont les bons.
	retirerCible(listeCibles, 2);
	cout << "cible 1 : " << listeCibles.elements[0].id << endl;
	cout << "cible 2 : " << listeCibles.elements[1].id << endl;
	cout << "cible 3 : " << listeCibles.elements[2].id << endl;
	

	//TODO: Écrire les cibles (ecrireCibles) dans le fichier fichierTestCibles. Vérifier que la tête d'écriture est rendue au bon endroit.
	fstream fichierTestCibles("fichierTestCibles.bin", ios::in | ios::out | ios::trunc | ios::binary);

	Cible tableauCibles2[3] = {};
	ListeCibles listeCibles2 = { tableauCibles2, 0, size(tableauCibles) };

	//TODO: Remettre la tête de lecture au début du fichier puis lire les cibles (lireCibles) dans cibles2. Vérifier que les 2 bonnes cibles y sont.

	//TODO: Créer une variable de type JournalDetection avec des valeurs quelconques et une ListeCibles déjà créé ci-dessus.
	//TODO: Écrire ce journal (ecrireJournalDetection) dans un nouveau fichier binaire.
	//TODO: Vérifier que ok est vrai.
	//NOTE: La relecture du fichier pour vérifier qu'il est bon se fera seulement dans la partie 2.  Vous pouvez pour l'instant vérifier que la taille du fichier est bonne (propriétés du fichier dans Windows; la "taille" en octets devrait être une taille d'entête plus le bon nombre de cibles; attention de ne pas regarder la "taille sur disque" qui peut être différente de la "taille" dans les propriétés du fichier).  Vous pouvez aussi ouvrir le fichier binaire avec un éditeur binaire (par exemple celui de VisualStudio) pour voir si les ID sont bien dans le fichier.

	//TODO: Ajouter une observation (ecrireObservation) au fichier créé ci-dessus à l'indice 1 (deuxième cible).
	//NOTE: Même chose que ci-dessus: la taille du fichier ne devrait pas avoir changée, et dans l'éditeur binaire vous devriez voir le texte après le deuxième ID.

}

void tests_partie2() {
	//TODO: Allouer une liste de cibles (allouerListe) de capacité 2; vérifier que la capacité est la bonne et que le nombre d'éléments est zéro.
	//TODO: Ajouter une cible la liste; ça devrait fonctionner.
	//TODO: Conserver le pointeur vers le tableau de cibles dans une variable.
	//TODO: Désallouer la liste (desallouerListe); vérifier que les valeurs sont à zéro.
	//TODO: Allouer une nouvelle liste de cibles de capacité 2; vérifier que son pointeur est le même que celui conservé ci-dessus.  NOTE: Il n'y a pas de manière dans le standard ISO C++ pour vérifier que la mémoire a bien été désallouée.  Ce test n'est donc pas standard et pourrait échouer même si le programme est correct, mais on a la garantie qu'il peut réussir uniquement si la désallocation est faite.
	//TODO: Désallouer cette deuxième liste.

	//NOTE: lireJournalDetection est directement testé par ce qu'il y a à faire dans le main.
}

int main() {
	tests_partie1();
	tests_partie2();

	const string nomFichierCibles = "Cibles.data";
	const string nomFichierCiblesFinal = "Cibles_final.data";

	string observation = "Cercle noir, E rouge";

	//Cible c11 = { 11, {38.140728, -76.426494}, "Triangle gris, O orange", "cible_11.jpg" };

	// TODO: Lire le journal de détection "Cibles.data".

	// TODO: Faire la vérification d'erreur et terminer le programme avec un
	//       message s'il y a erreur.

	// TODO: Afficher le journal.  (Devrait afficher un journal avec 10 cibles ayant des données valides.)

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