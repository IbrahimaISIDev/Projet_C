#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// Structure pour stocker les informations de connexion
typedef struct
{
    char login[35];
    char password[25];

} CONNEXION;

// Fonction pour vérifier les identifiants de connexion
int verifierIdentifiants(CONNEXION *identifiants, int nbrIdentifiants, char *login, char *password) 
{
    int i;
    for (i = 0; i < nbrIdentifiants; i++) {
        if (strcmp(identifiants[i].login, login) == 0 && strcmp(identifiants[i].password, password) == 0) {
            return i; // Retourne l'index de l'identifiant trouvé
        }
    }
    return -1; // Identifiants invalides
}

int main()
{
    // Création des fichiers pour stocker les identifiants
    FILE *AdminFile = fopen("admin.txt", "r");
    FILE *studentFile = fopen("etudiant.txt", "r");

    if (AdminFile == NULL || studentFile == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return 1;
    }

    // Lecture des identifiants de l'admin
    CONNEXION connecAdmin;
    fscanf(AdminFile, "%s %s", connecAdmin.login, connecAdmin.password);
    fclose(AdminFile);

    // Lecture des identifiants de l'étudiant
    CONNEXION connecEtudiant;
    fscanf(studentFile, "%s %s", connecEtudiant.login, connecEtudiant.password);
    fclose(studentFile);

    // Création d'un tableau contenant les identifiants
    CONNEXION identifiants[2] = {connecAdmin, connecEtudiant};

    // Variables pour l'authentification
    char login[35];
    char *password;

    // Login control...
    puts("====================================================================");
    puts("\t\tBienvenue dans la page de connexion\n");

    int c;

    do {
        puts("Veuillez saisir votre login: ");
        fgets(login, sizeof(login), stdin);

        // Supprimer le caractère de nouvelle ligne de la chaîne
        login[strcspn(login, "\n")] = '\0';

        if (strlen(login) == 0) {
            printf("Le nom d'utilisateur ne peut pas être vide.\n");
        } else if (isspace((unsigned char)login[0])) {
            printf("Le nom d'utilisateur ne peut pas commencer par un espace.\n");
        } else {
            break; // Sortir de la boucle si le login est valide
        }

        // Vider le tampon d'entrée
        while ((c = getchar()) != '\n' && c != EOF);

    } while (1);

    do {
        password = getpass("Veuillez-entrer votre mot de passe : ");

        // Supprimer le caractère de nouvelle ligne de la chaîne
        password[strcspn(password, "\n")] = '\0';

        if (strlen(password) == 0) {
            printf("Le mot de passe ne peut pas être vide.\n");
        } else if (isspace((unsigned char)password[0])) {
            printf("Le mot de passe ne peut pas commencer par un espace.\n");
        } else {
            break; // Sortir de la boucle si le login est valide
        }

        // Vider le tampon d'entrée
        while ((c = getchar()) != '\n' && c != EOF);

    } while (1);


    // Vérification des identifiants
    if (verifierIdentifiants(&connecAdmin, 3, login, password))
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
            
            if (choix==5)
            {
                puts("Merci et à la prochaine !");
                break;
            }
        } while (choix < 1 || choix > 5);
        return choix;
    }
    else if (verifierIdentifiants(&connecEtudiant, 6, login, password))
    {
        // Menu pour l'étudiant
        int choix = 1;
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

            if (choix==5)
            {
                puts("Merci et à la prochaine !");
                break;
            }
            
        } while (choix < 1 || choix > 5);
        return choix;
    }
    else
    {
        printf("\nInvalid password or username !\n");
    }

    return 0;
}
