#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void affiche_vache(char eyes[3],int tail_length) {
     printf("  ^__ ^\n");
    printf("  (%s)\\_______\n",eyes);
    printf("  (__)\\       )");
    for (int i = 0; i < tail_length; i++) {
        printf("\\/\\)");
    }
    printf("\n");
    printf("      ||----w |\n");
    printf("      ||     ||\n");
    for (int i = 0; i < tail_length; i++) {
        printf("      ||     ||\n");
    }
}


int main(int argc, char *argv[]) {
    char default_eyes[] = "^^"; 
    char eyes[3]; 
    int tail_length = 0; 

    strcpy(eyes, default_eyes);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--eyes") == 0) {
            if (i + 1 < argc && strlen(argv[i + 1]) == 2) {
                strcpy(eyes, argv[i + 1]);
                i++; 
            } else {
                printf("Erreur: Les yeux doivent être une chaîne de deux caractères.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "--tail") == 0) {
            if (i + 1 < argc) {
                tail_length = atoi(argv[i + 1]);
                i++; 
            } else {
                printf("Erreur: La longueur de la queue doit être spécifiée.\n");
                return 1;
            }
        }
    }

    affiche_vache(eyes, tail_length);

    return 0;
}
