#include "main.h"

int main(){
	Engine *engine = new Engine();

	printf("Pierwsz element z (%d) to:\n", engine->get_questions_number());

	const size_t size = engine->get_questions_number();
	size_t i = 0;

	for(; i < size; i++){
		printf("%s\n", engine->get_random_question()->to_string().c_str());
	}

	return 0;
}
