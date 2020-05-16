#include "Roztried.h"
#include "Filter.h"

using namespace std;
Roztried::Roztried() :
	tabulkaVsetkehoPodlaNazvu_(new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>),
	tabulkaVsetkeho_(new SortedSequenceTable<int, UzemnaJednotka*>),
	stat(new UzemnaJednotka("Slovensko", TypUzemnejJednotky::STAT, nullptr))
{
}


Roztried::~Roztried()
{

	for (const auto& temp : *this->tabulkaVsetkehoPodlaNazvu_)
	{
		string kluc = temp->getKey();
		delete (*this->tabulkaVsetkehoPodlaNazvu_)[kluc];
	}

	this->tabulkaVsetkehoPodlaNazvu_->clear();
	delete this->tabulkaVsetkehoPodlaNazvu_;
	this->tabulkaVsetkehoPodlaNazvu_ = nullptr;

	if (!this->tabulkaVsetkeho_->isEmpty())
	{

		for (auto temp : *this->tabulkaVsetkeho_)
		{
			if (temp->accessData() != nullptr)
			{
				delete temp->accessData();
			}

		}
		this->tabulkaVsetkeho_->clear();
		delete this->tabulkaVsetkeho_;
		this->tabulkaVsetkeho_ = nullptr;
	}

	

	//delete stat;


}


void Roztried::roztriedUzemneJednotky()
{
	string nacitavam, word;
	ifstream opener;
	/*opener.imbue(locale(setlocale(LC_NUMERIC, "de_DE.UTF-8")));*/
	opener.open("NRSR_2020_SK_tab0c.csv");
	LinkedList<UzemnaJednotka*>* zretazenieStat = new LinkedList<UzemnaJednotka*>();
	zretazenieStat->add(stat);
	this->tabulkaVsetkehoPodlaNazvu_->insert(stat->getNazov(), zretazenieStat);
	this->tabulkaVsetkeho_->insert(0, stat);

	if (opener.is_open())
	{
		int pocitadlo = 0;
		int pocokresy = 0;
		while (!opener.eof())
		{
			structures::ArrayList<Informacia*>* array = new structures::ArrayList<Informacia*>();
			getline(opener, nacitavam);
			stringstream s(nacitavam);

			while (getline(s, word, '|'))
			{
				Informacia* u = new Informacia(word);
				array->add(u);
			}


			if (!array->isEmpty() && pocitadlo > 0)
			{
				int kodKraja = stoi((*array)[0]->getInformacia());
				string nazovKraja = (*array)[1]->getInformacia();
				int kodOkresu = stoi((*array)[4]->getInformacia());
				string nazovOkresu = (*array)[5]->getInformacia();
				string nazovOkresu1 = "Okres: " + nazovOkresu;
				int kodObce = stoi((*array)[6]->getInformacia());
				string nazovObce = (*array)[7]->getInformacia();
				int pocetOkrskov = stoi((*array)[9]->getInformacia());
		
					/*cout << kodKraja << " " << nazovKraja << " "   << " "  << " " << kodOkres << " " << nazovOkresu
						<< " " << kodObce << " " << nazovObce << " " << " " <<  endl;*/

				UzemnaJednotka* novyOkres = nullptr;
				UzemnaJednotka* novyKraj = nullptr;

				if (!this->tabulkaVsetkeho_->containsKey(kodKraja))
				{
					novyKraj = new UzemnaJednotka(nazovKraja, TypUzemnejJednotky::KRAJ, stat);
					this->tabulkaVsetkeho_->insert(kodKraja, novyKraj);
					stat->pridajPotomka(kodKraja, novyKraj);		
					novyKraj->setKodUJ(kodKraja);
				}

				if (!this->tabulkaVsetkeho_->containsKey(kodOkresu))
				{
					UzemnaJednotka* krajDoKtorehoPatrim = (*this->tabulkaVsetkeho_)[kodKraja];
					novyOkres = new UzemnaJednotka(nazovOkresu, TypUzemnejJednotky::OKRES, krajDoKtorehoPatrim);
					this->tabulkaVsetkeho_->insert(kodOkresu, novyOkres);
					krajDoKtorehoPatrim->pridajPotomka(kodOkresu, novyOkres);
					novyOkres->setKodUJ(kodOkresu);
				}

				UzemnaJednotka* okresDoKtorehoPatrim = (*this->tabulkaVsetkeho_)[kodOkresu];
				UzemnaJednotka* novaObec = new UzemnaJednotka(nazovObce, TypUzemnejJednotky::OBEC, okresDoKtorehoPatrim);
				this->tabulkaVsetkeho_->insert(kodObce, novaObec);
				okresDoKtorehoPatrim->pridajPotomka(kodObce, novaObec);
				novaObec->setKodUJ(kodObce);
				UzemnaJednotka* okres = novaObec->getkamPatrimJa();
				UzemnaJednotka* kraj = okres->getkamPatrimJa();
				UzemnaJednotka* stat = kraj->getkamPatrimJa();
					
					
				LinkedList<UzemnaJednotka*>* zretazenieObci = new LinkedList<UzemnaJednotka*>();
					
				if (this->tabulkaVsetkehoPodlaNazvu_->containsKey(nazovOkresu))
				{
					
					LinkedList<UzemnaJednotka*>* kolizia = this->tabulkaVsetkehoPodlaNazvu_->operator[](nazovOkresu);
					if ((*kolizia)[0]->getTypUzemnejJednotky() != OKRES)
					{
						kolizia->add(novaObec);
					}
				}
				else
				{
					
					LinkedList<UzemnaJednotka*>* zretazenieOkresov = new LinkedList<UzemnaJednotka*>();
					zretazenieOkresov->add(novyOkres);
					this->tabulkaVsetkehoPodlaNazvu_->insert(nazovOkresu, zretazenieOkresov);


				}

				if (this->tabulkaVsetkehoPodlaNazvu_->containsKey(nazovObce))
				{
					LinkedList<UzemnaJednotka*>* uj = (*this->tabulkaVsetkehoPodlaNazvu_)[nazovObce];
					uj->add(novaObec);
					delete zretazenieObci;
					zretazenieObci = nullptr;

					/*cout  << " " << pocitadlo << " " << novaObecPodlaNazvu->getNazov() << "  " << novaObecPodlaNazvu->getkamPatrimJa()->getNazov()
					<< " " << (*uj)[0]->getNazov() << "  " << (*uj)[0]->getkamPatrimJa()->getNazov() << " " << uj->size() << endl;*/

				}
				else
				{
					zretazenieObci->add(novaObec);
					this->tabulkaVsetkehoPodlaNazvu_->insert(nazovObce, zretazenieObci);
				}


				if (!this->tabulkaVsetkehoPodlaNazvu_->containsKey(nazovKraja))
				{
					LinkedList<UzemnaJednotka*>* zretazenieKrajov = new LinkedList<UzemnaJednotka*>();
					zretazenieKrajov->add(novyKraj);
					this->tabulkaVsetkehoPodlaNazvu_->insert(nazovKraja, zretazenieKrajov);
					
				}

				
					
				
				//cout << pocitadlo << endl;
				
			}
			pocitadlo++;
			for (int i = array->size() - 1; i >= 0; i--)
			{
				delete (*array)[i];
			}
			delete array;
			array = nullptr;

		}
		opener.close();


		/*int pocitadlo1 = 0;
		for (TableItem<int, UzemnaJednotka*>* temp : *stat->getKtoPatriDoMna())
		{
			wcout << "Kraj: " << temp->accessData()->getNazov() << " " << endl;
			//UzemnaJednotka* uj = temp->accessData();

			SortedSequenceTable<int, UzemnaJednotka*>* okresy = temp->accessData()->getKtoPatriDoMna();

			for (TableItem<int, UzemnaJednotka*>* temp1 : *okresy)
			{


				//wcout << "Okres: " << temp1->accessData()->getNazov() << " " << endl;
				wstring nazovOkresu = temp1->accessData()->getNazov();
				//cout << " " << endl;

				SortedSequenceTable<int, UzemnaJednotka*>* obce = temp1->accessData()->getKtoPatriDoMna();
				wcout << "V okrese: " << nazovOkresu  << " je: " << obce->size() << " obcí. " <<  endl;
				/*for (TableItem<int, UzemnaJednotka*>* temp2 : *obce) {
					wcout << temp2->accessData()->getNazov() << " " << pocitadlo1 << endl;
					pocitadlo1++;
				}-
			}

		}*/
	}
}

