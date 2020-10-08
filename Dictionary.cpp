//============================================================================
// Author      : Zhenia Steger
// Description : Class to create and manipilate words in the dictionary.
// ============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Dictionary.h"

using namespace std;

#define MAXWORDS 10000
#define WORDSPERFILE 100

bool Dictionary::failure = false; // returns from methods
bool Dictionary::success = true; // returns from methods

// PURPOSE: Default constructor
// PARAMETERS: Sets maxWordsInDict and maxWordsPerFile
// Creates a dictionary with 10000 words max and 100 words per file
Dictionary::Dictionary() : maxWordsInDict(MAXWORDS), maxWordsPerFile(WORDSPERFILE)
{
    totalWordsInDict = 0;
    for(int i = 0; i < 26; i++)
        numOfWordsInFile[i] = 0; // Referring to A.txt to Z.txt
}

// PURPOSE: Constructor with params
// PARAMETERS: dictMaxWords is the amount of words in the dictionary
//    fileMaxWords is the amount of words in the file
Dictionary::Dictionary(int dictMaxWords, int fileMaxWords) : maxWordsInDict(dictMaxWords), maxWordsPerFile(fileMaxWords)
{
    totalWordsInDict = 0;
    for(int i = 0; i < 26; i++)
        numOfWordsInFile[i] = 0; // Referring to A.txt to Z.txt
}

// PURPOSE: Adds a word to dictionary
// PARAMETERS: word - the word to be added
bool Dictionary::AddAWord(string word)
{
    word = toLowerString(word);
    ofstream data;
    if(!data)
        return Dictionary::failure;
    if(SearchForWord(word) == success)	// if already in dictionary
        return Dictionary::failure;
    else
    {
        totalWordsInDict++;
            if(totalWordsInDict > maxWordsInDict)
              return Dictionary::failure;				// if size is exceeded

        numOfWordsInFile[word[0] - 'a']++;
            if(numOfWordsInFile[word[0] - 'a'] > maxWordsPerFile)
                return Dictionary::failure;				// if size is exceeded

        string fileName = "#.txt";
        fileName[0] = toupper(word[0]);
        data.open(fileName.data(), ios::app);			// opens in append mode
        data << word << endl;
        data.close();

        return Dictionary::success;
    }
}

// PURPOSE: Deletes a word from the dictionary
// PARAMETERS: word - the word to be deleted
bool Dictionary::DeleteAWord(string word)
{
    vector<string> fileWords;
    ifstream fin;
    ofstream outToFile;
    string wordInFile;

    word = toLowerString(word);
    string fileName = "#.txt";
    fileName[0] = toupper(word[0]);
    fin.open(fileName.data());

    if(!fin)
        return Dictionary::failure;

    if(SearchForWord(word) == failure)		// if not found in the dictionary
      return Dictionary::failure;

    fin >> wordInFile;
    while(fin)
    {
      if(wordInFile == word)
        {
            totalWordsInDict--;
            numOfWordsInFile[word[0] - 'a']--;
        }
      else
        {
            fileWords.push_back(wordInFile);		// push to vector if not the word
        }
        fin >> wordInFile;
    }

    outToFile.open(fileName.data());
    for(int i = 0; i < fileWords.size(); i++)
      {
        outToFile << fileWords[i] << endl;
      }
    fin.close();
    outToFile.close();
    return Dictionary::success;
}

// PURPOSE: Searches for a word in the file
// PARAMETERS: word - the word we are searching for
bool Dictionary::SearchForWord(string word)
{
  string wordIn;
  ifstream data;
  word = toLowerString(word);
  string fileName = "#.txt";
  fileName[0] = toupper(word[0]);

  if(!data)
      return Dictionary::failure;

  data.open(fileName.data());

  data >> wordIn;
  while(data)
  {
    if(wordIn == word)
    {
      data.close();
        return Dictionary::success; // if the word is found
    }
  data >> wordIn;
  }
  return Dictionary::failure; // if the word is not found
}

// PURPOSE: Prints a file in the dictionary
// PARAMETERS: fileName - the file to be printed to the screen
bool Dictionary::PrintAFileInDict(string fileName)
{
    ifstream data;
    string wordIn;

    data.open(fileName.data());
    if(!data)
        return Dictionary::failure;

    data >> wordIn;
    while(data)
    {
      cout << wordIn << endl;
      data >> wordIn;
    }
    data.close();
    return Dictionary::success;
}

// PURPOSE: Spell checks the dictionary
// PARAMETERS: fileName - the name of the file to be spell-checked
bool Dictionary::SpellChecking(string fileName)
{
  ifstream data;
  data.open(fileName.data());
  if(!data)
    return Dictionary::failure;
  string word;

  data >> word;
  while(data)
  {
    if(SearchForWord(word) == false)
      cout << "Mis-spelled: " << word << endl;
      data >> word;
  }
  return Dictionary::success;
}

// PURPOSE: Inserts words into the dictionary
// PARAMETERS: fileName - the name of the file to be imported into the dictionary
bool Dictionary::InsertWordsIntoDict(string fileName)
{
  ifstream fin;
  fin.open(fileName.data());

  if(!fin)
      return Dictionary::failure;

  string word;

  while(fin)
  {
    fin >> word;
    if(SearchForWord(word) == failure)
      AddAWord(word);
  }
  fin.close();
  return Dictionary::success;
}

// PURPOSE: Processes the transaction file for commands and data
// PARAMETERS: none
void Dictionary::ProcessTransactionFile()
{
  ifstream fin;
  fin.open("transactionFile.txt");

  if(!fin)
  {
    cout << "The file does not exist." << endl;
  }
  string action;
  string data;
  fin >> action >> data;
  while(fin)
  {

  if(action == "AddW") // if adding a word
  {
    cout << "Adding Word: " << data << endl;
    AddAWord(data);
  }
  else if(action == "DeleteW") // if deleting a word
      {
        cout << "Deleting Word: " << data << endl;
        DeleteAWord(data);
      }
      else if(action == "SearchW") // if searching for a word
      {
          cout << "Searching for word: " << data;
          bool found;
          found = SearchForWord(data);
          if(found == true)
              cout << "		Word was found!" << endl;
          if(found == false)
          cout << "		Word was not found." << endl;

      }
      else if(action == "InsertF")						// if inserting a file
      {
          cout << "Inserting words from file " << data << endl;
          InsertWordsIntoDict(data);
      }
      else if(action == "PrintF")							// if printing a file
      {
          cout << endl << "=====================" << endl;
          cout << "Printing file " << data << endl;
          PrintAFileInDict(data);
          cout << "=====================" << endl << endl;
      }
      else if(action == "SpellCheck")						// if spell checking a file
      {
          cout << "Spell Checking file " << data << endl;
          SpellChecking(data);
      }
      else 												// if the command is a mystery
      {
          cout << "I dont know what to do with this line." << endl;
      }
      fin >> action >> data;
  }
  fin.close();
}

// PURPOSE: Converts words to lower case
// PARAMETES: s - the string to be made lower case
string Dictionary::toLowerString(string s)
{
    for(int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

// END OF DICTIONARY.CPP
