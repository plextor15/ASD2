#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <stdlib.h>
#include <math.h>

const int LiczbaSymulacji = 10; //finalnie 2000
const double pi = 3.14159265358979323846;

double Los01()
{
	return (1.0 * rand()) / RAND_MAX;
}

//double LosDyskretna(int max)
//{
//	double r = Los01();
//	int j = rand() % max;
//
//	return;
//}

double N01_BM(double my, double sigma)	//rozkaad N(0,1) – metoda Boxa-Millera
{
	double u1, u2, R, Th, z1, z2;

	u1 = Los01();
	u2 = Los01();

	R = sqrt(-2 * log(u1));
	Th = 2 * pi * u2;

	z1 = R * sin(Th);
	z2 = R * cos(Th);

	return (z1 * sigma) + my;
}

int main()	//wszystkie czasy w minutach, odleglosci w kilometrach
{
	srand(time(NULL));
	double tmp = 0;
	bool check = true;


	const int ilePoryDnia = 3;
	double PrawdopodPoraDnia[ilePoryDnia] = { 0.29169, 0.54171, 0.16668 };
	// 1h/24 = 0.04167
	// noc 23-6 = 7h 60km/h - 1.2
	// dzien = 13h 50km/h - 1
	// ok 8 i ok 16 = 4h 30km/h - 0.6
	int PoraWyjazdu, PoraWjazdu;
	double CzasWyjazdu, CzasWjazdu;
	double SzybkoscPoraDnia_miasto[ilePoryDnia] = { 1.2, 1, 0.6 };
	const double PredkoscWMiescie = 0.833;	// 50km/h w km/min
	double WielkoscKorkow;
	const double maxKorek = 0.1;	//np: 5km/h dla 50km/h
	const double KmDoAutostrady = 10.5; //odleglosc od wjazdu/wyjazdu z autostrady do miejsca docelowego w miescie

	const double maxCzasNaBramce = 30;
	double CzasNaBramce;


	int ilePostojow;
	const int maxPostojow = 5;
	double TabProbPostojow[maxPostojow] = { 0.05, 0.7, 0.5, 0.1, 0.02 };	//indexy+1 to liczba postojow
	//double TabCzasyPostojow[maxPostojow];
	double PostojeCzasCalkowity;
	bool czyToaleta;
	double CzasWToalecie = 3.5;
	double CzasZjedzenia;
	double maxCzasZjedzenia;
	double PrawdopodobZjedzeniaCzegos = 0.4;
	double myZjedzenia = 3, sigmaZjedzenia = 0.65; //N(0,2) Boxa-Mullera

	const int ileBramek = 4;

	//do dyskretnej
	int j;
	double r;

	//metoda Boxa-Millera
	double u1, u2, R, Th, z1, z2;

	std::ofstream wynikowy;
	wynikowy.open("wynikowy.txt");

	for (size_t L = 0; L < LiczbaSymulacji; L++)	//petla przebiegu jednej symulacji
	{
		//WYJAZD Z MIASTA
		//losowanie dyskretne pory dnia
		do
		{
			r = Los01();
			j = rand() % ilePoryDnia;
			if (r <= PrawdopodPoraDnia[j])
			{
				PoraWyjazdu = j;	//max tyle postojow ile prawdopodob w tabeli
				check = false;
			}
			else
			{
				check = true;
			}
		} while (check);

		WielkoscKorkow = Los01();
		CzasNaBramce = Los01() * maxCzasNaBramce;

		CzasWyjazdu = ( (-(1-maxKorek)*WielkoscKorkow+1) * SzybkoscPoraDnia_miasto[PoraWyjazdu]) * KmDoAutostrady + CzasNaBramce;

		//POSTOJE
		PostojeCzasCalkowity = 0;
		//ilosc postojow losowana z rozkladu zmiennej dyskretnej
		do
		{
			r = Los01();
			j = rand() % maxPostojow;
			if (r <= TabProbPostojow[j])
			{
				ilePostojow = j;	//max tyle postojow ile prawdopodob w tabeli
				check = false;
			}
			else
			{
				check = true;
			}
		} while (check);

		//co bedzie robione na kazdym postoju
		for (size_t i = 0; i < ilePostojow; i++)
		{
			//wyjscie do toalety - TAK/NIE
			if (Los01() > 0.5)
			{
				czyToaleta = true;
			}
			else
			{
				czyToaleta = false;
			}
			//std::cout << "Toaleta: " << czyToaleta << "\n";	//FOR DEBUG ONLY!!! 

			//czy zjedzenie czegos
			if (Los01() > PrawdopodobZjedzeniaCzegos)
			{
				CzasZjedzenia = N01_BM(myZjedzenia, sigmaZjedzenia);
			}
			else
			{
				CzasZjedzenia = 0;
			}

			if (czyToaleta)
			{
				PostojeCzasCalkowity += CzasWToalecie + CzasZjedzenia;
			}
			else
			{
				PostojeCzasCalkowity += CzasZjedzenia;
			}
			PostojeCzasCalkowity += 2;	//np: zaparkowanie
			//std::cout << "Czas zjedzenia: " << CzasZjedzenia << "\n";	//FOR DEBUG ONLY!!! 
		}
		//std::cout << "calkowity czas: " << PostojeCzasCalkowity << " w tym - " << ilePostojow << "\n\n\n";	//FOR DEBUG ONLY!!!

	//BRAMKI DO OPLAT



	}
	//wyjazd z miasta

	//jazda autostrada

	//bramki do oplat



	//wjazd do miasta

	wynikowy.close();
	return 0;
}
