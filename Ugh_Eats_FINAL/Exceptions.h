#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include "Date_time.h"
using namespace std;
//Exception Handling

class InvalidStringException { 
	string error;
public:	
	/**
	 * @brief Construct a new Invalid String Exception object
	 * 
	 * @param e 
	 */
	InvalidStringException(string e) { error = e; }
	/**
	 * @brief Get the Error object
	 * 
	 * @return string 
	 */
	string getError() {return error;}

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param s InvalidStringException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidStringException & s) {
		out << "Invalid String Exception: " << s.getError() << " is invalid \n";
		return out;
	};
};

class InvalidOptionException { 
	int opt;
public:
	/**
	 * @brief Construct a new Invalid Option Exception object
	 * 
	 * @param o 
	 */
	InvalidOptionException(int o) { opt = o; }
	/**
	 * @brief Get the Option object
	 * 
	 * @return int 
	 */
	int getOption() { return opt; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param o InvalidOptionException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidOptionException & o) {
		out << "Invalid Option Exception: " << o.getOption() << " isn't an option \n";
		return out;
	};
};

class InvalidNumberException { 
private:
	string n;
public:
	/**
	 * @brief Construct a new Invalid Number Exception object
	 * 
	 * @param ni 
	 */
	InvalidNumberException(string ni) { n = ni; }
	/**
	 * @brief Get the String object
	 * 
	 * @return string 
	 */
	string getString() { 
		if (n == "") n = "empty string";
		return n; 
	}

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param s InvalidNumberException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream  & out, InvalidNumberException & s)
	{
		out << "Invalid Number Exception: " << s.getString() << " isn't a number \n";
		return out;
	}
};

class InvalidDateException { 
	string date_error;
public:
	/**
	 * @brief Construct a new Invalid Date Exception object
	 * 
	 * @param d 
	 */
	InvalidDateException(string d) { date_error = d; }
	/**
	 * @brief Get the Date Error object
	 * 
	 * @return string 
	 */
	string getDateError() { return date_error; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param d InvalidDateException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidDateException & d) {
		out << "Invalid Date Exception: " << d.getDateError() << " is invalid \n";
		return out;
	}
};

class InvalidAddressException { 
	string address_error;
public:
	/**
	 * @brief Construct a new Invalid Address Exception object
	 * 
	 * @param a 
	 */
	InvalidAddressException(string a) { address_error = a; }
	/**
	 * @brief Get the Address Error object
	 * 
	 * @return string 
	 */
	string getAddressError() {
		if (address_error == "" || address_error == "\n") address_error= "empty string";
		return address_error; 
	}

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param a InvalidAddressException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidAddressException & a) {
		out << "Invalid Address Exception: " << a.getAddressError() << " is invalid \n";
		return out;
	}
};

class InvalidCityException { 
	string city_error;
public:
	/**
	 * @brief Construct a new Invalid City Exception object
	 * 
	 * @param c 
	 */
	InvalidCityException(string c) { city_error = c; }
	/**
	 * @brief Get the City Error object
	 * 
	 * @return string 
	 */
	string getCityError() { return city_error; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param c InvalidCityException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidCityException & c) {
		out << "Invalid City Exception: " << c.getCityError() << " isn't covered by this Base \n";
		return out;
	}
};

class InvalidNIFException { 
private:
	string nif;
public:
	/**
	 * @brief Construct a new InvalidNIFException object
	 * 
	 * @param n 
	 */
	InvalidNIFException(string n) { nif = n; }
	/**
	 * @brief Get the NIF object
	 * 
	 * @return string 
	 */
	string getNIF() { return nif; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param n InvalidNIFException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidNIFException & n)
	{
		out << "Invalid NIF Exception: " << n.getNIF() << " isn't a valid NIF \n";
		return out;
	}
};

class InvalidProductException 
{
private:
	string product;
public:
	/**
	 * @brief Construct a new Invalid Product Exception object
	 * 
	 * @param p 
	 */
	InvalidProductException(string p) { product = p; }
	/**
	 * @brief Get the Product object
	 * 
	 * @return string 
	 */
	string getProduct() { return product; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param p InvalidProductException
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidProductException & p)
	{
		out << "Invalid Product Exception: " << p.getProduct() << " can't be converted to a product \n";
		return out;
	}
};

class RestaurantNotFoundException { 
	string restaurant_error;
public:
	/**
	 * @brief Construct a new Restaurant Not Found Exception object
	 * 
	 * @param r 
	 */
	RestaurantNotFoundException(string r) { restaurant_error = r; }
	/**
	 * @brief Get the Restaurant Error object
	 * 
	 * @return string 
	 */
	string getRestaurantError() { return restaurant_error; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param r RestaurantNotFoundException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, RestaurantNotFoundException & r) {
		out << "Restaurant Not Found Exception: " << r.getRestaurantError() << " not found \n";
		return out;
	}
};

class GeographicAreaNotFoundException { 
	string geographic_area_error;
public:
	/**
	 * @brief Construct a new Geographic Area Not Found Exception object
	 * 
	 * @param g 
	 */
	GeographicAreaNotFoundException(string g) { geographic_area_error = g; }
	/**
	 * @brief Get the Geographic Area Error object
	 * 
	 * @return string 
	 */
	string getGeographicAreaError() { return geographic_area_error; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g GeographicAreaNotFoundException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, GeographicAreaNotFoundException & g) {
		out << "Geographic Area Not Found Exception: " << g.getGeographicAreaError() << " not found \n";
		return out;
	}

};

