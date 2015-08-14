#include "worlds.h"

/*
 IA		Very Luminous Supergiant
 IB		Less Luminous Supergiant
 II		Luminous Giant
 III	Giant
 IV		Sub-Giant
 V		Main Sequence (dwarf)
 VI		Sub-Dwarf
 VII	White Dwarf
*/

typedef enum {IA,IB,II,III,IV,V,VI,VII=0} star_luminosityClass;

typedef struct star_star star_star;
struct star_star{
	
	double					luminosity;
	star_luminosityClass	luminosityClass;
	double  				temperature;
	double 					mass;
	
};