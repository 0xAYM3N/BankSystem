#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Core/clsCurrency.h"
#include "../Lib/clsInputValidate.h"

class clsCurrencyCalculatorScreen : protected clsScreen {
private:
	static float _ReadAmount() {
		float Amount = 0;
		std::cout << "\nEnter Amount to Exchange: ";
		Amount = clsInputValidate::ReadFloatNumber();
		return Amount;
	}

	static void _PrintCurrencyCard(clsCurrency &Currency, std::string Title = "Currency Card") {
		std::cout << "\n" << Title;
		std::cout << "\n_________________________";
		std::cout << "\nCountry       : " << Currency.Country();
		std::cout << "\nCurrency Code : " << Currency.CurrencyCode();
		std::cout << "\nCurrency Name : " << Currency.CurrencyName();
		std::cout << "\nRate(1$)      : " << Currency.Rate();
		std::cout << "\n_________________________\n";
	}

	static clsCurrency _GetCurrency(std::string msg) {
		std::string CurrencyCode = "";
		std::cout << msg;
		CurrencyCode = clsInputValidate::ReadString();

		while(!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			std::cout << "Currency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCalclulationResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo) {
		float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
		std::cout << "\nConvert from";
		_PrintCurrencyCard(CurrencyFrom, "Convert From:");

		std::cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " USD" << std::endl;

		if(CurrencyTo.CurrencyName() == "USD") {
			return;
		}

		std::cout << "Convert from USD to:\n";
		_PrintCurrencyCard(CurrencyTo, "To");
		
		float AmountInCurrencyTo = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);

		std::cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = "
			<< AmountInCurrencyTo << CurrencyTo.CurrencyCode() << " " << std::endl;
	}
public:
	static void ShowCurrencyCalculatorScreen() {
		char Continue = 'Y';
		while(toupper(Continue) == 'Y') {
			std::system("clear");
			_DrawScreenHeader("\t\t Currency Calc Screen\n");

			clsCurrency CurrencyFrom = _GetCurrency("\nEnter Currency1 Code: ");
			clsCurrency CurrencyTo = _GetCurrency("\nEnter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalclulationResults(Amount, CurrencyFrom, CurrencyTo);

			std::cout << "\nDo You Want to perform another calulation [Y/n]: ";
			std::cin >> Continue;
		}
	}
};
