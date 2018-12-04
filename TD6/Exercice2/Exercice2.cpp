#include <iostream>
#include <string>
using namespace std;

string lireEntree(){
	string texte;
	getline(cin, texte);
	return texte;
}

void afficherTexte(const string& texte){
	cout.write(&texte[0], texte.size());
}

//TODO: Fonction dec2int.
long long dec2int(string texte) {
	int taille = texte.length();
	int numero = 0;
	for (int i = 0; i < taille; i++) {
		numero += (texte[i] - 48) * pow(10.0, taille - i - 1);
	}
	return(numero);
}

//TODO: Fonction hex2int.
int hex2int(string texte){
	int taille = texte.length();
	int base = 1, decimal = 0;
	for (int i = 0; i < taille; i++) {
		if (texte[i] >= '0' && texte[i] <= '9') {
			decimal += (texte[i] - 48) * pow(16, taille - i - 1);
		} else if (texte[i] >= 'A' && texte[i] <= 'F') {
			decimal += (texte[i] - 55)*pow(16, taille - i - 1);
		}
	}
	return (decimal);
}

//TODO: Fonction int2dec.
string int2dec(int decimal){
	string resultat = "";
	int quotient = decimal, reste = 0, j = 0;
	while (quotient != 0) {
		resultat += " ";
		reste = quotient % 16;
		if (reste < 10) {
			resultat[j] = reste + 48;
		}
		else {
			resultat[j] = reste + 55;
		}
		quotient /= 16;
		j++;
	}
	string temp = "";
	for (int i = resultat.size() - 1; i >= 0; i--) {
		temp += resultat[i];
	}	
	resultat = temp;
	return { resultat };
}

int main(){
	afficherTexte("Entrer un nombre decimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.
	string decimal = lireEntree();

	afficherTexte("Entrer un nombre hexadecimal: ");
	//TODO: Lire l'entrée en utilisant lireEntree.
	string hexadecimal = lireEntree();
	//TODO: Utiliser vos fonctions dec2int, hex2int et int2dec pour calculer la somme des deux nombres.
	string resultat = int2dec(dec2int(decimal) + hex2int(hexadecimal));

	afficherTexte("La somme decimale est: ");
	//TODO: Afficher la somme en utilisant afficherTexte.
	afficherTexte(resultat);
}