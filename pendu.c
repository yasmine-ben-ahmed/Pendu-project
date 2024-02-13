#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Global variables to store the secret word and current word
char MotSecret[TAILLE_MAX];
char motActuel[TAILLE_MAX];

// Global variable for the trie data structure
TArbre trie;

// Function to read a character from the user
char lireCaractere() {
    char caractere = 0;
    // Read the character
    scanf(" %c", &caractere); // Notice the space before %c to skip whitespace characters

    // Clear the input buffer
    while (getchar() != '\n'); // Keep reading characters until encountering a newline

    // If the user enters '0', return a special value to indicate exit
    if (caractere == '0') {
        return -1;  // Return a special value to indicate exit
    }
    
    return caractere;
}

// Function to read a line of input
/*void lireLigne(char* mot) {
    int i = 0;

    while ((mot[i] = getchar()) != '\n') {
        // Use isdigit to check if the character is a digit
        if (!isdigit(mot[i])) {
            printf("\t \t!!!! Please enter a number.\n");
            // Clear the input buffer to prevent issues with subsequent inputs
            while (getchar() != '\n');
            i = 0;  // Reset the index to restart input
        } else {
            // Convert the character to uppercase
            mot[i] = toupper(mot[i]);
            i++;
        }
    }
    mot[i] = '\0'; // Null-terminate the string
}*/



void genererMotSecret(TArbre *Mdico) {
    *Mdico = arbreConsVide();

    // Pick a single random word
    if (piocherMot(MotSecret) == 1) {
        printf("_________________________________________________\n\n");
        // Display the secret word
        printf("\n \t \t ((Secret word: %s))\n", MotSecret);

        // Insert the secret word into the dictionary tree (if necessary)
        dicoInsererMot(MotSecret, Mdico);
    } else {
        printf("Error retrieving the secret word.\n\n");
    }
}

void displayHangman(int tries) {
    switch (tries) {
        case 8:
            // Display Hangman figure for 8 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 7:
            // Display Hangman figure for 7 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 6:
            // Display Hangman figure for 6 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");           
            printf("  |     |\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 5:
            // Display Hangman figure for 5 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");             
            printf("  |    /|\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 4:
            // Display Hangman figure for 4 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 3:
            // Display Hangman figure for 3 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");            
            printf("  |    /\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 2:
            // Display Hangman figure for 2 tries left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");            
            printf("  |    / \\\n");
            printf("  |\n");
            printf("  |\n");
            break;
        case 1:
            // Display Hangman figure for 1 try left
            printf("  _______\n");
            printf("  |     |\n");
            printf("  |     O\n");
            printf("  |    ---\n");
            printf("  |    /|\\\n");
            printf("  |     |\n");            
            printf("  |    / \\\n");
            printf("  |\n");
            break;
    }
}



int jeuxDePendu(TArbre trie) {
    int i, taille;
    char motCache[TAILLE_MAX];
    char carLu, cardif;
    int attempts, nb_fautes;

    // Copy the secret word into a local variable
    strcpy(motCache, MotSecret);

    // Display welcome message

    printf("\t______________________________________________________________\n");
    printf("\t______________________________________________________________\n");
    printf("\n \t**************!! Welcome to the Hangman Game !!************\n");
    printf("\t______________________________________________________________\n");
    printf("\t______________________________________________________________\n\n");
   
    // Prompt user to start the game
    while (carLu != '1') {
        printf(" \t \t!! If you are ready, type 1 to start !! (or press 0 to quit)\n");

        // Read user input
        carLu = lireCaractere();
        
        // Check if user wants to quit
        if (carLu == -1) {
            // User entered '0', exit the game
            printf("\t \t !!!! Hangman game is over...!!!!\n");
            exit(0);
        }
    } 
    
    // Start the game
    if (carLu == '1') {
        printf(" \t \t____The game begins____ \n");
    }

    // Determine the length of the secret word
    taille = strlen(motCache);

    // Initialize the current guessed word with dashes
    for (i = 0; i < taille; i++) {
        motActuel[i] = '-';
    }
    motActuel[taille] = '\0';

    // Choose difficulty level

    printf("\n \t \tDifficulty Level (Please choose the level of difficulty)\n");
    printf("\n \t \t Hard (Tape 1)\n");
    printf("\n \t \t Medium (Tape 2)\n");
    printf("\n \t \t Easy (Tape 3)\n");
    cardif = lireCaractere();


    // Set the maximum number of wrong attempts based on the chosen difficulty
    switch (cardif) {
        case '1':
            nb_fautes = 3 ;
            break ;
        case '2':
            nb_fautes = 5 ;
            break ;
        case '3':
            nb_fautes = 8 ;
            break ;
        default:
		printf("Invalid choice! (Hangman game is over...)\n");
		exit(0);
		break;            
    }
    
    printf("\n \t \tNumber of maximum errors : %d \n", nb_fautes);
    
    //printf("\nMot secret : %s \n", motCache);
    
    printf("___________________________________________\n");
    
    // Main game loop: continue until the word is guessed or maximum attempts are reached
    while (strncmp(motActuel, motCache, taille) != 0 && nb_fautes > 0) {
        // Display current state of the game
        printf("\n \t \t What is the secret word? %s\n", motActuel);
        printf("\t \t Remaining wrong attempts: %d\n", nb_fautes);

        // Prompt user to propose a letter
        do {
            printf("\n \t \t Propose a letter: (or press 0 to quit)\n");

            // Read user input
            carLu = lireCaractere();
            
            // Validate user input: check if it's a letter
            if (isalpha(carLu)) {
                break;
            } else {
                // Invalid input, prompt user to enter a letter again
                // Clear the input buffer to prevent issues with subsequent inputs
                while (getchar() != '\n');
            }
        } while (1);

        // Check if user wants to quit
        if (carLu == -1) {
            // User entered '0', exit the game
            printf("\t \t !!!! Hangman game is over...!!!!\n");
            exit(0);
        }

// Search for the guessed letter in the trie
    TArbre result = rechercheCaractereTrie(trie, carLu);

    if (result != NULL && carLu == result->caractere) {
    // Guessed letter found
        printf("\n \t \t Letter found: %c\n", result->caractere);

        int letterFound = 0;

        for (i = 0; i < taille; i++) {
            if (motCache[i] == result->caractere && motActuel[i] == '-') {
                motActuel[i] = carLu;
                letterFound = 1;
            }
        }

        if (letterFound) {
            attempts++;

            printf("____________________________________________________________________________\n");


                // Check if the word has been fully guessed
            if (strncmp(motActuel, motCache, taille) == 0) {
	printf("\n\n \t \t ____Congratulations :)\n  \n \t \tThe word to guess is __%s__ !\n\n",
		   motCache);
                printf("____________________________________________________________________________\n");
              
            }
        } else {
            // The letter has already been guessed
           printf("\n \t \t Letter already guessed. You have %d Remaining wrong attempts left.\n", nb_fautes);
               printf("____________________________________________________________________________\n");
        }
    } else {
        // result == NULL or carLu != result->caractere
        // Guessed letter not found in the trie
        attempts++;
        nb_fautes--;
        
        printf("\n \t \t Letter not found. You have %d Remaining wrong attempts left.\n", nb_fautes);
        
	displayHangman(nb_fautes +1);  // Display Hangman for wrong letter
        printf("____________________________________________________________________________\n");
        
    }
}
 //while

// Game over: player wins or loses
if (strncmp(motActuel, motCache, taille) != 0) {
    printf("\n\n \t \t °__° You lost! \n \n \t \t The word was %s\n\n", motCache);
    
}



    return 0;
}

