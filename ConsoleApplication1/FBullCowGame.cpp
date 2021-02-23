/*The game logic.No view code or direct user interaction*/
#pragma once
#include "pch.h"
#include "FBullCowGame.h"
#include <time.h>
#include <map>
//to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

int32 FBullCOwGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCOwGame::GetHiddenWordLenght() const{return MyHiddenWord.length();}
FBullCOwGame::FBullCOwGame(){Reset(); }//default constructor
bool FBullCOwGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCOwGame::GetMaxTries() const { 
	TMap <int32, int32>WordLengthToMaxTries{ { 3,5 }, { 4, 6 }, { 5, 7 }, { 6,8 }, { 7,9 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
bool FBullCOwGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true;}//a one or 0 letter word is considered an Isogram
	TMap <char, bool> LetterSeen; // setup our map
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter] == false) { LetterSeen[Letter] = true; }
		else  return false;
		
	}
	return true;
}

FString FBullCOwGame::GetRandomWord()//generates a random word form an array of 10 preset words
{
	srand(time(NULL)); //initialize the random seed
	const FString RandomWord[10] = { "planet", "ant", "path","fish","podcast", "persian","trouble","mexican","object","cat"};
	int32 RandIndex = rand() % 10; //generates a random number between 0 and 3
	return RandomWord[RandIndex];
}

bool FBullCOwGame::IsValidSymbol(FString Guess) const
{
	if (Guess.length() < 1) { return true; }//a 0 letter word is considered valid
	for (auto Letter : Guess) {
		if (!isalpha(Letter)) {
			return false;
		}
	}
	return true;
}

bool FBullCOwGame::IsLowercase(FString Guess) const
{
	if (Guess.length() < 1) { return true; }//a 0 letter word is considered lowercase
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

void FBullCOwGame::Reset()
{
	MyHiddenWord = GetRandomWord();
	MyCurrentTry = 1;
	bGameIsWon = false;
}


FBullCowCount FBullCOwGame::SubmitValidGuess(FString Guess)
{
	int32 GuessLenght = Guess.length();
	int32 HiddenWordLenght = MyHiddenWord.length();
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	for (int32 GChar = 0; GChar < GuessLenght; GChar++) 
	{
		for (int32 MHWChar = 0; MHWChar < HiddenWordLenght; MHWChar++) 
		{
			if (Guess[GChar]==MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls== HiddenWordLenght)
	{
		bGameIsWon = true;
	}
	else { bGameIsWon = false; }
	return BullCowCount;
}

EGuessStatus FBullCOwGame::CheckGuessValidity(FString Guess) const
{
	if (!IsValidSymbol(Guess)) { //If the guess contains invalid symbols, return error
		return EGuessStatus::Invalid_Symbol;
	} else
	if (!IsIsogram(Guess)) { //If the guess isn't an Isogram, return error
		return EGuessStatus::Not_Isogram;
	}
	else
		if (!IsLowercase(Guess)) { //If the guess isn't all lowercase, return error
			return EGuessStatus::Not_Lowercase;
	}
	else 
		if (GetHiddenWordLenght()!=Guess.length()) {//If the guess is the wrong lenght
			return EGuessStatus::Wrong_Lenght;
	}
		else {//otherwise
			return EGuessStatus::OK; //return OK
		}

}


