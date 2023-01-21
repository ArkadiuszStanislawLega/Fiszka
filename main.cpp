#include "main.h"

int main(){
	Model *model = new Model();
	View *view = new View(model);
	Controller *controller = new Controller(model, view);

	controller->start_app();
	return 0;
}
