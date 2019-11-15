#pragma once
#include <string>
#include "Date_time.h"
using namespace std;
//Exception Handling

class InvalidStringException { //Implemented
	string error;
public:	
	InvalidStringException(string e) { error = e; }
	string getError() {return error;}

	friend ostream & operator<<(ostream & out, InvalidStringException & s) {
		out << "Invalid String Exception: " << s.getError() << " is invalid \n";
		return out;
	};
};

// ostream & operator<<(ostream & out, InvalidStringException & s);

class InvalidOptionException { //Implemented
	int opt;
public:
	InvalidOptionException(int o) { opt = o; }
	int getOption() { return opt; }

	friend ostream & operator<<(ostream & out, InvalidOptionException & o) {
		out << "Invalid Option Exception: " << o.getOption() << " isn't an option \n";
		return out;
	};
};

// ostream & operator<<(ostream & out, InvalidOptionException & o);

class InvalidNumberException { //Implemented
private:
	string n;
public:
	InvalidNumberException(string ni) { n = ni; }
	string getString() { return n; }
	friend ostream & operator<<(ostream  & out, InvalidNumberException & s)
	{
		out << "Invalid Number Exception: " << s.getString() << " isn't a number \n";
		return out;
	}
};



class InvalidDateException { // Implemented
	string date_error;
public:
	
	InvalidDateException(string d) { date_error = d; }
	string getDateError() { return date_error; }

	friend ostream & operator<<(ostream & out, InvalidDateException & d) {
		out << "Invalid Date Exception: " << d.getDateError() << " is invalid \n";
		return out;
	}
};

// ostream & operator<<(ostream & out, InvalidDateException & d);

//class InvalidTimeException {
//	string time_error;
//public:
//	InvalidTimeException(string t) { time_error = t; }
//	string getTimeError() { return time_error; }
//
//	friend ostream & operator<<(ostream & out, InvalidTimeException & t) {
//		out << "Invalid Time Exception: " << t.getTimeError() << " is invalid \n";
//		return out;
//	}
//};

// ostream & operator<<(ostream & out, InvalidTimeException & t);

class InvalidAddressException { //Implemented
	string address_error;
public:
	InvalidAddressException(string a) { address_error = a; }
	string getAddressError() { return address_error; }

	friend ostream & operator<<(ostream & out, InvalidAddressException & a) {
		out << "Invalid Address Exception: " << a.getAddressError() << " is invalid \n";
		return out;
	}
};

// ostream & operator<<(ostream & out, InvalidAddressException & a);


class InvalidCityException { // when the client lives in a city that the base doesn't cover
	string city_error;
public:
	InvalidCityException(string c) { city_error = c; }
	string getCityError() { return city_error; }

	friend ostream & operator<<(ostream & out, InvalidCityException & c) {
		out << "Invalid City Exception: " << c.getCityError() << " isn't covered by this Base \n";
		return out;
	}
};


class InvalidNIFException { // Implemnented
private:
	string nif;
public:
	InvalidNIFException(string n) { nif = n; }
	string getNIF() { return nif; }
	friend ostream & operator<<(ostream & out, InvalidNIFException & n)
	{
		out << "Invalid NIF Exception: " << n.getNIF() << " isn't a valid NIF \n";
		return out;
	}
};


class InvalidProductException // Implemented
{
private:
	string product;
public:
	InvalidProductException(string p) { product = p; }
	string getProduct() { return product; }
	friend ostream & operator<<(ostream & out, InvalidProductException & p)
	{
		out << "Invalid Product Exception: " << p.getProduct() << " can't be converted to a product \n";
		return out;
	}
};


class RestaurantNotFoundException { //Implemented
	string restaurant_error;
public:
	RestaurantNotFoundException(string r) { restaurant_error = r; }
	string getRestaurantError() { return restaurant_error; }

	friend ostream & operator<<(ostream & out, RestaurantNotFoundException & r) {
		out << "Restaurant Not Found Exception: " << r.getRestaurantError() << " not found \n";
		return out;
	}
};

// ostream & operator<<(ostream & out, RestaurantNotFoundException & r);

class GeographicAreaNotFoundException { //Implemented
	string geographic_area_error;
public:
	GeographicAreaNotFoundException(string g) { geographic_area_error = g; }
	string getGeographicAreaError() { return geographic_area_error; }

