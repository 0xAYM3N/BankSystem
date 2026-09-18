#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include "clsScreen.h"
#include "../Lib/clsString.h"

class clsLoginRegister : protected clsScreen {
private:
	static void _PrintLoginRegisterRecord(clsUser::stLoginRegisterRecord LoginRegister) {
		std::cout << std::setw(15) << "" << "| " << std::setw(30) << std::left << LoginRegister.DateAndTime;
		std::cout << "| " << std::setw(15) << std::left << LoginRegister.UserName;
		std::cout << "| " << std::setw(15) << std::left << LoginRegister.Password;
		std::cout << "| " << std::setw(10) << std::left << LoginRegister.Permissions << "\n";
	}
public:
	static void ShowLoginRegisterScreen() {
		if(!CheckAccessRghts(clsUser::enPermissions::pLoginRegister)) {
			return;
		}

		std::vector<clsUser::stLoginRegisterRecord> vLoginRegister = clsUser::GetLoginRegisterList();

		std::string Title = "\t\t  Show Login Register Screen\n";
		std::string SubTitle = "\t    (" + std::to_string(vLoginRegister.size()) + ") Record(s)";

		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::setw(15) << "" << "______________________________________________________________"
			"_______________________\n";
		std::cout << std::setw(15) << "" << "| " << std::left << std::setw(30) << "Date/Time";
		std::cout << "| " << std::left << std::setw(15) << "UserName";
		std::cout << "| " << std::left << std::setw(15) << "Password";
		std::cout << "| " << std::left << std::setw(10) << "permissions\n";
		std::cout << std::setw(15) << "" << "______________________________________________________________"
			"_______________________\n";

		if(vLoginRegister.size() == 0) {
			std::cout << std::setw(42) << "" << "No Login Register Available In the System!\n";
		} else {
			for(clsUser::stLoginRegisterRecord &LoginRegister : vLoginRegister) {
				_PrintLoginRegisterRecord(LoginRegister);
			}
		}

		std::cout << std::setw(15) << "" << "______________________________________________________________"
			"_______________________\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
