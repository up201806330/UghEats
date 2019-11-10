#include "Main_menu.h"
#include "Base.h"
#include "utils.h"


void main_menu_client(Client* client) {
	while (true) {
		string input;
		utils::clear_screen();

		cout << "Welcome to Ugh Eats, " << client->get_name() << endl;
		cout << "1. Make order" << endl;
		cout << "2. Edit Info" << endl;
		cout << "CTRL+Z to save and exit" << endl;
		cout << ">> ";

		getline(cin, input);

		if (input == "1") client->make_order();
		if (input == "2") client->edit();
		if (cin.eof()) exit(0); //<------------------------- implement something to save and exit

		else continue;
	}
}

void main_menu_admin(Base * base) {
	
}

void main_menu_client_login(Base * base){
	while (true) {
		string input;
		utils::clear_screen();

		cout << "1. Login" << endl;
		cout << "2. Sign up" << endl;
		cout << ">> ";
		getline(cin, input);

		if (input == "1") {
			vector<Client*>::iterator it;
			vector<Client*> clients = base->getClients();

			cout << "\n\nClient name: ";
			getline(cin, input);
			if (cin.eof()) continue;
			
			for (it = clients.begin(); it != clients.end(); it++) {
				if ((*it)->get_name() == input) main_menu_client(*it);
			}
			
			cout << "\nClient not found; Try again (Enter to continue)" << endl;
			cout << ">> ";
			cin.ignore();
		}

		if (input == "2") {
			utils::clear_screen();
			base->addClient(); //try para apanhar execao blacklisted ; sem isto nao funciona corretamente
			main_menu_client(base->getClients().at(base->getClients().size() - 1));
		}

		if (cin.eof()) break;
		
		else continue;
	}
}

void main_menu(vector<Base*> bases) {
	while (true) {
		string input;
		size_t temp;
		Base * selected_base;
		utils::clear_screen();

		cout << "Pick a Base:" << endl;

		for (auto n = 0; n < bases.size(); n++) {
			cout << n + 1 << ". " << bases.at(n)->getDistrict() << endl;
		}

		cout << ">> ";
		
		cin >> temp;
		if (cin.fail() || temp > bases.size() || cin.eof()) {
			cin.clear();
			continue;
		}

		else {
			selected_base = bases.at(temp - 1);
		}
		cin.ignore();

		cout << "\n\n";
		cout << "Client or Admin ?" << endl;
		cout << "1. Client" << endl;
		cout << "2. Admin" << endl;
		cout << ">> ";

		getline(cin, input);

		if (input == "1") main_menu_client_login(selected_base);
		if (input == "2") main_menu_admin(selected_base);
		if (cin.eof()) {
			cin.clear();
			continue;
		}
		else continue;
	}
}