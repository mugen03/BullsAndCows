/*
This is the console executable, that makes use of the BullCow class.
MVC pattern. This file in responsible for all user interfactions.
Game logic - FBullCowGame class
*/

#pragma once

#include "stdafx.h"
#include<iostream>
#include<string>
#include"FBullCowGame.h"

// added these using statements to make it compatible with Unreal style
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

// entry point
int main()
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

// introduce the games. 
void PrintIntro() 
{
	std::cout << "\nWelcome to Bulls and Cows, a fun word game."<<std::endl;
	std::cout << " _                 _"<<std::endl;
	std::cout << "|_)   || _  ()    /   _      _"<<std::endl;
	std::cout << "|_)|_|||_>  (_X   \\_ (_)\\/\\/_>"<<std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter Isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// get user input and return it
FText GetValidGuess()
{
	EGuessStatus status = EGuessStatus::INVALID;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		FText Guess = "";
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		status = BCGame.CheckGuessValidity(Guess);
		switch (status) {
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a letter with no repeating characters.\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter a word, all in lower case.\n";
			break;
		default:
			break;
		}
		return Guess;
	} while (status != EGuessStatus::OK);
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again? [y/n]";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

// Start the play
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "You can try " << MaxTries << std::endl;


	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows<<"\n\n";
	}
}




