#include "Date_time.h"
#include "utils.h"
#include <vector>

Date::Date()
{

}

Date::Date(size_t d, size_t m, size_t y)
{
	day = d;
	month = m;
	year = y;
}


Date::~Date() {

};

void Date::parse(string str){
	vector <string> parts = utils::split(str,'/');
	day = stoi(parts.at(0));
	month = stoi(parts.at(1));
	year = stoi(parts.at(2));
}

void Date::setDay(size_t d)
{
	day = d;
}

void Date::setMonth(size_t m)
{
	month = m;
}

void Date::setYear(size_t y)
{
	year = y;
}



size_t Date::get_day() const {
	return day;
}

size_t Date::get_month() const {
	return month;
}

size_t Date::get_year() const {
	return year;
}

string Date::str() const //implementar dps
{
	string result = day + "/";
	result += month;
	result += "/";
	result += year;
	return result;
}

Time::Time(){

}

Time::~Time(){

}

void Time::parse(string str){
	vector<string> parts = utils::split(str, ':');

	time.tm_hour = stoi(parts.at(0));
	time.tm_min = stoi(parts.at(1));
	time.tm_sec = stoi(parts.at(2));
}