void Roztried::priradDataObciam()
{
	string nacitavam, word;
	ifstream opener;
	setlocale(LC_NUMERIC, "de_DE.UTF-8");
	opener.open("NRSR_2020_SK_tab02e.csv");

	if (opener.is_open())
	{
		int pocitadlo = 0;

		while (!opener.eof())
		{
			structures::ArrayList<Informacia*>* array = new structures::ArrayList<Informacia*>();
			getline(opener, nacitavam);
			stringstream s(nacitavam);

			while (getline(s, word, '|'))
			{
				Informacia* u = new Informacia(word);
				array->add(u);
			}

			if (!array->isEmpty() && pocitadlo > 0)
			{

				int kodObce = stoi((*array)[0]->getInformacia());
				int cisloOkrsku = stoi((*array)[1]->getInformacia());
				int p_Zap = stoi((*array)[2]->getInformacia());
				int p_Zuc = stoi((*array)[3]->getInformacia());
				double ucast = stod((*array)[4]->getInformacia());
				int p_ooo = stoi((*array)[5]->getInformacia());
				double p_o = stod((*array)[6]->getInformacia());
				int p_noc = stoi((*array)[7]->getInformacia());
				double p_noc_pct = stod((*array)[8]->getInformacia());
				int p_hl = stoi((*array)[9]->getInformacia());
				double p_hl_pct = stod((*array)[10]->getInformacia());

				UzemnaJednotka* obec = (*this->tabulkaVsetkeho_)[kodObce];		
				obec->setPocetZapisanychVolicov(p_Zap);
				obec->setUcast(ucast);
				obec->setPocetZucastnenych(p_Zuc);
				obec->setPocetVolicovOsobne(p_ooo);
				obec->setPocetVolicovZCudziny(p_noc);
				obec->setSpolu(p_ooo);
				obec->setSpolu(p_noc);
				obec->setPlatneHlasy(p_hl);

				UzemnaJednotka* okres = obec->getkamPatrimJa();
				okres->setPocetZapisanychVolicov(p_Zap);
				okres->setUcast(ucast);
				okres->setPocetZucastnenych(p_Zuc);
				okres->setPocetVolicovOsobne(p_ooo);
				okres->setPocetVolicovZCudziny(p_noc);
				okres->setSpolu(p_ooo);
				okres->setSpolu(p_noc);
				okres->setPlatneHlasy(p_hl);



				UzemnaJednotka* kraj = okres->getkamPatrimJa();
				kraj->setPocetZapisanychVolicov(p_Zap);
				kraj->setUcast(ucast);
				kraj->setPocetZucastnenych(p_Zuc);
				kraj->setPocetVolicovOsobne(p_ooo);
				kraj->setPocetVolicovZCudziny(p_noc);
				kraj->setSpolu(p_ooo);
				kraj->setSpolu(p_noc);
				kraj->setPlatneHlasy(p_hl);



				UzemnaJednotka* stat = kraj->getkamPatrimJa();
				stat->setPocetZapisanychVolicov(p_Zap);
				stat->setUcast(ucast);
				stat->setPocetZucastnenych(p_Zuc);
				stat->setPocetVolicovOsobne(p_ooo);
				stat->setPocetVolicovZCudziny(p_noc);
				stat->setSpolu(p_ooo);
				stat->setSpolu(p_noc);
				stat->setPlatneHlasy(p_hl);

			}

			pocitadlo++;
			for (int i = array->size() - 1; i >= 0; i--)
			{
				delete (*array)[i];
			}
			delete array;
			array = nullptr;

		}
		opener.close();
	}
}


