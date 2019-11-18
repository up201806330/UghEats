#define _CRT_SECURE_NO_WARNINGS
#include "Date_time.h"
#include "utils.h"
#include "Exceptions.h"
#include <vector>
#include <iomanip>
#include <random>


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
	just_date = false;
}

void Date_time::addRandomTimeInterval()
{
	srand((unsigned int)time(NULL));
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

bool Date_time::getJustDate() const
{
	return just_date;
}

bool Date_time::parse(string x)
{
	vector<string> parts = utils::split(x, ':');
	if (parts.size() == 3) { //� so uma data
		if (!isNumber(parts.at(0)) || !isNumber(parts.at(1)) || !isNumber(parts.at(2)))
			return false;
		this->setDay(stoi(parts.at(0)));
		this->setMonth(stoi(parts.at(1)));
		this->setYear(stoi(parts.at(2)));
		just_date = true;
		return true;
	}

	else if (parts.size() == 5) { // Tb tem hora
		if (!isNumber(parts.at(0)) || !isNumber(parts.at(1)) || !isNumber(parts.at(2)) || !isNumber(parts.at(3)) || !isNumber(parts.at(4)))
			return false;
		this->setDay(stoi(parts.at(0)));
		this->setMonth(stoi(parts.at(1)));
		this->setYear(stoi(parts.at(2)));
		this->setHours(stoi(parts.at(3)));
		this->setMinutes(stoi(parts.at(4)));
		just_date = false;
		return true;
	}
	else
		return false;
	
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

