#include "Address.h"
#include <vector>
#include "utils.h"
#include "Exceptions.h"

Address::Address() {

}

Address::~Address() {

}

bool Address::parse(string str) { //needs reinforcing aka apanhar excecoes dos stois
	vector<string> parts = utils::split(str, '/');
	for (auto &part : parts) utils::trim(part);

	if (parts.size() != 7)
		return false;
	district = parts.at(0);
	if (!isString(district))
		return false;
	town = parts.at(1);
	if (!isString(town))
		return false;
	street = parts.at(2);
	if (!isString(street))
		return false;

	
	if (!isNumber(parts.at(3)) || !isNumber(parts.at(4)) || !isNumber(parts.at(5)) || !isNumber(parts.at(6)))
		return false;
	number = stoi(parts.at(3));
	floor = stoi(parts.at(4));
	latitude = stod(parts.at(5));
	longitude = stod(parts.at(6));
	return true;
	
}


void Address::setTown(string cidade) {
	town = cidade;
}

void Address::setDistrict(string distrito) {
	district = distrito;
}

void Address::setStreet(string rua) {
	street = rua;
}

void Address::setNumber(unsigned int n) {
	number = n;
}

void Address::setFloor(int flr) {
	floor = flr;
}

string Address::get_town() const {
	return town;
}

string Address::get_district() const {
	return district;
}

string Address::get_street() const {
	return street;
}

unsigned int Address::get_number() const {
	return number;
}

int Address::get_floor() const {
	return floor;
}

string Address::str() const
{
	string result = district + " / ";
	result += town + " / ";
	result += street + " / ";
	result += to_string(number) + " / ";
	result += to_string(floor) + " / ";
	result += to_string(latitude) + " / ";
	result += to_string(longitude) + " / ";
	return result;
}

std::ostream & operator<<(std::ostream & stream, Address address) {
	
	/*
	stream << "Town: " << address.town << endl;
	stream << "District: " << address.district << endl;
	stream << "Street: " << address.street << endl;
	stream << "Number: " << address.number << endl;
	*/
	stream << address.district << " / ";
	stream << address.town << " / ";
	stream << address.street << " / ";
	stream << address.number << " / ";
	stream << address.floor << " / ";
	stream << address.latitude << " / ";
	stream << address.longitude;

	return stream;
}