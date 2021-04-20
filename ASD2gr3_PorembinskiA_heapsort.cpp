/*
*	Kopcowanie na podstawie schematu ze strony:
*	https://eduinf.waw.pl/inf/alg/003_sort/0015.php
*/
#include <iostream>

void kopcowanie(long *dane, int start, int end) {
	long tmp;
	int a, b;
	int i = start;

	while (i <= end) {
	//for (i <= end; i++) {
		tmp = dane[i];
		a = i;
		b = a / 2;

		while ((tmp > dane[b])&&(b > 0)) {
			dane[a] = dane[b];
			a = b;
			b = a / 2;
		}
		dane[a] = tmp;

		i++;
	}

	return;
}

void zamiana(long *dane, int ktory, int koniec) {
	long tmp = dane[koniec];
	dane[koniec] = dane[ktory];
	dane[ktory] = tmp;
	return;
}

int ileTestow = 0;

int main() {
	long *dane = NULL;
	int ileDanych = 0;

	//zmienne do petli sortowania
	//int a, b;
	//long tmp = 0;

	std::cin >> ileTestow;
	while (ileTestow > 0) {
		std::cin >> ileDanych;
		dane = new long[ileDanych + 1];

		//wczytywanie liczb do tablicy
		dane[0] = 0;	//nie bedzie dotykana
		for (int j = 1; j < ileDanych + 1; j++) {
			std::cin >> dane[j];
			//std::cout << dane[j] << ' '; //DEBUG ONLY!!
		}
		//std::cout << "\n----------------------\n"; //DEBUG ONLY!! Tylko do testowania

		////DEBUG ONLY!!
		//std::cout << '\n';
		//for (int i = 0; i < ileDanych+1; i++) {
		//	std::cout << dane[i] << ' ';
		//} std::cout << "\nWaskol\n";
		////DEBUG ONLY!!

		//tworzenie kopca
		kopcowanie(dane, 1, ileDanych);

		//wypisanie kopca
		for (int i = 1; i < ileDanych + 1; i++) {
			std::cout << dane[i] << ' ';
		}
		std::cout << '\n';
		
		//wybieranie wierzcholka
		for (int i = 0; i < ileDanych-1; i++){ //debug
			zamiana(dane, 1, ileDanych-i);
			kopcowanie(dane, 1, ileDanych-1-i);

			if (2 < ileDanych - i) {
				for (int j = 1; j < ileDanych - i; j++) {
					std::cout << dane[j] << ' ';
				}
			std::cout << '\n';
			}
		}

		//wypisanie posortowanych
		for (int i = 1; i < ileDanych + 1; i++) {
			std::cout << dane[i] << ' ';
		}
		std::cout << '\n';

		////DEBUG ONLY!!
		//std::cout << '\n';
		//for (int i = 0; i < ileDanych+1; i++) {
		//	std::cout << dane[i] << ' ';
		//}//DEBUG ONLY!!

		delete[] dane;
		dane = NULL; //debug
		ileTestow -= 1;
		std::cout << '\n'; //pusta linia miedzy przypadkami
	}

	return 0;
}
