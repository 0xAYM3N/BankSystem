#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen {
private:
	enum enTransactionMenuOptions {
		Deposit = 1, Withdraw = 2,
		TotalBalance = 3, Transfer = 4,
		TransferLog = 5, MainMenu = 6,
	};

	static short _ReadTransactionsMenuOption() {
		std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between [1 to 6]: ");
		return Choice;
	}

	static void _ShowDepositScreen() {
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithdrawScreen() {
		clsWithrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen() {
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen() {
		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen() {
		clsTransferLogScreen::ShowTransferLogScreen();
	}

	static void _GoBackToTransactionsMenu() {
		std::cout << "\nPress Enter to go back to Transactions Menu...";
		std::cin.get();
		ShowTransactionsMenu();
	}

	static void _PerformTransactionOption(enTransactionMenuOptions TransactionMenuOption) {
		switch(TransactionMenuOption) {
			case enTransactionMenuOptions::Deposit:
				std::system("clear");
				_ShowDepositScreen();
				_GoBackToTransactionsMenu();
				break;
			case enTransactionMenuOptions::Withdraw:
				std::system("clear");
				_ShowWithdrawScreen();
				_GoBackToTransactionsMenu();
				break;
			case enTransactionMenuOptions::TotalBalance:
				std::system("clear");
				_ShowTotalBalancesScreen();
				_GoBackToTransactionsMenu();
				break;
			case enTransactionMenuOptions::Transfer:
				std::system("clear");
				_ShowTransferScreen();
				_GoBackToTransactionsMenu();
				break;
			case enTransactionMenuOptions::TransferLog:
				std::system("clear");
				_ShowTransferLogScreen();
				_GoBackToTransactionsMenu();
				break;
			case enTransactionMenuOptions::MainMenu: {}
		}
	}

public:
	static void ShowTransactionsMenu() {
		if(!CheckAccessRghts(clsUser::enPermissions::pTransactions)) {
			return;
		}

		std::system("clear");
		_DrawScreenHeader("\t\t  Transaction Screen\n");

		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t\t  Transactions Menu\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";
		std::cout << std::setw(37) << std::left << "" << "\t[1] Deposit.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[2] Withdraw.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[3] Total Balance.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[4] Transfer.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[5] Transfer Log.\n";
		std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
		std::cout << std::setw(37) << std::left << "" << "==============================================\n";

		_PerformTransactionOption((enTransactionMenuOptions)_ReadTransactionsMenuOption());
	}
};
