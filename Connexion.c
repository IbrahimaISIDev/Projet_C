#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

#define longMax 20
#define longPwd 20

struct termios term, oldterm;

typedef struct
{
    char login[longMax];
    char password[longPwd];
} Identifiants;

int verifierIdentifiants(Identifiants *identifiants, int nombreIdentifiants, char *login, char *password)
{
    for (int i = 0; i < nombreIdentifiants; i++)
    {
        if (strcmp(identifiants[i].login, login) == 0 && strcmp(identifiants[i].password, password) == 0)
        {
            return 1; // Identifiants valides
        }
    }
    return 0; // Identifiants invalides
}

int menuAdmin()
{
    // Menu pour l'administrateur
    int choix;
    do
    {
        puts("=====================================================");
        puts("\tBienvenue dans le menu de l'administrateur :");
        puts("=====================================================");
        puts("1 - GESTION DES ÉTUDIANTS");
        puts("2 - GÉNÉRATION DE FICHIERS");
        puts("3 - MARQUER LES PRÉSENCES");
        puts("4 - ENVOYER UN MESSAGE");
        puts("5 - Quitter");
        puts("======= Merci d'entrer votre choix : ");
        scanf("%d", &choix);
        if (choix < 1 || choix > 5)
        {
            printf("Choix invalide. Veuillez entrer un choix entre  1 et 5.\n");
        }

        if (choix == 3)
        {
            char option;
            int code;
            puts("Entrer votre code [Q pour quitter] :");
            /*  do
             {
                 scanf("%d",&code)

             } while (/* condition ; */
        }

        if (choix == 5)
        {
            puts("Merci et à la prochaine !");
            break;
        }
    } while (choix < 1 || choix > 5);
    return choix;
}

int menuEtudiant()
{
    // Menu pour l'étudiant
    int choix;
    do
    {
        puts("===============================================");
        puts("\tBienvenue dans le menu de l'apprenant :");
        puts("===============================================");
        puts("1 - Marquer présence");
        puts("2 - Nombre de minutes d'absences");
        puts("3 - MARQUER LES PRÉSENCES");
        puts("4 - Mes messages");
        puts("5 - Quitter");
        puts("======= Merci d'entrer votre choix : ");
        scanf("%d", &choix);
        if (choix < 1 || choix > 5)
        {
            printf("Choix invalide. Veuillez entrer un choix entre  1 et 5.\n");
        }

        if (choix == 1)
        {
            /* code */
        }

        if (choix == 5)
        {
            puts("Merci et à la prochaine !");
            break;
        }

    } while (choix < 1 || choix > 5);
    return choix;
}

