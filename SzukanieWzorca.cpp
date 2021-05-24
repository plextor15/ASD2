#include <fstream>
#include <iostream>
#include <string>
#include <math.h>

int LiczbaPrzypadkow;
std::string DoZnalezienia;
std::string CiagZPliku = "";
//std::vector<char> CiagZPliku;
std::ifstream Plik;

const int LP = 227;//157    97;
int N;			//dlugosc wzorca
int P = 256;	//podstawa systemu dla ASCII

int H;	//hash wzorca
int HzPoprzedniego = 0;
int HzPliku = -1;	//hash z ciagu z pliku
int Licznik;	//na ktorej pozycji jest kursor z ifstream w pliku
int DlugoscPliku;
int DoPotegi = 0;


//int Suma(std::string ciagZnakow) { //do policzenia hasha
//	long long wynik = 0;
//	long long tmp = 0;
//	for (int i = 0; i < N; i++){
//		tmp = (ciagZnakow[i] * ((int)pow(P, N - i - 1))) % LP;
//		std::cout << "\n  " << ciagZnakow[i] << "  256^" << i;	//DEBUG ONLY!!
//		wynik += tmp;
//		//wynik = (wynik + tmp) % LP;
//	}
//	wynik = wynik % LP;
//	while (wynik < 0){
//		wynik += LP;
//	}
//	return (int)wynik;
//}

int power_modulo_fast(int a, int b)
//http://www.algorytm.org/przetwarzanie-tekstu/algorytm-kr-karpa-rabina/kr-c.html
//funkcja podnoszaca do potegi
//(c)2006 Tomasz Lubinski
{
	int i;
	int result = 1;
	long int x = a % LP;

	for (i = 1; i <= b; i <<= 1)
	{
		x %= LP;
		if ((b & i) != 0)
		{
			result *= x;
			result %= LP;
		}
		x *= x;
	}

	return result % LP;
}

int Suma(std::string ciagZnakow) { //do policzenia hasha			//DOBRE
	long long wynik = 0;
	long long tmp = 0;

//std::cout << "\n ------ " << N << " -----";	//DEBUG ONLY!!
	for (int i = N-1; i >= 0; i--){
		//tmp = ((long long)pow(P,i) % LP);
		tmp = ((long long)power_modulo_fast(P, i) % LP);
		tmp = (tmp * (int)ciagZnakow[N - 1 - i]) % LP;
//std::cout << "\n  " << ciagZnakow[N-1-i] << "  256^" << i << " = " << (int)ciagZnakow[N - 1 - i];	//DEBUG ONLY!!
		//wynik = (wynik + tmp) % LP;
		wynik = wynik + tmp;
	}
	wynik = wynik % LP;
	while (wynik < 0) {
		wynik += LP;
	}
//std::cout << "\n ------ " << wynik << " -----";	//DEBUG ONLY!!
	return (int)wynik;
}

int f(int h, int out, int in) {
//std::cout << " | " << x << " | ";//DEBUG ONLY!!
	int wynikTMP = ((((h - (out * DoPotegi) % LP) * P) % LP) + in) % LP;
	//long long wynikTMP = ((long long)h - (long long)out * (long long)DoPotegi) * (long long)P + (long long)in;
	//wynikTMP = wynikTMP % (long long)LP;

	while (wynikTMP < 0){
		//wynikTMP = wynikTMP + (long long)LP;
		wynikTMP += LP;
	}

	return wynikTMP;
}

