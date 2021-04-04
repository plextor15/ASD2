#include <iostream>

int ileTestow = 0;

int main() {
	long *dane = NULL;
	int ileDanych = 0;

	std::cin >> ileTestow;
	for (int i = 0; i < ileTestow; i++) {
		std::cin >> ileDanych;
		dane = new long[ileDanych];

		for (int j = 0; j < ileDanych; j++) {
			std::cin >> dane[j];

		}
	}

	return 0;
}
