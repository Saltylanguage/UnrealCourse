/* This is the console executable that makes use of the FBullCowGame class
   This acts as the view in a MVC pattern, and is responsible for all user
   interaction.  For Game Logic see the FBullCowGame Class.
*/

#pragma once
#include <iostream>
#include "FBullCowGame.h"

//make syntax Unreal Friendly
using int32 = int;
using FText = std::string;


//function prototypes 

//Main Game logic
void PlayGame();

//print functions
void PrintIntro();
void PrintGuess(FText guess);
void PrintHiddenWord();
void PrintGameSummary();

//helper functions
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame myGame; // instantiate a new game, resets at new game

int main()
{
	do
	{
		system("cls");
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

//Main Game Logic (Plays a single game to Completion)
void PlayGame()
{
	myGame.Reset();
	int32 maxTries = myGame.GetMaxTries();

	//loop asking for guesses until the player wins or runs out of tries
	while (!myGame.IsGameWon() && myGame.GetCurrentTry() <= maxTries)
	{
		FText guess = GetValidGuess();	
		FBullCowCount BC_Count = myGame.SubmitValidGuess(guess);
	
		std::cout << "Bulls = " << BC_Count.Bulls;
		std::cout << ". Cows = " << BC_Count.Cows << std::endl;

		PrintGuess(guess);
		PrintHiddenWord(); //prints Hidden Word IF player has won to show match
	}

	PrintGameSummary();
	return;
}


//Start of Print Functions
void PrintIntro()
{

	std::cout << std::endl << std::endl << "Welcome to Bulls and Cows, a fun word game." << std::endl;

	myGame.GetHiddenWord() = myGame.SetHiddenWord();

	std::cout << "Can you guess the " << myGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;
	return;
}

void PrintGuess(FText guess)
{
	std::cout << "Player Guess: " << guess << std::endl;
}

void PrintHiddenWord()
{
	if (myGame.IsGameWon())
	{
		std::cout << "Hidden Word = " << myGame.GetHiddenWord() << std::endl << std::endl;
		return;
	}
	else
	{
		return;
	}
}

void PrintGameSummary()
{
	if (myGame.IsGameWon())
	{
		std::cout << "Congratulations!  You Won!" << std::endl;
	}
	else
	{
		std::cout << "Out of Tries. :(  Better Luck Next Time..." << std::endl;
	}
	std::cout << std::endl;
}
//End of Print Functions


//loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText playerGuess;
	EGuessStatus Status = EGuessStatus::INVALID_STATUS;
	do
	{
		int32 CurrentTry = myGame.GetCurrentTry();
		std::cout << std::endl << "Try " << CurrentTry << " of " << myGame.GetMaxTries();
		std::cout << " Enter your guess: " << std::endl;
	
		getline(std::cin, playerGuess);

		Status = myGame.IsValidGuess(playerGuess);

		switch (Status)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << myGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Entry is not an isogram.  Please Enter a word with no repeating letters." << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Entry is not all lower case.  Please enter all lower case letters." << std::endl;
			break;
		default:
			//assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return playerGuess;
}

//Controls Replay Option (Yes: Resets Game, No: Ends Program)
bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n)" << std::endl << std::endl;
	FText response = "";

	getline(std::cin, response);

	while (response[0] != 'y' && response[0] != 'n' && response[0] != 'Y' && response[0] != 'N')
	{
		std::cout << "Improper Response, please Enter either Y or N:" << std::endl;
		getline(std::cin, response);
	}
	std::cout << std::endl;
	return ((response[0] == 'y') || (response[0] == 'Y'));


}