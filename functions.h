#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

bool playWordGuessingGame(const char* randomWord);
bool playWordGuessingGameAutomatic(const char* randomWord, char** words, int numWords, int numSuggestion);

#endif // FUNCTIONS_H
