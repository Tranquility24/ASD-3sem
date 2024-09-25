#include "iostream"
#include "stack"
#include "vector"
#include <time.h>

constexpr char TAB = '\t';

// Таблица ошибок

#define ERROR00 "ERROR #00: введено неправильное количество дисков"
#define ERROR01 "ERROR #01: введена неправильная начальная позиция"
#define ERROR02 "ERROR #02: введена неправильная финальная позиция"
#define ERROR03 "ERROR #03: начальная и финальная позиция совпадают"

// Функции вывода стержней с дисками

void checkOutput(std::stack<int>& rod, bool& checkPrint, const unsigned short& sizeMain, const unsigned short& sizeC, const unsigned short& sizeB);
void checkingChangesNumberDisks(bool& checkPrint, unsigned short& size);
void displayRods(std::vector<std::stack<int>> rods);

// Функции алгоритма башни Ханоя

void moveDisk(std::vector<std::stack<int>>& rods, const int& numberDisks, const int& positionStarting, const int& positionFinal, int& numberMoves);
void hanoi(std::vector<std::stack<int>>& rods, int numberDisks, const int& positionStarting, const int& positionFinal, const int& positionIntermediate, int& numberMoves);

int main() {

	setlocale(LC_ALL, "RU");

	int positionStarting{}, positionFinal{}, positionIntermediate{};
	int numberDisks{};
	int numberMoves{};

	std::vector<std::stack<int>> rods;

	try {

		for (int i = 0; i < 3; i++) {
			rods.push_back({});
		}

		std::cout << "Количество дисков:";
		std::cin >> numberDisks;
		numberDisks <= 0 ? throw std::exception(ERROR00) : false;

		std::cout << "Начальная позиция башни (1-3):";
		std::cin >> positionStarting;
		(positionStarting > 3 ) || ( positionStarting < 1 ) ? throw std::exception(ERROR01) : false;

		std::cout << "Финальная позиция башни (1-3):";
		std::cin >> positionFinal;
		(positionFinal > 3) || (positionFinal < 1) ? throw std::exception(ERROR02) : false;

		std::cout << std::endl;

		(positionStarting == positionFinal) ? throw std::exception(ERROR03) : false;

		positionStarting--;
		positionFinal--;

		positionIntermediate = 3 - positionStarting - positionFinal;

		for (int i = numberDisks; i != 0; i--) {

			rods[positionStarting].push(i);
		}

		std::cout << "Башни до:" << std::endl;
		displayRods(rods);

		clock_t start = clock();

		hanoi(rods, numberDisks, positionStarting, positionFinal, positionIntermediate, numberMoves);

		clock_t end = clock();
		double seconds = (double)(end - start) / CLOCKS_PER_SEC;

		std::cout << "Общее количество шагов: " << numberMoves << std::endl;
		std::cout << "Время: " << seconds << std::endl;

	}
	catch (const std::exception& ex) {

		std::cout << ex.what() << std::endl;
	}	

	return 0;
}

void checkOutput(std::stack<int>& rod, bool& checkPrint, const unsigned short & sizeMain, const unsigned short& sizeC, const unsigned short& sizeB) {

	if ((sizeMain >= sizeB) && (sizeMain >= sizeC)) {

		std::cout << TAB << rod.top();
		checkPrint = true;

		rod.pop();

	} else {

		std::cout << TAB << ' ';

	}

}

void checkingChangesNumberDisks(bool& checkPrint, unsigned short& size) {

	if (checkPrint) {

		--size;
		checkPrint = false;
	}
}

void displayRods(std::vector<std::stack<int>> rods)	{

	struct SizeRods {

		unsigned short sizeA;
		unsigned short sizeB;
		unsigned short sizeC;

	} size{ rods.at(0).size(), rods.at(1).size(), rods.at(2).size() };

	struct CheckPrint {

		bool checkPrintA;
		bool checkPrintB;
		bool checkPrintC;

	} print{ false, false, false };

	while (size.sizeA || size.sizeB || size.sizeC) {

		checkOutput(rods.at(0), print.checkPrintA, size.sizeA, size.sizeB, size.sizeC);
		checkOutput(rods.at(1), print.checkPrintB, size.sizeB, size.sizeA, size.sizeC);
		checkOutput(rods.at(2), print.checkPrintC, size.sizeC, size.sizeB, size.sizeA);

		std::cout << std::endl;

		checkingChangesNumberDisks(print.checkPrintA, size.sizeA);
		checkingChangesNumberDisks(print.checkPrintB, size.sizeB);
		checkingChangesNumberDisks(print.checkPrintC, size.sizeC);
	}

	std::cout << TAB << "_________________" << std::endl << std::endl << std::endl;

}

void moveDisk(std::vector<std::stack<int>>& rods, const int& numberDisks,const int& positionStarting, const int& positionFinal, int& numberMoves) {

	if (!rods.at(positionStarting).empty()) {

		rods.at(positionFinal).push(rods.at(positionStarting).top());
		rods.at(positionStarting).pop();
		numberMoves++;

		std::cout << "Шаг номер:" << numberMoves << std::endl;
		std::cout << "Перемещяем диск " << numberDisks << " с позиции " << positionStarting + 1 << " на " << positionFinal + 1 << std::endl << std::endl;

		displayRods(rods);

	}
}

void hanoi(std::vector<std::stack<int>>& rods, int numberDisks, const int& positionStarting, const int& positionFinal, const int& positionIntermediate, int& numberMoves) {

	if (numberDisks == 1) {

		moveDisk(rods, numberDisks,positionStarting, positionFinal, numberMoves);

	} else {

 		hanoi(rods, numberDisks - 1, positionStarting, positionIntermediate, positionFinal, numberMoves);
		moveDisk(rods, numberDisks,positionStarting, positionFinal, numberMoves);
		hanoi(rods, numberDisks - 1, positionIntermediate, positionFinal, positionStarting, numberMoves);
	}
}