class CuisineTypeNotFoundException { //Implemented
	string cuisine_type_error;
public:
	/**
	 * @brief Construct a new Cuisine Type Not Found Exception object
	 * 
	 * @param c 
	 */
	CuisineTypeNotFoundException(string c) { cuisine_type_error = c; }
	/**
	 * @brief Get the Cuisine Type Error object
	 * 
	 * @return string 
	 */
	string getCuisineTypeError() { return cuisine_type_error; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g CuisineTypeNotFoundException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c) {
		out << "Cuisine Type Not Found Exception: " << c.getCuisineTypeError() << " not found \n";
		return out;
	}
};

class ClientNotFoundException { //Implemented
private:
	string name;
public:
	/**
	 * @brief Construct a new Client Not Found Exception object
	 * 
	 * @param n 
	 */
	ClientNotFoundException(string n) { name = n; }
	/**
	 * @brief Get the Name object
	 * 
	 * @return string 
	 */
	string getName() { return name; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g ClientNotFoundException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, ClientNotFoundException & c) {
		out << "Client Not Found Exception: " << c.getName() << " not found \n";
		return out;
	}
};

class InvalidDatesException { 
	string datei, datef;
public:
	/**
	 * @brief Construct a new Invalid Dates Exception object
	 * 
	 * @param d1 
	 * @param d2 
	 */
	InvalidDatesException(string d1, string d2) { datei = d1; datef = d2; }
	/**
	 * @brief Get the starting date object
	 * 
	 * @return string 
	 */
	string getDateI() { return datei; }
	/**
	 * @brief Get the ending date object
	 * 
	 * @return string 
	 */
	string getDateF() { return datef; }
	
	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g InvalidDatesException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidDatesException & d) {
		out << "Invalid Dates Exception: " << d.getDateI() << " is after " << d.getDateF()<<endl;
		return out;
	}
};

class InvalidPriceRangeException { 
	double min, max;
public:
	/**
	 * @brief Construct a new Invalid Price Range Exception object
	 * 
	 * @param mi 
	 * @param ma 
	 */
	InvalidPriceRangeException(double mi, double ma) { min = mi; max = ma; }
	/**
	 * @brief Get the Min object
	 * 
	 * @return double 
	 */
	double getMin() { return min; }
	/**
	 * @brief Get the Max object
	 * 
	 * @return double 
	 */
	double getMax() { return max; }
	
	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g InvalidPriceRangeException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, InvalidPriceRangeException & p) {
		out << "Invalid Price Range Exception: " << p.getMin() << " is bigger than " << p.getMax() << endl;
		return out;
	}
};

class BlackListedException{  
private:
	string client;
public:
	/**
	 * @brief Construct a new Black Listed Exception object
	 * 
	 * @param c 
	 */
	BlackListedException(string c) { client = c; }
	/**
	 * @brief Get the Client object
	 * 
	 * @return string 
	 */
	string getClient() { return client; }

	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g BlackListedException object
	 * @return ostream& output stream reference
	 */
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
	/**
	 * @brief Construct a new File Open Error Exception object
	 * 
	 * @param f 
	 */
	FileOpenErrorException(string f) { filename = f; }
	/**
	 * @brief Get the Filename object
	 * 
	 * @return string 
	 */
	string getFilename() { return filename; }
	
	/**
	 * @brief Overload for the operator<<
	 * 
	 * @param out output stream
	 * @param g FileOpenErrorException object
	 * @return ostream& output stream reference
	 */
	friend ostream & operator<<(ostream & out, FileOpenErrorException & f)
	{
		out << "File Open Error Exception: couldn't open " << f.getFilename() << endl;
		return out;
	}
};

/**
 * @brief Checks if the input option is valid on said menu
 * 
 * @param max last option on menu
 * @param ans input option
 * @return true 
 * @return false 
 */
inline bool InvalidOptions(size_t max, int ans)
{
	if (ans < 0 || ans > max)
		return true;
	else
		return false;
}

/**
 * @brief Checks if the string can be stored as a number
 * 
 * @param str 
 * @return true 
 * @return false 
 */
inline bool isNumber(string str)
{
	if (str == "" || str == "\n") return false;

	for (int i = 0; i < str.size(); i++)
	{
		if ((int(str[i]) < 48) || (int(str[i]) > 57))
			if (int(str[i]) != 46)
				return false;
	}
	return true;
}

/**
 * @brief Checks if the string is merely composed of letters and whitespaces
 * 
 * @param str 
 * @return true 
 * @return false 
 */
inline bool isString(string str)
{
	if (str == "" || str == "\n") return false;

	for (int i = 0; i < str.size(); i++) 
	{
		if (str[i] < 65 || str[i] > 90) //letras maiusculas
			if (str[i] < 97 || str[i] > 122) //letras minusculas
				if (str[i] != 45 && str[i] != 32) //aceitar "-" e espa�o
					return false;

	}
	return true;

}

/**
 * @brief Checks if the input date is valid in terms of day of the month and the validity of the hour
 * 
 * @param d 
 * @return true 
 * @return false 
 */
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

#endif

