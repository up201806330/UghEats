#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <ctime>
#include <iostream>

using namespace std;

class Date {
	size_t day;
	size_t month;
	size_t year;

public:
	Date();
	Date(size_t d, size_t m, size_t y);

	~Date();

	void parse(string str);

	void setDay(size_t d);
	void setMonth(size_t m);
	void setYear(size_t y);
	size_t get_day() const;
	size_t get_month() const;
	size_t get_year() const;

	string str() const;

	//Implementar depois
	friend bool operator==(const Date & l, const Date & r);
	friend bool operator<(const Date & l, const Date & r);  //const??
	friend ostream & operator<<(std::ostream & stream, const Date & date);

};

class Time {
	struct tm time;

public:
	Time();

	~Time();

	void parse(string str);
	friend ostream & operator<<(ostream & out, Time & t);

};

#endif
