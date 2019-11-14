#define _CRT_SECURE_NO_WARNINGS
#include "Date_time.h"
#include "utils.h"
#include "Exceptions.h"
#include <vector>
#include <iomanip>
#include <random>
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

bool Date::parse(string str){
	vector <string> parts = utils::split(str,'/');
	if (parts.size() != 3)
		return false;
	if (!isNumber(parts[0]) || !isNumber(parts[1]) || !isNumber(parts[2]))
		return false;
	day = stoi(parts.at(0));
	month = stoi(parts.at(1));
	year = stoi(parts.at(2));
	if (month < 1 || month > 12 || year < 0)
		return false;
	else
	{
		if (day < 1 || day > daysOfMonth(month, year))
			return false;
	}
	return true;
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
	strct = { 0 };
	/*
	time_t date_time;
	time(&date_time);
	strct = *localtime(&date_time);
*/
}

void Date_time::setYear(int y)
{
	strct.tm_year = y - 1900;
}

void Date_time::setMonth(int m)
{
	strct.tm_mon = m - 1;
}

void Date_time::setDay(int d)
{
	strct.tm_mday= d;
}

void Date_time::setHours(int h)
{
	strct.tm_hour = h;
}

void Date_time::setMinutes(int m)
{
	strct.tm_min = m;
}

void Date_time::setTm(tm x)
{
	strct = x;
}

void Date_time::setCurrentTime()
{
	time_t rawtime;
	time(&rawtime);
	strct = *localtime(&rawtime);
}

void Date_time::addRandomTimeInterval()
{
	srand(time(NULL));
	int interval = rand() % 41 + 30; //random from 0 to 40 and adds 30

	strct.tm_min += interval;
	mktime(&strct); //normalizes
}

tm * Date_time::getTm()
{
	return &strct;
}

int Date_time::getYear() const
{
	return strct.tm_year + 1900;
}

int Date_time::getMonth() const
{
	return strct.tm_mon + 1;
}

int Date_time::getDay() const
{
	return strct.tm_mday;
}

int Date_time::getHours() const
{
	return strct.tm_hour;
}

int Date_time::getMinutes() const
{
	return strct.tm_min;
}

void Date_time::parse(string x)
{
	vector<string> parts = utils::split(x, ':');
	if (parts.size() == 3) { //� so uma data
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

bool operator<(const Date_time & left, const Date_time & right) {
	return (left.getYear() < right.getYear() || (left.getYear() == right.getYear() && left.getMonth() < right.getMonth()) || (left.getYear() == right.getYear() && left.getMonth() == right.getMonth() && left.getDay() < right.getDay()) || (left.getYear() == right.getYear() && left.getMonth() == right.getMonth() && left.getDay() == right.getDay() && left.getHours() < right.getHours()) || (left.getYear() == right.getYear() && left.getMonth() == right.getMonth() && left.getDay() == right.getDay() && left.getHours() == right.getHours() && left.getMinutes() < right.getMinutes()));
}


bool operator==(const Date_time & left, const Date_time & right) {
	if (left.just_date != right.just_date) return false;

	else if (left.just_date) {
		return (left.getDay() == right.getDay() && left.getMonth() == right.getMonth() && left.getYear() == right.getYear());
	}

	else {
		return (left.getDay() == right.getDay() && left.getMonth() == right.getMonth() && left.getYear() == right.getYear() && left.getMinutes() == right.getMinutes() && left.getHours() == right.getHours());
	}

}

Date_time operator+(const Date_time & left, const Date_time & right)
{
	Date_time result;
	if (left.just_date && right.just_date) {
		result.setDay(left.getDay() + right.getDay());
		result.setMonth(left.getMonth() + right.getMonth());
		result.setYear(left.getYear() + right.getYear());
	}
	else {
		result.setDay(left.getDay() + right.getDay());
		result.setMonth(left.getMonth() + right.getMonth());
		result.setYear(left.getYear() + right.getYear());
		result.setHours(left.getHours() + right.getHours());
		result.setMinutes(left.getMinutes() + right.getMinutes());
	}
	mktime(result.getTm());
	return result;
}

ostream& operator<<(ostream & out, const Date_time right) {
	out << setw(2) << setfill('0') << right.getDay() << " / " << setw(2) << setfill('0') << right.getMonth() << " / " << right.getYear();
	if (!right.just_date) out << " ; " << setw(2) << setfill('0') << right.getHours() << ":" << setw(2) << setfill('0') << right.getMinutes();
	return out;
}

