#include "main.h"

int main(){
	Question *q = new Question("Wartosc", "Odpowiedz");
	std::cout << q->getAnswer() << " " << q->getValue() << "\n";
}
