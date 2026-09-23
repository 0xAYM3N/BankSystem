#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include "clsScreen.h"
#include "../Core/clsCurrency.h"

class clsListCurrenciesScreen : protected clsScreen {
private:
	static void _PrintCurrencyRecord(clsCurrency Currency) {
		std::cout << std::setw(5) << "" << "| " << std::setw(30) << std::left << Currency.Country();
		std::cout << "| " << std::setw(25) << std::left << Currency.CurrencyCode();
		std::cout << "| " << std::setw(25) << std::left << Currency.CurrencyName();
		std::cout << "| " << std::setw(10) << std::left << Currency.Rate() << "\n";
	}
public:
	static void ShowListCurrenciesScreen() {
		std::vector<clsCurrency> vCurrencies = clsCurrency::GetCurreniesList();
		std::string Title = "\t\t List Currencies Screen\n";
		std::string SubTitle = "\t    (" + std::to_string(vCurrencies.size()) + ") Currency";
		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::setw(5) << "" << "______________________________________________________________"
			"______________________________________________________________\n";
		std::cout << std::setw(5) << "" << "| " << std::left << std::setw(30) << "Country";
		std::cout << "| " << std::left << std::setw(25) << "Currency Code";
		std::cout << "| " << std::left << std::setw(25) << "Currency Name";
		std::cout << "| " << std::left << std::setw(10) << "Rate/(1$)\n";
		std::cout << std::setw(5) << "" << "______________________________________________________________"
			"______________________________________________________________\n";

		if(vCurrencies.size() == 0) {
			std::cout << std::setw(42) << "" << "No Currencies Available In the System!\n";
		}
		else {
			for(clsCurrency &Currency : vCurrencies) {
				_PrintCurrencyRecord(Currency);
			}
		}

		std::cout << std::setw(5) << "" << "______________________________________________________________"
			"______________________________________________________________\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
