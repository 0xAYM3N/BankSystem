#pragma once
#include <iostream>
#include "clsScreen.h"
#include "../Core/clsBankClient.h"
#include "../Lib/clsInputValidate.h"

class clsFindClientScreen : protected clsScreen{
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
	static void ShowFindClientScreen() {
		if(!CheckAccessRghts(clsUser::enPermissions::pFindClient)) {
			return;
		}

		_DrawScreenHeader("\t\t  Find Client Screen\n");

		std::string AccountNumber = "";
		std::cout << "Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			std::cout << "Account Number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		if (!Client.IsEmpty()) {
			std::cout << "\nClient Found :-)\n";
		} else {
			std::cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client);
	}
};
