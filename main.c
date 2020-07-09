#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TAILLE_PLATEAU 10
#define TAILLE_PORTE_AVION 5
#define TAILLE_CROISEUR 4
#define TAILLE_CONTRE_TORPILLEUR 3
#define TAILLE_TORPILLEUR 2

#define EAU 0
#define EAU_TOUCHE 1
#define BATEAU_TOUCHE 2
#define PORTE_AVION 50
#define PORTE_AVION_TOUCHE 51
#define CROISEUR 40
#define CROISEUR_TOUCHE 41
#define CONTRE_TORPILLEUR 30
#define CONTRE_TORPILLEUR_TOUCHE 31
#define SOUS_MARIN 32
#define SOUS_MARIN_TOUCHE 33
#define TORPILLEUR 20
#define TORPILLEUR_TOUCHE 21

typedef struct {
	int x, y;
	char dir;
} Coordonnees;

void afficheLogo(){
    printf("()                    _\n");
    printf("||-.,.,.,.,,.,.,...-'\" ;\n");
    printf("||     _          _    |;=============================================================\n");
    printf("||   _( )        ( )_  |;                        Bataille Navale\n");
    printf("||  (_  \\ /\\\\//\\ / ._) |;\n");
    printf("||    '\\ (  )(  ) /    |; fait par Valentin Poudens, Nina Fernette, Adrien D'Arco \n");
    printf("||       \\\\//\\\\//      |;=============================================================\n");
    printf("||        .))((.       |;\n");
    printf("||      _/ |||| \\_     |;\n");
    printf("||    ('  /\"\"\"\"\\  ')   |;\n");
    printf("||     \"(_)    (_)\"    |;\n");
    printf("||-.,.,.,.,.,.,.,.,..-';\n");
    printf("||;\n");
    printf("||;\n");
    printf("||;\n");
    printf("||;\n");
}

int** initPlateau(){
    int** plateau = (int**)malloc(sizeof(int*)*TAILLE_PLATEAU);
    for(int i=0;i<TAILLE_PLATEAU;i++){
        plateau[i] = (int*)malloc(sizeof(int)*TAILLE_PLATEAU);
    }
    for(int i=0;i<TAILLE_PLATEAU;i++){
        for(int j=0;j<TAILLE_PLATEAU;j++){
            plateau[i][j]=0;
        }
    }
    return plateau;
}

void affichePlateau(int** plateau){
    printf("  ");
    for(int j=0;j<TAILLE_PLATEAU;j++){
            printf(" %i ",j+1);
    }
    printf("\n");
    for(int i=0;i<TAILLE_PLATEAU;i++){
        printf("%c ",65+i);
        for(int j=0;j<TAILLE_PLATEAU;j++){
            printf(" %i ",plateau[i][j]);
        }
        printf("\n");
    }
}

Coordonnees strToCoord(char string[], int hasDirection) {
	Coordonnees c;
	char strX[2 + 1];
	int i;

	if (hasDirection > 0) {
		hasDirection = 1;
		c.dir = string[strlen(string) - 1];
	} else {
		hasDirection = 0;
	}

	c.y = string[0] - 'a';
	for (i = 0; i < strlen(string)-(1 + hasDirection); i++) {
		strX[i] = string[i + 1];
	}
	for (i + 1; i < strlen(strX); i++) {
		strX[i] = '\0';
	}

	c.x = strtol(strX, NULL, 10) - 1;

	return c;
}

int main()
{
    int** terrain_j1 = initPlateau();
    int** terrain_j1_adverse = initPlateau();   //vision de joueur 2 sur joueur 1
    int** terrain_j2 = initPlateau();
    int** terrain_j2_adverse = initPlateau();   //vision de joueur 1 sur joueur 2

    Coordonnees attaque;

    afficheLogo();

    affichePlateau(terrain_j1);

    /*printf("attaque en h5 \n");
    attaque = strToCoord("h5",0);
    printf("x(numéro) : %i et y(lettre) : %i \n",attaque.x,attaque.y);*/


}
