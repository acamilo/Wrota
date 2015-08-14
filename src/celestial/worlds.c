#include "worlds.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../helper.h"
#include <math.h>
#include <string.h>


world_world *root;
int idSingleton = 0;

// turbo ugly.
const char *world_type_strings[] = {"Black Hole","Star","Planet","Moon"};

// worlds form a tree. there is one root world at the base.
// A world has children. firstChild points to the first in a doubly linked list
// child worlds of a parent are a doubly linked list with a reference to thier parent
// a wor

world_world *worlds_getRoot(){
	return root;
}

void worlds_addWorld(world_world *new){
	worlds_addWorldTo(0, new);
}

int worlds_init(){
	root = worlds_initWorld(0);
	if (root==0) {
		//printf("Could not MALLOC root world");
		return -1;
	}
	
	root->posx = 0.0;
	root->posy = 0.0;
	root->type = BlackHole;
	strcpy(root->name,"Black Hole");
	
	return 0;
}

void worlds_addWorldTo(world_world *parent, world_world *child){
	
	// No Parent? its on the top of the tree
	if (parent==0) {
		parent = root;
		////printf("[worlds]\t No parent provided. '%s' is a child of '%s'\n",child->name,root->name);
	}
	// Is child an orphan?
	if(child->parent != 0){
		//printf("[worlds]\t'%s' is not an orphan. orphaning it.\n",child->name);
		
		// is child the firstChild of it's parent?
		if (child->parent->firstChild == child) {
			// its a first child.
			// Does it have siblings?
			if(child->next) child->parent->firstChild=child->next; // yes, next in line gets to be first child
			else child->parent->firstChild = 0;// only child

			
		}
		// Child needs to be removed. linked list needs to be stitched.
		world_world *prev = child->prev;
		world_world *next = child->next;
		
		// make it an orphan
		if (prev) prev->next=next;
		if (next) next->prev=prev;
		child->parent->numChildren--;
		child->parent=0;
	}
	
	// Does this world have children?
	if (parent->firstChild == 0) {
		////printf("[worlds]\t'%s' is first child of '%s'.\n",child->name,parent->name);
		// ADD it and inc count
		parent->firstChild = child;
		parent->numChildren++;
		child->parent = parent;
		// aaand we're done. 
		return;
	}
	
	// Has Children. Must walk to end.
	world_world *lastChild = parent->firstChild;
	while(lastChild->next) lastChild = lastChild->next;
	
	// we're at the end. add new child.
	lastChild->next = child;
	child->prev = lastChild;
	child->parent = parent;
	parent->numChildren++;
	////printf("[worlds]\t'%s' is child #%d of '%s'.\n",child->name,parent->numChildren,parent->name);
	
}

void worlds_printWorld(world_world *world){
	printf("\n World #%d (%s)['%s']\n", world->ID,world_type_strings[world->type],world->name);
	printf("\tLy x: \t%f\n",world->posx);
	printf("\tLy y: \t%f\n",world->posy);
	
	printf("\n\tNext:\t\t");
	if(world->next) printf("'%s'",world->next->name);
	else printf("'%s'","none");
	
	printf("\n\tPrev:\t\t");
	if(world->prev) printf("'%s'",world->prev->name);
	else printf("'%s'","none");
	
	printf("\n\tparent:\t\t");
	if(world->parent) printf("'%s'",world->parent->name);
	else printf("'%s'","none");
	
	printf("\n\tfirstChild:\t");
	if(world->firstChild) {
		printf("'%s'",world->firstChild->name);
		printf("\n\tnumChilds:\t%d",world->numChildren);
	}
	else printf("'%s'","none");
	printf("\n");
	
}

void worlds_dumpWorlds(world_world *in,int lvl){
	if (in->parent) if(in->type == Star && in->parent->type == BlackHole) printf("\n");
	for(int i=0; i<=lvl; i++) printf("\t");
	printf("World #%d (%s)['%s']\n", in->ID,world_type_strings[in->type],in->name);

	
	//worlds_printWorld(in);
	world_world *ch = in->firstChild;
	if (ch==0) return;
	lvl++;
	//worlds_dumpWorlds(ch);
	while(ch) {
		worlds_dumpWorlds(ch,lvl);
		ch=ch->next;
	}
}



