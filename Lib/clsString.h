#pragma once
#include <iostream>
#include <cctype>
#include <vector>

class clsString {
private:
	std::string _Value;
	std::vector<std::string> vStr;
public:
	clsString() {
		_Value = "";
	}

	clsString(std::string Value) {
		_Value = Value;
	}

	void SetValue(std::string Value) {
		_Value = Value;
	}

	std::string GetValue() {
		return _Value;
	}

	static int Length(std::string str) {
		return str.length();
	}

	int Length() {
		return Length();
	}

	static void PrintFirstLetterOfEachWord(std::string str) {
		bool isFirstLetter = true;
		for(int i = 0; i < str.length(); ++i) {
			if(str[i] != ' ' && isFirstLetter) {
				std::cout << str[i] << " ";
			}
			isFirstLetter = (str[i] == ' ' ? true : false);
		}
	}

	void PrintFirstLetterOfEachWord() {
		PrintFirstLetterOfEachWord(_Value);
	}

	static std::string UpperFirstLetterOfEachWord(std::string str) {
		bool isFirstLetter = true;
		for(int i = 0; i < str.length(); ++i) {
			if(str[i] != ' ' && isFirstLetter) {
				str[i] = toupper(str[i]);
			}
			isFirstLetter = (str[i] == ' ' ? true : false);
		}
		return str;
	}

	void UpperFirstLetterOfEachWord() {
		_Value =  UpperFirstLetterOfEachWord(_Value);
	}

	static std::string LowerFirstLetterOfEachWord(std::string str) {
		bool isFirstLetter = true;
		for(int i = 0; i < str.length(); ++i) {
			if(str[i] != ' ' && isFirstLetter) {
				str[i] = tolower(str[i]);
			}
			isFirstLetter = (str[i] == ' ' ? true : false);
		}
		return str;
	}

	void LowerFirstLetterOfEachWord() {
		_Value =  LowerFirstLetterOfEachWord(_Value);
	}

	static std::string UpperAllLetters(std::string str) {
		for(int i = 0; i < str.length(); ++i) {
			str[i] = toupper(str[i]);
		}
		return str;
	}

	void UpperAllLetters() {
		_Value = UpperAllLetters(_Value);
	}

	static std::string LowerAllLetters(std::string str) {
		for(int i = 0; i < str.length(); ++i) {
			str[i] = tolower(str[i]);
		}
		return str;
	}

	void LowerAllLetters() {
		_Value = LowerAllLetters(_Value);
	}

	static char InvertCharacterCase(char Char) {
		return isupper(Char) ? tolower(Char) : toupper(Char);
	}

	static std::string InvertAllLettersCase(std::string str) {
		for(int i = 0; i < str.length(); ++i) {
			str[i] = InvertCharacterCase(str[i]);
		}
		return str;
	}

	void InvertAllLettersCase() {
		_Value =  InvertAllLettersCase(_Value);
	}

	static short CpaitalLettersCount(std::string str) {
		short counter = 0;
		for(short i = 0; i < str.length(); ++i) {
			if(isupper(str[i])) {
				counter++;
			}
		}
		return counter;
	}

	short CpaitalLettersCount() {
		return CpaitalLettersCount(_Value);
	}

	static short SmallLettersCount(std::string str) {
		short counter = 0;
		for(short i = 0; i < str.length(); ++i) {
			if(islower(str[i])) {
				counter++;
			}
		}
		return counter;
	}

	short SmallLettersCount() {
		return SmallLettersCount(_Value);
	}

	enum enWhatToCount { 
		CapitalLetters = 1, 
		SmallLetters = 2, 
		All = 3 
	};

