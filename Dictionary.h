//============================================================================
// Author      : Zhenia Steger
// Description : Header for Dictionary.
// ============================================================================

#ifndef DICTIONARY_H
#define DICTIONARY_H

using namespace std;

class Dictionary
{

	public:
		Dictionary();
		Dictionary(int dictMaxWords, int fileMaxWords);
		string toLowerString(string s);
		bool AddAWord(string word);
		bool DeleteAWord(string word);
		bool SearchForWord(string word);
		bool PrintAFileInDict(string fileName);
		bool SpellChecking(string fileName);
		bool InsertWordsIntoDict(string fileName);
		void ProcessTransactionFile();

	private:
		const int maxWordsInDict;
		const int maxWordsPerFile;
		int totalWordsInDict;
		int numOfWordsInFile[26];
		static bool failure;
		static bool success;
};

#endif
