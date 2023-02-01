#ifndef STRINGS
#define STRINGS
#include <string>

using std::string;

static const string DATABASE_NAME = "fiszka.db";
static const string TABLE_QUESTIONS = "Questions";
static const string TABLE_TAGS  = "Tags";
static const string TABLE_QUESTIONS_TAGS  = "Questions_tags";
static const string COLUMN_ID  = "Id";
static const string COLUMN_VALUE = "Value";
static const string COLUMN_ANSWER = "Answer";
static const string COLUMN_TAG  = "Tag";
static const string COLUMN_QUESTION_ID = "Question_id";
static const string COLUMN_TAG_ID = "Tag_id";
static const string CREATE_TABLE_IF_NOT_EXISTS  = "create table if not exists";
static const string INTEGER_NOT_NULL = "INTEGER NOT NULL";
static const string PRIMARY_KEY  = "INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL";
static const string TEXT = "TEXT NOT NULL";
static const string FOREIGN_KEY = "FOREIGN KEY ";
static const string REFERENCES = "REFERENCES ";
static const string SELECT = "SELECT ";
static const string FROM = "FROM ";
static const string WHERE = "WHERE ";
static const string INSERT = "INSERT INTO ";
static const string VALUES = "VALUES";
static const string UPDATE = "UPDATE ";
static const string SET = "SET ";
static const string DELETE = "DELETE FROM ";
static const string INNER_JOIN = "INNER JOIN ";
static const string ON = "ON ";
static const string AND = "AND ";
static const string LIMIT  = "LIMIT ";

static const char ANSWER_YES_LARGE = 'Y';
static const char ANSWER_YES_SMALL = 'y';

static const string TAG_LIST = "Tags list";
static const string ADD_TAG = "Add tag";
static const string ADD_QUESTION = "Add question";
static const string ADD_TAG_TO_QUESTION = "Add the tag to the question";
static const string REMOVE_TAG = "Remove the tag";
static const string REMOVE_QUESTION = "Remove the question";
static const string REMOVE_TAG_FROM_QUESTION = "Remove the tag from the question";
static const string SELECT_TAG = "Select tag";
static const string MAKE_SERIES = "Make questions series";

static const string MAIN_MENU = "MAIN MENU";
static const string SELECTED_TAG = "Selected tag";
static const string CHOSE_NUMBER = "Chose number";
static const string WRONG_VALUE = "Wrong value";
static const string WRONG_VALUE_TRY_AGAIN = "Wrong value. Try again.";
static const string SELECT_TAG_FIRST = "Select the tag first";
static const string TAGS_LIST = "Tags list";
static const string TAG_CREATED_CORRECTLY = "The tag created correctly"; 
static const string DATABASE_ERROR = "Database error";
static const string INFO_CREATING_QUESTION = "Add a question. First, the query, and then after pressing the ENTER key, the answer. Then confirm by pressing the ENTER key.";  
static const string QUESTION_CREATED_CORRECTLY = "The question created correctly";
static const string CHOSE_TAG = "Choose the tag from the list";
static const string ADD_THE_TAG = "Add the tag";
static const string TO_THE_QUESTION = "to the question";
static const string VALUE = "Value";
static const string ANSWER = "Answer";
static const string TAG_ADDED_SUCCESFULLY = "The tag added succesfully";
static const string INFO_CONFIRM_REMOVE = "Confirm deletion by typing (Y)";
static const string THE_TAG = "The tag";
static const string SUCCESFULLY_REMOVED = "has been succesfuly removed from database";
static const string QUESTIONS_LIST_TO_REMOVED = "List of the questions to removed"; 
static const string CHOOSE_QUESTION = "Choose one question";
static const string NO_QUESTIONS_TO_REMOVE = "There are no questions to remove";
static const string QUESTIONS_SUCCESFULLY_REMOVED = "The question succesfully deleted";
static const string INFO_QUESTIONS_NUMBER_IN_SERIES = "Enter number of questions you want to do in series. The number must be less than";
static const string LIST_OF_TAGS = "List of tags from databse";
static const string RANDOM_QUESTION_LIST = "Random question list";

#endif
