#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "../Core/clsBankClient.h"
#include "../Lib/clsUtil.h"
#include "clsScreen.h"

class clsTotalBalancesScreen : protected clsScreen {
private:
	static void _PrintClientRecordBalanceLine(clsBankClient Client) {
		std::cout << std::setw(10) << "" << "| " << std::setw(23) << std::left << Client.AccountNumber();
		std::cout << "| " << std::setw(40) << std::left << Client.FullName();
		std::cout << "| " << std::setw(10) << std::left << Client.GetAccountBalance();
	}
public:
	static void ShowTotalBalancesScreen() {
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		std::string Title = "\t\t  Total Balances Screen";
		std::string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		// std::string SubTitle = "\t    (" + std::to_string(vClients.size()) + ") Client(s)";
		_DrawScreenHeader(Title, SubTitle);

		std::cout << "\n" << std::setw(10) << "" << "_______________________________________________________"
			"_________________________________________\n";

		std::cout << std::setw(10)  << "" << "| " << "Accout Number";
		std::cout << std::setw(10)  << "" << "| " << "Client Name";
		std::cout << std::setw(29)  << "" << "| " << "Balance";
		std::cout << "\n" << std::setw(10) << "" << "_______________________________________________________"
			"_________________________________________\n";

		double TotalBalances = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0) {
			std::cout << std::setw(43) << "" << "No Clients Available In the System!\n";
		} else {
			for (clsBankClient &Client : vClients) {
				_PrintClientRecordBalanceLine(Client);
				cout << endl;
			}
		}

		std::cout << std::setw(10) << "" << "_______________________________________________________"
			"_________________________________________\n";
		std::cout << std::setw(45) << "" << "Total Balances = " << TotalBalances << std::endl;
		std::cout << std::setw(32) << "" << "( " << clsUtil::NumberToText(TotalBalances) << ")";

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
