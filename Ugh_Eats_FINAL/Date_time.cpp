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

string Date::str() const 
{
	string result = to_string(day) + "/";
	result += to_string(month);
	result += "/";
	result += to_string(year);
	return result;
}


bool operator<(const Date & l, const Date & r)
{
	if (l.year != r.year)
		return l.year < r.year;
	else
	{
		if (l.month != r.month)
			return l.month < r.month;
		else
			return l.day < r.day;
	}



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

ostream & operator<<(ostream & out, Time & t)
{
	if (t.time.tm_hour < 10)
		out << 0 << t.time.tm_hour << ":";
	else
		out << t.time.tm_hour << ":";
	if (t.time.tm_min < 10)
		out << 0 << t.time.tm_min << ":";
	else
		out << t.time.tm_min << ":";
	if (t.time.tm_sec < 10)
		out << 0 << t.time.tm_sec;
	else
		out << t.time.tm_sec;
	return out;
}

bool operator<(const Time & left, const Time & right)
{
	if (left.time.tm_hour != right.time.tm_hour)
		return left.time.tm_hour < right.time.tm_hour;
	else
	{
		if (left.time.tm_min != right.time.tm_min)
			return left.time.tm_min < right.time.tm_min;
		else
			return left.time.tm_sec < right.time.tm_sec;
	}
}