world_world *worlds_initWorld(world_world *in){
	// If they've passed us a null pointer, MALLOC a new world.
	if (in==0) in = (world_world*)malloc(sizeof(world_world));
	
	// malloc failed, pass null pointer up.
	if (in==0) return in;
	
	// Initialise world.
	strcpy(in->name,"");
	in->posx = NAN;
	in->posy = NAN;
	
	// clear out pointers
	in->next = 0;
	in->prev = 0;
	in->parent = 0;
	in->firstChild = 0;
	in->numChildren = 0;
	
	// each world gets a unieque ID
	in->ID = idSingleton++;
	
	return in;

}

int stars = 0;
int planets = 0;

void worlds_worldTest(){
	srand(time(0));
	
	for (int i=0; i<100; i++) {
		//printf("\033[2J\033[1;1H");
		//printf("Stars:\t%d\nPlanets:\t%d\n",stars,planets);
		stars++;
		printf("\n");
		// make a new world
		world_world *x = worlds_initWorld(0);
		x->posx = normFloatRand();
		x->posy = normFloatRand();
		x->type = Star;
		sprintf(x->name,"GUC%d-A",x->ID);
		
		
		worlds_addWorldTo(0,x);
		printf ("[world]\t'%s' has been born!\n",x->name);
		// Bachelor star?
		if(normFloatRand()<0.1){
			printf ("\t'%s' Is a Bachelor Star\n",x->name);
			continue; // aaaand we're done with this one
		}
		
		// Binary
		if(normFloatRand()>0.6){
			stars++;
			world_world *c = worlds_initWorld(0);
			c->posx = normFloatRand();
			c->posy = normFloatRand();
			c->type = Star;
			sprintf(c->name,"GUC%d-B",x->ID);
			worlds_addWorldTo(x,c);
			
			printf ("\t'%s' Is in a Binary Pair with it's smaller companion '%s' \n",x->name,c->name);
		}
		
		// Planets?
		
		if(normFloatRand()>0.6){
			printf("\t'%s' has planets!\n",x->name);
			int numPlanets = normFloatRand()*0.8*10;
			
			for (int j=0;j<numPlanets;j++){
				planets++;
				world_world *pl = worlds_initWorld(0);
				pl->posx = normFloatRand();
				pl->posy = normFloatRand();
				pl->type = Planet;
				sprintf(pl->name,"GUC%d-A%c",x->ID,'a'+j);
				printf("\t\tNew planet '%s'\n",pl->name);
				worlds_addWorldTo(x,pl);
				if (normFloatRand()>0.2){
					int numMoons = normFloatRand()*0.3*10;
					for (int k=0;k<numMoons;k++){
						world_world *moon = worlds_initWorld(0);
						moon->posx = normFloatRand();
						moon->posy = normFloatRand();
						moon->type = Moon;
						sprintf(moon->name,"GUC%d-A%c%d",x->ID,'a'+j,k);
						worlds_addWorldTo(pl,moon);
					}
				}

			}
			continue;
		}
		

	}
	
	//worlds_dumpWorlds(worlds_getRoot(),0);
/*
	world_world *w = worlds_initWorld(0);
	strcpy(w->name,"Delta Pavonis");
	w->posx=1.5;
	w->posy=4;
	worlds_addWorldTo(0,w);
	
	world_world *x = worlds_initWorld(0);
	strcpy(x->name,"Hadees");
	x->posx=0.8;
	x->posy=0.2;
	worlds_addWorldTo(w,x);
	
	x = worlds_initWorld(0);
	strcpy(x->name,"Roc");
	x->posx=0.1;
	x->posy=0.1;
	worlds_addWorldTo(w,x);
	
	x = worlds_initWorld(0);
	strcpy(x->name,"Resurgem");
	x->posx=0.01;
	x->posy=0.05;
	worlds_addWorldTo(w,x);
	
	worlds_dumpWorlds(worlds_getRoot(),0);
*/

	
}