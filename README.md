# Cowsay

Un projet étudiant en C et Bash : vache personnalisable, lecture animée,
vache sauvage, jeu Tamagoshi et variantes mathématiques. Les dessins ASCII,
les personnalités et les scripts historiques sont conservés.

## Compiler et essayer

Un système Unix/Linux (ou WSL), `make` et un compilateur C sont nécessaires.
Les quatre programmes C n'ont aucune dépendance externe supplémentaire.

```sh
make
./newcow --eyes OO --tail 2
./reading_cow readingcowTxt
./reading_cow --no-delay readingcowTxt
./wild_cow
./tamagoshi_cow
make test
make clean
```

`make all` compile `newcow`, `reading_cow`, `wild_cow` et `tamagoshi_cow`.
Le nom historique du fichier `tamagoshi cow.c` est conservé ; son exécutable
s'appelle `tamagoshi_cow`. Toutes les commandes proposent `--help`, sans lancer
l'animation ni demander les dépendances facultatives.

Le Makefile active C11 et les avertissements (`-Wall -Wextra -Wpedantic`,
formats et prototypes). Les options restent personnalisables :

```sh
make clean
make CC=gcc CFLAGS='-O0 -g -Werror'
# Compilation manuelle toujours possible :
cc -D_DEFAULT_SOURCE -std=c11 -Wall -Wextra reading_cow.c -o reading_cow
```

## Quel argument donner ?

| Programme | Entrée | Exemple |
| --- | --- | --- |
| `newcow` | Options de dessin, **aucun texte** | `./newcow -e OO --tail 2` |
| `reading_cow` | **Chemin d'un fichier texte**, pas une phrase | `./reading_cow readingcowTxt` |
| `wild_cow` | Aucun argument | `./wild_cow` |
| `tamagoshi_cow` | Aucun argument ; réponses au clavier | `./tamagoshi_cow` |
| `cow_primaryschool.sh` | Entier : compter jusqu'à N | `bash cow_primaryschool.sh 3` |
| `cow_highschool.sh` | Entier : carrés de 1 à N | `bash cow_highschool.sh 3` |
| `cow_college.sh` | Entier : Fibonacci jusqu'à N | `bash cow_college.sh 5` |
| `cow_university.sh` | Entier : nombres premiers jusqu'à N | `bash cow_university.sh 7` |
| `smart_cow.sh` | **Chaîne contenant une expression** pour `bc` | `bash smart_cow.sh '2+3*4'` |
| `crazy_cow.sh` | Entier à convertir en binaire | `bash crazy_cow.sh 5` |

Pour faire lire une phrase à `reading_cow`, créez d'abord un fichier :

```sh
printf '%s\n' 'Bonjour le monde' > message.txt
./reading_cow --no-delay message.txt
# Chemin avec espaces ou commençant par un tiret :
./reading_cow -- 'mon message.txt'
./reading_cow -- ./-message.txt
```

La lecture conserve une image par caractère et une pause d'une seconde.
`--no-delay` supprime les pauses et les séquences d'effacement, et produit toutes
les images sur la sortie standard. Le mot courant repart à zéro à chaque espace,
comme dans la version d'origine. Le tampon grandit selon le plus long mot,
sans charger tout le fichier. La sortie d'un très long mot peut être volumineuse
puisque chaque image réaffiche son préfixe. Un fichier vide réussit sans sortie ;
un fichier absent, illisible, une erreur de lecture ou un manque de mémoire
produit un diagnostic sur stderr et un code d'échec.

Les yeux de `newcow` occupent exactement deux octets (par exemple `^^`, `OO`,
`xx`). `--tail` accepte un entier de 0 à `INT_MAX` ; les grandes valeurs génèrent
beaucoup de lignes. Les scripts numériques acceptent 0 à 1 000 000, avec zéros
initiaux décimaux. Cette borne évite les débordements arithmétiques. Les scripts
scolaires font une pause entre les résultats ; Ctrl+C interrompt une animation.

