#include <iostream>
#include "bullandcow.h"

using namespace std;

void printIntro();
void playGame();
bool playAgain();
void printGameSummary();
string getValidGuess();

BullCowGame game;

int main()
{
    bool reply = false;

    do {
        printIntro();
        playGame();
        reply = playAgain();

        if (reply) {
            system("clear");
        }
    } while (reply);

    return 0;
}

void printIntro()
{
    cout << "                                                  " << "\n";
    cout << "               }   {         ___                  " << "\n";
    cout << "               (o o)        (o o)                 " << "\n";
    cout << "    /-------^-- \\ /          \\ /----^-------\\    " << "\n";
    cout << "   / |  BULL   | o            o |   COW    | \\   " << "\n";
    cout << "  *  |-,-------|                |----------|  *   " << "\n";
    cout << "     ^         ^                ^          ^      " << "\n";
    cout << "                                                  " << "\n";
    cout << "WELCOME TO BULLS AND COWS, A FUN WORD GAME.\n";
    cout << "Can you guess the " << game.getHiddenWordLength() << " letter isogram I'm thinking of?\n";
    cout << "\n";
}

string getValidGuess()
{
    GuessStatus status = GuessStatus::InvalidStatus;
    string result = "";

    do {
        int currentTries = game.getCurrentTry();
        string guess = "";

        cout << "Try " << currentTries << " of " << game.getMaxTries() << " Enter your guess: ";
        getline(cin, guess);

        status = game.checkGuessValidity(guess);

        switch (status) {
        case GuessStatus::OK:
            return guess;
        case GuessStatus::NotIsogram:
            cout << "Please enter a word without repeating letters.\n\n";
            break;
        case GuessStatus::WrongLength:
            cout << "Please enter a " << game.getHiddenWordLength() << " letter word.\n\n";
            break;
        case GuessStatus::NotLowercase:
            cout << "Please enter all lowercase letters.\n\n";
            break;
        default:
            cout << "Invalid guess. Please try again.\n\n";
            break;
        }

    } while (status != GuessStatus::OK);

    return result;
}

void printGameSummary()
{
    if (game.isGameWon()) {
        cout << "WELL DONE! - YOU WIN!\n";
    } else {
        cout << "Better luck next time!\n";
    }
}

void playGame()
{
    game.reset();
    int maxTries = game.getMaxTries();

    while (!game.isGameWon() && game.getCurrentTry() <= maxTries) {
        string guess = getValidGuess();
        BullCowCount bullCowCount = game.submitValidGuess(guess);

        cout << "Bulls = " << bullCowCount.bulls << ", Cows = " << bullCowCount.cows << "\n\n";
    }

    printGameSummary();
}

bool playAgain()
{
    cout << "Do you want to play again with a new hidden word? (y/n): ";
    string response;
    getline(cin, response);

    return (response[0] == 'y' || response[0] == 'Y');
}
