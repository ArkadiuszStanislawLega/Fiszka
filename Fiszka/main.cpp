#include "main.h"

int main(int argc, const char * argv[]) {
	std::vector<Question> questions;
	questions.push_back(Question("Wartosc", "odpowiedz"));
	for(int i = 0; i < questions.size(); i++){
	 	std::cout << questions[i].getAnswer() << " " << questions[i].getValue() << "\n";
	}
	printf("%lu\n", rand()%questions.size()+1);
	 
    return 0; 
}
