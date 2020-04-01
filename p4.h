#ifndef P4H
#define P4H

struct puissance4 {
	int w;
	int h;
	char* j1;
	char* j2;
	int** grille;
	int coup;
} typedef P4;

P4 initialisePartie(int largeur, int hauteur, char* joueur1, char* joueur2);

int poserPiece(P4* partie, int* col);

void afficheGrille(P4* partie);

int verifieCase(P4* partie, int x, int y);

int verifieGagne(P4* partie);

void affichePartie(P4* partie);

#endif