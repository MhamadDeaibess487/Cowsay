#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s [-e|--eyes <2 caractères>] [--tail <entier>]\n"
               "Personnalise la vache (aucun texte en argument).\n"
               "La queue doit être comprise entre 0 et %d.\n"
               "Exemple: %s --eyes OO --tail 2\n", argv[0], INT_MAX, argv[0]);
        return 0;
    }
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
                fprintf(stderr, "Erreur: Les yeux doivent être une chaîne de deux caractères.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "--tail") == 0) {
            if (i + 1 < argc) {
                char *end;
                errno = 0;
                long value = strtol(argv[i + 1], &end, 10);
                if (errno || *end || end == argv[i + 1] || value < 0 || value > INT_MAX) {
                    fprintf(stderr, "Erreur: --tail attend un entier entre 0 et %d.\n", INT_MAX);
                    return 1;
                }
                tail_length = (int)value;
                i++; 
            } else {
                fprintf(stderr, "Erreur: La longueur de la queue doit être spécifiée.\n");
                return 1;
            }
        } else {
            fprintf(stderr, "Argument inconnu: %s (voir --help).\n", argv[i]);
            return 1;
        }
    }

    affiche_vache(eyes, tail_length);

    return 0;
}
