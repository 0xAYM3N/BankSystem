#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include "../Screen/clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/clsDate.h"
#include "../Lib/clsUtil.h"

class clsUser : public clsPerson {
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	std::string _UserName;
	std::string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	static clsUser _ConvertLineToObject(std::string Line, std::string Seperator = "#//#") {
		std::vector<std::string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], 
				 vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stod(vUserData[6]));
	}

	static clsUser _GetEmptyUserObject() {
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static std::vector<clsUser> _LoadUsersDataFromFile() {
		std::vector<clsUser> vUsers;

		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::in); // Read Mode

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				clsUser User = _ConvertLineToObject(Line);
				vUsers.push_back(User);
			}

			MyFile.close();
		}
		return vUsers;
	}

	static std::string _ConvertUserObjectToLine(clsUser User, std::string Seperator = "#//#") {
		std::string stUserRecord = "";
		stUserRecord += User.GetFirstName() + Seperator;
		stUserRecord += User.GetLastName() + Seperator;
		stUserRecord += User.GetEmail() + Seperator;
		stUserRecord += User.GetPhone() + Seperator;
		stUserRecord += User.GetUserName() + Seperator;
		stUserRecord += clsUtil::EncryptText(User.GetPassword()) + Seperator;
		stUserRecord += std::to_string(User.GetPermissions());

		return stUserRecord;
	}

	static void _SaveUsersDataToFile(std::vector<clsUser> vUsers) {
		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::out); // overwrite
		std::string DataLine;

		if(MyFile.is_open()) {
			for(clsUser &U : vUsers) {
				if(U.MarkedForDeleted() == false) {
					DataLine = _ConvertUserObjectToLine(U);
					MyFile << DataLine << std::endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		std::vector<clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for(clsUser &U : _vUsers) {
			if(U.GetUserName() == GetUserName()) {
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
	}

	void _AddDataLineToFile(std::string stDataLine) {
		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::out | std::ios::app);

		if(MyFile.is_open()) {
			MyFile << stDataLine << std::endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}
public:
	struct stLoginRegisterRecord {
		std::string DateAndTime;
		std::string UserName;
		std::string Password;
		int Permissions;
	};

	enum enPermissions {
		eAll = -1, pShowClientsList = 1,
		pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClientInfo = 8, pFindClient = 16,
		pTransactions = 32, pManageUsers = 64,
		pLoginRegister = 128,
	};

	clsUser(enMode Mode, std::string FirstName, std::string LastName, std::string Email,
		 std::string Phone, std::string UserName, std::string Password, int Permissions) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted() { return _MarkedForDelete; }

	std::string GetUserName() { return _UserName; }
	void SetUserName(std::string UserName) { _UserName = UserName; }

	std::string FullName() { return GetFirstName() + " " + GetLastName(); }

	std::string GetPassword() { return _Password; }
	void SetPassword(std::string Password) { _Password = Password; }

	int GetPermissions() { return _Permissions; }
	void SetPermissions(int Permissions) { _Permissions = Permissions; }

	static clsUser Find(std::string UserName, std::string Password) {
		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::in); // read Mode

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				clsUser User = _ConvertLineToObject(Line);

				if(User.GetUserName() == UserName && User.GetPassword() == Password) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(std::string UserName) {
		std::fstream MyFile;
		MyFile.open("Data/Users.txt", std::ios::in); // read Mode

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				clsUser User = _ConvertLineToObject(Line);

				if(User.GetUserName() == UserName) {
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(std::string UserName) {
		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1 , svFaildAccountNumberExists = 2 };
	enSaveResults Save() {
		switch (_Mode) {
			case enMode::EmptyMode:
				return enSaveResults::svFaildEmptyObject;
			case enMode::UpdateMode:
				_Update();
				return enSaveResults::svSucceeded;
			case enMode::AddNewMode:
				if(clsUser::IsUserExist(_UserName)) {
					return enSaveResults::svFaildAccountNumberExists;
				} else {
					_AddNew();
					// We need to set the mode to update after add new
					_Mode = enMode::UpdateMode;
					return enSaveResults::svSucceeded;
				}
			default:
				return enSaveResults::svFaildEmptyObject;
		}
	}

	static clsUser GetAddNewUserObject(std::string UserName) {
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static std::vector<clsUser> GetUsersList() {
		return _LoadUsersDataFromFile();
	}

	bool Delete() {
		std::vector<clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for(clsUser &U : vUsers) {
			if(U.GetUserName() == GetUserName()) {
				U._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}

	bool CheckAccessPermissions(enPermissions Permissions) {
		if(this->_Permissions == enPermissions::eAll) {
			return true;
		}

		if((Permissions & this->_Permissions) == Permissions) {
			return true;
		} else {
			return false;
		}
	}

	std::string _PrepareLoginRecord(std::string Seperator = "#//#") {
		std::string stLoginRecord = "";
		stLoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		stLoginRecord += GetUserName() + Seperator;
		stLoginRecord += clsUtil::EncryptText(GetPassword()) + Seperator;
		stLoginRecord += std::to_string(GetPermissions());
		return stLoginRecord;
	}

	void RegisterLogin() {
		std::fstream MyFile;
		MyFile.open("Data/LoginRegister.txt", std::ios:: out | std::ios::app);

		std::string stDataLine = _PrepareLoginRecord();
		if(MyFile.is_open()) {
			MyFile << stDataLine << std::endl;
		}
		MyFile.close();
	}

	static stLoginRegisterRecord ConvertLoginRegisterLineToRecord(std::string Line) {
		stLoginRegisterRecord LoginRegisterRecord;

		std::vector<std::string> vUserLoginRegister = clsString::Split(Line, "#//#");
		LoginRegisterRecord.DateAndTime = vUserLoginRegister[0];
		LoginRegisterRecord.UserName = vUserLoginRegister[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vUserLoginRegister[2]);
		LoginRegisterRecord.Permissions = std::stoi(vUserLoginRegister[3]);

		return LoginRegisterRecord;
	}

	static std::vector<stLoginRegisterRecord> GetLoginRegisterList() {
		std::vector<stLoginRegisterRecord> vLoginRegsiter;

		std::fstream MyFile;
		MyFile.open("Data/LoginRegister.txt", std::ios::in); // Read Mode
		stLoginRegisterRecord LoginRegisterRecord;

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				LoginRegisterRecord = ConvertLoginRegisterLineToRecord(Line);
				vLoginRegsiter.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}
		return vLoginRegsiter;
	}
};
