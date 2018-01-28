/*
This is the 
*/

#pragma once
#include<string>

using FString = std::string;
using int32 = int;

// all variables initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID,
	NOT_ISOGRAM,
	NOT_LOWERCASE,
	WRONG_LENGTH,
	OK
};

class FBullCowGame {
public:
	FBullCowGame();
	
	int32	GetMaxTries() const;
	int32	GetCurrentTry() const;
	int32	GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); // TODO make a more rich return value
	void SetMaxTries(int32 iMaxTries);
	void SetCurrentTry(int32 iCurrentTry);
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 CurrentTry;
	int32 MaxTries;
	FString HiddenWord;
	bool bGameIsWon;

	bool IsIsoGram(FString) const;
	bool IsLowerCase(FString) const;
};