#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p4.h"

char* copyString(char* str) {
	int len = strlen(str) * sizeof(char);
	char* copy = (char*) malloc(len);
	memcpy(copy, str, len);
	return copy;
}

P4 initialisePartie(int largeur, int hauteur, char* joueur1, char* joueur2) {
	P4 partie;
	partie.w = largeur;
	partie.h = hauteur;
	partie.grille = (int**) malloc(partie.w * sizeof(int*));
	for (int w = 0; w < partie.w; w++) {
		*(partie.grille + w) = (int*) malloc(partie.h * sizeof(int));
		for (int h = 0; h < partie.h; h++) {
			*(*(partie.grille + w) + h) = 0;
		}
	}
	partie.j1 = copyString(joueur1);
	partie.j2 = copyString(joueur2);
	partie.coup = 1;
	return partie;
}

int lastIndexOf(int* tab, int taille, int val) {
	for (int i = taille - 1; i >= 0; i--)
		if (*(tab + i) == val)
			return i;
	return -1;
}

int numJoueur(int coup) {
	int num = coup % 2;
	if (! num)
		num = 2;
	return num;
}

int poserPiece(P4* partie, int* col) {
	*col = -1;
	do {
		printf("Colonne : ");
		scanf("%d", col);
	} while (*col <= 0 || *col > partie->w);
	(*col)--;
	
	int index = lastIndexOf(*(partie->grille + *col), partie->h, 0);
	if (index == -1)
		return -1;
	
	*(*(partie->grille + *col) + index) = numJoueur(partie->coup);
	(partie->coup)++;
	return index;
}

void affMul(char* str, int count) {
	for (int i = 0; i < count; i++)
		printf(str);
}

char* getRepr(int num) {
	switch (num) {
	case 0:
		return "  ";
	case 1:
		return "@@";
	case 2:
		return "##";
	default:
		return "??";
	}
}

void affSep(int w) {
	printf("+");
	affMul("--+", w);
	printf("\n");
}

void afficheGrille(P4* partie) {
	affSep(partie->w);
	
	for (int ligne = 0; ligne < partie->h; ligne++) {
		printf("|");
		for (int col = 0; col < partie->w; col++)
			printf("%s|", getRepr(*(*(partie->grille + col) + ligne)));
		printf("\n");
		affSep(partie->w);
	}
	for (int i = 1; i <= partie->w; i++)
		printf(" %d ", i);
	printf("\n");
}

int caseOK(P4* partie, int x, int y) {
	return x >= 0 && y >= 0 && x < partie->w && y < partie->h;
}

int verifieCaseDir(P4* partie, int x, int y, int dx, int dy, int OK) {
	int nbOK = 0;
	for (int i = -3; i <= 3; i++) {
		if (caseOK(partie, x + (i * dx), y + (i * dy))) {
			if (*(*(partie->grille + x + (i * dx)) + y + (i * dy)) == OK)
				nbOK++;
			else
				nbOK = 0;
			if (nbOK >= 4)
				return OK;
		}
	}
	return 0;
}

int verifieCase(P4* partie, int x, int y) {
	int OK = *(*(partie->grille + x) + y);
	
	return OK && (verifieCaseDir(partie, x, y, 1, 0, OK) // Horizontal
			|| verifieCaseDir(partie, x, y, 0, 1, OK) // Vertical
			|| verifieCaseDir(partie, x, y, 1, 1, OK) // Diagonal (-- / ++)
			|| verifieCaseDir(partie, x, y, 1, -1, OK)); // Diagonal (-+ / +-)
}

int verifieGagne(P4* partie) {
	int gagne;
	for (int w = 0; w < partie->w; w++) {
		for (int h = 0; h < partie->h; h++) {
			if ((gagne = verifieCase(partie, w, h)))
				return gagne;
		}
	}
	return 0;
}

void affichePartie(P4* partie) {
	if (partie->coup % 2)
		printf("%s (@@)", partie->j1);
	else
		printf("%s (##)", partie->j2);
	printf(" à toi de jouer ! Choisis ta colonne !\n");
	afficheGrille(partie);
}