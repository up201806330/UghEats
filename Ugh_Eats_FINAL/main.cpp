#pragma comment(lib, "winmm.lib")

#include <iostream>



#include "Address.h"
#include "People.h"
#include "Base.h"
#include "Date_time.h"
#include "utils.h"
#include "Restaurant.h"
#include "Main_menu.h"
// #include "hash_table.h"

#include <Windows.h>
#include <mmsystem.h>




int main() {
	// PlaySound(TEXT("MicrosoftWindowsXPStartupSoundEffect.wav"), NULL, SND_FILENAME | SND_ASYNC);
	string path = "bases.txt";
	vector<Base*> bases = Base::load(path);

	//bases[0]->seeOneTechnician();


	main_menu(bases);
	
	
	
	return 0;

}
