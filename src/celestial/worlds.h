typedef struct world world;

struct world {
	char name[50];
	double posx;
	double posy;
	int ID;
	world *next;
	world *prev;
	world *parent;
	world *firstChild;
	int numChildren;
};

int worlds_init();

world *worlds_getRoot(void);
void worlds_addWorld(world *new);
void worlds_addWorldTo(world *parent, world *child);
void worlds_dumpWorlds(world *in,int lvl);
void worlds_printWorld(world *world);
world *worlds_initWorld(world *in);


void worlds_worldTest(void);
