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


Date Date::getCurrentDate(tm* temp) {

	time_t t = time(NULL);
	temp = localtime(&t);
	
	Date date(temp->tm_mday, temp->tm_mon, temp->tm_year);

	return date;
}
Date Date::getCurrentDate()
{

	time_t t = time(NULL);
	tm *temp = localtime(&t);

	Date date(temp->tm_mday, temp->tm_mon, temp->tm_year);

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
	//tm * temp;
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

Time::Time(){

}

Time::Time(struct tm t)
{
	time = t;
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


bool addTimeAndMinutes(tm time, int min, tm * result) // returns true if the day changes
{
	if ((time.tm_min + min) > 60)
	{
		result->tm_sec = time.tm_sec;
		result->tm_min = (time.tm_min + min) % 60;
		result->tm_hour = time.tm_hour + ((time.tm_min + min) / 60);
		if ((time.tm_hour >= 22) && (result->tm_hour < 2))
			return true;
		else
			return false;
	}
	else
	{
		result->tm_sec = time.tm_sec;
		result->tm_min = time.tm_min + min;
		result->tm_hour = time.tm_hour;
		return false;
	}
}


Date addOneDay(Date d)
{
	Date result;
	if ((d.day + 1) > d.daysOfMonth(d.month, d.year))
	{
		if (d.month == 12)
		{
			result.day = 1;
			result.month = 1;
			result.year = d.year + 1;
		}
		else
		{
			result.day = 1;
			result.month = d.month++;
			result.year = d.year;
		}
	}
	else
	{
		result.day = d.day++;
		result.month = d.month;
		result.year = d.year;
	}
	return result;
		
}