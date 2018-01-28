/*
This is the heart of bull cow game functionality.
It does not directly interact with the user.
*/

#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>

#define TMap std::map

void FBullCowGame::Reset()
{
	constexpr int32 CURRENT_TRY = 1;
	constexpr int32 MAX_TRY = 5;
	const FString HIDDEN_WORD = "Ans";
	HiddenWord = HIDDEN_WORD;
	SetCurrentTry(CURRENT_TRY);
	SetMaxTries(MAX_TRY);
	bGameIsWon = false;
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return CurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}
// To support flow channel (Google it!) we will map # of tries to length of word
int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32>  WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,14},{7,20} };
	return WordLengthToMaxTries[HiddenWord.length()];
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{ 

	if (!IsIsoGram(Guess)) 
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	else if (!IsLowerCase(Guess)) 
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	return EGuessStatus::OK;
}

void FBullCowGame::SetMaxTries(int32 iMaxTries)
{
	MaxTries = iMaxTries;
}

void FBullCowGame::SetCurrentTry(int32 iCurrentTry)
{
	CurrentTry = iCurrentTry;
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	FBullCowCount BullCowCount;
	int32 MagicWordLength = HiddenWord.length();
	int32 GuessStringLength = Guess.length();
	for (int32 HWChar = 0; HWChar < MagicWordLength; HWChar++) 
	{
		for (int32 GChar = 0; GChar < GuessStringLength; GChar++) 
		{
			if (HiddenWord[HWChar] == Guess[GChar])
			{
				if (HWChar == GChar)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == MagicWordLength) 
		bGameIsWon = true;
	else 
		bGameIsWon = false;

	return BullCowCount;
}

bool FBullCowGame::IsIsoGram(FString Word) const
{
	if (Word.length() <= 1) return true;
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		if (!LetterSeen[Letter]) {
			LetterSeen[Letter] = true;
		}
		else {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() == 0 || Word =="\0") return true;
	for (auto Letter : Word) {
		if (Letter == ' ')continue;
		if (!islower(Letter)) return false;
	}
	return true;
}
