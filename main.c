#include "src/helper.h"
#include "src/celestial/worlds.h"

int main(){
	worlds_init();
	worlds_worldTest(10);
	worlds_dumpWorlds(worlds_getRoot(),0);
	return 0;
}

