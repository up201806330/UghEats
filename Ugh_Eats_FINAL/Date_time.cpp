#define _CRT_SECURE_NO_WARNINGS
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


Date Date::getCurrentDate() {

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	
	Date date(timePtr->tm_mday, timePtr->tm_mon, timePtr->tm_year);

	return date;
}


// return the number of days given the month and year
int Date::daysOfMonth(int month, int year) {

	bool leapYear = false;

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		leapYear = true;
	}

	if ((month < 8 && month % 2 == 1) || (month >= 8 && month % 2 == 0)) {
		return 31;
	}

	else if (month == 2) {
		return leapYear ? 29 : 28;
	}

	return 30;
}


// checks if a date isn't before a reference (date)
bool Date::validDate(Date & ToEvaluateDate) {
	Date currentDate = Date::getCurrentDate();
	bool validDate = true;

	// basic verification
	if (ToEvaluateDate.get_year() <= 0 || (ToEvaluateDate.get_month() <= 0 || ToEvaluateDate.get_month() > 12) || ToEvaluateDate.get_day() <= 0) {
		validDate = false;
	}

	// year verification
	else if (ToEvaluateDate.get_year() < currentDate.get_year()) {
		validDate = false;
	}

	// same year, month verification
	else if ((ToEvaluateDate.get_year() == currentDate.get_year()) && (ToEvaluateDate.get_month() < currentDate.get_month())) {
		validDate = false;
	}

	// same year / month, day verification
	else if ((ToEvaluateDate.get_year() == currentDate.get_year()) && (ToEvaluateDate.get_month() == currentDate.get_month()) && (ToEvaluateDate.get_day() < currentDate.get_day())) {
		validDate = false;
	}

	// day verification
	else if (daysOfMonth(ToEvaluateDate.get_month(), ToEvaluateDate.get_year()) < ToEvaluateDate.get_day()) {
		validDate = false;
	}

	return validDate;
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

// by default, any Time object is initialized with the current time
Time::Time(){

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);

	timeStruct.tm_hour = timePtr->tm_hour;
	timeStruct.tm_min = timePtr->tm_min;
	timeStruct.tm_sec = timePtr->tm_sec;
}

Time::Time(int h, int m, int s) {
	timeStruct.tm_hour = h;
	timeStruct.tm_min = m;
	timeStruct.tm_sec = s;
}

Time::~Time(){

}

void Time::parse(string str){
	vector<string> parts = utils::split(str, ':');

	timeStruct.tm_hour = stoi(parts.at(0));
	timeStruct.tm_min = stoi(parts.at(1));
	timeStruct.tm_sec = stoi(parts.at(2));
}


Time Time::getCurrentTime() {

	
}

ostream & operator<<(ostream & out, Time & t)
{
	if (t.timeStruct.tm_hour < 10)
		out << 0 << t.timeStruct.tm_hour << ":";
	else
		out << t.timeStruct.tm_hour << ":";
	if (t.timeStruct.tm_min < 10)
		out << 0 << t.timeStruct.tm_min << ":";
	else
		out << t.timeStruct.tm_min << ":";
	if (t.timeStruct.tm_sec < 10)
		out << 0 << t.timeStruct.tm_sec;
	else
		out << t.timeStruct.tm_sec;
	return out;
}

bool operator<(const Time & left, const Time & right)
{
	if (left.timeStruct.tm_hour != right.timeStruct.tm_hour)
		return left.timeStruct.tm_hour < right.timeStruct.tm_hour;
	else
	{
		if (left.timeStruct.tm_min != right.timeStruct.tm_min)
			return left.timeStruct.tm_min < right.timeStruct.tm_min;
		else
			return left.timeStruct.tm_sec < right.timeStruct.tm_sec;
	}
}