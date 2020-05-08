#include "Roztried.h"


using namespace std;
Roztried::Roztried() :
	tabulkaObci_(new SortedSequenceTable<int, UzemnaJednotka*>),
	tabulkaKrajov_(new SortedSequenceTable<int, UzemnaJednotka*>),
	tabulkaOkresov_(new SortedSequenceTable<int, UzemnaJednotka*>),
	stat(new UzemnaJednotka(L"Slovensko", TypUzemnejJednotky::STAT, nullptr))
{	
}


Roztried::~Roztried()
{
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
	wstring nacitavam, word;
	wifstream opener;

	
	opener.open("NRSR_2020_SK_tab0c.csv");	

	if (opener.is_open())
	{
		int pocitadlo = 0;
		
			while (!opener.eof()) 
			{	
				structures::ArrayList<Informacia*>* array = new structures::ArrayList<Informacia*>();
				getline(opener, nacitavam);
				wstringstream s(nacitavam);

				while (getline(s, word, L'|'))
				{
					Informacia* u = new Informacia(word);
					array->add(u);
				}


				if (!array->isEmpty())
				{
					wstring slovo = (*array)[0]->getInformacia();
					wstringstream convert(slovo);
					int kodKraja = 0;
					convert >> kodKraja;

					wstring nazovKraja = (*array)[1]->getInformacia();

					slovo = (*array)[2]->getInformacia();
					wstringstream convert1(slovo);
					int kodObvodu = 0;
					convert1 >> kodObvodu;

					wstring nazovObvodu = (*array)[3]->getInformacia();

					slovo = (*array)[4]->getInformacia();
					wstringstream convert2(slovo);
					int kodOkresu = 0;
					convert2 >> kodOkresu;

					wstring nazovOkresu = (*array)[5]->getInformacia();

					slovo = (*array)[6]->getInformacia();
					wstringstream convert3(slovo);
					int kodObce = 0;
					convert3 >> kodObce;

					wstring nazovObce = (*array)[7]->getInformacia();

					slovo = (*array)[8]->getInformacia();
					wstringstream convert4(slovo);
					int typObce = 0;
					convert4 >> typObce;

					slovo = (*array)[9]->getInformacia();
					wstringstream convert5(slovo);
					int okrsok = 0;
					convert5 >> okrsok;

					if (pocitadlo > 0)
					{
						/*wcout << kodKraja << " " << nazovKraja << " " << kodObvodu << " " << nazovObvodu << " " << kodOkresu << " " << nazovOkresu
							<< " " << kodObce << " " << nazovObce << " " << typObce << " " << okrsok << endl;*/
						
					
						
						if (!this->tabulkaKrajov_->containsKey(kodKraja))
						{
							UzemnaJednotka* novyKraj = new UzemnaJednotka(nazovKraja, TypUzemnejJednotky::KRAJ, stat);
							this->tabulkaKrajov_->insert(kodKraja, novyKraj);
							stat->pridajPotomka(kodKraja, novyKraj);
						}				
						
						if (!this->tabulkaOkresov_->containsKey(kodOkresu))
						{
							UzemnaJednotka* krajDoKtorehoPatrim = (*this->tabulkaKrajov_)[kodKraja];
							UzemnaJednotka* novyOkres = new UzemnaJednotka(nazovOkresu, TypUzemnejJednotky::OKRES, krajDoKtorehoPatrim);
							this->tabulkaOkresov_->insert(kodOkresu, novyOkres);
							krajDoKtorehoPatrim->pridajPotomka(kodOkresu, novyOkres);
						}
							
						UzemnaJednotka* okresDoKtorehoPatrim = (*this->tabulkaOkresov_)[kodOkresu];
						UzemnaJednotka* novaObec = new UzemnaJednotka(nazovObce, TypUzemnejJednotky::OBEC, okresDoKtorehoPatrim);
						this->tabulkaObci_->insert(kodObce, novaObec);
						okresDoKtorehoPatrim->pridajPotomka(kodObce, novaObec);

					
						
					

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
	wstring nacitavam, word;
	wifstream opener;


	opener.open("NRSR_2020_SK_tab02e.csv");

	if (opener.is_open())
	{
		int pocitadlo = 0;

		while (!opener.eof())
		{
			structures::ArrayList<Informacia*>* array = new structures::ArrayList<Informacia*>();
			getline(opener, nacitavam);
			wstringstream s(nacitavam);

			while (getline(s, word, L'|'))
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

				//wcout << (*this->tabulkaObci_)[kodObce]->getNazov() << endl;		
				wcout << kodObce << " " << cisloOkrsku << " " << ucast << endl;

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

SortedSequenceTable<int, UzemnaJednotka*>* Roztried::getTabulkaObci()
{
	return this->tabulkaObci_;
}
