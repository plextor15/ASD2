#include <iostream>
#include <vector>

struct coord{
	long long X;
	long long Y;
} TMPcoord;

int main() {
	std::vector<coord> Male, Duze;
	int maleLampiony, duzeLampiony;
	long long x, y;

	std::cin >> duzeLampiony;
	for (int i = 0; i < duzeLampiony; i++){
		std::cin >> TMPcoord.X >> TMPcoord.Y;
		Duze.push_back(TMPcoord);
	}

	std::cin >> maleLampiony;
	for (int i = 0; i < maleLampiony; i++){
		std::cin >> TMPcoord.X >> TMPcoord.Y;
		Male.push_back(TMPcoord);
	}

	return 0;
}