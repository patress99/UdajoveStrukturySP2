#pragma once
#include <string>

class Informacia
{
private:
	std::string informacia_;
public:

	Informacia(std::string informacia);
	~Informacia();

	std::string getInformacia();
};

