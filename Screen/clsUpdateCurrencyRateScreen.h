#pragma once
#include <iostream>
#include <limits>
#include "clsScreen.h"
#include "../Core/clsCurrency.h"
#include "../Lib/clsInputValidate.h"

class clsUpdateCurrencyRateScreen : protected clsScreen {
private:
	static float _ReadRate(clsCurrency &Currency) {
		std::cout << "\nEnter New Rate: ";
		float NewRate = 0;
		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

	static void _PrintCurrency(clsCurrency &Currency) {
		std::cout << "\nCurrency Card:";
		std::cout << "\n_________________________";
		std::cout << "\nCountry       : " << Currency.Country();
		std::cout << "\nCurrency Code : " << Currency.CurrencyCode();
		std::cout << "\nCurrency Name : " << Currency.CurrencyName();
		std::cout << "\nRate          : " << Currency.Rate();
		std::cout << "\n_________________________\n";
	}
public:
	static void ShowUpdateCurrencyRateScreen() {
		_DrawScreenHeader("\t\t Update Currency Rate Screen\n");

		std::string CurrencyCode = "";
		std::cout << "Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while(!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			std::cout << "Currency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		char Answer = 'n';
		std::cout << "\nAre You Sure You Want to update currency rate [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			std::cout << "\n\nUpdate Currency Info:\n";
			std::cout << "___________________\n";

			Currency.UpdateRate(_ReadRate(Currency));
			std::cout << "\nCurrency Reat Updated Successfuly :)\n";
			_PrintCurrency(Currency);
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};

