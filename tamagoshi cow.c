#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define BYEBYELIFE 0
#define LIFESUCKS 1
#define LIFEROCKS 2

#define MAX_JOUEURS 10
#define TAILLE_NOM 50

#define TAILLE_MAX_PHRASE 150

struct Joueur {
    char nom[TAILLE_NOM]; // Le nom du joueur
    int score; // Le score du joueur
};

void afficherLettreParLettre(const char* phrase, int delai) {
    int longueur = strlen(phrase); // Obtient la longueur de la phrase
    for (int i = 0; i < longueur; i++) {
        printf("%c", phrase[i]); // Affiche le caractère actuel de la phrase
        fflush(stdout); // Vide le tampon de sortie pour afficher immédiatement le caractère
        usleep(delai * 1000); // Pause de temps en millisecondes entre l'affichage de chaque caractère
    }
    printf("\n"); // Nouvelle ligne après avoir affiché tous les caractères de la phrase
}

void saisirNomsJoueurs(struct Joueur* joueurs, int* nbJoueurs) {
    char nom[TAILLE_NOM]; // Variable locale pour stocker le nom temporaire du joueur
    *nbJoueurs = 0; // Initialise le nombre de joueurs à 0
    printf("Saisissez le nom du joueur %d (ou 'stop' pour arrêter) : ", *nbJoueurs + 1);
    fgets(nom, sizeof(nom), stdin); // Lit la saisie du joueur
    nom[strcspn(nom, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne de la saisie

    while (strcmp(nom, "stop") != 0 && *nbJoueurs < MAX_JOUEURS) {
        strncpy(joueurs[*nbJoueurs].nom, nom, sizeof(joueurs[*nbJoueurs].nom) - 1); // Copie le nom saisi dans la structure du joueur actuel
        joueurs[*nbJoueurs].nom[sizeof(joueurs[*nbJoueurs].nom) - 1] = '\0'; // Ensure null termination
        joueurs[*nbJoueurs].score = 0; // Initialise le score du joueur actuel à 0
        (*nbJoueurs)++; // Incrémente le nombre de joueurs
        printf("Saisissez le nom du joueur %d (ou 'stop' pour arrêter) : ", *nbJoueurs + 1);
        fgets(nom, sizeof(nom), stdin); // Lit la saisie du joueur
        nom[strcspn(nom, "\n")] = '\0'; // Supprime le caractère de nouvelle ligne de la saisie
    }
    printf("\n");
}

void regles(char* reponse) {
    char phrase[TAILLE_MAX_PHRASE];
    int delai = 50; // Délai entre chaque lettre en millisecondes
    for (int i = 0; i < strlen(reponse); i++) {
        reponse[i] = tolower(reponse[i]); // Convertit la réponse en minuscules
    }

    while (strcmp(reponse, "oui") != 0 && strcmp(reponse, "non") != 0 &&
           strcmp(reponse, "o") != 0 && strcmp(reponse, "n") != 0) {
        printf("Réponse invalide. Veuillez réessayer : ");
        scanf("%s", reponse);
        for (int i = 0; i < strlen(reponse); i++) {
            reponse[i] = tolower(reponse[i]); // Convertit la réponse en minuscules
        }
    }

    if (strcmp(reponse, "oui") == 0 || strcmp(reponse, "o") == 0) {
        // Affiche les règles du jeu
        strncpy(phrase, "But du jeu :", sizeof(phrase)-1);
        phrase[sizeof(phrase)-1] = '\0'; // Ensure null termination
        afficherLettreParLettre(phrase, delai);
        printf("    -> faire survivre votre vache le plus longtemps possible en maintenant un bon niveau de santé\n\n");
        strncpy(phrase, "Comment jouer?", sizeof(phrase)-1);
        phrase[sizeof(phrase)-1] = '\0'; // Ensure null termination
        afficherLettreParLettre(phrase, delai);
        printf("    -> nourrir la vache à chaque tour en fonction de vos réserves disponibles\n");
        printf("    -> votre stock de nourriture peut augmenter au début de votre tour\n\n");
        strncpy(phrase, "Difficultés :", sizeof(phrase)-1);
        phrase[sizeof(phrase)-1] = '\0'; // Ensure null termination
        afficherLettreParLettre(phrase, delai);
        printf("    -> votre vache peut digérer difficilement et ainsi perdre en niveau de santé\n");
        printf("    -> vos réserves de nourriture peuvent devenir avariées\n");
        printf("    -> si votre vache atteint 0 de niveau de santé, elle meurt de faim, à 10 de suralimentation\n\n\n");
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // Vide le tampon d'entrée

    printf("\n");
    strncpy(phrase, "Appuyez sur Entrée pour continuer...", sizeof(phrase)-1);
    phrase[sizeof(phrase)-1] = '\0'; // Ensure null termination
    afficherLettreParLettre(phrase, delai);
    getchar(); // Attend la pression de la touche Entrée
    strncpy(phrase, "Début de la partie!", sizeof(phrase)-1);
    phrase[sizeof(phrase)-1] = '\0'; // Ensure null termination
    afficherLettreParLettre(phrase, delai); // Affiche la phrase lettre par lettre avec un délai
    sleep(1); // Pause d'une seconde
}

// Rest of your code remains unchanged


void affiche_vache(int* etat)
{
    if (*etat == BYEBYELIFE)
    {
        // Affiche une représentation de vache lorsque l'état est BYEBYELIFE
        printf("                           \n\
                            ________\n\
                      ^__^/         )----- \n\
                      (XX)/||----w |\n\
                      (__) ||     ||\n\
                        U\n");
    } 
    else if (*etat == LIFESUCKS) 
    {
        // Affiche une représentation de vache lorsque l'état est LIFESUCKS
        printf("                           \n\
                           _________\n\
                      ^__^/         )\\/\\\n\
                      (~~)/||----w |\n\
                      ( _) ||     ||\n\n");
    } 
    else if (*etat == LIFEROCKS) 
    {
        // Affiche une représentation de vache lorsque l'état est LIFEROCKS
        printf("                       ^__^\n\
                       (^^)\\_______\n\
                       (__)\\       )\\/\\\n\
                           ||----w |\n\
                           ||     ||\n\n");
    }
}

int quantiteNourrir(int* stock)
{
    char phrase[TAILLE_MAX_PHRASE];
    int delai = 50; // Délai entre chaque lettre en millisecondes

    int donner = 0;

    if (*stock == 0) {
        char phrase[] = "Votre stock est de 0, nourriture en vue?";
        afficherLettreParLettre(phrase, delai);
        printf("\n");
    } else {
        printf("\n");
        char phrase[] = "Quelle quantité souhaitez-vous donner à manger?";
        afficherLettreParLettre(phrase, delai);
        sleep(1);
        printf("Entrez un nombre entre 0 et %d -> ", *stock);
        scanf("%d", &donner);
        printf("\n");
    }

    return donner;
}


void stockApresNourriture(int* stock, int* nourrir)
{
    *stock -= *nourrir; // Réduit le stock de nourriture en fonction de la quantité donnée (*nourrir)

    if (*stock < 0) {
        *stock = 0; // Si le stock devient négatif, le stock est mis à 0 pour éviter les valeurs négatives
    }
}


void evolutionStock(int* stock)
{
    char phrase[TAILLE_MAX_PHRASE] = " ";
    int delai = 50; // Délai entre chaque lettre en millisecondes

    srand(time(NULL)); // Initialise le générateur de nombres aléatoires avec une graine basée sur l'heure actuelle
    int increment = rand() % 7 - 3; // Génère un nombre aléatoire entre -3 et 3

    if (increment <= 0 && *stock == 0) {
        // Cas où l'incrémentation est négative et le stock est déjà à 0
        strcpy(phrase, "Aucune aide pour ce tour et stock à 0, solitude?");
        afficherLettreParLettre(phrase, delai);
        sleep(2);
        strcpy(phrase, "Il semblerait ...");
        afficherLettreParLettre(phrase, delai);
        printf("\n");
        sleep(1);
        strcpy(phrase, "Moment difficile ...");
        afficherLettreParLettre(phrase, delai);
        printf("\n");
        sleep(2);
        strcpy(phrase, "Mort en vue?");
        afficherLettreParLettre(phrase, delai);
        printf("\n");
        sleep(1);
        strcpy(phrase, "Aucune action possible, le tour passe ...");
        afficherLettreParLettre(phrase, delai);
        printf("\n");
        sleep(1);
    } else if (increment < 0) {
        // Cas où l'incrémentation est négative
        strcpy(phrase, "Pas de chance, votre stock est avarié...");
        afficherLettreParLettre(phrase, delai);
        sleep(1);
        printf("Vous perdez %d unité(s)\n\n", increment);
    } else if (increment > 0) {
        // Cas où l'incrémentation est positive
        printf("Super ! Vous avez gagné %d unité(s)\n", increment);
    } else if (increment == 0 && *stock != 0) {
        // Cas où l'incrémentation est nulle mais le stock n'est pas vide
        strcpy(phrase, "Pas de stock en moins ni en plus pour ce tour ...");
        afficherLettreParLettre(phrase, delai);
        sleep(1);
        strcpy(phrase, "Si vous avez fait des provisions, tout va bien !");
        afficherLettreParLettre(phrase, delai);
    } else if (increment == 0 && *stock > 0) {
        // Cas où l'incrémentation est nulle et le stock est supérieur à 0
        strcpy(phrase, "Moment difficile ...");
        afficherLettreParLettre(phrase, delai);
        printf("\n");
    }

    *stock = *stock + increment; // Met à jour le stock en ajoutant l'incrémentation

    if (*stock < 0) {
        *stock = 0; // Réinitialise le stock à 0 s'il devient négatif
    } else if (*stock > 10) {
        *stock = 10; // Limite le stock à une valeur maximale de 10
    }

    sleep(1);
    printf("Il vous reste donc %d unité(s)\n", *stock);
}


int digestion()
{
    srand(time(NULL)); // Initialise le générateur de nombres aléatoires avec une graine basée sur l'heure actuelle

    int val_digestion = rand() % 4; // Génère un nombre aléatoire entre 0 et 3

    return -val_digestion; // Retourne la valeur de digestion avec un signe négatif
}


void niveauDeSante(int* fitness, int* nourrir, int* val_digestion)
{
    *fitness = (*fitness + *nourrir) + *val_digestion; // Met à jour le niveau de santé en ajoutant la quantité nourrie et la valeur de digestion

    if (*fitness < 0) {
        *fitness = 0; // Réinitialise le niveau de santé à 0 s'il devient négatif
    } else if (*fitness > 10) {
        *fitness = 10; // Limite le niveau de santé à une valeur maximale de 10
    }
}


void changementEtat(int* fitness, int* etat)
{
    if (*fitness == 0 || *fitness == 10) {
        *etat = BYEBYELIFE; // Si le niveau de santé est à 0 ou à 10, l'état est défini comme BYEBYELIFE
    } else if ((*fitness >= 1 && *fitness <= 3) || (*fitness >= 7 && *fitness <= 9)) {
        *etat = LIFESUCKS; // Si le niveau de santé est entre 1 et 3 ou entre 7 et 9, l'état est défini comme LIFESUCKS
    } else if (*fitness >= 4 && *fitness <= 6) {
        *etat = LIFEROCKS; // Si le niveau de santé est entre 4 et 6, l'état est défini comme LIFEROCKS
    }
}


int automate(int* stock, int* fitness, int* etat, int* nourrir, int* val_digestion, int* score)
{
    char phrase[TAILLE_MAX_PHRASE] = " ";
    int delai = 50; // Délai entre chaque lettre en millisecondes

    while (*etat != BYEBYELIFE) // Tant que l'état de la vache n'est pas BYEBYELIFE
    {
        switch (*etat)
        {
            case LIFESUCKS:
                printf("\n");
                affiche_vache(etat); // Affiche la vache dans son état actuel
                sleep(1);
                if (*etat == 0) {
                    strcpy(phrase, "Comme un sentiment de fin, au revoir");
                    afficherLettreParLettre(phrase, delai);
                    return *score; // Si l'état est devenu 0, c'est la fin de la partie, le score est retourné
                }
                *nourrir = quantiteNourrir(stock); // Demande au joueur de saisir la quantité de nourriture à donner
                sleep(1);
                stockApresNourriture(stock, nourrir); // Met à jour le stock de nourriture après le repas
                evolutionStock(stock); // Fait évoluer le stock de nourriture pour le tour suivant
                sleep(2);
                system("clear"); // Efface l'écran pour la prochaine étape
                *val_digestion = digestion(); // Génère une valeur aléatoire pour la digestion
                niveauDeSante(fitness, nourrir, val_digestion); // Met à jour le niveau de santé de la vache
                changementEtat(fitness, etat); // Met à jour l'état de la vache en fonction du niveau de santé
                (*score)++; // Incrémente le score
                break;

            case LIFEROCKS:
                printf("\n");
                affiche_vache(etat); // Affiche la vache dans son état actuel
                sleep(1);
                if (*etat == 0) {
                    strcpy(phrase, "Comme un sentiment de fin, au revoir");
                    afficherLettreParLettre(phrase, delai);
                    return *score; // Si l'état est devenu 0, c'est la fin de la partie, le score est retourné
                }
                *nourrir = quantiteNourrir(stock); // Demande au joueur de saisir la quantité de nourriture à donner
                sleep(1);
                stockApresNourriture(stock, nourrir); // Met à jour le stock de nourriture après le repas
                evolutionStock(stock); // Fait évoluer le stock de nourriture pour le tour suivant
                sleep(2);
                system("clear"); // Efface l'écran pour la prochaine étape
                *val_digestion = digestion(); // Génère une valeur aléatoire pour la digestion
                niveauDeSante(fitness, nourrir, val_digestion); // Met à jour le niveau de santé de la vache
                changementEtat(fitness, etat); // Met à jour l'état de la vache en fonction du niveau de santé
                (*score)++; // Incrémente le score
                break;           
        }
    }
    return *score; // Retourne le score final de la partie
}


int main()
{
    char phrase[TAILLE_MAX_PHRASE] = " ";
    int delai = 50; 

    struct Joueur joueurs[MAX_JOUEURS];  // Tableau de joueurs
    int nbJoueurs;  

    system("clear");  // Efface l'écran
    saisirNomsJoueurs(joueurs, &nbJoueurs);  
    strcpy(phrase, "Liste des joueurs :");
    afficherLettreParLettre(phrase, delai);

    for (int i = 0; i < nbJoueurs; i++) {
        printf("    Joueur %d -> %s\n", i + 1, joueurs[i].nom); 
        sleep(1);  
    }
    sleep(1); 

   
    for (int i = 0; i < nbJoueurs; i++) {
        
        int etat = LIFEROCKS;  
        int stock = 5; 
        int fitness = 5; 
        int score = 0; 
        
        char reponse[10]; 
        int nourrir;  
        int val_digestion;  


        system("clear"); 
        sleep(1); 
        printf("C'est à %s de jouer\n\n", joueurs[i].nom);  
        sleep(1);  
        strcpy(phrase, "Afficher les règles du jeu?\n[Oui(o)/Non(n)] :");
        afficherLettreParLettre(phrase, delai);
        scanf("%s", reponse);
        regles(reponse);  
        system("clear");  
        printf("Voici votre stock de départ -> %d unités\n", stock);
        sleep(1);  

       
        score = automate(&stock, &fitness, &etat, &nourrir, &val_digestion, &score);  
        joueurs[i].score = score - 1;  
        system("clear");  

       
        affiche_vache(&etat);  
        sleep(2);  
        printf("\n\n");
        printf("Fin de partie\n\n");
        sleep(1);  

        
        if (fitness == 0) {
            strcpy(phrase, "Votre vache s'allonge péniblement et s'endort");
            afficherLettreParLettre(phrase, delai);
            printf("\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf(".\n\n");
            sleep(1);
            strcpy(phrase, "Elle est morte de faim");
            afficherLettreParLettre(phrase, delai);
            printf("\n");
        } else if (fitness == 10) {
            strcpy(phrase, "Il y en a même jusqu'au plafond ... ?");
            afficherLettreParLettre(phrase, delai);
            printf("\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf(".\n\n");
            strcpy(phrase, "Explosion très probable!");
            afficherLettreParLettre(phrase, delai);
            printf("\n");
        }
        sleep(1);
        printf("Votre score : %d\n", score - 1);
        sleep(2);
    }
    system("clear");


    strcpy(phrase, "Scores des joueurs :");
    afficherLettreParLettre(phrase, delai);
    printf("\n");
    sleep(1);
    for (int i = 0; i < nbJoueurs; i++) {
        printf("    %s -> %d\n\n", joueurs[i].nom, joueurs[i].score);
        sleep(1);
    }
    printf("\n");
    strcpy(phrase, "Merci d'avoir joué :)");
    afficherLettreParLettre(phrase, delai);

    return 0;
}