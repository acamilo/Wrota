#ifndef WORLDS_H
#define WORLDS_H

typedef enum {BlackHole=0,Star=1,Planet=2,Moon=3} world_type;


typedef struct world_world world_world;

struct world_world {
	// name
	char name[50];
	
	// placeholder for now. i'll probubly do better then x and y
	double posx;
	double posy;
	
	// unique ID
	int ID;
	
	// Tree, Double linked list pointers
	world_world *next;
	world_world *prev;
	world_world *parent;
	world_world *firstChild;
	
	// number of children "cache"
	int numChildren;
	
	// body type
	world_type type;
};



int worlds_init();

world_world *worlds_getRoot(void);
void worlds_addWorld(world_world *new);
void worlds_addWorldTo(world_world *parent, world_world *child);
void worlds_dumpWorlds(world_world *in,int lvl);
void worlds_printWorld(world_world *world);
world_world *worlds_initWorld(world_world *in);


void worlds_worldTest(int stars);



#endif
