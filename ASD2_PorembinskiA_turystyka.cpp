#include <iostream>
#include <vector>
#include <algorithm>	//potrzebne do std::sort() w Kruskal'u

struct Krawedz{
	int Wezel1;
	int Wezel2;
	int Waga;

	//potrzebne do sort()
	bool operator<(Krawedz const& k) {
		return Waga < k.Waga;
	}
	bool operator>(Krawedz const& k) {
		return Waga > k.Waga;
	}
} TMPKrawedz;

struct Wezel{
	int Rodzic;		//jak 0 to nie istnieje
	int Wierzcholek;
	int Dziecko1;	//jak 0 to nie istnieje
	int Dziecko2;	//jak 0 to nie istnieje
} WezelTMP;

int main() {
	//std::vector<Krawedz> Graf;
	int LiczbaMiast, LiczbaDrog;
	int NrMiasta1, NrMiasta2, LiczbaPasazerow;
	int PoczatekTrasy, KoniecTrasy, DoPrzewiezienia;

	std::cin >> LiczbaMiast;
	std::cin >> LiczbaDrog;

	//Krawedz* Graf = new Krawedz[LiczbaDrog];
	std::vector<Krawedz> Graf(LiczbaDrog);
	//Krawedz TMP;

	for (int i = 0; i < LiczbaDrog; i++) {
		//drogi miedzy miastami
		std::cin >> NrMiasta1;
		std::cin >> NrMiasta2;
		std::cin >> LiczbaPasazerow;

		//TMPKrawedz.Wezel1 = NrMiasta1;
		//TMPKrawedz.Wezel2 = NrMiasta2;
		//TMPKrawedz.Waga = 0 - LiczbaPasazerow;
		TMPKrawedz = { NrMiasta1, NrMiasta2, 0 - LiczbaPasazerow };

		//Graf.push_back(TMP);
		Graf[i] = TMPKrawedz;
	}

	//Kruskal
	Krawedz* Pomoc = new Krawedz[LiczbaDrog];
	std::vector< std::vector<Wezel> > Las(LiczbaMiast);

	//posortowanie od min do max 
	std::sort(Graf.begin(), Graf.end());

	//stworzenie lasu
	for (int i = 0; i < LiczbaMiast; i++) {
		WezelTMP = { 0, i + 1, 0, 0 };
		Las[i].push_back(WezelTMP);
	}

	//robienie MDR
	for (int i = 0; i < LiczbaDrog; i++){

	}

	//DEBUG ONLY!!
	std::cout << "Graf: \n";
	for (int i = 0; i < LiczbaDrog; i++){
		std::cout << Graf[i].Wezel1 << "-" << Graf[i].Wezel2 << "  " << Graf[i].Waga << "\n";
	}

	//DEBUG ONLY!!
	std::cout << "\nLas: \n";
	for (int i = 0; i < LiczbaMiast; i++) {
		std::cout << Las[i][0].Wierzcholek << "  ";
	}

	/*while (true){
		//skad dokad i ile
		std::cin >> PoczatekTrasy;
		std::cin >> KoniecTrasy;
		if (PoczatekTrasy == 0 && KoniecTrasy == 0) {
			break;
		}
		std::cin >> DoPrzewiezienia;
	}*/

	return 0;
}