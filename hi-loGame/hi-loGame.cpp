#include <iostream>
#include <random>
#include <ctime>

int getInteger() {
	while (true) {
		int x;
		std::cout << "Input: ";
		std::cin >> x;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Invalid input, please try again.\n";
		}
		else {
			std::cin.ignore(32767, '\n');
			return x;
		}
	}
}

void getIntegerTest() {
	int x{ getInteger() };
	std::cout << "Output: " << x;
}

int getRandomNumber(int min, int max) {
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::uniform_int_distribution die{ min, max };
	return die(mersenne);
}

void printMenu(int maxPossibilities, int min, int max) {
	std::cout << "Hello, this is the brand new hi-lo game.\n";
	std::cout << "________________________________________\n\n";
	std::cout << "INSTRUCTIONS:\n";
	std::cout << "We are going to keep in mind one number,\n";
	std::cout << "between " << min << " - " << max << " and You have to find out\n";
	std::cout << "the number.\n\nYou have only "<<maxPossibilities<<" possibilities\n\n";
	std::cout << "Good Luck !\n";
}

bool controller(int number, int randomNumber) {
	if (number > randomNumber) {
		std::cout << "Pick up a lower number.\n";
		return false;
	}
	else if (number < randomNumber) {
		std::cout << "Pick up a higher number.\n";
		return false;
	}
	else {
		std::cout << "You won!\n";
		return true;
	}
}

void controllerTester() {
	int random{ 50 };
	int number1{ 1 };
	int number2{ 51 };
	int number3{ 50 };
	bool firstTry{ controller(number1, random) };
	std::cout << firstTry<<'\n';
	bool secondTry{ controller(number2, random) };
	std::cout << secondTry <<'\n';
	bool thirdTry{ controller(number3, random) };
	std::cout << thirdTry << '\n';
}

int getGuess(int min, int max) {
	std::cout << "We are waiting for your guess\n";
	while (true) {
		int x{ getInteger() };
		if (x < 1 || x>100) {
			std::cout << "Invalid input, please try again.\n";
		}
		return x;
	}
}

int getOperation() {

	while (true) {
		std::cout << "1) If you want to play a new game\n";
		std::cout << "2) If you want to exit\n";
		int x{ getInteger() };
		if (x != 1 && x != 2) {
			std::cout << "Invalid input, please try again.\n";
		}
		return x;
	}
}


int main() {

	// CONSTANTS OF THE GAME
	constexpr int maxPossibilities{ 7 };
	constexpr int minNumber{ 1 };
	constexpr int maxNumber{ 100 };
	int winsCounter{ 0 };
	int looseCounter{ 0 };

	while (true) {
		printMenu(maxPossibilities, minNumber, maxNumber);
		std::cout << "NEW GAME:\n\n\n";
		{
			int random = getRandomNumber(minNumber, maxNumber);
			int i{};
			int guess{};
			bool guessController;
			for (i = 0; i < maxPossibilities; i++) {
				guess = getGuess(minNumber, maxNumber);
				printf("Guess #%d: %d\n", i + 1, guess);
				guessController = controller(guess, random);
				if (guessController == true) {
					winsCounter++;
					break;
				}
			}
			if (guessController == false) {
				std::cout << "You loose!\n";
				std::cout << "The correct number was: " << random;
				looseCounter++;
			}
		}
		int operation{ getOperation() };
		if (operation == 2) {
			break;
			std::cout << "Goodbye!\n";
		}
	}
	printf("You won %d times\n", winsCounter);
	printf("You loose %d times\n", looseCounter);
	return 0;
}
	