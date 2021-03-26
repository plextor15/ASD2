/*
*	Kolejka
*	Adam Porembinski
*/

#include <iostream>

int main() {
	short ileZestawow;
	short nrDanejWej;
	short min;
	short tmp;
	
	short* tab1;	//pierwsza linijka punktow
	short* tab2;	//druga linijka punktow

	short ileLiczb01;
	short ileLiczb02;

	std::cin >> ileZestawow;
	nrDanejWej = 2 * ileZestawow;

	bool zero = false;//true jak z porownania wyjdzie 0
	while (nrDanejWej > 0)
	{
		//pierwsza tablica
		std::cin >> ileLiczb01;
		tab1 = new short[ileLiczb01];
		for (short i = 0; i < ileLiczb01; i++)
		{
			std::cin >> tab1[i];
		}

		//druga tablica
		std::cin >> ileLiczb02;
		tab2 = new short[ileLiczb02];
		for (short i = 0; i < ileLiczb02; i++)
		{
			std::cin >> tab2[i];
		}

		min = 1005;	//bo jest wieksze niz najwieksza mozliwa roznica, a trzeba "wyzerowac"
		
		for (short i = 0; i < ileLiczb01; i++){
			for (short j = 0; j < ileLiczb02; j++){
				tmp = std::abs(tab1[i] - tab2[j]);

				if (tmp == 0){
					std::cout << "0\n";
					zero = true;
					break;
				}
				if (tmp < min){
					min = tmp;
				}
			}

			if (zero){
				break;
			}
		}

		if (!zero){
			std::cout << min << "\n";
		}
			
		zero = false;
		nrDanejWej -= 2;
		delete[] tab1;
		delete[] tab2;
	}

	return 0;
}