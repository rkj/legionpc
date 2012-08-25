#ifndef D_RAND_H_D
#define D_RAND_H_D

namespace Core {

/// Ustawia ziarno generatora liczb psedolosowych
void Randomize(unsigned long seed);

/// Ustawia ziarno generatora liczb psedolosowych wedlug aktualnego czasu
void RandomizeTimer(void);

/// Zwraca 32 bitowa liczbe pseudolosowa
unsigned long Randi(void);

/// Zwraca liczbe psedolosowa z przedzialu [0,pl_max]
unsigned long Randi(unsigned long pl_max);

/// Zwraca liczbe psedolosowa z przedzialu [pl_min,pl_max]
long Randi(long pl_min,long pl_max);

/// Zwraca zmiennopozycyjna liczbe psedolosowa z przedzialu [0,1]
float Randf(void);

/// Zwraca zmiennopozycyjna liczbe psedolosowa z przedzialu [pl_min,pl_max]
float Randf(float pl_min,float pl_max);

}	//namespace Core

#endif
