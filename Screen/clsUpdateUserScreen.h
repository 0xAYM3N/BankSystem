#pragma once
#include <iostream>
#include <limits>
#include "clsScreen.h"
#include "../Core/clsUser.h"
#include "../Lib/clsInputValidate.h"

class clsUpdateUserScreen : protected clsScreen {
private:
	static int _ReadPermissions() {
		short Permissions = 0;

		char Answer = 'n';
		std::cout << "Do You Want to give the user full accesse [Y/n]: ";
		std::cin >> Answer;

		if(toupper(Answer) == 'Y') {
			return -1;
		}
		std::cout << "\nDo You Want to give access to:\n ";

		std::cout << "\nshow Client list [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pShowClientsList;
		}

		std::cout << "\nAdd New Client [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		std::cout << "\nDelete Client [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		std::cout << "\nUpdate Client [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pUpdateClientInfo;
		}

		std::cout << "\nFind Client [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pFindClient;
		}

		std::cout << "\nTransactions [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pTransactions;
		}

		std::cout << "\nManage Users [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pManageUsers;
		}

		std::cout << "\nLogin Register [Y/n]: ";
		std::cin >> Answer;
		if(toupper(Answer) == 'Y') {
			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		return Permissions;
	}

	static void _ReadUserInfo(clsUser &User) {
		std::cout << "\nEnter FirstName: ";
		User.SetFirstName(clsInputValidate::ReadString());

		std::cout << "\nEnter LastName: ";
		User.SetLastName(clsInputValidate::ReadString());

		std::cout << "\nEnter Email: ";
		User.SetEmail(clsInputValidate::ReadString());

		std::cout << "\nEnter Phone: ";
		User.SetPhone(clsInputValidate::ReadString());

		std::cout << "\nEnter Password: ";
		User.SetPassword(clsInputValidate::ReadString());

		std::cout << "\nEnter Permissions: \n";
		User.SetPermissions(_ReadPermissions());
	}

	static void _PrintUser(clsUser &User) {
		std::cout << "\nUser Card:";
		std::cout << "\n___________________";
		std::cout << "\nUsername    : " << User.GetUserName();
		std::cout << "\nFirstName   : " << User.GetFirstName();
		std::cout << "\nLastName    : " << User.GetLastName();
		std::cout << "\nFull Name   : " << User.FullName();
		std::cout << "\nEmail       : " << User.GetEmail();
		std::cout << "\nPhone       : " << User.GetPhone();
		std::cout << "\nPassword    : " << User.GetPassword();
		std::cout << "\nPermissions : " << User.GetPermissions();
		std::cout << "\n___________________\n";
	}
public:
	static void ShowUpdateUserScreen() {
		_DrawScreenHeader("\t\t  Update User Screen\n");

		std::string UserName = "";
		std::cout << "Enter Username: ";
		UserName = clsInputValidate::ReadString();

		while(!clsUser::IsUserExist(UserName)) {
			std::cout << "User is not found, choose another one: ";
			UserName = clsInputValidate::ReadString();
		}


		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'n';
		std::cout << "\nAre You Sure You Want to update this user [Y/n]: ";
		std::cin >> Answer;

		if(tolower(Answer) == 'y') {
			std::cout << "\n\nUpdate Client Info:\n";
			std::cout << "___________________\n";

			_ReadUserInfo(User);

			clsUser::enSaveResults SaveResult;
			SaveResult = User.Save();

			switch(SaveResult) {
				case clsUser::enSaveResults::svSucceeded: 
					std::cout << "\nUser updated successfully :)\n";
					_PrintUser(User);
					break;
				case clsUser::enSaveResults::svFaildEmptyObject:
					std::cout << "\nError user was not saved because its empty\n";
					_PrintUser(User);
					break;
				case clsUser::enSaveResults::svFaildAccountNumberExists:
					std::cout << "\nError user was not saved because account number is used!\n";
					break;
			}
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
};
