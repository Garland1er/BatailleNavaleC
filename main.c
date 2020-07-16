#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TAILLE_PLATEAU 10
#define TAILLE_PORTE_AVION 5
#define TAILLE_CROISEUR 4
#define TAILLE_CONTRE_TORPILLEUR_SOUS_MARIN 3
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
#define SOUS_MARIN 20
#define SOUS_MARIN_TOUCHE 21
#define TORPILLEUR 10
#define TORPILLEUR_TOUCHE 11

//Rappel : plateau[lettre][chiffre] et y = lettre et x = chiffre
typedef struct {
	int x, y;
	char dir;
} Coordonnees;

void clearscreen(){
    for ( int i = 0; i < 50; i++ )
        printf("\n");
}

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
    for(int i=0;i<TAILLE_PLATEAU;i++)
        plateau[i] = (int*)malloc(sizeof(int)*TAILLE_PLATEAU);
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
            printf("  %i  ",j+1);
    }
    printf("\n");
    for(int i=0;i<TAILLE_PLATEAU;i++){
        printf("%c ",'A'+i);
        for(int j=0;j<TAILLE_PLATEAU;j++){
            if(plateau[i][j]<10)
                printf("  %i  ",plateau[i][j]);
            else
                printf(" %i  ",plateau[i][j]);
        }
        printf("\n");
    }
}

void afficheValCases(){
    printf("\nValeur correspondante aux cases :\n");
    printf("eau : %i / eau touchee : %i\n",EAU,EAU_TOUCHE);
    printf("bateau touche (plateau adverse) : %i\n",BATEAU_TOUCHE);
    printf("porte-avion : %i / porte-avion touche : %i\n",PORTE_AVION,PORTE_AVION_TOUCHE);
    printf("croiseur : %i / croiseur touche : %i\n",CROISEUR,CROISEUR_TOUCHE);
    printf("contre-torpilleur : %i / contre-torpilleur touche : %i\n",CONTRE_TORPILLEUR, CONTRE_TORPILLEUR_TOUCHE);
    printf("sous-marin : %i / sous-marin touche: %i\n",SOUS_MARIN,SOUS_MARIN_TOUCHE);
    printf("torpilleur : %i / torpilleur touche : %i\n",TORPILLEUR,TORPILLEUR_TOUCHE);
}

Coordonnees strToCoord(char string[], int direction) {
	Coordonnees c;
	char strX[2 + 1];
	int i;

	if (direction > 0) {
		direction = 1;
		c.dir = string[strlen(string) - 1];
	} else {
		direction = 0;
	}

	c.y = string[0] - 'a';
	for (i = 0; i < strlen(string)-(1 + direction); i++) {
		strX[i] = string[i + 1];
	}
	for (i + 1; i < strlen(strX); i++) {
		strX[i] = '\0';
	}

	c.x = strtol(strX, NULL, 10) - 1;

	return c;
}

int** placeBateau(int** plateau,char* nom, int taille, int val_bateau){
    int done, error, i;
	Coordonnees c;
	char orientation[10], str_coord[3], reponse;

	affichePlateau(plateau);

	printf("Veuillez placer le %s (%i cases) en fournissant une coordonnee et son orientation(vers la droite avec v ou vers le bas avec h), par exemple 'a7v' ou 'd2h'\n\n", nom, taille);

	do {
		error = 0;
		done = 0;
		strcpy(orientation, "horizontal");

		printf("Position : ");
		scanf("%s", str_coord);

		c = strToCoord(str_coord, 1);

		if (c.x < 0 || c.y < 0 || c.x > TAILLE_PLATEAU || c.y > TAILLE_PLATEAU) {
			puts(" > Coordonnees hors tableau.");
			error = 1;
		} else if (c.dir == 'v') {
			strcpy(orientation, "vertical");
			// Sortie de carte
			if (c.y + taille > TAILLE_PLATEAU) {
				printf(" > Vous ne pouvez pas placer votre bateau ici. Il sortirait de la carte...\n");
				error = 1;
			} else {
				// Chevauchements
				for (i = c.y; i < c.y + taille; i++) {
					if (plateau[i][c.x] != EAU) {
						puts(" > Il y a dejà un bateau ici...");
						error = 1;

						break;
					}
				}
			}
		} else if (c.x + taille > TAILLE_PLATEAU) {
			printf(" > Vous ne pouvez pas placer votre bateau ici. Il sortirait de la carte...\n");
			error = 1;
		} else {
			// Chevauchements
			for (i = c.x; i < c.x + taille; i++) {
				if (plateau[c.y][i] != EAU) {
					puts(" > Il y a dejà un bateau ici...");
					error = 1;

					break;
				}
			}
		}

		if (error == 0) {
			getchar();
			printf("Placement %s en %c:%i. Est-ce correct ? [o/N] ", orientation, c.y + 'a', c.x + 1);
			reponse = getchar();
			if (reponse == 'o' || reponse == 'O') {
				done = 1;
			}
		}
	} while (done == 0);

	//ajoute la case dans le tableau
    if (c.dir == 'v') {
        for (i = c.y; i < c.y + taille; i++) {
			plateau[i][c.x] = val_bateau;
		}
	} else {
		for (i = c.x; i < c.x + taille; i++) {
			plateau[c.y][i] = val_bateau;
		}
	}
	return plateau;
}

