#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../Lib/clsString.h"

class clsCurrency {
private:
	enum enMode { EmptyMode = 1, UpdateMode = 2 };
	enMode _Mode;

	std::string _Country;
	std::string _CurrencyCode;
	std::string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(std::string Line, std::string Seperator = "#//#") {
		std::vector<std::string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Seperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static std::string _ConvertCurrencyObjectToLine(clsCurrency Currency, std::string Seperator = "#//#") {
		std::string stCurrencyRecord = "";
	       stCurrencyRecord += Currency.Country() + Seperator;
	       stCurrencyRecord += Currency.CurrencyCode() + Seperator;
	       stCurrencyRecord += Currency.CurrencyName() + Seperator;
	       stCurrencyRecord += std::to_string(Currency.Rate());

	       return stCurrencyRecord;
	}
	
	static std::vector<clsCurrency> _LoadCurrenciesDataFromFile() {
		std::fstream MyFile;
		MyFile.open("Data/Currencies.txt", std::ios::in); // Read Mode

		std::vector<clsCurrency> vCurrencyies;

		if(MyFile.is_open()) {
			std::string Line;
			while(std::getline(MyFile, Line)) {
				clsCurrency CurrencyRecord = _ConvertLineToCurrencyObject(Line);
				vCurrencyies.push_back(CurrencyRecord);
			}
			MyFile.close();
		}

		return vCurrencyies;
	}

	static void _SaveCurrencyDataToFile(std::vector<clsCurrency> vCurrencies) {
		std::fstream MyFile;
		MyFile.open("Data/Currencies.txt", std::ios::out);
		std::string DataLine;

		if(MyFile.is_open()) {
			for(clsCurrency &C : vCurrencies) {
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyFile << DataLine << std::endl;
			}
			MyFile.close();
		}
	}

	void _Update() {
		std::vector<clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurrenciesDataFromFile();
		
		for(clsCurrency &C : _vCurrencies) {
			if(C.CurrencyCode() == CurrencyCode()) {
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject() {
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}
public:
	clsCurrency(enMode Mode, std::string Country, std::string CurrencyCode, std::string CurrencyName, float Rete) {
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rete;
	}

	static std::vector<clsCurrency> GetAllUSDRates() {
        return _LoadCurrenciesDataFromFile();
	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	std::string Country() { return _Country; }
	std::string CurrencyCode() { return _CurrencyCode; }
	std::string CurrencyName() { return _CurrencyCode; }
	float Rate() { return _Rate; }
	void UpdateRate(float NewRate) { 
		_Rate = NewRate; 
		_Update();
	}

	static clsCurrency FindByCode(std::string CurrencyCode) {
		CurrencyCode = clsString::UpperAllLetters(CurrencyCode);

		std::fstream MyFile;
		MyFile.open("Data/Currencies.txt", std::ios::in); // Read Mode

		std::vector<clsCurrency> vCurrencyies;

		if(MyFile.is_open()) {
			std::string Line;
			while(std::getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if(Currency.CurrencyCode() == CurrencyCode) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(std::string Country) {
		Country = clsString::UpperAllLetters(Country);

		std::fstream MyFile;
		MyFile.open("Data/Currencies.txt", std::ios::in); // Read Mode

		std::vector<clsCurrency> vCurrencyies;

		if(MyFile.is_open()) {
			std::string Line;
			while(std::getline(MyFile, Line)) {
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if(clsString::UpperAllLetters(Currency.Country()) == Country) {
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(std::string CurrencyCode) {
		clsCurrency C = FindByCode(CurrencyCode);
		return (!C.IsEmpty());
	}

	static std::vector<clsCurrency> GetCurreniesList() {
		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {
		float AmountInUSD = ConvertToUSD(Amount);

		if(Currency2.CurrencyCode() == "USD") {
			return AmountInUSD;
		}
		return float(AmountInUSD * Currency2.Rate());
	}
};
