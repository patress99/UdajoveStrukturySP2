#include "Roztried.h"


using namespace std;
Roztried::Roztried() :
	tabulkaObci_(new SortedSequenceTable<int, UzemnaJednotka*>),
	tabulkaKrajov_(new SortedSequenceTable<int, UzemnaJednotka*>),
	tabulkaOkresov_(new SortedSequenceTable<int, UzemnaJednotka*>),
	tabulkaObciPodlaNazvu_(new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>),
	tabulkaVsetkehoPodlaNazvu_(new SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*>),
	tabulkaVsetkeho_(new SortedSequenceTable<int, UzemnaJednotka*>),
	stat(new UzemnaJednotka("Slovensko", TypUzemnejJednotky::STAT, nullptr))
{
}


Roztried::~Roztried()
{

	for (const auto& temp : *this->tabulkaObciPodlaNazvu_)
	{
		string kluc = temp->getKey();
		delete (*this->tabulkaObciPodlaNazvu_)[kluc];
	}
	this->tabulkaObciPodlaNazvu_->clear();
	delete this->tabulkaObciPodlaNazvu_;




	if (!this->tabulkaObci_->isEmpty())
	{
		for (size_t i = 0; i < this->tabulkaObci_->size(); i++)
		{
			if (this->tabulkaObci_->getItemAtIndex(i).accessData() != nullptr)
			{
				delete this->tabulkaObci_->getItemAtIndex(i).accessData();
			}

		}
		delete this->tabulkaObci_;
	}

	if (!this->tabulkaOkresov_->isEmpty())
	{
		for (size_t i = 0; i < this->tabulkaOkresov_->size(); i++)
		{
			if (this->tabulkaOkresov_->getItemAtIndex(i).accessData() != nullptr)
			{
				delete this->tabulkaOkresov_->getItemAtIndex(i).accessData();
			}

		}
		delete this->tabulkaOkresov_;
	}

	if (!this->tabulkaKrajov_->isEmpty())
	{
		for (size_t i = 0; i < this->tabulkaKrajov_->size(); i++)
		{
			if (this->tabulkaKrajov_->getItemAtIndex(i).accessData() != nullptr)
			{
				delete this->tabulkaKrajov_->getItemAtIndex(i).accessData();

			}

		}
		delete this->tabulkaKrajov_;
	}


	delete stat;


}


