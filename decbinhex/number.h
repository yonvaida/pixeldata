#pragma once
#include <afxwin.h>
#include <string>

class Number {
public:
	Number();
	CString toBin(unsigned int value);
	CString toHex(unsigned int value);
	unsigned int fromBin(CString value);
	unsigned int fromHex(CString value);
	CString formatString(CString value);
	
	
private:
	std::string toString(CString value);
	BOOL validateBin(std::string value);
	BOOL ValidateHex(std::string value);
	
};