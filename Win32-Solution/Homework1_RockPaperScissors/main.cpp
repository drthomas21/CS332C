#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(NULL));

	return 0;
}

int didPlayer1Win(char player1Choice, char player2Choice) {
	if (player1Choice == player2Choice) {
		return 0;
	}

	char beats[3][2] = { {'r','s'}, {'s','p'}, {'p','r'} };
	for (int i = 0; i < sizeof(beats); i++) {
		if (player1Choice == beats[i][0]) {
			if(player2Choice)
		}
	}
}

int computerChoice() {
	switch (rand() * 3) {
	case 0:
		break;
	case 1:
		break;

	}
}