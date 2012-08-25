
#include <ctime>

#include "Rand.h"

namespace Core {

static unsigned long seed32;

inline unsigned long _rand32(void) {
	//Marsaglia (1972)
	seed32 = 69069 * seed32 + 1;		//powinno byc modulo 2^32 ale na kompach 32bitowych samo tak sie dzieje
	return seed32;
}

void Randomize(unsigned long seed) {
	seed32 = seed;
}

void RandomizeTimer(void) {
	seed32 = std::time(0);
}

unsigned long Randi(void) {
	return _rand32();
}

unsigned long Randi(unsigned long pl_max) {
	return _rand32() % (pl_max+1);
}

long Randi(long pl_min,long pl_max) {
	unsigned long dif = pl_max;
	dif -= pl_min;
	dif += 1;
	return pl_min + (_rand32() % dif);
}


float Randf(void) {
	float x = (float)(_rand32() % 100001);
	return x/100000.0f;
}

float Randf(float pl_min,float pl_max) {
	float dif = pl_max - pl_min;
	return Randf() * dif + pl_min;
}


}	//namespace Core
