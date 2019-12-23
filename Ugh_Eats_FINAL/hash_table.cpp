#include "hash_table.h"

bool eqAdmin::operator()(const Admin * a1, const Admin * a2) const {
	return (
		a1->get_name() == a2->get_name() &&
		a1->get_NIF() == a2->get_NIF() &&
		a1->get_role() == a2->get_role() &&
		a1->get_wage() == a2->get_wage()
		);
}

int hashAdmin::operator()(const Admin * a1) const {

	int v = 0;

	/*
	for (char & c : a1->get_name()) {
		v += 37 * v + c;
	}
	*/

	int nif = a1->get_NIF();

	while (nif > 0) {
		v += 51 * v + nif % 10;

		nif /= 10;
	}

	return v;
}



bool eqDeliv::operator()(const Delivery * d1, const Delivery * d2) const {
	return (
		d1->get_name() == d2->get_name() &&
		d1->get_NIF() == d2->get_NIF() &&
		d1->get_wage() == d2->get_wage()
		);
}

int hashDeliv::operator()(const Delivery * d1) const {

	int v = 0;

	int nif = d1->get_NIF();

	while (nif > 0) {
		v += 51 * v + nif % 10;

		nif /= 10;
	}

	return v;
}
