#include "Informacia.h"

Informacia::Informacia(std::wstring informacia)
	:informacia_(informacia)
{
}


Informacia::~Informacia()
{
}

std::wstring Informacia::getInformacia()
{
	return informacia_;
}