SequenceTable<int, UzemnaJednotka*>* Roztried::getTabulkaVsetkeho()
{
	return this->tabulkaVsetkeho_;
}

SequenceTable<string, LinkedList<UzemnaJednotka*>*>* Roztried::getTabulkaVsetkehoPodlaNazvu()
{
	return this->tabulkaVsetkehoPodlaNazvu_;
}

void Roztried::najdiPodlaNazvu(string nazov)
{
	cout << this->tabulkaVsetkeho_->size() << endl;
	cout << this->tabulkaVsetkehoPodlaNazvu_->size() << endl;
	if (!this->tabulkaVsetkehoPodlaNazvu_->containsKey(nazov))
	{
		cout << "Zadany nazov neexistuje" << endl;

	}
	else
	{
		LinkedList<UzemnaJednotka*>* uj = (*this->tabulkaVsetkehoPodlaNazvu_)[nazov];
		for (size_t i = 0; i < uj->size(); i++)
		{
			if ((*uj)[i]->getkamPatrimJa() != nullptr)
			{
				cout << (*uj)[i]->getNazov() << " " << (*uj)[i]->getkamPatrimJa()->getNazov() << " " << (*uj)[i]->getPocetZapisanychVolicov() << u8" volebná úèas:" << 
				(*uj)[i]->getUcast() << u8" úèas: " << (*uj)[i]->ucastVPct() << endl;
			}
			else
			{
				cout << "Stat: " << (*uj)[i]->getNazov() << ", pocet zapisanych volicov: " << (*uj)[i]->getPocetZapisanychVolicov() << u8" úèas: " << (*uj)[i]->ucastVPct() <<  endl;
			}

		}
	}
}

void Roztried::filterNajdiNazov(string nazov)
{
/*	Filter_fi<UzemnaJednotka, string>* f = new Filter_fi<UzemnaJednotka, string>(nazov);
	KriteriumNazov *kriterium = new KriteriumNazov();

	LinkedList<UzemnaJednotka*>* uJ = (*this->tabulkaVsetkehoPodlaNazvu_)[nazov];
	for (size_t i = 0; i < uJ->size(); i++)
	{
		UzemnaJednotka* filtrovanaUJ = (*uJ)[i];
		if (f->ohodnot(*filtrovanaUJ, *kriterium))
		{
			cout << filtrovanaUJ->getNazov() << " " << filtrovanaUJ->getkamPatrimJa()->getNazov() << endl;
		}
	}

	delete f;
	delete kriterium;*/
}

void Roztried::patrim(string nazov)
{


	UzemnaJednotka* uJ = (*this->tabulkaVsetkeho_)[6];
	cout << (*this->tabulkaVsetkeho_)[0]->getNazov() << endl;
	if (uJ->patriPod((*this->tabulkaVsetkeho_)[6]))
	{
		
		cout << "ano patri" << endl;
	}
	else
	{
		cout << "nie nepatri" << endl;
	}
	
}
