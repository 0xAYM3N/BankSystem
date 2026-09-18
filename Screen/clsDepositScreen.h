#pragma once
#include "clsScreen.h"
#include "../Core/clsBankClient.h"
#include "../Lib/clsInputValidate.h"

class clsDepositScreen : protected clsScreen {
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
	static void ShowDepositScreen() {
		_DrawScreenHeader("\t\t     Deposit Screen\n");

		std::string AccountNumber = "";
		AccountNumber = _ReadAccountNumber();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			std::cout << "\nClient with account Number [" << AccountNumber << "] does not exist\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		std::cout << "Enter deposit amount: ";
		Amount = clsInputValidate::ReadDblNumber();

		char Answer = 'n';
		std::cout << "\nAre You Sure you want to perform this transaction [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			Client.Deposit(Amount);
			std::cout << "\nAmount deposited successfully\n";
			std::cout << "\nNew Balance is: " << Client.GetAccountBalance();
		} else {
			std::cout << "\nOperation Was Cancelled\n";
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
