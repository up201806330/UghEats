#pragma once
#include <string>
using namespace std;
//Exception Handling

class InvalidStringException {
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



class InvalidDateException {
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

class InvalidTimeException {
	string time_error;
public:
	InvalidTimeException(string t) { time_error = t; }
	string getTimeError() { return time_error; }

	friend ostream & operator<<(ostream & out, InvalidTimeException & t) {
		out << "Invalid Time Exception: " << t.getTimeError() << " is invalid \n";
		return out;
	}
};

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


class InvalidCityException { // when the client lives in a city that the base doesn't cover // Implemented
	string city_error;
public:
	InvalidCityException(string c) { city_error = c; }
	string getCityError() { return city_error; }

	friend ostream & operator<<(ostream & out, InvalidCityException & c) {
		out << "Invalid City Exception: " << c.getCityError() << " isn't covered by this Base \n";
		return out;
	}
};


// ostream & operator<<(ostream & out, InvalidCityException & c);

class RestaurantNotFoundException {
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

class GeographicAreaNotFoundException {
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


class CuisineTypeNotFoundException {
	string cuisine_type_error;
public:
	CuisineTypeNotFoundException(string c) { cuisine_type_error = c; }
	string getCuisineTypeError() { return cuisine_type_error; }

	friend ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c) {
		out << "Cuisine Type Not Found Exception: " << c.getCuisineTypeError() << " not found \n";
		return out;
	}
};

// ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c);

class InvalidDatesException { //when the user says the final date is before the first
	string datei, datef;
public:

	InvalidDatesException(string d1, string d2) { datei = d1; datef = d2; }
	string getDateI() { return datei; }
	string getDateF() { return datef; }

	friend ostream & operator<<(ostream & out, InvalidDatesException & d) {
		out << "Invalid Dates Exception: " << d.getDateI() << " is after " << d.getDateF();
		return out;
	}
};

// ostream & operator<<(ostream & out, InvalidDatesException & d);

class InvalidPriceRangeException { //when the minimum value is bigger than the maximum value
	int min, max;
public:
	InvalidPriceRangeException(int mi, int ma) { min = mi; max = ma; }
	int getMin() { return min; }
	int getMax() { return max; }

	friend ostream & operator<<(ostream & out, InvalidPriceRangeException & p) {
		out << "Invalid Price Range Exception: " << p.getMin() << " is bigger than " << p.getMax();
		return out;
	}
};

// ostream & operator<<(ostream & out, InvalidPriceRangeException & p);


class BlackListedException{
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


inline bool InvalidOptions(int max, int ans)
{
	if (ans < 1 || ans > max)
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
				if (str[i] != 45 || str[i] != 32) //aceitar "-" e espaço
					return false;

	}
	return true;

}