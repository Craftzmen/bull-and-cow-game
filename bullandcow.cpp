#include <iostream>
#include "bullandcow.h"
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

BullCowGame::BullCowGame() {
    reset();
}

void BullCowGame::reset() {
    vector<string> words = {"heat", "fire", "haze", "wave", "pine"};

    vector<string> fourLetterWords;
    for (const auto& word : words) {
        if (word.length() == 4) {
            fourLetterWords.push_back(word);
        }
    }

    srand(static_cast<unsigned>(time(nullptr)));

    myHiddenWord = fourLetterWords[rand() % fourLetterWords.size()];

    myCurrentTry = 1;
    gameIsWon = false;

    cout << "Game Started! The hidden word has been randomly selected. Good luck!" << endl;
}

bool BullCowGame::isGameWon() const {
    return gameIsWon;
}

int BullCowGame::getMaxTries() const {
    return myHiddenWord.length() * 2;
}

int BullCowGame::getCurrentTry() const {
    return myCurrentTry;
}

int BullCowGame::getHiddenWordLength() const {
    return myHiddenWord.length();
}

GuessStatus BullCowGame::checkGuessValidity(const string& guess) const {
    if (!isIsogram(guess)) {
        return GuessStatus::NotIsogram;
    } else if (!isLowerCase(guess)) {
        return GuessStatus::NotLowercase;
    } else if (guess.length() != getHiddenWordLength()) {
        return GuessStatus::WrongLength;
    } else {
        return GuessStatus::OK;
    }
}

BullCowCount BullCowGame::submitValidGuess(const string& guess) {
    myCurrentTry++;
    BullCowCount bullCowCount;
    int wordLength = myHiddenWord.length();

    for (int i = 0; i < wordLength; i++) {
        for (int j = 0; j < wordLength; j++) {
            if (myHiddenWord[i] == guess[j]) {
                if (i == j) {
                    bullCowCount.bulls++;
                } else {
                    bullCowCount.cows++;
                }
            }
        }
    }

    if (bullCowCount.bulls == wordLength) {
        gameIsWon = true;
    } else {
        gameIsWon = false;
    }

    return bullCowCount;
}

bool BullCowGame::isIsogram(const string& guess) const {
    map<char, bool> letterSeen;
    for (auto letter : guess) {
        letter = tolower(letter);

        if (!letterSeen[letter]) {
            letterSeen[letter] = true;
        } else {
            return false;
        }
    }

    return true;
}

bool BullCowGame::isLowerCase(const string& guess) const {
    for (auto letter : guess) {
        if (!islower(letter)) {
            return false;
        }
    }

    return true;
}