int main()
{
    FILE *fichierAdmin = fopen("admin.txt", "r");
    FILE *fichierEtudiant = fopen("etudiant.txt", "r");

    if (fichierAdmin == NULL || fichierEtudiant == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return 1;
    }

    Identifiants identifiantsAdmin[100];
    Identifiants identifiantsEtudiant[100];
    int nbrIdentifiantsAdmin = 0;
    int nbrIdentifiantsEtudiant = 0;

    // Lecture des identifiants de l'admin
    while (fscanf(fichierAdmin, "%s %s", identifiantsAdmin[nbrIdentifiantsAdmin].login, identifiantsAdmin[nbrIdentifiantsAdmin].password) == 2)
    {
        nbrIdentifiantsAdmin++;
    }
    fclose(fichierAdmin);

    // Lecture des identifiants de l'étudiant
    while (fscanf(fichierEtudiant, "%s %s", identifiantsEtudiant[nbrIdentifiantsEtudiant].login, identifiantsEtudiant[nbrIdentifiantsEtudiant].password) == 2)
    {
        nbrIdentifiantsEtudiant++;
    }
    fclose(fichierEtudiant);

    char login[longMax];
    char password[longPwd];

    do
    {
        puts("====================================================================");
        puts("\t\tBienvenue dans la page de connexion\n");
        puts("Veuillez saisir votre login: ");

        fgets(login, longMax, stdin);
        login[strcspn(login, "\n")] = 0; // Supprime le caractère de nouvelle ligne
        if (strlen(login) == 0)
        {
            printf("\nVous avez laissé le champ vide. Veuillez rentrer votre login.\n");
            continue;
        }

        int i = 0;
        char c;

        // Désactiver l'écho des caractères saisis
        printf("Entrez votre mot de passe : ");
        fflush(stdout); // Pour vider le buffer de sortie
        tcgetattr(STDIN_FILENO, &term);
        oldterm = term;
        term.c_lflag &= ~(ICANON | ECHO); // Désactiver l'écho des caractères saisis
        tcsetattr(STDIN_FILENO, TCSANOW, &term);

        // Lire les caractères un par un et les masquer
        while ((c = getchar()) != '\n' && i < longPwd - 1)
        {
            if (c == '\b' && i > 0)
            { // Gestion de la touche backspace
                printf("\b \b");
                i--;
            }
            else
            {
                password[i++] = c;
                printf("*");
            }
        }
        password[i] = '\0';

        // Restaurer les paramètres du terminal
        tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);

        printf("\n"); // Ajouter une nouvelle ligne

        if (verifierIdentifiants(identifiantsAdmin, nbrIdentifiantsAdmin, login, password))
        {
            // Menu pour l'admin
            menuAdmin();
        }
        else if (verifierIdentifiants(identifiantsEtudiant, nbrIdentifiantsEtudiant, login, password))
        {
            // Menu pour l'étudiant
            menuEtudiant();
        }
        else
        {
            printf("Login ou mot de passe invalides.\n");
        }

    } while (1);

    fclose(fichierAdmin);
    fclose(fichierEtudiant);

    int sousChoix;
    char fichierEtudiants;
    char etudiant;
    switch (sousChoix) {
            case 1:
                // Marquer la présence d'un étudiant
                int matricule;
                printf("Matricule de l'etudiant : ");
                scanf("%d", &matricule);

                // Rechercher l'étudiant dans le fichier
                rewind(fichierEtudiants);
                struct Etudiant etudiant;
                int etudiantTrouve = 0;

                while (fscanf(fichierEtudiants, "%d %s %s %s", &etudiant.id, etudiant.nom, etudiant.prenom, etudiant.matricule) == 4) {
                    if (etudiant.id == matricule) {
                        etudiantTrouve = 1;
                        printf("%s %s (Matricule : %s) est present.\n", etudiant.prenom, etudiant.nom, etudiant.matricule);

                        // Marquer la présence dans le fichier
                        marquerPresence(fichierPresence, etudiant.id, etudiant.nom, etudiant.prenom);
                        break;
                    }
                }

                if (!etudiantTrouve) {
                    printf("Le matricule %d n'existe pas.\n", matricule);
                }

                // Demander à l'admin de taper Q pour revenir au menu principal
                char reponse;
                printf("Taper Q pour revenir au menu principal : ");
                scanf(" %c", &reponse);

                if (reponse == 'Q' || reponse == 'q') {
                    // Demander le mot de passe pour revenir au menu principal
                    char mdp[50];
                    printf("Saisir le mot de passe pour revenir au menu principal : ");
                    scanf("%s", mdp);
                    // Vérifier le mot de passe pour revenir au menu principal
                    if (strcmp(mdp, adminPassword) != 0) {
                        printf("Mot de passe incorrect. Fin du programme.\n");
                        exit(EXIT_SUCCESS);
                    }
                }
                break;

            case 2:
                // Afficher la liste des étudiants présents
                rewind(fichierPresence);
                printf("\nListe des etudiants presents :\n");
                while (fscanf(fichierPresence, "%d", &matricule) == 1) {
                    printf("Matricule : %d\n", matricule);
                }
                break;

            case 0:
                // Quitter le programme
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide. Veuillez saisir un nombre entre 0 et 2.\n");
        }
    } while (sousChoix != 0);

    // Fermer les fichiers

    return 0;
}