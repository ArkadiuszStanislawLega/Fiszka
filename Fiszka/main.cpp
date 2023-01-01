#include "main.h"

int main(int argc, const char * argv[]) {
	Question *q = new Question("Wartosc", "Odpowiedz");
	std::cout << q->getAnswer() << " " << q->getValue() << "\n";

    return 0;
}
