#include <stdio.h>
#include <unistd.h>
#include <string.h>

void update(void)
{
    printf("\033[H\033[J");
}

void gotoxy(int x, int y) 
{
    printf("\033[%d;%dH", y, x);
}

void affiche_vache(void)
{
    printf("                          ^__^\n\
                          (00)\\_______\n\
                          (__)\\       )\\/\\\n\
                              ||----w |\n\
                              ||     ||\n");
}

void bouge_langue(void)
{
    unsigned long t=50000;

    update();
    affiche_vache();
    sleep(1);

    update();
    printf("                          ^__^\n\
                          (00)\\_______\n\
                          (__)\\       )\\/\\\n\
                              ||----w |                     \\\\||//\n\
                              ||     ||                      \\||/\n");

    sleep(2);
    usleep(t+300000);
    update();
    printf("                          ^__^\n\
                          (00)\\____\n\
                          (__)\\    )\\/\n\
                              ||--w|                        \\\\||//\n\
                              ||  ||                         \\||/\n");
    usleep(t);
    update();
    fflush(stdout);
    printf("                         ^__^\n\
                         (00)\\___\n\
                         (__)\\   )\\\n\
                             ||-w|                          \\\\||//\n\
                             || ||                           \\||/\n");
    usleep(t);
    update();
    fflush(stdout);
    printf("                        ^__^\n\
                        (00)__\n\
                        (__)  )\n\
                          ||w|                              \\\\||//\n\
                          || |                               \\||/\n");
    usleep(t);
    update();
    printf("                        ^__^\n\
                        (00)_\n\
                        (__) )\n\
                          |||                               \\\\||//\n\
                          |||                                \\||/\n");
    usleep(t);
    update();
    printf("                       ^__^\n\
                       (00)\n\
                       (__))\n\
                        ||                                  \\\\||//\n\
                        ||                                   \\||/\n");
    usleep(t);
    update();
    printf("                      ^__^\n\
                      (00)\n\
                      (__)\n\
                       ||                                   \\\\||//\n\
                       ||                                    \\||/\n");
    usleep(t);
    update();
    printf("                     ^__^\n\
                     (00)\n\
                    ((__)\n\
                      ||                                    \\\\||//\n\
                      ||                                     \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
                   _(00)\n\
                  ( (__)\n\
                   |||                                      \\\\||//\n\
                   |||                                       \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
                  __(00)\n\
                 (  (__)\n\
                  |w||                                      \\\\||//\n\
                  | ||                                       \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
                ___/(00)\n\
              /(   /(__)\n\
               |w-||                                        \\\\||//\n\
               || ||                                         \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
               ____/(00)\n\
            \\/(    /(__)\n\
              |w--||                                        \\\\||//\n\
              ||  ||                                         \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
             ______/(00)\n\
         /\\/(      /(__)\n\
            |w----||                                        \\\\||//\n\
            ||    ||                                         \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
             ______/(00)\n\
         /\\/(      /(__)\n\
            |w----||                                        \\\\||//\n\
            ||    ||                                         \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
             ______/(00)\n\
         /\\/(      /(__)\n\
            |w----||                                        \\\\||//\n\
            ||    ||                                         \\||/\n");
    usleep(t);
    update();
    printf("                    ^__^\n\
             ______/(00)\n\
         /\\/(      /(__)\n\
            |w----||                                        \\\\||//\n\
            ||    ||                                         \\||/\n");
    sleep(1);
    update();

    char ligne[150] = "                                                               ";

    for (int i = 40; i > 2; i--) {
        ligne[i-1] = '\0'; // Supprime le dernier espace

        usleep(100000);
        
        printf("                        ^__^\n\
                 ______/(00)\n\
             /\\/(      /(__)\n\
                /w----/\\%s \\\\||//\n\
               / |   /  | %s\\||/\n", ligne, ligne);
        update();

        usleep(100000);
        
        printf("                        ^__^\n\
                 ______/(00)\n\
             /\\/(      /(__)\n\
                |w----||%s\\\\||//\n\
                ||    ||%s \\||/\n", ligne, ligne);
        update();

        usleep(100000);
        
    }
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s\nAnimation de la vache sauvage dans le terminal.\n"
               "Exemple: %s\n", argv[0], argv[0]);
        return 0;
    }
    if (argc != 1) {
        fprintf(stderr, "Usage: %s (voir --help)\n", argv[0]);
        return 1;
    }
    bouge_langue();
    return 0;
}