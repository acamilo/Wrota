#ifndef STARS_H
#define STARS_H

#include "worlds.h"
/*
 IA+	Extreamly Luminous Super-Giant
 IA		Luminous Super-Giant
 IAB	Intermediate Luminous Super-Giants
 IB		Less Luminous Super-Giant
 II		Bright Giant
 III	Giant
 IV		Sub-Giant
 V		Main Sequence (dwarf)
 VI		Sub-Dwarf
 VII	White Dwarf
*/

typedef enum {IAP,IA,IAB,IB,II,III,IV,V,VI,VII=0} star_luminosityClass;

/*
 O		30,000k and above
 B		10,000k to 30,000k
 A		7,500k  to 10,000k
 F		6,000   to 7,500 K
 G		5,200   to 6,000 K
 K		3,700   to 5,200 K
 M		2,400   to 3,700 K
 L		Brown-Dwarf
 T		Methane containing Brown-Dwarf
 Y		Brown-Dwarf


*/
typedef enum {O,B,A,F,G,K,M=0,L,T,Y} star_spectralClass;

typedef struct star_star star_star;
struct star_star{
	world_world 			world;
	double					luminosity;
	star_luminosityClass	luminosityClass;
	double  				temperature;
	star_spectralClass		spectralClass;
	double 					mass;
	
};

#endif