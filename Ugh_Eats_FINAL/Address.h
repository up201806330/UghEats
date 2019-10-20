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
	
	void parse(string str);

	void setTown(string cidade);
	void setDistrict(string distrito);
	void setStreet(string rua);
	void setNumber(unsigned int n);
	void setFloor(int flr = -1);
	string get_town() const;
	string get_district() const;
	string get_street() const;
	unsigned int get_number() const;
	int get_floor() const;

	friend ostream & operator<<(std::ostream & stream, Address address);



};



#endif