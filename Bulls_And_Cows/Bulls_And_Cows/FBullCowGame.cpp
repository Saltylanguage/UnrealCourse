#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() // default constructor
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return myCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const
{
	return myHiddenWord.length();
}
 
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3, 4 }, { 4, 7 }, { 5,10 }, { 6,16 }, {7, 20 } };
	return WordLengthToMaxTries[myHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	myCurrentTry = 1;
	bPlayerWins = false;
	return;
}

EGuessStatus FBullCowGame::IsValidGuess(FString guess)const
{
	if (!IsIsogram(guess))//if the guess isnt an isogram 
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLowerCase(guess))// if the guess isnt all lower case 
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (guess.length() != GetHiddenWordLength()) //if guess length is wrong
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	else // all conditions met
	{
		return EGuessStatus::OK;
	}
}


//receives a valid guess, increments turn, and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	myCurrentTry++;
	FBullCowCount BC_Count;

	//loop through all letters in the hidden word
	for (size_t i = 0; i < myHiddenWord.length(); i++)
	{
		//compare every letter against the hidden word
		for (size_t j = 0; j < myHiddenWord.length(); j++)
		{

			if (guess[i] == myHiddenWord[j]) //if they match 
			{
				if (i == j)
				{
					BC_Count.Bulls++; //increment bulls if they're in the same place
				}
				else
				{
					BC_Count.Cows++; // incremenet cows if they're not
				}
			}
		}
	}
	if (BC_Count.Bulls == myHiddenWord.length())
	{
		bPlayerWins = true;
	}
	else
	{
		bPlayerWins = false;
	}
	return BC_Count;

}

bool FBullCowGame::IsGameWon() const
{
	return bPlayerWins;
}

bool FBullCowGame::EndGame() const
{
	if (bPlayerWins)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FString FBullCowGame::GetHiddenWord() const
{
	return myHiddenWord;
}

FString FBullCowGame::SetHiddenWord()
{

	TMap<int32, FString> HiddenWordSelection{ { 3, "and" },{ 4, "date" },{ 5, "scrap" },{ 6, "planet" },{ 7, "garnish" } }; //these strings MUST be isograms
	int32 playerChoice = 0;
	std::cout << "How long would you like your word to be? (Min Letters = 3, Max Letters = 7)" << std::endl;
	std::cin >> playerChoice;
	while (playerChoice < 3 || playerChoice > 7)
	{
		std::cout << "Please Select a Value Between 3 and 7" << std::endl;
		std::cin >> playerChoice;
	}
	myHiddenWord = HiddenWordSelection[playerChoice];
	std::cin.ignore();
	return myHiddenWord;

}


bool FBullCowGame::IsLowerCase(FString guess) const
{
	if (guess.length() == 0)
	{
		return true;
	}
	for (auto letter : guess)
	{
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}



bool FBullCowGame::IsIsogram(FString guess) const
{
	//treat 0 and 1 letter words as isograms (return true)
	if (guess.length() <= 1)
	{
		return true;
	}
	TMap<char, bool> LetterSeen;
	for (auto letter : guess) // for each letter in guess
	{
		letter = tolower(letter);
		// check if bool is still false
		if (LetterSeen[letter]) 	//if letter's bool is already true
		{
			return false;
		}
		else //otherwise change letter's bool to true
		{
			LetterSeen[letter] = true;
		}
	}// exit for loop:
	
	return true; 
}
