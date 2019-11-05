#include <iostream>
#include "Address.h"
#include "People.h"
#include "Base.h"
#include "Date_time.h"
#include "utils.h"
#include "Restaurant.h"

int main(){
	//string path; cout << "Please input the file path (with .txt): "; cin >> path;
	string path = "bases.txt";
	vector<Base*> bases = Base::load(path);
	
	cout << bases.at(0)->getAddress();
	return 0;
}