#pragma once
#include "clsScreen.h"
#include "../Lib/clsInputValidate.h"
#include "../Core/clsBankClient.h"

class clsWithrawScreen : protected clsScreen {
private:
	static std::string _ReadAccountNumber() {
		std::string AccountNumber = "";
		std::cout << "Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}

	static void _PrintClient(clsBankClient &Client) {
		std::cout << "\nClient Card:";
		std::cout << "\n___________________";
		std::cout << "\nFirstName   : " << Client.GetFirstName();
		std::cout << "\nLastName    : " << Client.GetLastName();
		std::cout << "\nFull Name   : " << Client.FullName();
		std::cout << "\nEmail       : " << Client.GetEmail();
		std::cout << "\nPhone       : " << Client.GetPhone();
		std::cout << "\nAcc. Number : " << Client.AccountNumber();
		std::cout << "\nPassword    : " << Client.GetPinCode();
		std::cout << "\nBalance     : " << Client.GetAccountBalance();
		std::cout << "\n___________________\n";
	}

public:
	static void ShowWithdrawScreen() {
		_DrawScreenHeader("\t\t     Withdraw Screen\n");

		std::string AccountNumber = "";
		AccountNumber = _ReadAccountNumber();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			std::cout << "\nClient with account Number [" << AccountNumber << "] does not exist\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		std::cout << "Enter withdraw amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'n';
		std::cout << "\nAre You Sure you want to perform this transaction [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			if(Client.Withdraw(Amount)) {
				std::cout << "\nAmount withdrawed successfully\n";
				std::cout << "\nNew Balance is: " << Client.GetAccountBalance();
			} else {
				std::cout << "\nCannot withdraw, Insuffecient Balance!\n";
				std::cout << "\nAmout to withdraw is: " << Amount;
				std::cout << "\nYour Balance is: " << Client.GetAccountBalance();
			}
		} else {
			std::cout << "\nOperation was cancelled.\n";
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
