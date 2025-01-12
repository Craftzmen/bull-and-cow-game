#ifndef BULLANDCOW_H
#define BULLANDCOW_H

#include <iostream>

struct BullCowCount {
    int bulls = 0;
    int cows = 0;
};

enum class GuessStatus {
    OK,
    NotIsogram,
    WrongLength,
    NotLowercase,
    InvalidStatus
};

class BullCowGame {
private:
    int myCurrentTry;
    bool gameIsWon;
    std::string myHiddenWord;

    bool isIsogram(const std::string& guess) const;
    bool isLowerCase(const std::string& guess) const;
public:
    BullCowGame();

    void reset();
    bool isGameWon() const;
    int getMaxTries() const;
    int getCurrentTry() const;
    int getHiddenWordLength() const;
    GuessStatus checkGuessValidity(const std::string& guess) const;
    BullCowCount submitValidGuess(const std::string& guess);
};

#endif // BULLANDCOW_H