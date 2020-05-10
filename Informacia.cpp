#include "Informacia.h"

Informacia::Informacia(std::string informacia)
	:informacia_(informacia)
{
}


Informacia::~Informacia()
{
}

std::string Informacia::getInformacia()
{
	return informacia_;
}
