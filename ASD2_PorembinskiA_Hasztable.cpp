#include <iostream>
#include <string>

int ileTestow = 0;
int KONIEC = 0;
char PUSTO[9] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0' };

struct TablicaMieszajaca
{
	bool dane = false;
	long klucz = 0;
	char lancuch[9] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0'}; //zeby nie bylo warningow
};

class CircleTable
{
public:
	int rozmiar = 0;
	TablicaMieszajaca* Tab = NULL;

	CircleTable();
	~CircleTable();

	void SetRozmiar(int wielkosc);
	int Haszuj(long x);
	void Porzadkuj(int index);//na samym dole
	void Zeruj(long klucz);

	void print();
	void add(long klucz, std::string znaki);
};

CircleTable::CircleTable()
{
}

CircleTable::~CircleTable()
{
	if (rozmiar != 0) {
		delete[] Tab;
	}
	Tab = NULL;
}

void CircleTable::SetRozmiar(int wielkosc)
{
	if (rozmiar != 0) {
		delete[] Tab;
	}
	
	rozmiar = wielkosc;
	Tab = new TablicaMieszajaca[wielkosc];

	return;
}

int CircleTable::Haszuj(long x)
{
	int wynik = x % rozmiar;
	return wynik;
}

void CircleTable::Zeruj(long klucz)		//Do debugu CZY NIE INDEX
{
	int index = Haszuj(klucz);

	if (index >= rozmiar){
		return;
	}
	
	//if (!Tab[index].dane){
	//	return;
	//}

	while (Tab[index].klucz != klucz ){//&& Tab[index].dane){
		index++;
	}

	Tab[index].klucz = 0;
	Tab[index].lancuch[0] = '\0';
	//for (int i = 0; i < 9; i++){
	//	Tab[index].lancuch[i] = '\0';
	//}
	Tab[index].dane = false;
	
	return;
}

void CircleTable::print()
{
	for (int i = 0; i < rozmiar; i++)
	{
		if (Tab[i].dane == true) {
			std::cout << i << " " << Tab[i].klucz << " " << Tab[i].lancuch << "\n";
		}
	}

	std::cout << "\n";
	return;
}

void CircleTable::add(long klucz, std::string znaki)
{
	int index = Haszuj(klucz);
	int orig_index = index;

	if (index >= rozmiar){
		return;
	}

	while (Tab[index].dane == true) {
		index += 1;

		if (index == orig_index) {	//czy wrocil skad przybyl
			return;
		}
		if (index == rozmiar) {	//zeby bylo przejscie
			index = 0;
		}
	}

	if (Tab[index].dane == false) {
		Tab[index].klucz = klucz;
		Tab[index].dane = true;

		//DO DEBUGU
		//(std::string)Tab[index].lancuch = znaki;
		for (int i = 0; (unsigned int)i < znaki.length(); i++)
		{
			Tab[index].lancuch[i] = znaki[i];
		}
	}

	return;
}


int main() {
	std::string tmp_1;
	int tmp_2;				int nr = 0;//DEBUG ONLY
	CircleTable Tabela;

	std::cin >> tmp_2;//			std::cout << "\nx; " << tmp_2;//DEBUG ONLY
	KONIEC = tmp_2;

	while (KONIEC)
	{
		std::cin >> tmp_1;		//std::cout << "\nNR" << ++nr;//DEBUG ONLY

		if (tmp_1 == "size"){
			std::cin >> tmp_2;
			Tabela.SetRozmiar(tmp_2);
		} 
		else if (tmp_1 == "stop") 
		{
			KONIEC--;	//kasowanie tablicy jest przy nowym size
			//			std::cout << "\nKONIEC " << KONIEC;
		} 
		else if (tmp_1 == "print")  
		{
			Tabela.print();
		} 
		else if (tmp_1 == "add") 
		{
			std::cin >> tmp_2;	//klucz
			std::cin >> tmp_1;	//lancuch
			Tabela.add(tmp_2, tmp_1);
		} 
		else if (tmp_1 == "delete") 
		{
			std::cin >> tmp_2;
			//std::cout << "DEBUG_DELETE " << tmp_2 << "\n";
			Tabela.Zeruj(tmp_2);
			Tabela.Porzadkuj(Tabela.Haszuj(tmp_2) + 1);//Debug
		}
	}

	return 0;
}

//tak na koniec bo bedzie najwiecej zajmowac
void CircleTable::Porzadkuj(int index)
{
	//sprawdza czy hasz sie zgadza
	//jak nie to jeden do gory

	int startowy = index;
	bool niezgodnyKlucz = false;
	bool czyJestMiejsce = false;//			std::cout << "_DEBUG";

	while (Tab[index].dane)//+1????? RACZEJ NIE
	{//										std::cout << "DEBUG_";
		//czy hasz sie zgadza
		if ( Haszuj(Tab[index].klucz) != index) {
			niezgodnyKlucz = true;//			std::cout << "1";
		}

					

		//czy jest wolne miejsce
		if (index == 0) {
			if (!Tab[rozmiar - 1].dane) {
				czyJestMiejsce = true;//		std::cout << "1";
			}
		}
		else {
			if (!Tab[index - 1].dane){
				czyJestMiejsce = true;//		std::cout << "1";
			}
		}

		//jak tak to przenosi
		if (niezgodnyKlucz && czyJestMiejsce) {
			Tab[index - 1] = Tab[index];
			//Zeruj(index);

			Tab[index].klucz = 0;
			for (int i = 0; i < 9; i++) {
				Tab[index].lancuch[i] = '\0';
			}
			Tab[index].dane = false;
		}

		if (index == rozmiar - 1){
			index = 0;
		}
		else {
			index++;
		}

		//sprawdzenie czy przeszedl cala tablice
		if (startowy == index) {
			break;
		}

		//zerowanie wartosci przed kolejnym przebiegiem
		niezgodnyKlucz = false;
		czyJestMiejsce = false;
	}

	return;
}