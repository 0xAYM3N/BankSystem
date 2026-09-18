#pragma once
#include <iostream>
#include <limits>
#include "clsScreen.h"
#include "../Core/clsBankClient.h"
#include "../Lib/clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen {
private:
	static void _ReadClientInfo(clsBankClient &Client) {
		std::cout << "\nEnter FirstName: ";
		Client.SetFirstName(clsInputValidate::ReadString());

		std::cout << "\nEnter LastName: ";
		Client.SetLastName(clsInputValidate::ReadString());

		std::cout << "\nEnter Email: ";
		Client.SetEmail(clsInputValidate::ReadString());

		std::cout << "\nEnter Phone: ";
		Client.SetEmail(clsInputValidate::ReadString());

		std::cout << "\nEnter PinCode: ";
		Client.SetPinCode(clsInputValidate::ReadString());

		std::cout << "\nEnter Account Balance: ";
		Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
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
	static void ShowUpdateClientScreen() {
		if(!CheckAccessRghts(clsUser::enPermissions::pUpdateClientInfo)) {
			return;
		}

		_DrawScreenHeader("\t\t       Update Screen\n");
		std::string AccountNumber = "";

		std::cout << "Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();

		while(!clsBankClient::IsClientExist(AccountNumber)) {
			std::cout << "Account number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'n';
		std::cout << "\nAre You Sure You Want to update this client [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			std::cout << "\n\nUpdate Client Info:\n";
			std::cout << "___________________\n";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResults SaveResult;
			SaveResult = Client.Save();

			switch(SaveResult) {
				case clsBankClient::enSaveResults::svSucceeded: 
					std::cout << "\nAccount Updated Successfully :)\n";
					_PrintClient(Client);
					break;
				case clsBankClient::enSaveResults::svFaildEmptyObject:
					std::cout << "\nError account was not saved because its empty\n";
					_PrintClient(Client);
					break;
				case clsBankClient::enSaveResults::svFaildAccountNumberExists:
					std::cout << "\nError account was not saved because account number is used!\n";
					break;
			}
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};

