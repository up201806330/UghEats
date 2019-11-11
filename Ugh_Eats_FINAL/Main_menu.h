#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <vector>
class Base;
class Client;

void main_menu(std::vector<Base*> bases);
void main_menu_client(Client* client, Base * base);
void main_menu_admin_clients(Base * base);
void main_menu_admin_workers(Base * base);
void main_menu_admin_restaurant(Base * base);
void main_menu_admin_profits(Base * base);
void main_menu_admin(Base * base);
void main_menu_client_login(Base * base);




#endif 
