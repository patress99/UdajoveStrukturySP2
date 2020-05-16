#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(string nazov, TypUzemnejJednotky typ, UzemnaJednotka* kamPatrim) :
	nazov_(nazov), typUzemnejJednotky_(typ), kamPatrimJa_(kamPatrim)
{
	this->ktoPatriDoMna_ = new SortedSequenceTable<int, UzemnaJednotka*>();
	this->pocet_zap_volicov_ = 0;
	this->ucast_ = 0.0;
	this->pocet_zuc_volicov_ = 0;
	this->platneHlasy_ = 0.0;
	this->p_ooo = 0;
	this->p_noc = 0;
}

UzemnaJednotka::~UzemnaJednotka()
{
	if (this->ktoPatriDoMna_ != nullptr)
	{
		delete this->ktoPatriDoMna_;
		this->ktoPatriDoMna_ = nullptr;
	}
}

void UzemnaJednotka::pridajPotomka(int key, UzemnaJednotka* uJ)
{
	this->ktoPatriDoMna_->insert(key, uJ);

}

void UzemnaJednotka::setKodUJ(int key)
{
	this->kodUJ_ = key;
}

int UzemnaJednotka::getKodUJ() const
{
	return this->kodUJ_;
}

void UzemnaJednotka::setUcast(double ucast)
{
	this->ucast_ += ucast;
}

double UzemnaJednotka::getUcast() const
{
	return ((this->pocet_zuc_volicov_ / this->pocet_zap_volicov_) * 100.00);
}


void UzemnaJednotka::setPocetZapisanychVolicov(int pocet)
{
	this->pocet_zap_volicov_ +=  pocet;
}

int UzemnaJednotka::getPocetZapisanychVolicov() const
{
	return pocet_zap_volicov_;
}

void UzemnaJednotka::setPocetZucastnenych(int pocet)
{
	this->pocet_zuc_volicov_ += pocet;
}

int UzemnaJednotka::getPocetZUcastnenych()
{
	return this->pocet_zuc_volicov_;
}

double UzemnaJednotka::ucastVPct()
{
	return ((this->pocet_zuc_volicov_/this->pocet_zap_volicov_)*100.00);
}

void UzemnaJednotka::splnaFilter(bool nastav)
{
	this->splnaFilter_ = nastav;
}

void UzemnaJednotka::vypis()
{
	cout << endl;
	cout << u8"Úèas v %: " << this->ucastVPct() << u8", poèet zapísaných volièov: " << this->getPocetZapisanychVolicov() << u8", poèet zúèastnených volièov: " << this->getPocetZUcastnenych() << 
	u8", poèet obálok odovzdaných osobne " << this->getPocetVolicovOsobne() << u8", z cudziny " << this->getPocetVolicovZCudziny() << u8", podiel platných hlasov: " <<
	" " << this->podielPlatnychHlasov() << " " << endl;
	cout << endl;
	cout << endl;
}



SortedSequenceTable<int, UzemnaJednotka*>* UzemnaJednotka::getKtoPatriDoMna()
{
	return ktoPatriDoMna_;
}

UzemnaJednotka* UzemnaJednotka::getkamPatrimJa()
{
	if (kamPatrimJa_ != nullptr)
	{
		return kamPatrimJa_;
	}
	else
	{
		return nullptr;
	}

}

void UzemnaJednotka::vymaz()
{
	delete this;
}

bool UzemnaJednotka::patriPod(UzemnaJednotka* uJ) const
{
	
	//cout << uJ->getKodUJ() << " " << this->getKodUJ() << endl;
	if (this->getTypUzemnejJednotky() == OBEC)
	{
	
		UzemnaJednotka* okres = kamPatrimJa_;
		UzemnaJednotka* kraj = okres->getkamPatrimJa();
		UzemnaJednotka* stat = kraj->getkamPatrimJa();
		return okres->getKodUJ() == uJ->getKodUJ() || kraj->getKodUJ() == uJ->getKodUJ() || stat->getKodUJ() == uJ->getKodUJ();
	}
	if (this->getTypUzemnejJednotky() == OKRES)
	{
		
		UzemnaJednotka* kraj = kamPatrimJa_;
		UzemnaJednotka* stat = kraj->getkamPatrimJa();
		return kraj->getNazov() == uJ->getNazov() || stat->getNazov() == uJ->getNazov();
	}

	if (this->getTypUzemnejJednotky() == KRAJ)
	{

		UzemnaJednotka* stat = kamPatrimJa_;
		return stat->getNazov() == uJ->getNazov();
	}

	if (this->getTypUzemnejJednotky() == STAT)
	{	
		return false;
	}

}

string UzemnaJednotka::getNazov() const
{
	return nazov_;
}

TypUzemnejJednotky UzemnaJednotka::getTypUzemnejJednotky() const
{
	return typUzemnejJednotky_;
}
