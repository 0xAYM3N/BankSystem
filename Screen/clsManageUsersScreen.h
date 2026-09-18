#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen : protected clsScreen {
private:
	enum enManageUsersOptions {
		ShowUsersList = 1, AddNewUsers = 2,
		DeleteUsers = 3, UpdateUsers = 4,
		FindUsers = 5, BackMainMenue = 6,
	};

	static short _ReadTransactionsMenuOption() {
		std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between [1 to 6]: ");
		return Choice;
	}

	static void _GoBackToManageUsersMenu() {
		std::cout << "\nPress Enter to go back to Manage Users Menue...";
		std::cin.get();
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen() {
		clsUsersListScreen::ShowUsersListScreen();
    }

    static void _ShowAddNewUserScreen() {
		clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUserScreen() {
		clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {
		clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {
		clsFindUserScreen::ShowFindUserScreen();
    }

	static void _PerformManageUsersOptions(enManageUsersOptions ManageUsersOptions) {
		switch(ManageUsersOptions) {
			case enManageUsersOptions::ShowUsersList:
				std::system("clear");
				_ShowListUsersScreen();
				_GoBackToManageUsersMenu();
				break;
			case enManageUsersOptions::AddNewUsers:
				std::system("clear");
				_ShowAddNewUserScreen();
				_GoBackToManageUsersMenu();
				break;
			case enManageUsersOptions::DeleteUsers:
				std::system("clear");
				_ShowDeleteUserScreen();
				_GoBackToManageUsersMenu();
				break;
			case enManageUsersOptions::UpdateUsers:
				std::system("clear");
				_ShowUpdateUserScreen();
				_GoBackToManageUsersMenu();
				break;
			case enManageUsersOptions::FindUsers:
				std::system("clear");
				_ShowFindUserScreen();
				_GoBackToManageUsersMenu();
				break;
			case enManageUsersOptions::BackMainMenue: {}
		}
	}

public:
	static void ShowManageUsersMenu() {
		if(!CheckAccessRghts(clsUser::enPermissions::pManageUsers)) {
			return;
		}

		std::system("clear");
		_DrawScreenHeader("\t\t  Manage Users Screen\n");

		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\t   Manage Users Menu\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] List Users\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Add Users \n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Users\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Update Users \n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Find Users\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";

		_PerformManageUsersOptions((enManageUsersOptions)_ReadTransactionsMenuOption());
	}
};
