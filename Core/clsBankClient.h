#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../Screen/clsPerson.h"
#include "../Lib/clsString.h"
#include "../Lib/clsDate.h"

class clsBankClient : public clsPerson {
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	std::string _AccountNumber;
	std::string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToObject(std::string Line, std::string Seperator = "#//#") {
		std::vector<std::string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], 
					   vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject() {
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static std::vector<clsBankClient> _LoadClientsDataFromFile() {
		std::vector<clsBankClient> vClients;

		std::fstream MyFile;
		MyFile.open("Data/Clients.txt", std::ios::in); // Read Mode
	
		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}
		return vClients;
	}

	static std::string _ConvertClientObjectToLine(clsBankClient Client, std::string Seperator = "#//#") {
		std::string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.GetPinCode() + Seperator;
        stClientRecord += std::to_string(Client.GetAccountBalance());

        return stClientRecord;
    }

	static void _SaveClientsDataToFile(std::vector<clsBankClient> vClients) {
		std::fstream MyFile;
		MyFile.open("Data/Clients.txt", std::ios::out); // overwrite
		std::string DataLine;

		if(MyFile.is_open()) {
			for(clsBankClient &C : vClients) {
				if(C.MarkedForDeleted() == false) {
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << std::endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update() {
		std::vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for(clsBankClient &C : _vClients) {
			if(C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(std::string stDataLine) {
		std::fstream MyFile;
		MyFile.open("Data/Clients.txt", std::ios::out | std::ios::app);

		if(MyFile.is_open()) {
			MyFile << stDataLine << std::endl;
			MyFile.close();
		}
	}

	void _AddNew() {
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

public: 
	struct stTransferLogRecord {
		std::string DateAndTime;
		std::string SourceAccountNumber;
		std::string DestinationAccountNumber;
		float Amount;
		float SrcBalanceAfter;
		float DestBalanceAfter;
		std::string UserName;
	};
private:
	static stTransferLogRecord _ConvertTransferLogLineToRecord(std::string Line) {
		stTransferLogRecord TransferLogRecord;

		std::vector<std::string> vTransferLog = clsString::Split(Line, "#//#");
		TransferLogRecord.DateAndTime = vTransferLog[0];
		TransferLogRecord.SourceAccountNumber = vTransferLog[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLog[2];
		TransferLogRecord.Amount = std::stof(vTransferLog[3]);
		TransferLogRecord.SrcBalanceAfter = stof(vTransferLog[4]);
		TransferLogRecord.DestBalanceAfter = stof(vTransferLog[5]);
		TransferLogRecord.UserName = vTransferLog[6];

		return TransferLogRecord;
	}
public:
	clsBankClient(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone, 
			   std::string AccountNumber, std::string PicCode, float AccountBalance) :
		clsPerson (FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PicCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	std::string AccountNumber() { return _AccountNumber; }

	std::string GetPinCode() { return _PinCode; }
	void SetPinCode(std::string PinCode) { _PinCode = PinCode; }

	float GetAccountBalance() { return _AccountBalance; }
	void SetAccountBalance(float AccountBalance) { _AccountBalance = AccountBalance; }

	std::string FullName() {
		return GetFirstName() + " " + GetLastName();
	}

    bool MarkedForDeleted() { return _MarkedForDelete; };

	static clsBankClient Find(std::string AccountNumber) {
		std::fstream MyFile;
		MyFile.open("Data/Clients.txt", std::ios::in); // read Mode

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToObject(Line);

				if(Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(std::string AccountNumber, std::string PinCode) {
		std::vector<clsBankClient> vClients;

		std::fstream MyFile;
		MyFile.open("Data/Clients.txt", std::ios::in); // read Mode

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				clsBankClient Client = _ConvertLineToObject(Line);

				if(Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode) {
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(std::string AccountNumber) {
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
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
				if(clsBankClient::IsClientExist(_AccountNumber)) {
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

	static clsBankClient GetAddNewClientObject(std::string AccountNumber) {
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete() {
		std::vector<clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for(clsBankClient &C : vClients) {
			if(C.AccountNumber() == _AccountNumber) {
				C._MarkedForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static std::vector<clsBankClient> GetClientsList() {
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances() {
		std::vector<clsBankClient> vCliets = clsBankClient::GetClientsList();
		double TotalBalances = 0;

		for(clsBankClient &C : vCliets) {
			TotalBalances += C.GetAccountBalance();
		}

		return TotalBalances;
	}

	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {
		if(Amount <= _AccountBalance) {
			_AccountBalance -= Amount;
			Save();
			return true;
		}
		return false;
	}

	std::string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, std::string UserName, std::string Seperator = "#//#") {
		std::string stLoginRecord = "";
		stLoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		stLoginRecord += AccountNumber() + Seperator;
		stLoginRecord += DestinationClient.AccountNumber() + Seperator;
		stLoginRecord += std::to_string(Amount) + Seperator;
		stLoginRecord += std::to_string(GetAccountBalance()) + Seperator;
		stLoginRecord += std::to_string(DestinationClient.GetAccountBalance()) + Seperator;
		stLoginRecord += UserName;
		return stLoginRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, std::string UserName) {
		std::fstream MyFile;
		MyFile.open("Data/TransferLog.txt", std::ios:: out | std::ios::app);

		std::string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);
		if(MyFile.is_open()) {
			MyFile << stDataLine << std::endl;
		}
		MyFile.close();
	}

	bool Transfer(double Amount, clsBankClient &DestinationClient, std::string UserName) {
		if(Amount > GetAccountBalance()) {
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, UserName);

		return true;
	}

	static std::vector<stTransferLogRecord> GetTransferLogList() {
		std::vector<stTransferLogRecord> vTransferLog;

		std::fstream MyFile;
		MyFile.open("Data/TransferLog.txt", std::ios::in); // Read Mode
		stTransferLogRecord TransferLogRecord;

		if(MyFile.is_open()) {
			std::string Line;
			while(getline(MyFile, Line)) {
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vTransferLog.push_back(TransferLogRecord);
			}

			MyFile.close();
		}
		return vTransferLog;
	}
};
