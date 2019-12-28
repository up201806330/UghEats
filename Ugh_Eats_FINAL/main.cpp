#pragma comment(lib, "winmm.lib")

#include <iostream>
#include "Address.h"
#include "People.h"
#include "Base.h"
#include "Date_time.h"
#include "utils.h"
#include "Restaurant.h"
#include "Main_menu.h"

#include <Windows.h>
#include <mmsystem.h>

int main() {
	// PlaySound(TEXT("MicrosoftWindowsXPStartupSoundEffect.wav"), NULL, SND_FILENAME | SND_ASYNC);
	string path = "bases.txt";
	vector<Base*> bases = Base::load(path);
	//Technician t;
	//t.load("technicians_p.txt", bases[0]);
	//cout << to_string(bases[0]->getTechnicians().size()) << endl;
	//bases[0]->removeTechnician();
	//cout << endl << to_string(bases[0]->getTechnicians().size()) << endl;
	//bases[0]->changeTechnician();


	//main_menu(bases);
	
	
	
	return 0;

}
