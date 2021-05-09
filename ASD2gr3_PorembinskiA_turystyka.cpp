//  Dijkstry() wykorzystany z
// https://eduinf.waw.pl/inf/alg/001_search/0138.php

#include <iostream>
#include <vector>
using namespace std;

struct Krawedz {
	int Wezel1;
	int Wezel2;
	int Waga;
}TMPKrawedz;

struct Droga {
	int Wezel1;
	int Wezel2;
	int Ilu;
}TMPDroga;

struct slistEl {
    slistEl* next;
    int v, w;           // numer wezla docelowego i waga krawedzi
};

const int MAXINT = 2147483647;

Krawedz* Graf;
std::vector<Droga> Przewozy;
std::vector<Krawedz> DrogaDoCelu;
int LiczbaMiast, LiczbaDrog;

int Dijkstry(int startowy, int koncowy) {
    int iluPasazerow;
    DrogaDoCelu.clear();
    DrogaDoCelu.shrink_to_fit();

    int i, j, m, n, v, u, w, x, y, sptr, * d, * p, * S;
    bool* QS;           // Zbiory Q i S
    slistEl** graf;     // Tablica list sąsiedztwa
    slistEl* pw, * rw;

    //cin >> v >> n >> m; // Węzeł startowy, liczba wierzchołków i krawędzi
    v = startowy;
    n = LiczbaMiast;
    m = LiczbaDrog;

    // Tworzymy tablice dynamiczne
    d = new int[n];          // Tablica kosztów dojścia
    p = new int[n];          // Tablica poprzedników
    QS = new bool[n];        // Zbiory Q i S
    graf = new slistEl * [n]; // Tablica list sąsiedztwa
    S = new int[n];          // Stos
    sptr = 0;                   // Wskaźnik stosu

    // Inicjujemy tablice dynamiczne
    for (i = 0; i < n; i++) {
        d[i] = MAXINT;
        p[i] = -1;
        QS[i] = false;
        graf[i] = NULL;
    }

    // Odczytujemy dane wejściowe
    for (i = 0; i < m; i++) {
        //cin >> x >> y >> w;    // Odczytujemy krawędź z wagą
        x = Graf[i].Wezel1;
        y = Graf[i].Wezel2;
        w = Graf[i].Waga;

        pw = new slistEl;      // Tworzymy element listy sąsiedztwa
        pw->v = y;             // Wierzchołek docelowy krawędzi
        pw->w = w;             // Waga krawędzi
        pw->next = graf[x];
        graf[x] = pw;           // Element dołączamy do listy
    }

    d[v] = 0; // Koszt dojścia v jest zerowy

    for (i = 0; i < n; i++) {// Wyznaczamy ścieżki
        for (j = 0; QS[j]; j++); {// Szukamy wierzchołka w Q o najmniejszym koszcie d
            for (u = j++; j < n; j++) {
                if (!QS[j] && (d[j] < d[u])) {
                    u = j;
                }
            }
        }

        QS[u] = true;// Znaleziony wierzchołek przenosimy do S

        // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q
        for (pw = graf[u]; pw; pw = pw->next)
            if (!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
            {
                d[pw->v] = d[u] + pw->w;
                p[pw->v] = u;
            }
    }




    //TO, PO CO DZIALA TA FUNKCJA
    std::vector<int> ghjkl;
    for (j = koncowy; j > -1; j = p[j]) {
        S[sptr++] = j;
    }
    while (sptr) {
        //cout << S[--sptr] << " ";
        ghjkl.push_back(S[--sptr]);
    }

    int najwiekszy = 0 - (MAXINT-100); //"ujemna nieskonczonosc"
    for (size_t i = 0; i < ghjkl.size()-1; i++){
        int w1 = ghjkl[i];
        int w2 = ghjkl[i + 1];

        for (size_t i = 0; i < LiczbaDrog; i++){
            if ((Graf[i].Wezel1 == w1) && (Graf[i].Wezel2 == w2)) {
                if (Graf[i].Waga > najwiekszy){
                    najwiekszy = Graf[i].Waga;
                }
                break;
            }
        }
    }

    iluPasazerow = najwiekszy;


    //DEBUG ONLY!!
    cout << "\n\n=================================\n";
    for (i = 0; i < n; i++)
    {
        cout << i << ": ";
        for (j = i; j > -1; j = p[j]) 
            S[sptr++] = j;
        while (sptr) 
            cout << S[--sptr] << " ";
        cout << "$" << d[i] << endl;
    }
    //DEBUG ONLY!!

    //Czysczenie po sobie
    delete[] d;
    delete[] p;
    delete[] QS;
    delete[] S;

    for (i = 0; i < n; i++) {
        pw = graf[i];
        while (pw) {
            rw = pw;
            pw = pw->next;
            delete rw;
        }
    }

    delete[] graf;

	return iluPasazerow;
}

int main() {
	//int LiczbaMiast, LiczbaDrog;
	
    int NrMiasta1, NrMiasta2, LiczbaPasazerow;
	std::cin >> LiczbaMiast >> LiczbaDrog;
	Graf = new Krawedz[LiczbaDrog];

	for (int i = 0; i < LiczbaDrog; i++) {	//drogi miedzy miastami
		std::cin >> NrMiasta1 >> NrMiasta2 >> LiczbaPasazerow;

		TMPKrawedz = { NrMiasta1-1, NrMiasta2-1, 0-LiczbaPasazerow };
		Graf[i] = TMPKrawedz;
	}

	int skad, dokad, ilu;
	while (true){
		std::cin >> skad >> dokad;
		if (skad == 0 && dokad == 0){
			break;
		} else {
			std::cin >> ilu;
			TMPDroga = {skad-1, dokad-1, ilu};
			Przewozy.push_back(TMPDroga);
		}
	}

    int ileKursow, przepustowosc;
    for (size_t i = 0; i < Przewozy.size(); i++){
        przepustowosc = Dijkstry(Przewozy[i].Wezel1, Przewozy[i].Wezel2);
        przepustowosc = 0 - przepustowosc;

        przepustowosc--; //bo kierowca
        ileKursow = Przewozy[i].Ilu / przepustowosc;

        //std::cout << ileKursow << "\n";
        std::cout << "\n\n" << ileKursow << "\n"; //DEBUG ONLY!!
    }

	return 0;
}