#include <iostream>
#include "bullandcow.h"

void printIntro();
void playGame();
bool playAgain();
void printGameSummary();
std::string getValidGuess();

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
    std::cout << "                                                  " << "\n";
    std::cout << "               }   {         ___                  " << "\n";
    std::cout << "               (o o)        (o o)                 " << "\n";
    std::cout << "    /-------^-- \\ /          \\ /----^-------\\    " << "\n";
    std::cout << "   / |  BULL   | o            o |   COW    | \\   " << "\n";
    std::cout << "  *  |-,-------|                |----------|  *   " << "\n";
    std::cout << "     ^         ^                ^          ^      " << "\n";
    std::cout << "                                                  " << "\n";
    std::cout << "WELCOME TO BULLS AND COWS, A FUN WORD GAME.\n";
    std::cout << "Can you guess the " << game.getHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << "\n";
}

std::string getValidGuess()
{
    GuessStatus status = GuessStatus::InvalidStatus;
    std::string result = "";

    do {
        int currentTries = game.getCurrentTry();
        std::string guess = "";

        std::cout << "Try " << currentTries << " of " << game.getMaxTries() << " Enter your guess: ";
        std::getline(std::cin, guess);

        status = game.checkGuessValidity(guess);

        switch (status) {
        case GuessStatus::OK:
            return guess;
        case GuessStatus::NotIsogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case GuessStatus::WrongLength:
            std::cout << "Please enter a " << game.getHiddenWordLength() << " letter word.\n\n";
            break;
        case GuessStatus::NotLowercase:
            std::cout << "Please enter all lowercase letters.\n\n";
            break;
        default:
            std::cout << "Invalid guess. Please try again.\n\n";
            break;
        }

    } while (status != GuessStatus::OK);

    return result;
}

void printGameSummary()
{
    if (game.isGameWon()) {
        std::cout << "WELL DONE! - YOU WIN!\n";
    } else {
        std::cout << "Better luck next time!\n";
    }
}

void playGame()
{
    game.reset();
    int maxTries = game.getMaxTries();

    while (!game.isGameWon() && game.getCurrentTry() <= maxTries) {
        std::string guess = getValidGuess();
        BullCowCount bullCowCount = game.submitValidGuess(guess);

        std::cout << "Bulls = " << bullCowCount.bulls << ", Cows = " << bullCowCount.cows << "\n\n";
    }

    printGameSummary();
}

bool playAgain()
{
    std::cout << "Do you want to play again with a new hidden word? (y/n): ";
    std::string response;
    std::getline(std::cin, response);

    return (response[0] == 'y' || response[0] == 'Y');
}
