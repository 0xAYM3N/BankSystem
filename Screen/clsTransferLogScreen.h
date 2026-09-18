#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include "clsScreen.h"
#include "../Lib/clsString.h"
#include "../Core/clsBankClient.h"

class clsTransferLogScreen : protected clsScreen {
private:
	static void _PrintLoginRegisterRecord(clsBankClient::stTransferLogRecord TransferLog) {
		std::cout << std::setw(10) << "" << "| " << std::setw(25) << std::left << TransferLog.DateAndTime;
		std::cout << "| " << std::setw(13) << std::left << TransferLog.SourceAccountNumber;
		std::cout << "| " << std::setw(13) << std::left << TransferLog.DestinationAccountNumber;
		std::cout << "| " << std::setw(13) << std::left << TransferLog.Amount;
		std::cout << "| " << std::setw(13) << std::left << TransferLog.SrcBalanceAfter;
		std::cout << "| " << std::setw(13) << std::left << TransferLog.DestBalanceAfter;
		std::cout << "| " << std::setw(13) << std::left << TransferLog.UserName << "\n";
	}
public:
	static void ShowTransferLogScreen(){
		std::vector<clsBankClient::stTransferLogRecord> vTransferLog = clsBankClient::GetTransferLogList();

		std::string Title = "\t\t  Show Transfer Log Screen";
		std::string SubTitle = "\t    (" + std::to_string(vTransferLog.size()) + ") Record(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::setw(10) << "" << "________________________________________________________"
			"_______________________________________________________\n";
		std::cout << std::setw(10) << "" << "| " << std::left << std::setw(25) << "Date/Time";
		std::cout << "| " << std::left << std::setw(13) << "S.AccNum";
		std::cout << "| " << std::left << std::setw(13) << "D.AccNum";
		std::cout << "| " << std::left << std::setw(13) << "Amount";
		std::cout << "| " << std::left << std::setw(13) << "S.Balance";
		std::cout << "| " << std::left << std::setw(13) << "D.Balance";
		std::cout << "| " << std::left << std::setw(5) << "User\n";
		std::cout << std::setw(10) << "" << "________________________________________________________"
			"_______________________________________________________\n";

		if(vTransferLog.size() == 0) {
			std::cout << std::setw(42) << "" << "No Transfer Available In the System!\n";
		} else {
			for(clsBankClient::stTransferLogRecord &TransferLog : vTransferLog) {
				_PrintLoginRegisterRecord(TransferLog);
			}
		}

		std::cout << std::setw(10) << "" << "________________________________________________________"
			"_______________________________________________________\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
