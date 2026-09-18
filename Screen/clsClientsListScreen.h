#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "../Core/clsBankClient.h"
#include "clsScreen.h"
#include "../Core/clsUser.h"

class clsClientsListScreen : protected clsScreen {
private:
	static void _PrintClientsRecord(clsBankClient Client) {
		std::cout << std::setw(10) << "" << "| " << std::setw(15) << std::left << Client.AccountNumber();
		std::cout << "| " << std::setw(24) << std::left << Client.FullName();
		std::cout << "| " << std::setw(13) << std::left << Client.GetPhone();
		std::cout << "| " << std::setw(20) << std::left << Client.GetEmail();
		std::cout << "| " << std::setw(10) << std::left << Client.GetPinCode();
		std::cout << "| " << std::left << Client.GetAccountBalance() << "\n";
	}
public:
	static void ShowClientsList() {
		if(!CheckAccessRghts(clsUser::enPermissions::pShowClientsList)) {
			return;
		}

		std::vector<clsBankClient> vClients = clsBankClient::GetClientsList();
		std::string Title = "\t\t  Client List Screen";
		std::string SubTitle = "\t    (" + std::to_string(vClients.size()) + ") Client(s)";
		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::setw(10) << "" << "____________________________________________________"
			"_________________________________________________\n";
		std::cout << std::setw(10) << "" << "| " << std::left << std::setw(15) << "Accout Number";
		std::cout << "| " << std::left << std::setw(24) << "Client Name";
		std::cout << "| " << std::left << std::setw(13) << "Phone";
		std::cout << "| " << std::left << std::setw(20) << "Email";
		std::cout << "| " << std::left << std::setw(10) << "Pin Code";
		std::cout << "| " << std::left << std::setw(12) << "Balance";
		std::cout << "\n" << std::setw(10) << "" << "____________________________________________________"
			"_________________________________________________\n";

		if(vClients.size() == 0) {
			std::cout << std::setw(40) << "" << "No Clients Available In the System!\n";
		}
		else {
			for(clsBankClient &Client : vClients) {
				_PrintClientsRecord(Client);
			}
		}

		std::cout << std::setw(10) << "" << "____________________________________________________"
			"_________________________________________________\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
