#include <iostream>
#include <ctime>
using namespace std;
int main(int argc, char* argv[])
{
	//entering numbers
	cout << "Enter size ";
	int size;
	cin >> size;
	int n = 0;
	cout << "Enter the number of steps ";
	int steps;
	cin >> steps;

	//create a field
	int**field = new int*[size + 4];
	for (int i = 0; i <= size + 3; ++i) {
		field[i] = new int[size + 4];
	}

	for (int i = 0; i <= size + 3; ++i) {
		for (int j = 0; j <= size + 3; ++j) {
			field[i][j] = 0;
		}
	}
	cout << "Enter 0 if you want to fill the field by yourself, or any another number if you want to fill the field with random numbers ";
	int isRand = 1;
	cin >> isRand;
	if (isRand == 0) {
		cout << "Fill the field" << endl;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				cin >> field[i + 2][j + 2];
				if (field[i + 2][j + 2] == 1) n++;
			}
		}
	}
	else {
		cout << "Enter the number of populated cells ";
		cin >> n;
		srand(time(0));
		int *source = new int[size*size];
		for (int i = 0; i < size*size; ++i) {
			source[i] = i;
		}

		for (int i = 0; i < size*size; ++i) {
			int j = rand() % (i + 1);
			int t = source[i];
			source[i] = source[j];
			source[j] = t;
		}

		for (int i = 0; i < n; ++i) {
			int x = source[i] % size;
			int y = source[i] / size;
			field[y + 2][x + 2] = 1;
		}
		delete[] source;
	}

	//simulation
	int born = 0;
	int death = 0;
	int population = n;
	int number = -1;
	bool f2 = true;
	int prev = -1;
	for (int k = 1; k <= steps; ++k) {
		bool f = false;
		int x0 = 0;
		int y0 = 0;
		int**ChField = new int*[size + 4];
		for (int i = 0; i <= size + 3; ++i) {
			ChField[i] = new int[size + 4];
		}

		for (int i = 0; i <= size + 3; ++i) {
			for (int j = 0; j <= size + 3; ++j) {
				ChField[i][j] = field[i][j];
			}
		}
		for (int j = 1; j <= size + 2; ++j) {
			for (int i = 1; i <= size + 2; ++i) {
				int count = field[j - 1][i] + field[j - 1][i - 1] + field[j][i - 1]
					+ field[j + 1][i - 1] + field[j + 1][i] + field[j + 1][i + 1] + field[j][i + 1] + field[j - 1][i + 1];

				if ((field[j][i] == 1) && (count != 2) && (count != 3)) {
					ChField[j][i] = 0;
					death++;
					population--;
				}
				if ((field[j][i] == 0) && (count == 3)) {
					ChField[j][i] = 1;
					born++;
					population++;
					if ((i == 1) || (j == 1) || (i == size + 2) || (j == size + 2)) {
						f = true;
					}
				}
			}
		}
		int oldsize = size;
		if (f) {
			x0 = size / 2;
			y0 = size / 2;
			size *= 2;
		}
		delete[] field;
		field = new int*[size + 4];
		for (int i = 0; i <= size + 3; ++i) {
			field[i] = new int[size + 4];
		}

		for (int i = 0; i <= size + 3; ++i) {
			for (int j = 0; j <= size + 3; ++j) {
				field[i][j] = 0;
			}
		}

		for (int i = 1; i <= oldsize + 2; ++i) {
			for (int j = 1; j <= oldsize + 2; ++j) {
				field[j + y0][i + x0] = ChField[j][i];
			}
		}
		delete[] ChField;

		if (k % 10 == 0) {
			cout << "Step " << k << endl;
			if (death != 0)
			{
				cout << "born/death:" << (double)born / (double)death << endl;
			}
			else
			{
				cout << "born/death:" << 0 << endl;
			}
			born = 0;
			death = 0;
			cout << "population:" << population << endl;
		}
		if (prev != population) {
			f2 = true;
			number = -1;
		}
		if ((prev == population) && (f2)) {
			f2 = false;
			number = k;
		}
		prev = population;
	}
	cout << "total population:" << population << endl;
	if (number != -1) cout << "is not changed after " << number << endl;
	int startX = 2;
	int startY = 2;
	int endX = size + 2;
	int endY = size + 2;
	if (endX - startX + 1 > 10) endX = startX + 10;
	if (endY - startY + 1 > 10) endY = startY + 10;
	for (int i = startY; i < endY; ++i) {
		for (int j = startX; j < endX; ++j) {
			cout << field[i][j] << ' ';
		}
		cout << endl;
	}
	bool continueWhile = true;
	cout << "Enter e if you want to exit, use wasd to move around the field ";
	while (true) {
		char command;
		cin >> command;
		endX = size + 1;
		endY = size + 1;
		switch (command) {
		case 'e': continueWhile = false;  break;
		case 'w': startY++;  break;
		case 'a': startX++;  break;
		case 's': startY--;  break;
		case 'd': startX--;  break;
		}
		if (!continueWhile) break;
		if (startX >= size + 2) startX = size + 1;
		if (startX < 2) startX = 2;
		if (startY >= size + 2) startY = size + 1;
		if (startY < 2) startY = 2;
		if (endX - startX + 1 > 10) endX = startX + 9;
		if (endY - startY + 1 > 10) endY = startY + 9;
		while ((endX - startX + 1 < 10) && (endX < size + 2)) endX++;
		while ((endY - startY + 1 < 10) && (endY < size + 2)) endY++;
		for (int k = 0; k < 25; ++k) cout << endl;
		cout << "Enter e if you want to exit, use wasd to move around the field " << endl;
		for (int i = startY; i <= endY; ++i) {
			for (int j = startX; j <= endX; ++j) {
				cout << field[i][j]<< ' ';
			}
			cout << endl;
		}
	}
	delete[] field;
	//system("pause");
	return 0;
}