Tamagoshi accueille jusqu'à dix joueurs (noms non vides, 49 octets maximum),
puis `stop` termine la liste. Donner `stop` immédiatement quitte le jeu.
Le jeu demande ensuite les règles et une quantité entière entre 0 et le stock.
Une réponse numérique invalide est redemandée ; EOF ou une ligne trop longue
termine avec un diagnostic. Les états de santé et les événements aléatoires
restent ceux du jeu d'origine.

## Aperçu des variantes

Vache personnalisée (`./newcow -e OO`, dessin par défaut avec ces yeux) :

```text
  ^__ ^
  (OO)\_______
  (__)\       )
      ||----w |
      ||     ||
```

Lecture animée (une image pendant la lecture de `ab`) :

```text
  "a"
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
             b  ||----w |
                ||     ||
```

La vache sauvage se retourne puis marche vers l'herbe ; aperçu d'une image :

```text
       ^__^
       (00)\_______
       (__)\       )\/\
           ||----w |
           ||     ||
```

Tamagoshi change d'expression suivant sa santé : `(^^)` en forme, `(~~)`
en difficulté, `(XX)` en fin de partie. Exemple d'invite :

```text
Voici votre stock de départ -> 5 unités
Entrez un nombre entre 0 et 5 ->
```

Les scripts utilisent les bulles ASCII du **programme externe `cowsay`**.
Ils ne compilent ni n'appellent les programmes C de ce dépôt. Extraits des
messages (les scripts scolaires terminent avec une vache tirant la langue) :

| Variante / commande | Messages dans les bulles |
| --- | --- |
| `bash cow_primaryschool.sh 3` | `La vache dit: 1`, `2`, `3` |
| `bash cow_highschool.sh 3` | `Le carré de 1 est 1`, `de 2 est 4`, `de 3 est 9` |
| `bash cow_college.sh 5` | `La vache dit : 1`, `1`, `2`, `3`, `5` |
| `bash cow_university.sh 7` | `la vach dit : 2`, `3`, `5`, `7` |
| `bash smart_cow.sh '2+3*4'` | `2+3*4 = 14` |
| `bash crazy_cow.sh 5` | `I'm now a dark side cow!`, `Le Nombre binaire de 5 est 101` |

Pour ces scripts seulement, installez `cowsay`, et `bc` pour les deux derniers.
Par exemple sur Debian/Ubuntu : `sudo apt install cowsay bc`. Le script
`crazy_cow.sh` utilise le modèle `vader-koala` fourni par certaines distributions
de `cowsay`. Assurez-vous que `cowsay` est dans le PATH (parfois `/usr/games`).
Les dépendances absentes sont signalées ; elles ne sont pas installées par `make`.

## Vérifications

`make test` teste les aides, arguments invalides, lecture normale, fichier vide,
absent ou illisible, mots de 8192 octets, fichier de 1 Mio et échecs d'allocation
initiaux ou pendant l'agrandissement. Une partie Tamagoshi à événements fixes
vérifie aussi les saisies invalides et la fin de partie, sans attendre les animations.
Les suites des scripts sont vérifiées avec
une doublure de `cowsay`, sans pauses. Les tests de calcul réels nécessitent `bc`
et sont signalés comme ignorés s'il manque. Le test des permissions est ignoré
si l'utilisateur peut lire malgré le mode 000.

Avec GCC ou Clang et leurs sanitizers :

```sh
make clean
make test CFLAGS='-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer' \
  LDFLAGS='-fsanitize=address,undefined'
```

Si LeakSanitizer est bloqué par le traçage de l'environnement, relancez avec
`ASAN_OPTIONS=detect_leaks=0 make test` pour vérifier les accès mémoire et les
comportements indéfinis ; cette exécution ne vérifie alors pas les fuites.
Refaites `make clean && make` pour revenir à une compilation normale.

`readingcowTxt` est l'exemple de texte d'origine ; `exemple-reaadingcow.mov`
est la vidéo de démonstration fournie avec le projet.
