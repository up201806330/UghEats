#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <vector>
class Base;
class Client;

void main_menu(std::vector<Base*> bases);
void main_menu_client(Client* client);
void main_menu_admin();
void main_menu_client_login(Base * base);




#endif 
