#pragma once
#include <iostream>
#include <cctype>
#include <limits>
#include "../Core/clsBankClient.h"
#include "../Lib/clsInputValidate.h"
#include "clsScreen.h"

class clsDeleteClientScreen : protected clsScreen {
private:
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
	static void ShowDeleteClientScreen() {
		if(!CheckAccessRghts(clsUser::enPermissions::pDeleteClient)) {
			return;
		}

		_DrawScreenHeader("\t\t  Delete Client Screen\n");

		std::string AccountNumber = "";
		std::cout << "Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			std::cout << "Account Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'n';
		std::cout << "\nAre you sure you want to delete this client: [Y/n]: ";
		std::cin >> Answer;
		if(tolower(Answer) == 'y') {
			if(Client.Delete()) {
				Client.Delete();
				std::cout << "\nAccount Deleted successfuly\n";
				_PrintClient(Client);
			} else {
				std::cout << "\nError Client Was Not Deleted\n";
			}
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
