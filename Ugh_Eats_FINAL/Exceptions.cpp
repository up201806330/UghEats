#include "Exceptions.h"

ostream & operator<<(ostream & out, InvalidStringException & s)
{
	out << "Invalid String Exception: " << s.getError() << " is invalid \n";
	return out;
}

ostream & operator<<(ostream & out, InvalidOptionException & o)
{
	out << "Invalid Option Exception: " << o.getOption() << "isn't an option \n";
	return out;
}

ostream & operator<<(ostream & out, InvalidDateException & d)
{
	out << "Invalid Date Exception: " << d.getDateError() << " is invalid \n";
	return out;
}

ostream & operator<<(ostream & out, InvalidTimeException & t)
{
	out << "Invalid Time Exception: " << t.getTimeError() << " is invalid \n";
	return out;
}

ostream & operator<<(ostream & out, InvalidAddressException & a)
{
	out << "Invalid Address Exception: " << a.getAddressError() << " is invalid \n";
	return out;
}

ostream & operator<<(ostream & out, InvalidCityException & c)
{
	out << "Invalid City Exception: " << c.getCityError() <<  "isn't covered by this Base \n";
	return out;
}

ostream & operator<<(ostream & out, RestaurantNotFoundException & r)
{
	out << "Restaurant Not Found Exception: " << r.getRestaurantError() << " not found \n";
	return out;
}

ostream & operator<<(ostream & out, GeographicAreaNotFoundException & g)
{
	out << "Geographic Area Not Found Exception: " << g.getGeographicAreaError() << " not found \n";
	return out;
}

ostream & operator<<(ostream & out, CuisineTypeNotFoundException & c)
{
	out << "Cuisine Type Not Found Exception: " << c.getCuisineTypeError() << " not found \n";
	return out;
}

ostream & operator<<(ostream & out, InvalidDatesException & d)
{
	out << "Invalid Dates Exception: " << d.getDateI() << " is after " << d.getDateF();
	return out;
}

ostream & operator<<(ostream & out, InvalidPriceRangeException & p)
{
	out << "Invalid Price Range Exception: " << p.getMin() << " is bigger than " << p.getMax();
	return out;
}