#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsClientsListScreen.h"
#include "../Lib/clsInputValidate.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExhangeScreen.h"
#include "../Core/clsGlobal.h"

class clsMainScreen : protected clsScreen{
private:
	enum enMainMenuOptions {
		ListClients = 1, AddNewClient = 2,
		DeleteClient = 3, UpdateClient = 4,
		FindClient = 5, Transactions = 6,
		ManageUsers = 7, LoginRegister = 8,
		CurrencyExchange = 9, Exit = 10,
	};

	static short _ReadMainMenuOption() {
		std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 10]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Number between [1 to 10]: ");
		return Choice;
	}

	static void _GoBackToMainMenu() {
		std::cout << "\nPress Enter to go back to Main Menue...";
		std::cin.get();
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen() {
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen() {
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen() {
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu() {
		clsTransactionsScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenu() {
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _ShowCurrencyExchangeMenu() {
		clsCurrencyExhangeScreen::ShowCurrencyExhangeMenu();
	}

	static void _ShowLoginRegister() {
		clsLoginRegister::ShowLoginRegisterScreen();
	}

	static void _Logout() {
		CurrentUser = clsUser::Find("", "");
		// NOTE: Using this method to go to login screen
		// after logout makes (Circular Reference) ⚠️
		// clsLoginScreen::ShowLoginScreen();
	}

	static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption) {
		switch(MainMenuOption) {
			case enMainMenuOptions::ListClients:
				std::system("clear");
				_ShowAllClientsScreen();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::AddNewClient:
				std::system("clear");
				_ShowAddNewClientsScreen();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::DeleteClient:
				std::system("clear");
				_ShowDeleteClientScreen();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::UpdateClient:
				std::system("clear");
				_ShowUpdateClientScreen();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::FindClient:
				std::system("clear");
				_ShowFindClientScreen();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::Transactions:
				std::system("clear");
				_ShowTransactionsMenu();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::ManageUsers:
				std::system("clear");
				_ShowManageUsersMenu();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::LoginRegister:
				std::system("clear");
				_ShowLoginRegister();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::CurrencyExchange:
				std::system("clear");
				_ShowCurrencyExchangeMenu();
				_GoBackToMainMenu();
				break;
			case enMainMenuOptions::Exit:
				std::system("clear");
				_Logout();
				break;
		}
	}

public:
	static void ShowMainMenu() {
		std::system("clear");
		_DrawScreenHeader("\t\t       Main Screen\n");

		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\t\tMain Menu\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] Show Client List.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Add New Client.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Client.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Update Client Info.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Transactions.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[7] Manage Users.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[8] Login Register.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[9] Currency Exchange.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[10] Logout.\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";

		_PerfromMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}
};
