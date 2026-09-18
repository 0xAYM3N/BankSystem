#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "../Core/clsBankClient.h"

class clsTransferScreen : protected clsScreen {
private:
	static std::string _ReadAccountNumber(std::string Message) {
		std::string AccountNumber = "";
		std::cout << Message;
		AccountNumber = clsInputValidate::ReadString();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			std::cout << "\nClient with account Number [" << AccountNumber << "] does not exist\n";
			std::cout << "Enter Another Account Number: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadAmount(clsBankClient SourceClient) {
		double Amount = 0;
		std::cout << "\nEnter Transfer Amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		while(!(Amount <= SourceClient.GetAccountBalance())) {
			std::cout << "\nAmount exceeds the available balance, Enter a another balance: ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		return Amount;
	}

	static void _PrintClient(clsBankClient &Client) {
		std::cout << "\nClient Card:";
		std::cout << "\n___________________";
		std::cout << "\nFull Name   : " << Client.FullName();
		std::cout << "\nAcc. Number : " << Client.AccountNumber();
		std::cout << "\nBalance     : " << Client.GetAccountBalance();
		std::cout << "\n___________________\n";
	}
public:
	static void ShowTransferScreen() {
		_DrawScreenHeader("\t\t     Transfer Screen\n");

		std::string AccountNumber = _ReadAccountNumber("\nEnter Account Number to transfer form: ");

		clsBankClient SourceClient = clsBankClient::Find(AccountNumber);
		_PrintClient(SourceClient);

		AccountNumber = _ReadAccountNumber("\nEnter Account Number to transfer to: ");

		while(SourceClient.AccountNumber() == AccountNumber) {
			std::cout << "\nCan not Transfer to the same Account Number\n";
			AccountNumber = _ReadAccountNumber("\nEnter Another Account Number to transfer to: ");
		}

		clsBankClient DestinationClient = clsBankClient::Find(AccountNumber);
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		std::cout << "\nAre You Sure you want to perform this operation [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			if(SourceClient.Transfer(Amount, DestinationClient, CurrentUser.GetUserName())) {
				std::cout << "\nTransfer done successfully\n";
			} else {
				std::cout << "\nTransfer Faild\n";
			}

			_PrintClient(SourceClient);
			_PrintClient(DestinationClient);
		} else {
			std::cout << "\nOperation was cancelled.\n";
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
