#pragma once
#include <iostream>
#include "clsDate.h"

class clsUtil {
public:
	static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To) {
		int RandNum = rand() % (To - From + 1) + From;
		return RandNum;
	}

	enum enCharType { SmallLetter = 1, CapitalLetter = 2 , Digit = 3, SpecialCharacter = 4, MixChars = 5 };

	static char GetRandomCharacter(enCharType CharType) {
		switch (CharType) {
			case enCharType::SmallLetter: {
				return char(RandomNumber(97, 122));
			}
			case enCharType::CapitalLetter: {
				return char(RandomNumber(65, 90));
			}
			case enCharType::Digit: {
				return char(RandomNumber(48, 57));
			}
			case enCharType::SpecialCharacter: {
				return char(RandomNumber(33, 47));
			}
			case enCharType::MixChars: {
				enCharType RandomType = enCharType(RandomNumber(1, 3));
				return GetRandomCharacter(RandomType);
			}
			default: 
				enCharType RandomType = enCharType(RandomNumber(1, 3));
				return GetRandomCharacter(RandomType);
		}
	}

	static std::string GenerateWord(enCharType CharType, short Length) {
		std::string Word;
		for (int i = 1; i <= Length; i++) {
			Word += GetRandomCharacter(CharType);
		}
		return Word;
	}

	static std::string GenerateKey(enCharType CharType) {
		std::string Key = "";
		Key = GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4) + "-";
		Key = Key + GenerateWord(CharType, 4);
		return Key;
	}

	static void GenerateKeys(enCharType CharType, short NumberOfKeys) {
		for (int i = 1; i <= NumberOfKeys; i++) {
			std::cout << "Kay [" << i << "] : " << GenerateKey(CharType) << std::endl;
		}
	}

	static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To) {
		for (int i = 0 ; i < arrLength; i++)
			arr[i] = RandomNumber(From, To);
	}

	static void FillArrayWithRandomWords(std::string arr[100], int arrLength, enCharType CharType, short Length) {
		for (int i = 0 ; i < arrLength; i++)
			arr[i] = GenerateWord(CharType, Length);
	}

	static void FillArrayWithRandomKeys(std::string arr[100], int arrLength, enCharType CharType) {
		for (int i = 0 ; i < arrLength; i++)
			arr[i] = GenerateKey(CharType);
	}

	static void Swap(clsDate& A, clsDate& B) {
		clsDate::SwapDates(A, B);
	}

	static void Swap(int& A, int& B) {
		int Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(double& A, double& B) {
		double Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(std::string& A, std::string& B) {
		std::string Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void ShuffleArray(int arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static void ShuffleArray(std::string arr[100], int arrLength) {
		for (int i = 0; i < arrLength; i++) {
			Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
		}
	}

	static std::string EncryptText(std::string Text, short EncryptionKey = 2) {
		for (int i = 0; i <= Text.length(); i++) {
			Text[i] = char((int) Text[i] + EncryptionKey);
		}
		return Text;
	}

	static std::string DecryptText(std::string Text, short EncryptionKey = 2) {
		for (int i = 0; i <= Text.length(); i++) {
			Text[i] = char((int)Text[i] - EncryptionKey);
		}
		return Text;
	}

	static std::string Tabs(int NumberOfTabs) {
		std::string Tabs = "";
		for(int i = 0; i < NumberOfTabs; i++) {
			Tabs += "\t";
		}
		return Tabs;
	}

	static string NumberToText(int Number) {
		if (Number == 0) {
			return "";
		}

		if (Number >= 1 && Number <= 19) {
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
				"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
				"Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99) {
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199) {
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999) {
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999) {
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999) {
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999) {
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999) {
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999) {
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else {
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}
	}
};