	friend ostream & operator<<(ostream & out, GeographicAreaNotFoundException & g) {
		out << "Geographic Area Not Found Exception: " << g.getGeographicAreaError() << " not found \n";
		return out;
	}

};

// ostream & operator<<(ostream & out, GeographicAreaNotFoundException & g);


class CuisineTypeNotFoundException { //Implemented
	string cuisine_type_error;
public:
	CuisineTypeNotFoundException(string c) { cuisine_type_error = c; }
	string getCuisineTypeError() { return cuisine_type_error; }

	friend ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c) {
		out << "Cuisine Type Not Found Exception: " << c.getCuisineTypeError() << " not found \n";
		return out;
	}
};

class ClientNotFoundException { //Implemented
private:
	string name;
public:
	ClientNotFoundException(string n) { name = n; }
	string getName() { return name; }
	friend ostream & operator<<(ostream & out, ClientNotFoundException & c) {
		out << "Client Not Found Exception: " << c.getName() << " not found \n";
		return out;
	}
};
// ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c);

class InvalidDatesException { //when the user says the final date is before the first // Implemented
	string datei, datef;
public:

	InvalidDatesException(string d1, string d2) { datei = d1; datef = d2; }
	string getDateI() { return datei; }
	string getDateF() { return datef; }

	friend ostream & operator<<(ostream & out, InvalidDatesException & d) {
		out << "Invalid Dates Exception: " << d.getDateI() << " is after " << d.getDateF()<<endl;
		return out;
	}
};

// ostream & operator<<(ostream & out, InvalidDatesException & d);

class InvalidPriceRangeException { //when the minimum value is bigger than the maximum value // Implemented
	double min, max;
public:
	InvalidPriceRangeException(double mi, double ma) { min = mi; max = ma; }
	double getMin() { return min; }
	double getMax() { return max; }

	friend ostream & operator<<(ostream & out, InvalidPriceRangeException & p) {
		out << "Invalid Price Range Exception: " << p.getMin() << " is bigger than " << p.getMax() << endl;
		return out;
	}
};

// ostream & operator<<(ostream & out, InvalidPriceRangeException & p);


class BlackListedException{ //Implemented 
private:
	string client;
public:
	BlackListedException(string c) { client = c; }
	string getClient() { return client; }
	friend ostream & operator<< (ostream & out, BlackListedException & c)
	{
		out << "Black Listed Exception: " << c.getClient() << " is black listed" << endl;
		return out;
	}
};


class FileOpenErrorException {
private:
	string filename;
public:
	FileOpenErrorException(string f) { filename = f; }
	string getFilename() { return filename; }
	friend ostream & operator<<(ostream & out, FileOpenErrorException & f)
	{
		out << "File Open Error Exception: couldn't open " << f.getFilename() << endl;
	}
};


inline bool InvalidOptions(int max, int ans)
{
	if (ans < 0 || ans > max)
		return true;
	else
		return false;
}

inline bool isNumber(string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if ((int(str[i]) < 48) || (int(str[i]) > 57))
			if (int(str[i]) != 46)
				return false;
	}
	return true;
}

inline bool isString(string str)
{
	for (int i = 0; i < str.size(); i++) 
	{
		if (str[i] < 65 || str[i] > 90) //letras maiusculas
			if (str[i] < 97 || str[i] > 122) //letras minusculas
				if (str[i] != 45 && str[i] != 32) //aceitar "-" e espaço
					return false;

	}
	return true;

}

inline bool isDateValid(Date_time d)
{
	int m = d.getMonth();
	int day = d.getDay();
	int y = d.getYear();
	if (m < 1 || m > 12)
		return false;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
	{
		if (day > 31 || day < 1)
			return false;
	}
	else if (m == 2)
	{
		if (y % 4 != 0)
		{
			if (day >29 || day < 1)
				return false;
		}
		else
		{
			if (day > 28 || day < 1)
				return false;
		}
	}
	else
	{
		if (day > 30 || day < 1)
			return false;
	}
	if (d.getJustDate())
		return true;
	else
	{
		if (d.getHours() < 0 || d.getHours() > 23 || d.getMinutes() < 0 || d.getMinutes() > 59)
			return false;
		else
			return true;
	}
		

}