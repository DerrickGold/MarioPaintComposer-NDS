#include <PA_BgStruct.h>

extern const char keyboard1_Tiles[];
extern const char keyboard1_Map[];
extern const char keyboard1_Pal[];

const PA_BgStruct keyboard1 = {
	PA_BgLarge,
	256, 1024,

	keyboard1_Tiles,
	keyboard1_Map,
	{keyboard1_Pal},

	28928,
	{8192}
};
