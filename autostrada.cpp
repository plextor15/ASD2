#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <stdlib.h>
#include <math.h>

const int LiczbaSymulacji = 1000; //finalnie 2000
const double pi = 3.14159265358979323846;
double CalkowityCzasJazdy;

double Los01()
{
	return (1.0 * rand()) / RAND_MAX;
}

int LosDyskretna(int max, double tab[]) //nie double
{
	double r;
	int j;
	bool check;

	do
	{
		r = Los01();
		j = rand() % max;
		if (r <= tab[j])
		{
			return j;	//max tyle postojow ile prawdopodob w tabeli
			//check = false;
		}
		else
		{
			check = true;
		}
	} while (check);

	return -1;
}

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

double RozkladTrojkatny(double x_od, double x_do)
{
	double tmp;
	double x = Los01();
	
	if (x <= 0.5)
	{
		tmp = sqrt(2 * x);
	}
	else
	{
		tmp = 2 - sqrt(2 * (1 - x));
	}

	return (x_do - x_od) * tmp + x_od;
}

int main()	//wszystkie czasy w minutach, odleglosci w kilometrach
{
	srand(time(NULL));
	double tmp = 0;
	bool check = true;


	const int ilePoryDnia = 3;
	double PrawdopodPoraDnia[ilePoryDnia] = { 0.29169, 0.54171, 0.16668 };
	double SzybkoscPoraDnia_miasto[ilePoryDnia] = { 1.2, 1, 0.6 };
	const double PredkoscWMiescie = 0.833;	// 50km/h w km/min
	// 1h/24 = 0.04167
	// noc 23-6 = 7h 60km/h - 1.2
	// dzien = 13h 50km/h - 1
	// ok 8 i ok 16 = 4h 30km/h - 0.6

	int PoraWyjazdu, PoraWjazdu;
	double CzasWyjazdu, CzasWjazdu;
	
	double WielkoscKorkow;
	const double maxKorek = 0.1;	//np: 5km/h dla 50km/h
	const double KmDoAutostrady = 10.5; //odleglosc od wjazdu/wyjazdu z autostrady do miejsca docelowego w miescie


	const int ileRodzajePogody = 4; //bardzo dobra, srednia, zla, fatalna
	double PrawdopodRodzajPogody[ileRodzajePogody] = { 0.7, 0.5, 0.1, 0.02 };
	double PredkoscRodzajPogody[ileRodzajePogody] = { 1, 0.9, 0.7, 0.5 };
	int RodzajPogody;
	double PredkoscPogoda;

	const double PredkoscNaAutostradzie = 2.33;
	const int ileStylJazdy = 2; //szybka, ekonomiczna
	double PrawdopodStylJazdy[ileStylJazdy] = { 0.6, 0.4 };
	double PredkoscStylJazdy[ileStylJazdy] = { 1, 0.8 };
	int StylJazdy;
	double PredkoscStylu;

	double iloscTirow;	// <0-1>
	const double minPredkoscBoTiry = 0.7; // % predkosci jakby ich nie bylo
	double PredkoscBoTiry; // to nie jest prekosc tirow, tylko % max predkosci jakby ich nie bylo

	double PredkoscWynikowa; // % max predkosci jaka moze byc
	double PredkoscJazdyAutostrada;
	double CzasJazdyAutostrada;


	const int ileBramek = 4;
	const double maxCzasNaBramce = 11;
	double CzasNaBramce;
	double CalkowityCzasBramek;


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



	double GestoscRuchu;
	double maxGestoscRuchu = 0.5; //polowa mozliwej predkosci

	//do dyskretnej
	//int j;
	//double r;
	//metoda Boxa-Millera
	//double u1, u2, R, Th, z1, z2;

	std::ofstream wynikowy;
	wynikowy.open("wynikowy.txt");

	for (size_t L = 0; L < LiczbaSymulacji; L++)	//petla przebiegu jednej symulacji
	{
		CalkowityCzasJazdy = 0;

		//WYJAZD Z MIASTA
		PoraWyjazdu = LosDyskretna(ilePoryDnia, PrawdopodPoraDnia);

		WielkoscKorkow = Los01();
		CzasNaBramce = Los01() * maxCzasNaBramce;

		CzasWyjazdu = ((-(1 - maxKorek) * WielkoscKorkow + 1) * SzybkoscPoraDnia_miasto[PoraWyjazdu]) * KmDoAutostrady + CzasNaBramce;

		//JAZDA PO AUTOSTRADZIE
		RodzajPogody = LosDyskretna(ileRodzajePogody, PrawdopodRodzajPogody);
		PredkoscPogoda = PredkoscRodzajPogody[RodzajPogody];
		StylJazdy = LosDyskretna(ileStylJazdy, PrawdopodStylJazdy);
		PredkoscStylu = PredkoscStylJazdy[StylJazdy];
		iloscTirow = Los01();
		PredkoscBoTiry = 1 - (1-minPredkoscBoTiry) * iloscTirow;

		/*if (PredkoscPogoda > PredkoscStylu)
		{
			PredkoscPogoda = PredkoscStylu;
		}

		if (PredkoscPogoda > PredkoscBoTiry)
		{
			PredkoscPogoda = PredkoscBoTiry;
		}*/
		if (true)
		{

		}
		
		CzasJazdyAutostrada = 0 * 0;

		//BRAMKI DO OPLAT
		tmp = 0;
		CalkowityCzasBramek = 0;
		for (size_t i = 0; i < ileBramek; i++)
		{
			tmp = N01_BM(0, 1.2);
			tmp = abs(tmp);
			tmp *= maxCzasNaBramce;
			CalkowityCzasBramek += tmp;
			//CzasNaBramce += 0.2; //czas na obsluzenie nas
		}


		//POSTOJE
		PostojeCzasCalkowity = 0;
		ilePostojow = LosDyskretna(maxPostojow, TabProbPostojow);
		
		for (size_t i = 0; i < ilePostojow; i++)//co bedzie robione na kazdym postoju
		{
			if (Los01() > 0.5)//wyjscie do toalety - TAK/NIE
			{
				czyToaleta = true;
			}
			else
			{
				czyToaleta = false;
			}
			//std::cout << "Toaleta: " << czyToaleta << "\n";	//FOR DEBUG ONLY!!! 

			if (Los01() > PrawdopodobZjedzeniaCzegos)//czy zjedzenie czegos
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
		
		//WJAZD Z MIASTA
		PoraWjazdu = (PoraWyjazdu + 2) % ilePoryDnia; //finalnie moze byc inaczej liczone
		GestoscRuchu = RozkladTrojkatny(0, 1);
		//CzasWjazdu = ((-(1 - maxGestoscRuchu) * GestoscRuchu + 1) * SzybkoscPoraDnia_miasto[PoraWjazdu]) * KmDoAutostrady;

		//CalkowityCzasJazdy = CzasWyjazdu + CalkowityCzasBramek + PostojeCzasCalkowity + CzasWjazdu;
		//std::cout << "\n" << CalkowityCzasJazdy << "\n"; //FOR DEBUG ONLY!!!
	}


	wynikowy.close();
	return 0;
}
