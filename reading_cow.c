#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void usage(FILE *out, const char *name)
{
    fprintf(out, "Usage: %s [--no-delay] [--] <fichier>\n"
                 "Lit un fichier texte, une lettre par image (pause de 1 seconde).\n"
                 "  --no-delay  Désactive les pauses et l'effacement de l'écran.\n"
                 "  --help      Affiche cette aide.\n"
                 "Exemples: %s readingcowTxt\n"
                 "          %s --no-delay -- mon-texte.txt\n", name, name, name);
}

int main(int argc, char *argv[])
{
    int delay = 1, options = 1;
    const char *path = NULL;
    for (int i = 1; i < argc; ++i) {
        if (options && strcmp(argv[i], "--help") == 0) {
            usage(stdout, argv[0]);
            return EXIT_SUCCESS;
        } else if (options && strcmp(argv[i], "--no-delay") == 0) {
            delay = 0;
        } else if (options && strcmp(argv[i], "--") == 0) {
            options = 0;
        } else if ((options && argv[i][0] == '-') || path != NULL) {
            usage(stderr, argv[0]);
            return EXIT_FAILURE;
        } else {
            path = argv[i];
        }
    }
    if (path == NULL) {
        usage(stderr, argv[0]);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror(path);
        return EXIT_FAILURE;
    }

    /* Keep only the current word. Grow before appending, including its NUL. */
    size_t length = 0, capacity = 0;
    char *word = NULL;
    int c, status = EXIT_SUCCESS;
    while ((c = fgetc(file)) != EOF) {
        if (c == ' ') {
            length = 0;
            if (word != NULL)
                word[0] = '\0';
        } else if (capacity - length < 2) {
            if (capacity > SIZE_MAX / 2) {
                fprintf(stderr, "%s: mot trop volumineux\n", path);
                status = EXIT_FAILURE;
                break;
            }
            size_t next = capacity ? capacity * 2 : 128;
            char *grown = realloc(word, next);
            if (grown == NULL) {
                fprintf(stderr, "%s: mémoire insuffisante\n", path);
                status = EXIT_FAILURE;
                break;
            }
            word = grown;
            capacity = next;
            word[length] = '\0';
        }
        printf("  \"%s\"\n", word ? word : "");
        printf("        \\   ^__^\n");
        printf("         \\  (oo)\\_______\n");
        printf("            (__)\\       )\\/\\\n");
        printf("             %c  ||----w |\n", c);
        printf("                ||     ||\n");
        if (c != ' ') {
            word[length++] = (char)c;
            word[length] = '\0';
        }
        if (delay) {
            fflush(stdout);
            sleep(1);
            printf("\033[2J\033[1;1H");
        }
    }
    if (ferror(file)) {
        fprintf(stderr, "%s: erreur de lecture\n", path);
        status = EXIT_FAILURE;
    }
    if (fclose(file) == EOF) {
        perror(path);
        status = EXIT_FAILURE;
    }
    free(word);
    if (fflush(stdout) == EOF) {
        perror("stdout");
        status = EXIT_FAILURE;
    }
    return status;
}
