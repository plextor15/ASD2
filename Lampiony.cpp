#include <iostream>
#include <vector>
#include <limits>
#include <math.h>

struct coord{
	long long X;
	long long Y;
	//long double X;
	//long double Y;
	bool znacznik;
} TMPcoord;

long long IloczynWektor(coord A, coord B, coord H) {
	return (H.Y - A.Y) * (B.X - A.X) - (H.X - A.X) * (B.Y - A.Y);
}

//long double JakiKat(coord A, coord B, coord H) {}

int main() {
	/*long double w, q;
	while (true){
		std::cin >> w >> q;
		coord A = { 0,0 }, B = { 0,2 }, C = {w,q};
		std::cout << "\n\n" << IloczynWektor(A, B, C) << "\n\n";
	}*/

std::cout << "DEBUG 01\n ";
	std::vector<coord> Male, Duze;
	int maleLampiony, duzeLampiony;
	//long long x, y;

	int Poczatkowy;
	long long minX = std::numeric_limits<long long>::max(), minY = minX;
	long long wartX = 0, wartY = 0;

	std::cin >> duzeLampiony;
std::cout << "DEBUG 02\n ";
	for (int i = 0; i < duzeLampiony; i++) {
		std::cin >> TMPcoord.X >> TMPcoord.Y;
		TMPcoord.znacznik = true;
		Duze.push_back(TMPcoord);

		if (TMPcoord.Y < minY) {
			minY = TMPcoord.Y;
			Poczatkowy = i;
		}
		else if (TMPcoord.Y == minY) {
			if (TMPcoord.X < minX) {
				minX = TMPcoord.X;
				Poczatkowy = i;
			}
		}
	}
std::cout << "DEBUG 03\n ";
	std::cin >> maleLampiony;
	std::cout << "\n  " << duzeLampiony << " , " << maleLampiony;//DEBUG ONLY!!

std::cout << "\nDEBUG 04\n ";
	for (int i = 0; i < maleLampiony; i++) {
		std::cin >> TMPcoord.X >> TMPcoord.Y;
		TMPcoord.znacznik = true;
		Male.push_back(TMPcoord);
		
		std::cout << "\n  " << TMPcoord.X << " , " << TMPcoord.Y;//DEBUG ONLY!!
	}
std::cout << "\nDEBUG 05\n ";
	std::cout << "\n  " << duzeLampiony << " , " << maleLampiony << "\n\n";//DEBUG ONLY!!


	std::vector<coord> hull;
	int l = 0, p = 0, q;
	//calculating the leftmost point
	//int l = 0;
	//for (int i = 1; i < n; i++)
	//	if (points[i].x < points[l].x)
	//		l = i;
	//moving in the clockwise direction

	// ten kawalek na podstawie
	// https://www.tutorialspoint.com/convex-hull-jarvis-s-algorithm-or-wrapping-in-cplusplus
	do {
		//adding current point to result
		hull.push_back(Duze[p]);
		q = (p + 1) % duzeLampiony;
		for (int i = 0; i < duzeLampiony; i++) {
			if (IloczynWektor(Duze[p], Duze[i], Duze[q]) < 0) {
				q = i;
			}
		}
		p = q;
	} while (p != l); //if didn't reached the first point


std::cout << "DEBUG 07\n ";
	for (size_t i = 0; i < hull.size(); i++) {
		std::cout << "(" << hull[i].X << ", " << hull[i].Y << ")\n";
	}
std::cout << "DEBUG 08\n ";
	int ileBokow = hull.size();
	int a, b;
	for (int i = 0; i < ileBokow; i++){
		a = i;
		if (i + 1 == ileBokow) {
			b = 0;
		}
		else {
			b = a + 1;
		}

		for (size_t j = 0; j < Male.size(); j++){
			if (IloczynWektor(hull[a], hull[b], Male[j]) > 0){ //to te po lewo
				Male[j].znacznik = false;
			}

			//DEBUG ONLY!!
			//std::cout << "\n" << Male[j].X << " " << Male[j].Y << "   " << Male[j].znacznik << "  (" << hull[a].X << "," << hull[a].Y << ")    (" << hull[b].X << "," << hull[b].Y << ")  " << IloczynWektor(hull[a], hull[b], Male[j]);
		}
		//std::cout << "\n";
	}
std::cout << "DEBUG 09\n ";
	int licznik = 0;
	for (size_t j = 0; j < Male.size(); j++) {
		if (Male[j].znacznik){
			licznik = licznik + 1;
		}
	}
std::cout << "DEBUG 10\n ";
	std::cout << "\n\n Wynik to: " << licznik;//DEBUG ONLY!!

	return 0;
}