#include <iostream>
#include <vector>
#include <limits>
#include <math.h>

struct coord{
	//long long X;
	//long long Y;
	long double X;
	long double Y;
} TMPcoord;

long double IloczynWektor(coord A, coord B, coord H) {
	return (H.Y - A.Y) * (B.X - A.X) - (H.X - A.X) * (B.Y - A.Y);
}

long double JakiKat(coord A, coord B, coord H) {

}

int main() {
	long double w, q;
	while (true)
	{
std::cin >> w >> q;
	coord A = { 0,0 }, B = { 0,2 }, C = {w,q};
	std::cout << "\n\n" << IloczynWektor(A, B, C) << "\n\n";
	}
	
	

	/*std::vector<coord> Male, Duze;
	int maleLampiony, duzeLampiony;
	long long x, y;

	int Poczatkowy;
	long long minX = std::numeric_limits<long long>::max(), minY = minX;
	std::cin >> duzeLampiony;
	for (int i = 0; i < duzeLampiony; i++){
		std::cin >> TMPcoord.X >> TMPcoord.Y;
		Duze.push_back(TMPcoord);

		if (TMPcoord.Y < minY){
			minY = TMPcoord.Y;
			Poczatkowy = i;
		}
		else if (TMPcoord.Y == minY){
			if (TMPcoord.X < minX) {
				minX = TMPcoord.X;
				Poczatkowy = i;
			}
		}
	}

	std::cin >> maleLampiony;
	for (int i = 0; i < maleLampiony; i++){
		std::cin >> TMPcoord.X >> TMPcoord.Y;
		Male.push_back(TMPcoord);
	}*/

	//pzesuwanie wszystkich lampionow


	return 0;
}