#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <ctime>
#include <iostream>

using namespace std;

class Date_time {
	struct tm strct;
	bool just_date;

public:
	Date_time();

	/**
	 * @brief Set the Year object
	 * 
	 * @param y 
	 */
	void setYear(int y);
	/**
	 * @brief Set the Month object
	 * 
	 * @param m 
	 */
	void setMonth(int m);
	/**
	 * @brief Set the Day object
	 * 
	 * @param d 
	 */
	void setDay(int d);
	/**
	 * @brief Set the Hours object
	 * 
	 * @param h 
	 */
	void setHours(int h);
	/**
	 * @brief Set the Minutes object
	 * 
	 * @param m 
	 */
	void setMinutes(int m);
	/**
	 * @brief Set the Tm object
	 * 
	 * @param x 
	 */
	void setTm(struct tm x);

	/**
	 * @brief Set object to current time
	 * 
	 */
	void setCurrentTime();
	/**
	 * @brief add time interval between 40 and 70 minutes to object
	 * 
	 */
	void addRandomTimeInterval();

	/**
	 * @brief Get the Tm object
	 * 
	 * @return struct tm* 
	 */
	struct tm * getTm();
	/**
	 * @brief Get the Year object
	 * 
	 * @return int 
	 */
	int getYear() const;
	/**
	 * @brief Get the Month object
	 * 
	 * @return int 
	 */
	int getMonth() const;
	/**
	 * @brief Get the Day object
	 * 
	 * @return int 
	 */
	int getDay() const;
	/**
	 * @brief Get the Hours object
	 * 
	 * @return int 
	 */
	int getHours() const;
	/**
	 * @brief Get the Minutes object
	 * 
	 * @return int 
	 */
	int getMinutes() const;
	/**
	 * @brief Get the Just Date bool
	 * 
	 * @return true 
	 * @return false 
	 */
	bool getJustDate() const;

	/**
	 * @brief operator< overload
	 * 
	 * @param left left side object
	 * @param right right side object
	 * @return true if successful
	 * @return false otherwise
	 */
	friend bool operator<(const Date_time & left, const Date_time & right);
	/**
	 * @brief operator== overload
	 * 
	 * @param left left side object
	 * @param right rigt side object
	 * @return true if successful
	 * @return false otherwise
	 */
	friend bool operator==(const Date_time & left, const Date_time & right);
	/**
	 * @brief operator+ overload
	 * 
	 * @param left left side object
	 * @param right left side object
	 * @return Date_time result object
	 */
	friend Date_time operator+(const Date_time & left, const Date_time & right);
	/**
	 * @brief operator<< overload
	 * 
	 * @param out out stream
	 * @param right right side operator
	 * @return ostream& result stream
	 */
	friend ostream& operator<<(ostream & out, const Date_time right);

	/**
	 * @brief parse string into object parameters
	 * 
	 * @param x string in format day:month:year:hour:minute or day:month:year
	 * @return true if successful
	 * @return false othewise
	 */
	bool parse(string x);

};

#endif
