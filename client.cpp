//============================================================================
// Author      : Zhenia Steger
// Purpose     : Creates a dictionary from an input file. Separates all of the
//                words in the file into individual files creating a searchable
//                dictionary.
// Input       : Takes a text file as input to create a dictionary.
//                This is preferably an essay which can later be spell checked.
//
// Instructions: Transaction file can do the following things:
//        AddW - adds a word to the dictinary
//        DeleteW - deletes a word from the dictionary
//        InsertF - inserts the supplied file into the dictionary provided
//                the size of the words in the file do not exceed the
//                size of the dictionary.
//        PrintF - prints one of the files in the dictionary; ex. A.txt
//        SearchW - returns bool value if the word is in the dictionary
//        SpellCheck - spell checks the supplied file agains the dictionary
//                If the file is not in the dictionary then it is
//                misspelled. (not a real spellcheck here)
//
// Compiler    : g++
// ============================================================================

#include "Dictionary.h"

using namespace std;

int main()
{
  Dictionary dict;
  dict.ProcessTransactionFile();
  return 0;
}
