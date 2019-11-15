#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
#include <string>
using namespace std;


class Address {
	string district;
	string town;
	string street;
	unsigned int number;
	int floor; //if non-aplicable, =-1
	double latitude;
	double longitude;

public:
	Address();

	~Address();
	
	/**
	 * @brief Checks if the str string passed as a parameter can correspond to a valid address (includes the district)
	 * 
	 * @param str String corresponding to the full address
	 * @return true If the address parsing occured without issues
	 * @return false If the address strings had an invalid number of elements or any invalid fields
	 */
	bool parse(string str);

	/**
	 * @brief Checks if the str string passed as a parameter can correspond to a valid address (doesn't include the district)
	 * 
	 * @param str String corresponding to the full address
	 * @param dist String with the name of the district
	 * @return true If the address parsing occured without issues
	 * @return false If the address strings had an invalid number of elements or any invalid fields
	 */
	bool parseInsideBase(string str, string dist);

	/**
	 * @brief Converts the address object to a string
	 * 
	 * @return string
	 */
	string str() const;


	/**
	 * @brief Set the Town object
	 * 
	 * @param cidade 
	 */
	void setTown(string cidade);

	/**
	 * @brief Set the District object
	 * 
	 * @param distrito 
	 */
	void setDistrict(string distrito);

	/**
	 * @brief Set the Street object
	 * 
	 * @param rua 
	 */
	void setStreet(string rua);

	/**
	 * @brief Set the Number object
	 * 
	 * @param n 
	 */
	void setNumber(unsigned int n);

	/**
	 * @brief Set the Floor object
	 * 
	 * @param flr 
	 */
	void setFloor(int flr = -1);


	/**
	 * @brief Get the town object
	 * 
	 * @return string 
	 */
	string get_town() const;

	/**
	 * @brief Get the district object
	 * 
	 * @return string 
	 */
	string get_district() const;

	/**
	 * @brief Get the street object
	 * 
	 * @return string 
	 */
	string get_street() const;

	/**
	 * @brief Get the number object
	 * 
	 * @return unsigned int 
	 */
	unsigned int get_number() const;

	/**
	 * @brief Get the floor object
	 * 
	 * @return int 
	 */
	int get_floor() const;
	
	

	/**
	 * @brief Displays an address in a formated way
	 * 
	 * @param stream 
	 * @param address 
	 * @return ostream& 
	 */
	friend ostream & operator<<(std::ostream & stream, Address address);

};



#endif