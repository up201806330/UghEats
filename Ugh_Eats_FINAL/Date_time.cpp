#define _CRT_SECURE_NO_WARNINGS
#include "Date_time.h"
#include "utils.h"
#include <vector>
/*
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

ostream & operator<<(std::ostream & stream, const Date & date)
{
	stream <<  to_string(date.day)  << "/" << to_string(date.month) << "/" << to_string(date.year);
	return stream;
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

/ *
Time::Time(struct tm t)
{
	time = t;
}
* /

Time::~Time(){

}

void Time::parse(string str){
	vector<string> parts = utils::split(str, ':');

	timeStruct.tm_hour = stoi(parts.at(0));
	timeStruct.tm_min = stoi(parts.at(1));
	timeStruct.tm_sec = stoi(parts.at(2));
}

/ *
Time Time::getCurrentTime() {

	
}
* /

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

bool operator<(const Date_time & left, const Date_time & right)
{
	return left.date_time < right.date_time;
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

*/

Date_time::Date_time()
{
	time(&date_time);
	tm = localtime(&date_time);
}

void Date_time::setYear(int y)
{
	tm->tm_year = y;
	// date_time = mktime(tm - 1900);
	date_time = mktime(tm);
}

void Date_time::setMonth(int m)
{
	tm->tm_mon = m;
	date_time = mktime(tm);
}

void Date_time::setDay(int d)
{
	tm->tm_mday= d;
	date_time = mktime(tm);
}

void Date_time::setHours(int h)
{
	tm->tm_hour = h;
	date_time = mktime(tm);
}

void Date_time::setMinutes(int m)
{
	tm->tm_min = m;
	date_time = mktime(tm);
}

int Date_time::getYear() const
{
	return tm->tm_year;
}

int Date_time::getMonth() const
{
	return tm->tm_mon;
}

int Date_time::getDay() const
{
	return tm->tm_mday;
}

int Date_time::getHours() const
{
	return tm->tm_hour;
}

int Date_time::getMinutes() const
{
	return tm->tm_min;
}

void Date_time::parse(string x)
{
	vector<string> parts = utils::split(x, ':');
	if (parts.size() == 3) { //É so uma data
		this->setDay(stoi(parts.at(0)));
		this->setMonth(stoi(parts.at(1)));
		this->setYear(stoi(parts.at(2)));
		just_date = true;
	}

	else if (parts.size() == 5) { // Tb tem hora
		this->setDay(stoi(parts.at(0)));
		this->setMonth(stoi(parts.at(1)));
		this->setYear(stoi(parts.at(2)));
		this->setHours(stoi(parts.at(3)));
		this->setMinutes(stoi(parts.at(4)));
		just_date = false;
	}
	
	//else throw something
}

ostream& operator<<(ostream & out, const Date_time & right) {
	out << right.getDay() << " / " << right.getMonth() << " / " << 1900 + right.getYear();
	if (!right.just_date) out << " : " << right.getHours() << ":" << right.getMinutes();
	return out;
}

