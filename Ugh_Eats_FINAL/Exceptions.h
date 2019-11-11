#pragma once
#include <string>
using namespace std;
//Exception Handling

class InvalidStringException
{
public:	
	string error;
	InvalidStringException(string e) { error = e; }
	string getError() {return error;}
};

ostream & operator<<(ostream & out, InvalidStringException & s);

class InvalidOptionException
{
public:
	int opt;
	InvalidOptionException(int o) { opt = o; }
	int getOption() { return opt; }
};

ostream & operator<<(ostream & out, InvalidOptionException & o);

class InvalidDateException
{
public:
	string date_error;
	InvalidDateException(string d) { date_error = d; }
	string getDateError() { return date_error; }
};

ostream & operator<<(ostream & out, InvalidDateException & d);

class InvalidTimeException
{
public:
	string time_error;
	InvalidTimeException(string t) { time_error = t; }
	string getTimeError() { return time_error; }
};

ostream & operator<<(ostream & out, InvalidTimeException & t);

class InvalidAddressException
{
public:
	string address_error;
	InvalidAddressException(string a) { address_error = a; }
	string getAddressError() { return address_error; }

};

ostream & operator<<(ostream & out, InvalidAddressException & a);


class InvalidCityException // when the client lives in a city that the base doesn't cover
{
public:
	string city_error;
	InvalidCityException(string c) { city_error = c; }
	string getCityError() { return city_error; }

};


ostream & operator<<(ostream & out, InvalidCityException & c);

class RestaurantNotFoundException
{
public:
	string restaurant_error;
	RestaurantNotFoundException(string r) { restaurant_error = r; }
	string getRestaurantError() { return restaurant_error; }
};

ostream & operator<<(ostream & out, RestaurantNotFoundException & r);

class GeographicAreaNotFoundException
{
public:
	string geographic_area_error;
	GeographicAreaNotFoundException(string g) { geographic_area_error = g; }
	string getGeographicAreaError() { return geographic_area_error; }

};

ostream & operator<<(ostream & out, GeographicAreaNotFoundException & g);


class CuisineTypeNotFoundException
{
public:
	string cuisine_type_error;
	CuisineTypeNotFoundException(string c) { cuisine_type_error = c; }
	string getCuisineTypeError() { return cuisine_type_error; }

};

ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c);

class InvalidDatesException //when the user says the final date is before the first
{
public:
	string datei, datef;
	InvalidDatesException(string d1, string d2) { datei = d1; datef = d2; }
	string getDateI() { return datei; }
	string getDateF() { return datef; }
};

ostream & operator<<(ostream & out, InvalidDatesException & d);

class InvalidPriceRangeException //when the minimum value is bigger than the maximum value
{
public:
	int min, max;
	InvalidPriceRangeException(int mi, int ma) { min = mi; max = ma; }
	int getMin() { return min; }
	int getMax() { return max; }
};

ostream & operator<<(ostream & out, InvalidPriceRangeException & p);