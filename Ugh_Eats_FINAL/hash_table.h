#pragma once

#include "People.h"

using namespace std;

/*
struct eqAdmin {
	bool operator() (const Admin* a1, const Admin* a2) const;
};

struct hashAdmin {
	int operator() (const Admin* a1) const;
};



struct eqDeliv {
	bool operator() (const Delivery* d1, const Delivery* d2) const;
};

struct hashDeliv {
	int operator() (const Delivery* d1) const;
};
*/


/*
struct eqAdmin {
	bool operator()(const Admin * a1, const Admin * a2) const {
		return (
			a1->get_name() == a2->get_name() &&
			a1->get_NIF() == a2->get_NIF() &&
			a1->get_role() == a2->get_role() &&
			a1->get_wage() == a2->get_wage()
			);
	}
};

struct hashAdmin {
	int operator()(const Admin * a1) const {

		int v = 0;

		int nif = a1->get_NIF();

		while (nif > 0) {
			v += 51 * v + nif % 10;

			nif /= 10;
		}

		return v;
	}
};


struct eqDeliv {
	bool operator() (const Delivery* d1, const Delivery* d2) const {
		return (
			d1->get_name() == d2->get_name() &&
			d1->get_NIF() == d2->get_NIF() &&
			d1->get_wage() == d2->get_wage()
			);
	}
};

struct hashDeliv {
	int operator() (const Delivery* d1) const {
		int v = 0;

		int nif = d1->get_NIF();

		while (nif > 0) {
			v += 51 * v + nif % 10;

			nif /= 10;
		}

		return v;
	}
};

*/