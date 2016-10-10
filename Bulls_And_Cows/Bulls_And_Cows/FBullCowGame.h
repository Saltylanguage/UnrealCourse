#pragma once
#include <iostream>
#include <string>

using int32 = int;
using FString = std::string;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};


class FBullCowGame
{
public:
	FBullCowGame();
	~FBullCowGame() {};

	void Reset(); //TODO make a more rich return value\

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;

	EGuessStatus IsValidGuess(FString guess) const;
	FBullCowCount SubmitValidGuess(FString);
	

	bool IsGameWon() const;
	bool EndGame() const;

	FString SetHiddenWord();

private:

	int32 myCurrentTry;	 
	FString myHiddenWord;
	bool bPlayerWins;

	bool IsLowerCase(FString guess) const;
	bool IsIsogram(FString guess) const;
	

};