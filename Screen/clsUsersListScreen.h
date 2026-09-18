#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include "clsScreen.h"
#include "../Core/clsUser.h"

class clsUsersListScreen : protected clsScreen {
private:
	static void _PrintUsersRecord(clsUser User) {
		std::cout << std::setw(5) << "" << "| " << std::setw(15) << std::left << User.GetUserName();
		std::cout << "| " << std::setw(25) << std::left << User.FullName();
		std::cout << "| " << std::setw(15) << std::left << User.GetPhone();
		std::cout << "| " << std::setw(30) << std::left << User.GetEmail();
		std::cout << "| " << std::setw(15) << std::left << User.GetPassword();
		std::cout << "| " << std::setw(10) << std::left << User.GetPermissions() << "\n";
	}
public:
	static void ShowUsersListScreen() {
		std::vector<clsUser> vUsers = clsUser::GetUsersList();
		std::string Title = "\t\t  Users List Screen";
		std::string SubTitle = "\t    (" + std::to_string(vUsers.size()) + ") User(s)";
		_DrawScreenHeader(Title, SubTitle);

		std::cout << std::setw(5) << "" << "______________________________________________________________"
			"______________________________________________________________\n";
		std::cout << std::setw(5) << "" << "| " << std::left << std::setw(15) << "Username";
		std::cout << "| " << std::left << std::setw(25) << "FullName";
		std::cout << "| " << std::left << std::setw(15) << "Phone";
		std::cout << "| " << std::left << std::setw(30) << "Email";
		std::cout << "| " << std::left << std::setw(15) << "Password";
		std::cout << "| " << std::left << std::setw(10) << "Permissions\n";
		std::cout << std::setw(5) << "" << "______________________________________________________________"
			"______________________________________________________________\n";

		if(vUsers.size() == 0) {
			std::cout << std::setw(42) << "" << "No Users Available In the System!\n";
		}
		else {
			for(clsUser &User : vUsers) {
				_PrintUsersRecord(User);
			}
		}

		std::cout << std::setw(5) << "" << "______________________________________________________________"
			"______________________________________________________________\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
