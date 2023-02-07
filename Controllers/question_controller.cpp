#include "question_controller.h"

void QuestionController::clean_input_buffer(){
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

QuestionController::QuestionController(){
	this->_model = NULL;
	this->_view = NULL;
	this->_selected_question = NULL;
}

QuestionController::QuestionController(Model *model, View *view){
	this->_model = model;
	this->_view = view;
	this->_selected_question = NULL;
}

void QuestionController::create(){
	Question *q = this->get_new_question();
	int sql_answer = QuestionDb::create(q);

	this->_view->get_question_view()->print_created_question(q, sql_answer); 
}

Question *QuestionController::get_new_question(){
	Question *q = new Question();
	string value, answer;
	this->_view->get_question_view()->print_create_question();
		
	this->clean_input_buffer();

	getline(cin, value);	
	getline(cin, answer);

	q->set_value(value);
	q->set_answer(answer);

	return q;
}

void QuestionController::select_question(){
	vector<Question *> questions = QuestionDb::read_all_questions();
	this->_view->get_question_view()->print_questions_vector(questions);
	this->_view->get_question_view()->print_select_question_number();

	int input;
	scanf("%d", &input);

	if(input > 0 && input < questions.size()){
		this->_selected_question = questions.at(input);
	} else {
		this->_view->print_wrong_value();
	}
}

void QuestionController::update(){
	if(this->_selected_question != NULL){
		string value, answer;
		this->clean_input_buffer();

		this->_view->get_question_view()->print_value();
		getline(cin, value);

		this->_view->get_question_view()->print_answer();
		getline(cin, answer);

		this->_selected_question->set_value(value);
		this->_selected_question->set_answer(answer);

		QuestionDb::update(this->_selected_question);
	} else {
		this->_view->get_question_view()->print_select_question();
	}
}

void QuestionController::remove(){
	if(this->_selected_question != NULL){
		char answer;
		int sql_answer {0};

		this->_view->get_question_view()->print_delete_question(this->_selected_question);
		scanf("%s", &answer);

		if(answer == ANSWER_YES_LARGE || answer == ANSWER_YES_SMALL){
			sql_answer += Database::delete_all_relation_with_question(this->_selected_question);
			sql_answer += QuestionDb::remove(this->_selected_question->get_id());
			this->_view->get_question_view()->print_deleted_question(SQLITE_OK == sql_answer ? 0 : 1);
			this->_selected_question = NULL;
		}
	} else {
		this->_view->get_question_view()->print_select_question();
	}
}

void QuestionController::add_tag(){
	if(this->_selected_question != NULL){
		int input, sql_answer;
		vector<Tag *> tags;

		this->_view->get_tag_view()->print_add_tag_to_question();

		tags = TagDb::read_all_tags();
		this->_view->get_tag_view()->print_tags_vector(tags);
		
		scanf("%d", &input);

		if(input >= 0 && input < tags.size()){
			sql_answer = Database::create_relation(tags.at(input), this->_selected_question);
			QuestionDb::read_related_tags(this->_selected_question);
			this->_view->get_tag_view()->print_added_tag_to_question(sql_answer);
		} else {
			this->_view->print_wrong_value();
		}
	} else {
		this->_view->get_question_view()->print_select_question();
	}
}

void QuestionController::remove_tag(){
	if(this->_selected_question != NULL){
		int input, sql_answer;
		this->_view->get_question_view()->print_remove_tag_from_question(this->_selected_question);
		this->_view->get_tag_view()->print_tags_vector(this->_selected_question->get_tags());
	
		scanf("%d", &input);

		if(input >= 0 && input < this->_selected_question->get_tags().size()){
			sql_answer = QuestionDb::remove_tag(this->_selected_question, this->_selected_question->get_tags().at(input));
			QuestionDb::read_related_tags(this->_selected_question);
			this->_view->get_question_view()->print_removed_tag_from_question(sql_answer);
		}
 	} else {
		this->_view->get_question_view()->print_select_question();
	}
}  

void QuestionController::main_menu(){
	int input;
	while(this->_is_working){
		if(this->_selected_question != NULL){
			this->_view->get_question_view()->print_selected_question(this->_selected_question);
			printf("%s\n", this->_selected_question->get_value().c_str());
		}

		this->_view->get_question_view()->print_main_menu();

		scanf("%d", &input);

		this->select_action(input);
	}
}

void QuestionController::select_action(int selected){
	if(selected == MENU_EXIT_VALUE){
		this->_is_working = false;
	} else {
		switch((Crud)selected){
			case Crud::create:
				{
					this->create();
					break;
				}
			case Crud::read:
				{
					this->select_question();
					break;
				}
			case Crud::update:
				{
					this->update();
					break;
				}
			case Crud::del:
				{
					this->remove();
					break;
				}
			case Crud::tag_add:
				{
					this->add_tag();
					break;
				}
			case Crud::tag_remove:
				{
					this->remove_tag();
					break;
				}
			case Crud::question_add: break;
			case Crud::question_remove: break;
			default: break;
		}
	} 
}