void Roztried::roztriedUzemneJednotky()
{
	string nacitavam, word;
	ifstream opener;
	opener.imbue(locale(setlocale(LC_NUMERIC, "de_DE.UTF-8")));
	opener.open("NRSR_2020_SK_tab0c.csv");
	LinkedList<UzemnaJednotka*>* zretazenieStat = new LinkedList<UzemnaJednotka*>();
	zretazenieStat->add(stat);
	this->tabulkaVsetkehoPodlaNazvu_->insert(stat->getNazov(), zretazenieStat);


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


			if (!array->isEmpty())
			{
				string slovo = (*array)[0]->getInformacia();
				stringstream convert(slovo);
				int kodKraja = 0;
				convert >> kodKraja;

				string nazovKraja = (*array)[1]->getInformacia();

				slovo = (*array)[2]->getInformacia();
				stringstream convert1(slovo);
				int kodObvodu = 0;
				convert1 >> kodObvodu;

				string nazovObvodu = (*array)[3]->getInformacia();

				slovo = (*array)[4]->getInformacia();
				stringstream convert2(slovo);
				int kodOkresu = 0;
				convert2 >> kodOkresu;

				string nazovOkresu = (*array)[5]->getInformacia();

				slovo = (*array)[6]->getInformacia();
				stringstream convert3(slovo);
				int kodObce = 0;
				convert3 >> kodObce;

				string nazovObce = (*array)[7]->getInformacia();

				slovo = (*array)[8]->getInformacia();
				stringstream convert4(slovo);
				int typObce = 0;
				convert4 >> typObce;

				slovo = (*array)[9]->getInformacia();
				stringstream convert5(slovo);
				int okrsok = 0;
				convert5 >> okrsok;

				if (pocitadlo > 0)
				{
					/*wcout << kodKraja << " " << nazovKraja << " " << kodObvodu << " " << nazovObvodu << " " << kodOkresu << " " << nazovOkresu
						<< " " << kodObce << " " << nazovObce << " " << typObce << " " << okrsok << endl;*/


					UzemnaJednotka* novyOkres = nullptr;
					UzemnaJednotka* novyKraj = nullptr;

					if (!this->tabulkaKrajov_->containsKey(kodKraja))
					{
						novyKraj = new UzemnaJednotka(nazovKraja, TypUzemnejJednotky::KRAJ, stat);
						this->tabulkaKrajov_->insert(kodKraja, novyKraj);
						stat->pridajPotomka(kodKraja, novyKraj);
					}

					if (!this->tabulkaOkresov_->containsKey(kodOkresu))
					{
						UzemnaJednotka* krajDoKtorehoPatrim = (*this->tabulkaKrajov_)[kodKraja];
						novyOkres = new UzemnaJednotka(nazovOkresu, TypUzemnejJednotky::OKRES, krajDoKtorehoPatrim);
						this->tabulkaOkresov_->insert(kodOkresu, novyOkres);
						krajDoKtorehoPatrim->pridajPotomka(kodOkresu, novyOkres);
					}

					UzemnaJednotka* okresDoKtorehoPatrim = (*this->tabulkaOkresov_)[kodOkresu];
					UzemnaJednotka* novaObec = new UzemnaJednotka(nazovObce, TypUzemnejJednotky::OBEC, okresDoKtorehoPatrim);
					this->tabulkaObci_->insert(kodObce, novaObec);
					okresDoKtorehoPatrim->pridajPotomka(kodObce, novaObec);

					if (!this->tabulkaVsetkeho_->containsKey(kodKraja))
					{
						this->tabulkaVsetkeho_->insert(kodKraja, novyKraj);
					}
					if (!this->tabulkaVsetkeho_->containsKey(kodOkresu))
					{
						this->tabulkaVsetkeho_->insert(kodOkresu, novyOkres);
					}
					this->tabulkaVsetkeho_->insert(kodObce, novaObec);
					LinkedList<UzemnaJednotka*>* zretazenie = new LinkedList<UzemnaJednotka*>();
					if (this->tabulkaObciPodlaNazvu_->containsKey(nazovObce))
					{
						LinkedList<UzemnaJednotka*>* uj = (*this->tabulkaObciPodlaNazvu_)[nazovObce];
						uj->add(novaObec);
						delete zretazenie;
						zretazenie = nullptr;

						/*cout  << " " << pocitadlo << " " << novaObecPodlaNazvu->getNazov() << "  " << novaObecPodlaNazvu->getkamPatrimJa()->getNazov()
						<< " " << (*uj)[0]->getNazov() << "  " << (*uj)[0]->getkamPatrimJa()->getNazov() << " " << uj->size() << endl;*/

					}
					else
					{
						zretazenie->add(novaObec);
						this->tabulkaObciPodlaNazvu_->insert(nazovObce, zretazenie);
					}


					LinkedList<UzemnaJednotka*>* zretazenieObci = new LinkedList<UzemnaJednotka*>();
					LinkedList<UzemnaJednotka*>* zretazenieKrajov = new LinkedList<UzemnaJednotka*>();
					LinkedList<UzemnaJednotka*>* zretazenieOkresov = new LinkedList<UzemnaJednotka*>();

					if (!this->tabulkaVsetkehoPodlaNazvu_->containsKey(nazovKraja))
					{
						zretazenieKrajov->add(novyKraj);
						this->tabulkaVsetkehoPodlaNazvu_->insert(nazovKraja, zretazenieKrajov);
					}

					if (!this->tabulkaVsetkehoPodlaNazvu_->containsKey(nazovOkresu))
					{
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
				}

				pocitadlo++;
			}

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

				(*this->tabulkaObci_)[kodObce]->setCisloOkrsku(cisloOkrsku);
				(*this->tabulkaObci_)[kodObce]->setPocetZapisanychVolicov(p_Zap);
				(*this->tabulkaObci_)[kodObce]->setPocetZucastnenychVolicov(p_Zuc);
				(*this->tabulkaObci_)[kodObce]->setUcast(ucast);
				(*this->tabulkaObci_)[kodObce]->setPOOO(p_ooo);
				(*this->tabulkaObci_)[kodObce]->setP_ooo_pct(p_o);
				(*this->tabulkaObci_)[kodObce]->setPNOC(p_noc);
				(*this->tabulkaObci_)[kodObce]->setP_noc_pct(p_noc_pct);
				(*this->tabulkaObci_)[kodObce]->setPHL(p_hl);
				(*this->tabulkaObci_)[kodObce]->setP_hl_pct(p_hl_pct);

				UzemnaJednotka* okres = (*this->tabulkaObci_)[kodObce]->getkamPatrimJa();
				okres->setPocetZapisanychVolicov(p_Zap);
				UzemnaJednotka* kraj = okres->getkamPatrimJa();
				kraj->setPocetZapisanychVolicov(p_Zap);
				UzemnaJednotka* stat = kraj->getkamPatrimJa();
				stat->setPocetZapisanychVolicov(p_Zap);
				//wcout << (*this->tabulkaObci_)[kodObce]->getNazov() << endl;		
				//wcout << kodObce << " " << cisloOkrsku << " " << ucast << endl;

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

SortedSequenceTable<int, UzemnaJednotka*> Roztried::getTabulkaObci()
{
	return *this->tabulkaObci_;
}

SortedSequenceTable<string, LinkedList<UzemnaJednotka*>*> Roztried::getTabulkaObciPodlaNazvu()
{
	return *this->tabulkaObciPodlaNazvu_;
}

SortedSequenceTable<int, UzemnaJednotka*> Roztried::getTabulkaVsetkeho()
{
	return *this->tabulkaVsetkeho_;
}

void Roztried::najdiObec(string nazovObce)
{
	LinkedList<UzemnaJednotka*>* uj = (*this->tabulkaObciPodlaNazvu_)[nazovObce];
	for (size_t i = 0; i < uj->size(); i++)
	{
		UzemnaJednotka* vyssiaUJ = (*uj)[i]->getkamPatrimJa();
		UzemnaJednotka* esteVyssiaUJ = vyssiaUJ->getkamPatrimJa();
		cout << (*uj)[i]->getNazov() << ", " << "ktore patria do okresu: " << " " << (*uj)[i]->getkamPatrimJa()->getNazov() << " " <<
			" a ten patri do: " << vyssiaUJ->getkamPatrimJa()->getNazov() << " " << "a tento kraj patri do statu: " << esteVyssiaUJ->getkamPatrimJa()->getNazov() <<
			" pcoet volicov v okrese: " << vyssiaUJ->getPocetZapisanychVolicov() << " kraji: " << esteVyssiaUJ->getPocetZapisanychVolicov() << endl;
	}
}

void Roztried::najdiPodlaNazvu(string nazov)
{
	LinkedList<UzemnaJednotka*>* uj = (*this->tabulkaVsetkehoPodlaNazvu_)[nazov];
	for (size_t i = 0; i < uj->size(); i++)
	{
		if ((*uj)[i]->getkamPatrimJa() != nullptr)
		{
			cout << (*uj)[i]->getNazov() << " " << (*uj)[i]->getkamPatrimJa()->getNazov() << " " << (*uj)[i]->getPocetZapisanychVolicov() << " " << endl;
		}
		else
		{
			cout << "Stat: " << (*uj)[i]->getNazov() << ", pocet zapisanych volicov: " << (*uj)[i]->getPocetZapisanychVolicov() << "." << endl;
		}

	}

}
