#pragma once
#include <iostream>

class clsPerson {
private:
	std::string _FirstName;
	std::string _LastName;
	std::string _Email;
	std::string _Phone;
public:
	clsPerson(std::string FirstName, std::string LastName, std::string Email, std::string Phone) {
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	std::string GetFirstName() { return _FirstName; }
	void SetFirstName(std::string FirstName) { _FirstName = FirstName; }

	std::string GetLastName() { return _LastName; }
	void SetLastName(std::string LastName) { _LastName = LastName; }

	std::string GetEmail() { return _Email; }
	void SetEmail(std::string Email) { _Email = Email; }

	std::string GetPhone() { return _Phone; }
	void SetPhone(std::string Phone) { _Phone = Phone; }
};
