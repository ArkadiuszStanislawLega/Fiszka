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
#endif
