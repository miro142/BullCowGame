/*This is the console executable, that makes use of the FBullCowGame class
this is where all of the interaction with the user takes place
for game logic see FBullCowGame
*/
#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"
//to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

//prototypes for the functions 
FBullCOwGame BCGame;
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
int main()
{
	do 
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		
	} while (AskToPlayAgain());
	return 0;
}
void PlayGame()
{
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries) 
	{
		Guess=GetValidGuess();
		FBullCowCount BullCowCount= BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << "\n\n";
	}
}
void PrintIntro() 
{
	BCGame.Reset();
	std::cout << "                                                                          WELCOME TO\n\n";
	std::cout <<"                            ,--,      ,--,                                                                                                                            "<< std::endl;
	std::cout <<"                         ,---.'|   ,---.'|                                             ,--.                                    ,----..                                "<< std::endl;
	std::cout <<"    ,---,.               |   | :   |   | :   .--.--.              ,---,              ,--.'|    ,---,              ,----..     /   /   \\             .---.  .--.--.    "<< std::endl;
	std::cout <<"  ,'  .'  \\         ,--, :   : |   :   : |  /  /    '.           '  .' \\         ,--,:  : |  .'  .' `\\           /   /   \\   /   .     :           /. ./| /  /    '.  "<< std::endl;
	std::cout <<",---.' .' |       ,'_ /| |   ' :   |   ' : |  :  /`. /          /  ;    '.    ,`--.'`|  ' :,---.'     \\         |   :     : .   /   ;.  \\      .--'.  ' ;|  :  /`. /  "<< std::endl;
	std::cout <<"|   |  |: |  .--. |  | : ;   ; '   ;   ; ' ;  |  |--`          :  :       \\   |   :  :  | ||   |  .`\\  |        .   |  ;. /.   ;   /  ` ;     /__./ \\ : |;  |  |--`   "<< std::endl;
	std::cout <<":   :  :  /,'_ /| :  . | '   | |__ '   | |_|  :  ;_            :  |   /\\   \\  :   |   \\ | ::   : |  '  |        .   ; /--` ;   |  ; \\ ; | .--'.  '   \\' .|  :  ;_     "<< std::endl;
	std::cout <<":   |    ; |  ' | |  . . |   | :.'||   | :.'\\  \\    `.         |  :  ' ;.   : |   : '  '; ||   ' '  ;  :        ;   | ;    |   :  | ; | '/___/ \ |    ' ' \\  \\    `.  "<< std::endl;
	std::cout <<"|   :     \\|  | ' |  | | '   :    ;'   :    ;`----.   \         |  |  ;/  \\   \\'   ' ;.    ;'   | ;  .  |        |   : |    .   |  ' ' ' :;   \\  \\;      :  `----.   \\ "<< std::endl;
	std::cout <<"|   |   . |:  | | :  ' ; |   |  ./ |   |  ./ __ \\  \\  |        '  :  | \\  \\ ,'|   | | \\   ||   | :  |  '        .   | '___ '   ;  \\; /  | \\   ;  `      |  __ \\  \\  | "<< std::endl;
	std::cout <<"'   :  '; ||  ; ' |  | ' ;   : ;   ;   : ;  /  /`--'  /        |  |  '  '--'  '   : |  ; .''   : | /  ;         '   ; : .'| \   \\  ',  /    .   \\    .\\  ; /  /`--'  / "<< std::endl;
	std::cout <<"|   |  | ; :  | : ;  ; | |   ,/    |   ,/  '--'.     /         |  :  :        |   | '`--'  |   | '` ,/          '   | '/  :  ;   :    /     \\   \\   ' \\ |'--'.     /  "<< std::endl;
	std::cout <<"|   :   /  '  :  `--'   \\'---'     '---'     `--'---'          |  | ,'        '   : |      ;   :  .'            |   :    /    \\   \\ .'       :   '  |--/   `- - '---'   "<< std::endl;
	std::cout <<"|   | ,'   :  ,      .-./                                      `--''          ;   |.'      |   ,.'               \\   \\ .'      `---`          \\   \\ ;                 "<< std::endl;
	std::cout <<"`----'      `--`----'                                                         '---'        '---'                  `---`                        '---/                  \n\n";   
	std::cout << "                                                                        A FUN WORD GAME\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking of?\n";
}
FText GetValidGuess() 
{
	FText  Guess;
	EGuessStatus Status=EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry <<" of "<<BCGame.GetMaxTries()<< ". ";
		std::cout << "Enter your guess : ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (word with no repeating letters)\n\n";
			break;
		case EGuessStatus::Invalid_Symbol:
			std::cout << "Please enter only letters\n\n";
			break;
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word that is all lowercase\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Play Again?(y/n)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	if (Response[0] == 'y'|| Response[0] == 'Y') {
		system("CLS");
		return true;
	}
	else 
		if (Response[0] == 'n' || Response[0] == 'N') {
			return false;
		}
		else std::cout << "Invalid  response!" << std::endl;
		return AskToPlayAgain();
}
void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You Win!" << std::endl;
}
	else std::cout << "Better Luck Next Time." << std::endl;
};
