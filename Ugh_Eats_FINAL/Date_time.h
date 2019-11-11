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

	
	int daysOfMonth(int month, int year);
	bool validDate(Date & ToEvaluateDate);

	static Date getCurrentDate(tm* temp);
	static Date getCurrentDate();
	//Implementar depois
	friend bool operator==(const Date & l, const Date & r);
	friend bool operator<(const Date & l, const Date & r);  //const??
	friend ostream & operator<<(std::ostream & stream, const Date & date);
	friend Date addOneDay(Date d);
};

class Time {
	struct tm timeStruct;

public:
	Time();
	Time(int h, int m, int s);

	~Time();

	void parse(string str);
	// static Time getCurrentTime();




	friend bool operator<(const Time & left, const Time & right);
	friend ostream & operator<<(ostream & out, Time & t);
	
};

bool addTimeAndMinutes(tm time, int min,tm * result);


#endif
