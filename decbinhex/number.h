#pragma once
#include <afxwin.h>
#include <string>

class Number {
public:
	Number();
	CString toBin(unsigned int value);
	CString toHex(unsigned int value);
	int fromBin(CString value);
	int fromHex(CString value);
private:
	BOOL validateBin(std::string value);
	BOOL ValidateHex(std::string value);
};