#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "../Core/clsUser.h"
#include "../Core/clsGlobal.h"
#include "../Lib/clsDate.h"

class clsScreen {
protected:
	static void _DrawScreenHeader(std::string Title, std::string SubTitle = "") {
		std::cout << std::setw(37) << std::left << "" << "______________________________________________\n";
		std::cout << std::setw(37) << std::left << "" << Title;
		if (SubTitle != "") {
			std::cout << "\n\t\t\t\t\t" << SubTitle << std::endl;
		}
		std::cout << std::setw(37) << std::left << "" << "______________________________________________\n";
		std::cout << std::setw(40) << "" << "User: " << CurrentUser.GetUserName() << std::endl;
		std::cout << std::setw(40) << "" << "Date: " << clsDate::DateToString(clsDate()) << std::endl;
	}

	static bool CheckAccessRghts(clsUser::enPermissions Permissions) {
		if(!CurrentUser.CheckAccessPermissions(Permissions)) {
			_DrawScreenHeader("\t   Access Denaid! Contact Your Admin\n");
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		} else {
			return true;
		}
	}
};
