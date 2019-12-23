#pragma once

#include "People.h"


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