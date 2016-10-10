#include "stdafx.h"
#include "number.h"

#include <vector>
#include <algorithm>


Number::Number() {
};

CString Number::toBin(unsigned int value){
	CString converted, temp;
	converted = "";
	int position = 1;
	for(int i=1;i<33;i++){
		int bin = value % 2;
		value = value / 2;
		temp.Format(_T("%u"), bin);
		converted = converted + temp;
		switch (position) {
		case 4:
			converted = converted + _T(" ");
			position++;
			break;
		case 8:
			converted = converted + _T("  ");
			position = 1;
			break;
		default:
			position++;
		}
	}

	return converted.MakeReverse();
}
CString Number::toHex(unsigned int value) {
	CString converted, temp;
	converted = "";
	int position = 1;
	for(int i=1;i<9;i++){
		switch (value % 16) {
		case 10:
			temp = "A";
			break;
		case 11:
			temp = "B";
			break;
		case 12:
			temp = "C";
			break;
		case 13:
			temp = "D";
			break;
		case 14:
			temp = "E";
			break;
		case 15:
			temp = "F";
			break;
		default:
			temp.Format(_T("%d"), value % 16);
			break;
		}
	value = value / 16;
		converted = converted + temp;
		if (i == 4) {
			converted = converted + _T(" ");
			
		}
		
	}
	
	return converted.MakeReverse();
};

BOOL Number::validateBin(std::string value) {
	for (size_t i = 0; i < value.length(); i++) {
		if (value[i] != '0'&&value[i] != '1')return false;
	}
	return true;


}


unsigned int Number::fromBin(CString value) {
	value.MakeReverse();
	unsigned int resultNumber = 0;
	CT2CA pszConvertedAnsiString(value);
	std::string tempString(pszConvertedAnsiString);
	if (validateBin(tempString)) {
		for (size_t i = 0; i < tempString.length(); i++) {
			resultNumber += ((int)tempString[i] - 48)*pow(2, i);
		}
	
	
	}
	return resultNumber;
}

BOOL Number::ValidateHex(std::string value) {
	
	for (size_t i = 0; i < value.length(); i++) {
		if (value[i] < '0')return false;
		if (value[i] > '9'&&value[i] < 'A')return false;
		if (value[i] > 'F'&&value[i] < 'a')return false;
		if (value[i] > 'f')return false;
	}
	return true;
}


unsigned int Number::fromHex(CString value) {
	value.MakeReverse();
	unsigned int resultNumber=0;
	CT2CA pszConvertedAnsiString(value);
	std::string tempString(pszConvertedAnsiString);
	
	if (ValidateHex(tempString)) {
		for (size_t i = 0; i < tempString.length(); i++) {
			switch (tempString[i]) {
			case 'a':
			case 'A':
				resultNumber += 10*pow(16,i);
				break;
			case 'b':
			case 'B':
				resultNumber += 11 * pow(16, i);
				break;
			case 'c':
			case 'C':
				resultNumber += 12 * pow(16, i);
				break;
			case 'd':
			case 'D':
				resultNumber += 13 * pow(16, i);
				break;
			case 'e':
			case 'E':
				resultNumber += 14 * pow(16, i);
				break;
			case 'f':
			case 'F':
				resultNumber += 15 * pow(16, i);
				break;
			default:
				resultNumber += ((int)tempString[i]-48) * pow(16, i);
			}
	
		}
		
	}	
	return resultNumber;
}