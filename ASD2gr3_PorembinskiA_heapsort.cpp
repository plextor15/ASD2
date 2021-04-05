/*
* 
*	https://eduinf.waw.pl/inf/alg/003_sort/0015.php
*/
#include <iostream>

int ileTestow = 0;

int main() {
	long *dane = NULL;
	int ileDanych = 0;

	//zmienne do petli sortowania
	int a, b;
	long tmp = 0;

	std::cin >> ileTestow;
	while (ileTestow > 0) {
		std::cin >> ileDanych;
		dane = new long[ileDanych + 1];

		//wczytywanie liczb do tablicy
		dane[0] = 0;	//nie bedzie dotykana
		for (int j = 1; j < ileDanych + 1; j++) {
			std::cin >> dane[j];
			std::cout << dane[j] << ' '; //DEBUG ONLY!!
		}

		//tworzenie kopca
		for (int i = 0; i < ileDanych; i++) {
			tmp = dane[i];
			a = i;
			b = a / 2;

			while ((tmp > dane[b])&&(b > 0)) {
				dane[a] = dane[b];
				a = b;
				b = a / 2;
			}
			dane[a] = tmp;
		}

		//DEBUG ONLY!!
		std::cout << '\n';
		for (int i = 0; i < ileDanych; i++) {
			std::cout << dane[i] << ' ';
		}
		//DEBUG ONLY!!

		delete[] dane;
		dane = NULL;
		ileTestow -= 1;
	}

	return 0;
}
