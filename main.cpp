#include "main.h"

int main(){
	Engine *engine = new Engine();

	printf("Pierwsz element to:\n");
	for(int i = 0; i <= engine->get_questions_number(); i++){
		printf("%s\n", engine->get_random_question()->to_string().c_str());
	}

	return 0;
}
