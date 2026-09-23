#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "../Core/clsCurrency.h"

class clsFindCurrencyScreen : protected clsScreen {
private:
	static void _PrintCurrency(clsCurrency &Currency) {
		std::cout << "\nCurrency Card:";
		std::cout << "\n_________________________";
		std::cout << "\nCountry       : " << Currency.Country();
		std::cout << "\nCurrency Code : " << Currency.CurrencyCode();
		std::cout << "\nCurrency Name : " << Currency.CurrencyName();
		std::cout << "\nRate          : " << Currency.Rate();
		std::cout << "\n_________________________\n";
	}

	static void _ShowResult(clsCurrency Currency)  {
		if (!Currency.IsEmpty()) {
			std::cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		} else {
			std::cout << "\nCurrency Was not Found :-(\n";
		}
	}
public:
	static void ShowFindUserScreen() {
		_DrawScreenHeader("\t\t  Find Currency Screen\n");

		std::cout << "Find By: [1] Code or [2] Country: ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 2, "Enter Number Between 1 and 2: ");

		if(Choice == 1) {
			std::string CurrencyCode = "";
			std::cout << "Enter Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResult(Currency);
		}
		if(Choice == 2) {
			std::string Country = "";
			std::cout << "Enter Currency Country: ";
			Country = clsInputValidate::ReadString();

			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
	}
};
