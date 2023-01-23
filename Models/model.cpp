#include "model.h"


Model::Model(){ 
	this->_db = new Database();
	this->_is_working = true;
	this->_current_tag = "";
	this->_questions_in_series = 0;
	this->_menu_user_selection = 0;
}

void Model::select_model(Views view){ 
	switch(view){
		case Views::main_v:
		{	
			this->get_main_menu_option();
			break;
		}
		case Views::add_tag:
		{
			this->get_add_tag();
			break;
		}
		case Views::tag_list:
		{
			this->get_tag_list();
			break;
	 	}
		case Views::add_question:
	 	{
			this->get_add_question();
			break;
		}
	} ;
}

Views Model::get_current_view(){
	return this->_current_view;
}

void Model::get_main_menu_option(){
	
}

void Model::get_add_tag(){
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getchar();
	int i = 0;
	std::cin >> i; 
	this->_current_view = Views::main_v;
}

void Model::get_tag_list(){
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getchar();
	this->_current_view = Views::main_v;
}

void Model::get_add_question(){
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getchar();
	this->_current_view = Views::main_v;
}

Database *Model::get_database(){
	return this->_db;
}

void Model::get_user_selection(){
	scanf("%d", &this->_menu_user_selection);
}

int Model::get_questions_in_series(){
	return this->_questions_in_series;
}

string Model::get_current_tag(){
	return this->_current_tag;
}

void Model::start_app(){
	this->randomise_questions();
}

vector<Question *> Model::get_randomised_questions(){
	return this->_randomised_questions;
} 

bool Model::is_working(){
	return this->_is_working;
}

void Model::get_tag(){
	std::cin >> this->_current_tag;	
}

void Model::get_questions_number_in_series(){
	std::cin >> this->_questions_in_series;
}

bool Model::is_questions_number_valid(){
	return this->_questions_in_series <= this->_randomised_questions.size();
}

void Model::randomise_questions(){
	int i = 0; 
	vector<long> ids = this->get_questions_id_with_tag();
	for(i = ids.size(); i > 0; i--){
		std::srand(time(NULL));
		long index = std::rand() % i;

		//Question * q = this->_db->get_question(ids[index]);
		//this->_randomised_questions.push_back(q);

		this->quick_remove_at(ids, index);
	}
}

vector<long> Model::get_questions_id_with_tag(){
	vector<long> questions_ids;
//	for(auto item : this->_db->get_questions_by_tags(set<string> {this->_current_tag})){
//		questions_ids.push_back(item.first);
//	}	
 	return questions_ids;
}

template <typename T>
void Model::quick_remove_at(std::vector<T> &v, std::size_t index){
	if(index < v.size()){
		v.at(index) = std::move(v.back());
		v.pop_back();
	} 
}

Question * Model::get_random_question(){
	if(this->_randomised_questions.size()){
		Question * value = this->_randomised_questions.at(0);
		this->_randomised_questions.at(0) = std::move(this->_randomised_questions.back());
		this->_randomised_questions.pop_back();
		return value;
	}
	return NULL;
}
