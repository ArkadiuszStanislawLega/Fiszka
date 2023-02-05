#include "tag_controller.h"

TagController::TagController(){
	this->_model = NULL;
	this->_view = NULL;
	this->_selected_tag = NULL;
	this->_is_working = true;
}

TagController::TagController(Model *model, View *view){
	this->_model = model;
	this->_view = view;
	this->_selected_tag = NULL;
	this->_is_working = true;
}

void TagController::clean_input_buffer(){
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void TagController::main_menu(){
	int input;
	while(this->_is_working){
		if(this->_selected_tag != NULL){
			this->_view->get_tag_view()->print_selected_tag(this->_selected_tag);
		}
		this->_view->get_tag_view()->print_main_menu_tag();

		scanf("%d", &input);

		this->select_action(input);
	}

}

void TagController::select_action(int action){
	if(action == 10){
		this->_is_working = false;
	} else {
		switch((Crud)action){
			case Crud::create:
				{
					this->create();
					break;
				}
			case Crud::read:
				{
					this->select_tag();
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
					this->add_question();
					break;
				}
			case Crud::tag_remove:
				{
					this->remove_question();
					break;
				}
			case Crud::question_add: break;
			case Crud::question_remove: break;
			default: break;
		}
	}
}

void TagController::create(){
	string tag;
	Tag *t;
	this->_view->get_tag_view()->print_create_tag();
	
	this->clean_input_buffer();

	getline(cin,tag);

	t = new Tag();
	t->set_tag(tag);
	this->_view->get_tag_view()->print_created_tag(t, TagDb::create(t));
} 

void TagController::select_tag(){
	int option_selected;
	vector<Tag *> tags;

	tags = TagDb::read_all_tags();

	this->_view->print_select_tag();
	this->_view->get_tag_view()->print_tags_list(tags);

	scanf("%d", &option_selected);

	if(option_selected >= 0 && option_selected < tags.size()){
		this->_model->set_selected_tag(tags.at(option_selected));
		this->_selected_tag = tags.at(option_selected);
	} else {
		this->_view->print_wrong_value();
	}
}

void TagController::update(){
	if(this->_selected_tag != NULL){
		string tag;
		int sql_answer;

		this->_view->get_tag_view()->print_set_new_tag();
		this->clean_input_buffer();
		getline(cin, tag);

		this->_selected_tag->set_tag(tag);
		sql_answer = TagDb::update(this->_selected_tag);
		this->_view->get_tag_view()->print_tag_updated(sql_answer);
	} else {
		this->_view->print_first_select_tag();
	}
}

void TagController::remove(){
	if(this->_selected_tag != NULL){
		char answer;
		int sql_answer {0};

		this->clean_input_buffer();
		this->_view->get_tag_view()->print_delete_tag(this->_model->get_selected_tag());
		scanf("%c", &answer);

		if(answer == ANSWER_YES_SMALL || answer == ANSWER_YES_LARGE){
			sql_answer += Database::delete_all_relation_with_tag(this->_selected_tag);
			sql_answer += TagDb::remove(this->_selected_tag->get_id());
			this->_view->get_tag_view()->print_deleted_tag(SQLITE_OK == sql_answer ? 0 : 1);
			this->_selected_tag = NULL;
		}
	} else {
		this->_view->print_first_select_tag();
	}
}

void TagController::add_question(){
	if(this->_selected_tag != NULL){
		int input, sql_answer;
		vector<Question *> questions;

		this->_view->get_tag_view()->print_add_tag_to_question();

		questions = QuestionDb::read_all_questions();
		this->_view->get_tag_view()->print_questions_vector(questions);

		scanf("%d", &input);

		if(input >= 0 && input < questions.size()){
			sql_answer = Database::create_relation(this->_selected_tag, questions.at(input));
			TagDb::read_related_questions(this->_selected_tag);
			this->_view->get_tag_view()->print_added_tag_to_question(sql_answer);
		} else {
			this->_view->print_wrong_value();
		}
		
	} else {
		this->_view->print_first_select_tag();
	}
}

void TagController::remove_question(){
	if(this->_selected_tag != NULL){
		int input, sql_answer;
		vector<Question *> related_questions;

		this->_view->get_tag_view()->print_remove_question_from_tag();
		this->_view->get_tag_view()->print_questions_vector(related_questions);

		scanf("%d", &input);

		if(input >= 0 && input < related_questions.size()){
			//TODO: Dorobic ta funkcje. Jest jak na razie pusta tylko w headerze. 
			//sql_answer = TagDb::remove_question(related_questions.at(input), this->_selected_tag);
			this->_view->get_tag_view()->print_removed_question_from_tag(sql_answer);

		} else {
			this->_view->print_wrong_value();
		}

	} else {
		this->_view->print_first_select_tag();
	}
}


