/* This is the console executable that makes use of the BullCow Class
This acts as the view in the MVC pattern and is responsible for all user interaction. For game logic see the
FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

//function prototypes 
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame;

int main()
{
	do {
		PrintIntro();
		PlayGame();
		
	} while (AskToPlayAgain());
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		//Submit valid guess to game and recieves counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

//loop continually until player enters a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";
	do {
		
		//get guess from player
		std::cout << "Try number: " << BCGame.GetCurrentTry() << " of "<< BCGame.GetMaxTries() << std::endl;
		std::cout << "Guess the word: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Invalid_Characters:
			std::cout << "Please enter only valid letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintIntro()
{
	//intoduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}
void PrintGameSummary()
{
	//TODO Add game summary
	if (BCGame.IsGameWon()) {
		std::cout << "Congrats! You won!\n\n";
	}
	else {
		std::cout << "Sorry, try again.\n\n";
	}
}
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again(y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

