#pragma once
#include <string>

using FString = std::string;
using int32 = int;
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};
enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Invalid_Symbol,
	Wrong_Lenght,
	Not_Lowercase,
};
class FBullCOwGame
{
	public:
		FBullCOwGame();
		int32 GetMaxTries() const;
		int32 GetCurrentTry() const;
		int32 GetHiddenWordLenght() const;
		bool IsGameWon() const;
		FBullCowCount SubmitValidGuess(FString);
		void Reset();
		EGuessStatus CheckGuessValidity(FString) const;
	private:
		FString GetRandomWord();
		bool IsValidSymbol(FString) const;
		bool IsLowercase(FString) const;
		bool IsIsogram(FString) const;
		int32 MyCurrentTry;
		int32 MyMaxTries;
		FString MyHiddenWord;
		bool bGameIsWon;
};