#pragma once
#include "clsDate.h"
#include <limits>

class clsInputValidate {
public:
	static bool IsNumberBetween(int Number, int From, int To) {
		if(Number >= From && Number <= To) {
			return true;
		}
		return false;
	}

	static bool IsNumberBetween(double Number, double From, double To) {
		if(Number >= From && Number <= To) {
			return true;
		}
		return false;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {
		//Date>=From && Date<=To
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)) &&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))) 
		{
			return true;
		}

		//Date>=To && Date<=From
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)) &&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)))
		{
			return true;
		}

		return false;
	}

	static std::string ReadString() {
		std::string str;
		getline(cin >> ws, str);
		return str;
	}

	static int ReadIntNumber(std::string ErrMsg="Invalid Number, Enter again: ") {
		int Number;
		std::cin >> Number;
		while(cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << ErrMsg;
			std::cin >> Number;
		}
		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, std::string ErrMsg)  {
		int Number = ReadIntNumber();
		while(!IsNumberBetween(Number, From, To)) {
			std::cout << ErrMsg;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, std::string ErrMsg)  {
		short Number = ReadIntNumber();
		while(!IsNumberBetween(Number, From, To)) {
			std::cout << ErrMsg;
			Number = ReadIntNumber();
		}
		return Number;
	}

	static double ReadDblNumber(std::string ErrMsg="Invalid Number, Enter again\n") {
		double Number;
		std::cin >> Number;
		while(cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << ErrMsg;
			std::cin >> Number;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, std::string ErrMsg) {
		double Number = ReadDblNumber();
		while(Number < From || Number > To) {
			std::cout << ErrMsg;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static float ReadFloatNumber(std::string ErrMsg="Invalid Number, Enter again\n") {
		float Number;
		std::cin >> Number;
		while(cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << ErrMsg;
			std::cin >> Number;
		}
		return Number;
	}

	static bool IsValidDate(clsDate Date) {
		return clsDate::IsValidDate(Date);
	}
};
