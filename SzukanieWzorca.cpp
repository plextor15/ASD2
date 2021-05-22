#include <fstream>
#include <iostream>
#include <string>
//#include <vector>

int LiczbaPrzypadkow;
std::string DoZnalezienia;
std::string CiagZPliku = "";
//std::vector<char> CiagZPliku;
std::ifstream Plik;

const int LP = 157;//157;
int N;			//dlugosc wzorca
int P = 256;	//podstawa systemu dla ASCII

int H;	//hash wzorca
int HzPoprzedniego = 0;
int HzPliku = -1;	//hash z ciagu z pliku
int Licznik;	//na ktorej pozycji jest kursor z ifstream w pliku
int DlugoscPliku;


int Suma(std::string ciagZnakow) { //do policzenia hasha
	int wynik = 0;
	int tmp = 0;
	int w = P % LP;
	//int dlugosc = (int)ciagZnakow.length(); //mozliwe ze size_t

	for (int i = 0; i < N; i++){
		tmp = ((int)ciagZnakow[i] * (( w ^ (N - i - 1)) % LP)  ) % LP;
		wynik += tmp;
	}

	wynik = wynik % LP;
	return wynik;
}

int f(int h, int out, int in) {
	int wynikTMP = ((h - (out * (P ^ (N - 1) % LP)) % LP) * P + in) % LP;
	
	while (wynikTMP < 0){
		wynikTMP += LP;
	}

	return wynikTMP;
}

bool BruteForce() {
	bool znalezionoWzorzec = true;
	std::cout << " brute ";//DEBUG ONLY!!
	for (int i = 1; i < N; i++){
		if (CiagZPliku[i] != DoZnalezienia[i]) {
			znalezionoWzorzec = false;
			break;
		}
	}

	return znalezionoWzorzec;
}

void KR() {
	Licznik++;

	//wylatywanie znaku
	char wylatujacy = CiagZPliku[0];
	CiagZPliku.erase(CiagZPliku.begin()); //nie dziala - jednak dziala
	
	//przychodzenie znaku
	char przychodzacy;
	Plik >> przychodzacy;
	CiagZPliku += przychodzacy;

	//HzPliku = f(HzPoprzedniego, wylatujacy, przychodzacy);	//obliczanie hasha dla aktualnie wyciagnietego
	HzPliku = Suma(CiagZPliku);
	if (HzPliku == H) {
		if (BruteForce()) {
			std::cout << "B";//DEBUG ONLY!!
			std::cout << Licznik << " ";	//jakby trafil
		}
	}

std::cout << "\n" << CiagZPliku << "  " << HzPliku;//DEBUG ONLY!!

	HzPoprzedniego = HzPliku;
	return;
}

int main() {
	//std::ifstream* Tablica;//tablica z ifstreami, zeby kazdy przypadek testowy mial kursor w pliku na pozycji zerowej

	std::ifstream tenSamPlik;
	std::string testowanie;

	std::string NazwaPliku;
	char charTMP;
	//int hashZPliku;

	std::cin >> LiczbaPrzypadkow;
	//Tablica = new std::ifstream[LiczbaPrzypadkow];
	
	//glowna petla programu
	while (LiczbaPrzypadkow > 0){
		Licznik = 0;
		std::cin >> NazwaPliku;

		//sprawdzenie jakiej dlugosci jest plik
		tenSamPlik.open(NazwaPliku);
		tenSamPlik >> testowanie;
		DlugoscPliku = (int)testowanie.length();
		tenSamPlik.close();
		//koniec sprawdzania dlugosci

		Plik.open(NazwaPliku);

		std::cin >> DoZnalezienia;
		N = DoZnalezienia.length();
		H = Suma(DoZnalezienia);	//hash do wzorca

		//poczatkowe zaciagniecie danych z pliku
		for (size_t i = 0; i < DoZnalezienia.length(); i++) {
			Plik >> charTMP;
			CiagZPliku.push_back(charTMP);
		}
		// i policzenie hasha
		HzPoprzedniego = Suma(CiagZPliku);
		if (HzPoprzedniego == H){
			if (BruteForce()) {
				std::cout << "B";//DEBUG ONLY!!
				std::cout << Licznik << " ";	//jakby znalazl na pierwszym miejscu
			}
		}
		
		//przesuwanie sie po pliku
		int tmpInt = DlugoscPliku - N;
		for (int i = 0; i < tmpInt; i++){
			KR();
		}

		//na koniec
		CiagZPliku = "";
		Plik.close();
		LiczbaPrzypadkow--;
		std::cout << " | kuniec " << H << " " << DoZnalezienia << "  " << NazwaPliku << "  " << DlugoscPliku;//DEBUG ONLY!!
		std::cout << "\n";
	}

	return 0;
}