int** initJeu(int** plateau){
    plateau = placeBateau(plateau ,"porte-avion", TAILLE_PORTE_AVION, PORTE_AVION);
    plateau = placeBateau(plateau ,"croiseur", TAILLE_CROISEUR, CROISEUR);
    plateau = placeBateau(plateau ,"contre torpilleur", TAILLE_CONTRE_TORPILLEUR_SOUS_MARIN, CONTRE_TORPILLEUR);
    plateau = placeBateau(plateau ,"sous marin", TAILLE_CONTRE_TORPILLEUR_SOUS_MARIN, SOUS_MARIN);
    plateau = placeBateau(plateau ,"torpilleur", TAILLE_TORPILLEUR, TORPILLEUR);

    return plateau;
}

int tourJoueur(int** plateau, int** vision_plateau_adverse, int** plateau_adverse){
    Coordonnees attaque;
    int error, done, victoire=2;
    char str_coord[2], reponse;

    afficheValCases();
    printf("Votre plateau :\n");
    affichePlateau(plateau);
    printf("\nLe plateau adverse :\n");
    affichePlateau(vision_plateau_adverse);

    do {
        error = 0;
		done = 0;

        printf("Indiquez les Coordonnees de l'attaque : ");
        scanf("%s", str_coord);
        attaque = strToCoord(str_coord, 0);

        if (attaque.x < 0 || attaque.y < 0 || attaque.x > TAILLE_PLATEAU || attaque.y > TAILLE_PLATEAU) {
			puts(" > Coordonnees hors tableau.");
			error = 1;
        }

        if (error == 0) {
            printf("Attaque en %c:%i. Est-ce correct ? [o/N] ", attaque.y + 'a', attaque.x + 1);
            scanf(" %c", &reponse);
			if (reponse == 'o' || reponse == 'O') {
				done = 1;
			}
        }
    }while(done == 0);

    switch(plateau_adverse[attaque.y][attaque.x]){
        case EAU :
            plateau_adverse[attaque.y][attaque.x]=EAU_TOUCHE;
            vision_plateau_adverse[attaque.y][attaque.x]=EAU_TOUCHE;
            break;
        case PORTE_AVION :
            plateau_adverse[attaque.y][attaque.x]=PORTE_AVION_TOUCHE;
            vision_plateau_adverse[attaque.y][attaque.x]=BATEAU_TOUCHE;
            break;
        case CROISEUR :
            plateau_adverse[attaque.y][attaque.x]=CROISEUR_TOUCHE;
            vision_plateau_adverse[attaque.y][attaque.x]=BATEAU_TOUCHE;
            break;
        case CONTRE_TORPILLEUR :
            plateau_adverse[attaque.y][attaque.x]=CONTRE_TORPILLEUR_TOUCHE;
            vision_plateau_adverse[attaque.y][attaque.x]=BATEAU_TOUCHE;
            break;
        case SOUS_MARIN :
            plateau_adverse[attaque.y][attaque.x]=SOUS_MARIN_TOUCHE;
            vision_plateau_adverse[attaque.y][attaque.x]=BATEAU_TOUCHE;
            break;
        case TORPILLEUR :
            plateau_adverse[attaque.y][attaque.x]=TORPILLEUR_TOUCHE;
            vision_plateau_adverse[attaque.y][attaque.x]=BATEAU_TOUCHE;
            break;
    }

    for(int i=0;i<TAILLE_PLATEAU;i++){
        for(int j=0;j<TAILLE_PLATEAU;j++){
            if (plateau_adverse[i][j]==PORTE_AVION || plateau_adverse[i][j]==CROISEUR || plateau_adverse[i][j]==CONTRE_TORPILLEUR || plateau_adverse[i][j]==SOUS_MARIN || plateau_adverse[i][j]==TORPILLEUR)
                victoire=0;
                break;
        }
        if (!victoire)
            break;
    }
    return victoire;
}

int main(){

    //------------------------------------------------initialisation------------------------------------------------//
    int** terrain_j1 = initPlateau();
    int** terrain_j2_adverse = initPlateau();   //vision de joueur 1 sur joueur 2
    int** terrain_j2 = initPlateau();
    int** terrain_j1_adverse = initPlateau();   //vision de joueur 2 sur joueur 1

    afficheLogo();
    printf("\nAppuyer sur entree pour demarrer");
    getchar();
    clearscreen();

    printf("Joueur 1 place ses bateaux :\n\n");
    terrain_j1 = initJeu(terrain_j1);

    clearscreen();
    printf("Joueur 2 place ses bateaux :\n\n");
    terrain_j2 = initJeu(terrain_j2);

    //------------------------------------------------partie en cours------------------------------------------------//
    int finpartie=0; char att_valid;
    do{
        clearscreen();
        printf("Tour joueur 1, appuyer sur entree :\n");
        scanf(" %c", &att_valid);
        finpartie = tourJoueur(terrain_j1, terrain_j2_adverse, terrain_j2);

        if(!finpartie) {
            clearscreen();
            printf("Tour joueur 2, appuyer sur entree :\n");
            scanf(" %c", &att_valid);
            finpartie = tourJoueur(terrain_j2, terrain_j1_adverse, terrain_j1);
        }
        else finpartie = 1;
    }while(finpartie == 0);

    //------------------------------------------------fin de partie------------------------------------------------//
    if(finpartie == 1) {
        clearscreen();
        printf("Victoire du joueur 1");
    }
    else{
        clearscreen();
        printf("Victoire du joueur 2");
    }

}
