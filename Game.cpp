#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <string>
#include <iomanip> 

using namespace std;

const string PATH = "C:\\Users\\Caesar\\Desktop\\wordlist.json";
fstream wordsFile;

void printHangman(unsigned int tries)
{
	if (tries == 1)
	{
		cout << "|----" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
	}
	else if (tries == 2)
	{
		cout << "|----" << endl;
		cout << "|   |" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
	}
	else if (tries == 3)
	{
		cout << "|----" << endl;
		cout << "|   |" << endl;
		cout << "|   O" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
	}
	else if (tries == 4)
	{
		cout << "|----" << endl;
		cout << "|   |" << endl;
		cout << "|   O" << endl;
		cout << "|   |" << endl;
		cout << "|    " << endl;
	}
	else if (tries == 5)
	{
		cout << "|----  " << endl;
		cout << "|   |  " << endl;
		cout << "|   O  " << endl;
		cout << "|  /|  " << endl;
		cout << "|" << endl;
	}
	else if (tries == 6)
	{
		cout << "|----  " << endl;
		cout << "|   |  " << endl;
		cout << "|   O  " << endl;
		cout << "|  /|\\" << endl;
		cout << "|      " << endl;
	}
	else if (tries == 7)
	{
		cout << "|----  " << endl;
		cout << "|   |  " << endl;
		cout << "|   O  " << endl;
		cout << "|  /|\\" << endl;
		cout << "|  /   " << endl;
	}
	else
	{
		cout << "|----  " << endl;
		cout << "|   |  " << endl;
		cout << "|   O  " << endl;
		cout << "|  /|\\" << endl;
		cout << "|  / \\" << endl;
	}

	cout << "\n\n" << endl;
}

void readWords(vector<string>& words) {
	
	string word;

	wordsFile.open(PATH.c_str());
	while (wordsFile >> word) {
		words.push_back(word);
	}

	wordsFile.close();
}

string choosingWord(vector<string>& words) {

	srand(time(NULL));

	int randomNumber = rand() % words.size();

	return  words.at(randomNumber);
}

bool checkIfLetterExists(string word, char c)
{
	short length = word.length();
	for (short i = 0; i < length; i++)
		if (word[i] == c) return true;
	return false;
}

int main() {
	
	vector<string> words;

	set<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	set<char> usedCharacters;

	readWords(words);

	cout << setw(10) << "WELCOME TO THE HANGMAN GAME!\n";
	
	string word = choosingWord(words), secretWord;
	word = word.substr(1, word.size() - 3);

	short letters = word.size(), guessedCharacters = 1;
	short tries = 0;

	secretWord = string(word.size(), '_');
		
	
	// cout << word << endl;
	cout << "Your word has " << letters << " letters in it." << endl;

	for (short i = 0; i < letters; i++)
		cout << secretWord[i] << ' ';

	cout << "\n\n" << endl;

	char guessCharacter;
	do
	{
		if (guessedCharacters == letters)
		{
			cout << "YOU HAVE WON!";
			break;
		}
		try
		{
			cin >> guessCharacter;
			
			if (guessCharacter >= 65 && guessCharacter <= 90)
			{
				guessCharacter += 32;
			}
			if(usedCharacters.find(guessCharacter) != usedCharacters.end()) cout << "YOU HAVE ALREADY USED THIS CHARACTER!\n";
			else if (alphabet.find(guessCharacter) != alphabet.end())
			{
					if (checkIfLetterExists(word, guessCharacter))
					{
						for (short i = 0; i < letters; i++)
							if (guessCharacter == word[i]) secretWord[i] = guessCharacter;
						cout << "Nice! You have found a character that exists in the word. \n";
						for (short i = 0; i < letters; i++)
							cout << secretWord[i] << ' ';
						cout << "\n\n";
						guessedCharacters++;
					}
					else
					{
						tries++;
						printHangman(tries);
						for (short i = 0; i < letters; i++)
							cout << secretWord[i] << ' ';
						cout << "\n\n";
						//cout << tries << endl;
					}
					usedCharacters.insert(guessCharacter);
			}
			else throw guessCharacter;

		}
		catch (char guessCharacter)
		{
			cout << "This is not a valid input. Try again!\n";
		}

	} while (tries != 8 || guessedCharacters == letters);

	if (tries >= 8)
	{
		cout << setw(8) << "YOU HAVE LOST! \n";
		cout << "Word was " << word;
	}

	return 0;
}