bool BruteForce() {
	bool znalezionoWzorzec = true;
//std::cout << " brute ";//DEBUG ONLY!!
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
	Plik >> std::noskipws >> przychodzacy;
	CiagZPliku += przychodzacy;

	HzPliku = f(HzPoprzedniego, (int)wylatujacy, (int)przychodzacy);	//obliczanie hasha dla aktualnie wyciagnietego
	//HzPliku = Suma(CiagZPliku); //DEBUG ONLY!!
	if (HzPliku == H) {
//std::cout << " $$ " << HzPliku << "==" << H;//DEBUG ONLY!!
		if (BruteForce()) {
//std::cout << "B";//DEBUG ONLY!!
			//std::cout << Licznik << " ";	//jakby trafil
std::cout << " [" << Licznik << "] ";	//DEBUG ONLY!!
		}
		
//else { std::cout << "X "; } //DEBUG ONLY!!
	}

std::cout << "\n" << CiagZPliku << "  in/out " << przychodzacy << "/" << wylatujacy << "  " << (int)przychodzacy << "/" << (int)wylatujacy << "  ";
std::cout << ", " << HzPoprzedniego << "  " << HzPliku << "   #:" << Suma(CiagZPliku);//DEBUG ONLY!!

	HzPoprzedniego = HzPliku;
	return;
}

int main() {
	////DEBUG ONLY!!
	//char lolxd;
	//for (size_t i = 0; i < 256; i++)
	//{
	//	lolxd = i;
	//	std::cout << i << ": " << lolxd << "\n";
	//}
	//std::cin >> lolxd;
	////DEBUG ONLY!!

	std::ifstream tenSamPlik;
	std::string testowanie;

	std::string NazwaPliku;
	char charTMP;

	std::cin >> LiczbaPrzypadkow;
	
	//glowna petla programu
	while (LiczbaPrzypadkow > 0){
		//DoPotegi = 0;
		H = 0;
		Licznik = 0;
		std::cin >> NazwaPliku;

		//sprawdzenie jakiej dlugosci jest plik
		tenSamPlik.open(NazwaPliku);
		//tenSamPlik >> std::noskipws >> testowanie;	//debug
		std::getline(tenSamPlik, testowanie);
//std::cout << testowanie; std::cin >> NazwaPliku; //DEBUG ONLY!!
		DlugoscPliku = (int)testowanie.length();
		tenSamPlik.close();
		//koniec sprawdzania dlugosci

		Plik.open(NazwaPliku);

		//std::cin >> DoZnalezienia;
		//std::cin >> std::noskipws >> DoZnalezienia;
		std::getline(std::cin, DoZnalezienia); //chyba nie dziala
		std::getline(std::cin, DoZnalezienia); //chyba nie dziala
		N = DoZnalezienia.length();
		H = Suma(DoZnalezienia);	//hash do wzorca

		//policzenie P^(N-1)
		//DoPotegi = (int)pow(P, N - 1);
		long long uiop = power_modulo_fast(P, N - 1);
		uiop = uiop % LP;
		DoPotegi = (int)uiop;
		//DoPotegi = DoPotegi % LP; 
		if (DoPotegi < 0){
			DoPotegi += LP;
		}
		std::cout << "\n" << N << "<" << DoPotegi << ">" << P << "\n\n";

		//poczatkowe zaciagniecie danych z pliku
		for (size_t i = 0; i < DoZnalezienia.length(); i++) {
			Plik >> std::noskipws >> charTMP;
			CiagZPliku.push_back(charTMP);
		}
		// i policzenie hasha
		HzPoprzedniego = Suma(CiagZPliku);
		if (HzPoprzedniego == H){
			if (BruteForce()) {
//std::cout << "B";//DEBUG ONLY!!
				std::cout << Licznik << " ";	//jakby znalazl na pierwszym miejscu
			}
		}

//std::cout << "\n  1. " << CiagZPliku << "  #: " << HzPoprzedniego << "\n";	//DEBUG ONLY!!
		
		//przesuwanie sie po pliku
		int tmpInt = DlugoscPliku - N;
		for (int i = 0; i < tmpInt; i++){
			KR();
		}

		//na koniec
		CiagZPliku = "";
		Plik.close();
		LiczbaPrzypadkow--;
std::cout << "\n |END " << H << "|_" << DoZnalezienia << "_| " << NazwaPliku << "-" << DlugoscPliku << " |" << DoPotegi << " :" << N << "\n\n";//DEBUG ONLY!!
		std::cout << "\n";
	}

	return 0;
}