	static short CountLetters(std::string str, enWhatToCount WhatToCount = enWhatToCount::All) {
		if(WhatToCount == enWhatToCount::All) {
			return str.length();
		}

		short counter = 0;
		for(int i = 0; i < str.length(); ++i) {
			if(WhatToCount == enWhatToCount::CapitalLetters && isupper(str[i])) {
				counter++;
			}

			if(WhatToCount == enWhatToCount::SmallLetters && islower(str[i])) {
				counter++;
			}
		}
		return counter;
	}

	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All) {
		return CountLetters(_Value);
	}

	static short LetterCount(std::string str, char Letter) {
		short Count = 0;
		for(short i = 0; i < str.length(); ++i) {
			if(str[i] == Letter) {
				Count++;
			}
		}
		return Count;
	}

	short LetterCount(char Char) {
		return LetterCount(_Value, Char);
	}

	static short CountSpecificLetter(std::string str, char Letter, bool MatchCase = true) {
		short Counter = 0;
		for(short i = 0; i < str.length(); ++i) {
			if(MatchCase) {
				if(str[i] == Letter) {
					Counter++;
				}
			} else {
				if(tolower(str[i]) == tolower(Letter)) {
					Counter++;
				}
			}
		}
		return Counter;
	}

	short CountLetters(char Char) {
		return CountSpecificLetter(_Value, Char);
	}

	static bool isVowel(char Letter) {
		Letter = tolower(Letter);
		return (Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u');
	}

	static short CountVowel(std::string str) {
		short Counter = 0;
		for(short i = 0; i < str.length(); ++i) {
			if(isVowel(str[i])) {
				Counter++;
			}
		}
		return Counter;
	}

	short CountVowel() {
		return CountVowel(_Value);
	}

	static void PrintVowels(std::string str) {
		for(short i = 0; i < str.length(); ++i) {
			if(isVowel(str[i])) {
				std::cout << str[i] << "   ";
			}
		}
	}

	void PrintVowels() {
		PrintVowels(_Value);
	}

	static void PrintEachWord(std::string str) {
		std::string delim = " ";
		short pos = 0;
		std::string Word;

		while((pos = str.find(delim)) != std::string::npos) {
			Word = str.substr(0, pos);
			if(Word != "") {
				std::cout << Word << std::endl;
			}

			str.erase(0, pos + delim.length());
		}
		if(str != "") {
			std::cout << str << std::endl;
		}
	}

	void PrintEachWord() {
		return PrintEachWord(_Value);
	}

	static short CountWords(std::string str) {
		std::string delim = " ";
		short Counter = 0;
		short pos = 0;
		std::string Word;

		while((pos = str.find(delim)) != std::string::npos) {
			Word = str.substr(0, pos);
			if(Word != "") {
				Counter++;
			}

			str.erase(0, pos + delim.length());
		}
		if(str != "") {
			Counter++;
		}
		return Counter;
	}

	short CountWords() {
		return CountWords(_Value);
	}

	static std::vector<std::string> Split(std::string str, std::string delim) {
		std::vector<std::string> vStr;
		short pos = 0;
		std::string Word;

		while((pos = str.find(delim)) != std::string::npos) {
			Word = str.substr(0, pos);
			vStr.push_back(Word);

			str.erase(0, pos + delim.length());
		}
		if(str != "") {
			vStr.push_back(str);
		}

		return vStr;
	}

	std::vector<std::string> Split(std::string delim) {
		return Split(_Value);
	}


	static void PrintVectorElement(std::vector<std::string> vStr) {
		for(std::string &Word : vStr) {
			std::cout << Word << std::endl;
		}
	}

	void PrintVectorElement() {
		return PrintVectorElement(vStr);
	}

	std::string TrimLeft(std::string str) {
		for(short i = 0; i < str.length(); ++i) {
			if(str[i] != ' ') {
				return str.substr(i, str.length() -1);
			}
		}
		return "";
	}

	std::string TrimLeft() {
		return TrimLeft(_Value);
	}

	std::string TrimRight(std::string str) {
		for(short i = str.length() - 1; i >= 0; --i) {
			if(str[i] != ' ') {
				return str.substr(0, i + 1);
			}
		}
		return "";
	}

	std::string TrimRight() {
		return TrimRight(_Value);
	}

	std::string Trim(std::string str) {
		return TrimLeft(TrimRight(str));
	}


	static std::string JoinString(std::vector<std::string> vStr, std::string delim) {
		std::string str = "";
		for(std::string &word : vStr) {
			str += word + delim;
		}

		return str.substr(0, str.length() - delim.length());
	}

	static std::string JoinString(std::string arrStr[], short length, std::string delim) {
		std::string str = "";
		for(short i = 0; i < length; ++i) {
			str += arrStr[i] + delim;
		}

		return str.substr(0, str.length() - delim.length());
	}

	static std::string ReverseWordsInString(std::string str) {
		std::vector<std::string> vStr;
		std::string str2 = "";

		vStr = Split(str, " ");

		std::vector<std::string>::iterator iter = vStr.end();

		while(iter != vStr.begin()) {
			--iter;
			str2 += *iter + " ";
		}

		str2 = str2.substr(0, str2.length() - 1); // remove last space

		return str2;
	}

	std::string ReverseWordsInString() {
		return ReverseWordsInString(_Value);
	}
	
	static std::string ReplaceWord(std::string str, std::string Word, std::string NewWord) {
		short pos = str.find(Word);

		while(pos != std::string::npos) {
			str = str.replace(pos, Word.length(), NewWord);
			pos = str.find(Word);
		}
		return str;
	}

	std::string ReplaceWord(std::string Word, std::string NewWord) {
		return ReplaceWord(_Value, Word, NewWord);
	}

	std::string LowerAllString(std::string Word) {
		for(short i = 0; i < Word.length(); ++i) {
			Word[i] = tolower(Word[i]);
		}
		return Word;
	}

	std::string ReplaceWordMatchCase(std::string str, std::string StringToReplace, std::string ReplaceTo, bool MatchCase) {
		std::vector<std::string>vStr = Split(str, " ");

		for(std::string &Word : vStr) {
			if(MatchCase) {
				if(Word == StringToReplace) {
					Word = ReplaceTo;
				}
			} else { 
				if (LowerAllString(Word) == LowerAllString(StringToReplace)) {
					Word = ReplaceTo;
				}
			} 
		}
		return JoinString(vStr, " ");
	}

	std::string ReplaceWordMatchCase(std::string Word, std::string NewWord, bool MatchCase) {
		return ReplaceWordMatchCase(_Value, Word, NewWord, MatchCase);
	}

	static std::string RemovePunct(std::string str) {
		std::string str2 = "";
		for(short i = 0; i < str.length(); ++i) {
			if(!ispunct(str[i])) {
				str2 += str[i];
			}
		}

		return str2;
	}

	std::string RemovePunct() {
		return RemovePunct(_Value);
	}
};
