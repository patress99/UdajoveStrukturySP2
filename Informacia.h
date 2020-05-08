#pragma once
#include <string>

class Informacia
{
private:
	std::wstring informacia_;
public:

	Informacia(std::wstring informacia);
	~Informacia();

	std::wstring getInformacia();
};

