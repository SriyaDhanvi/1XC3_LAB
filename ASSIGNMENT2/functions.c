#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "constants.h"
#include "functions.h"

bool playWordGuessingGame(const char* randomWord) {
    int attempts = 0;
    char guessedWord[MAX_WORD_LENGTH];
    int wordLength = strlen(randomWord);
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '-';
    }
    guessedWord[wordLength] = '\0';

    while (attempts < MAX_ATTEMPTS) {
        printf("Attempt %d: ", attempts + 1);
        
        char guess_word[1000];
        scanf(" %s", guess_word);

        int char_index = 0;
        char guess;

        while((guess_word[char_index] != '\0') && (attempts < MAX_ATTEMPTS)){
            //printf("Attempt %d: ", attempts + 1);
            guess = guess_word[char_index];
            char_index += 1;
            
            bool letterFound = false;
            for (int i = 0; i < wordLength; i++) {
                if (randomWord[i] == guess) {
                    guessedWord[i] = guess;
                    letterFound = true;
                }
            }
            
            printf("Attempt %d: %s\n", attempts + 1, guessedWord);

            if (strcmp(guessedWord, randomWord) == 0) {
                return true;
            }

            if (!letterFound) {
                printf("Incorrect guess. Try again.\n");
                attempts++;
            }
        }
    }
    return false;
}

// ##########################################################################################################################

bool playWordGuessingGameAutomatic(const char* randomWord, char** words, int numWords, int numSuggestion) {
    int attempts = 0;
    char guessedWord[MAX_WORD_LENGTH];
    int wordLength = strlen(randomWord);
    for (int i = 0; i < wordLength; i++) {
        guessedWord[i] = '-';
    }
    guessedWord[wordLength] = '\0';

    while (attempts < MAX_ATTEMPTS - 1) {
        printf("Attempt %d: ", attempts + 1);

        char guess_word[1000];
        scanf(" %s", guess_word);

        int char_index = 0;
        char guess;

        while((guess_word[char_index] != '\0') && (attempts < MAX_ATTEMPTS)){
            //printf("Attempt %d: ", attempts + 1);
            guess = guess_word[char_index];
            char_index += 1;
            
            bool letterFound = false;
            for (int i = 0; i < wordLength; i++) {
                if (randomWord[i] == guess) {
                    guessedWord[i] = guess;
                    letterFound = true;
                }
            }
            
            printf("Attempt %d: %s\n", attempts + 1, guessedWord);

            if (strcmp(guessedWord, randomWord) == 0) {
                return true;
            }

            if (!letterFound) {
                printf("Incorrect guess. Try again.\n");
                attempts++;
            }
        }
        
    }

    // Show suggestions after the 4th attempt
    int possibleWords = 0;
    for (int i = 0; (possibleWords < numSuggestion) && (i < numWords); i++) {
        int length_of_word = strlen(randomWord);

        if(strlen(words[i]) == length_of_word){
            int flag = 1;
            
            for(int j = 0; j < length_of_word; j++){
                if(guessedWord[j] != '-'){
                    if(randomWord[j] != words[i][j]){
                        flag = 0;
                        break;
                    }
                }
            }
            if(flag == 1){
                possibleWords += 1;
            }

        }
    }
    printf("The number of possible words: %d\nHere is upto the first %d possible words:\n\n", possibleWords, numSuggestion);
    
    possibleWords = 0;
    for (int i = 0; (possibleWords < numSuggestion) && (i < numWords); i++) {
        int length_of_word = strlen(randomWord);

        if(strlen(words[i]) == length_of_word){
            int flag = 1;
            
            for(int j = 0; j < length_of_word; j++){
                if(guessedWord[j] != '-'){
                    if(randomWord[j] != words[i][j]){
                        flag = 0;
                        break;
                    }
                }
            }
            if(flag == 1){
                printf("%s,\n", words[i]);
                possibleWords += 1;
            }

        }
    }
    printf("\n\n");

    // Final attempt
    while (attempts < MAX_ATTEMPTS) {
        printf("Attempt %d: ", attempts + 1);
        
        char guess_word[1000];
        scanf(" %s", guess_word);

        int char_index = 0;
        char guess;

        while((guess_word[char_index] != '\0') && (attempts < MAX_ATTEMPTS)){
            //printf("Attempt %d: ", attempts + 1);
            guess = guess_word[char_index];
            char_index += 1;
            
            bool letterFound = false;
            for (int i = 0; i < wordLength; i++) {
                if (randomWord[i] == guess) {
                    guessedWord[i] = guess;
                    letterFound = true;
                }
            }
            
            printf("Attempt %d: %s\n", attempts + 1, guessedWord);

            if (strcmp(guessedWord, randomWord) == 0) {
                return true;
            }

            if (!letterFound) {
                printf("Incorrect guess. Try again.\n");
                attempts++;
            }
        }
    }
    return false;
}


   