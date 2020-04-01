#include <stdio.h>
#include "p4.h"

void main(void) {
	int w = 7, h = 6;
	P4 partie = initialisePartie(w, h, "indy", "teo");
	int col, index, gagnant;
	do {
		affichePartie(&partie);
		while ((index = poserPiece(&partie, &col)) == -1);
	} while (! (gagnant = verifieCase(&partie, col, index)) && partie.coup <= w * h);
	affichePartie(&partie);
	if (gagnant == 1)
		printf("%s (@@) gagne", partie.j1);
	else
		printf("%s (##) gagne", partie.j2);
}