#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

class clsCurrencyExhangeScreen : protected clsScreen {
private:
	enum enCurrencyExchangeMenuOptions {
		ListCurrencies = 1, FindCurrency = 2,
		UpdateRate = 3, CurrencyCalculator = 4,
		MainMenu = 5,
	};

	static short _ReadCurrencyExchangeMenuOption() {
		std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between [1 to 5]: ");
		return Choice;
	}

	static void _ShowListCurrenciesScreen() {
		clsListCurrenciesScreen::ShowListCurrenciesScreen();
	}

	static void _ShowFindCurrencyScreen() {
		clsFindCurrencyScreen::ShowFindUserScreen();
	}

	static void _ShowUpdateCurrencyRateScreen() {
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen() {
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
		std::cout << "4";
	}

	static void _GoBackToCurrencyExchnageMenu() {
		std::cout << "\nPress Enter to go back to Currency Exchange Menu...";
		std::cin.get();
		ShowCurrencyExhangeMenu();
	}

	static void _PerformCurrencyExchangeOption(enCurrencyExchangeMenuOptions CurrencyExchangeMenuOption) {
		switch(CurrencyExchangeMenuOption) {
			case enCurrencyExchangeMenuOptions::ListCurrencies:
				std::system("clear");
				_ShowListCurrenciesScreen();
				_GoBackToCurrencyExchnageMenu();
				break;
			case enCurrencyExchangeMenuOptions::FindCurrency:
				std::system("clear");
				_ShowFindCurrencyScreen();
				_GoBackToCurrencyExchnageMenu();
				break;
			case enCurrencyExchangeMenuOptions::UpdateRate:
				std::system("clear");
				_ShowUpdateCurrencyRateScreen();
				_GoBackToCurrencyExchnageMenu();
				break;
			case enCurrencyExchangeMenuOptions::CurrencyCalculator:
				std::system("clear");
				_ShowCurrencyCalculatorScreen();
				_GoBackToCurrencyExchnageMenu();
				break;
			case enCurrencyExchangeMenuOptions::MainMenu: {}
		}
	}
public:
	static void ShowCurrencyExhangeMenu() {
		std::system("clear");
		_DrawScreenHeader("\t\t Currency Exchange Screen\n");

		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\t  Currency Exchange Menu\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] List Currencies.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Find Currency.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Update Rate.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Currency Calculator.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";

		_PerformCurrencyExchangeOption((enCurrencyExchangeMenuOptions)_ReadCurrencyExchangeMenuOption());
	}
};
