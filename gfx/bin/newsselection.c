#include <PA_BgStruct.h>

extern const char newsselection_Tiles[];
extern const char newsselection_Map[];
extern const char newsselection_Pal[];

const PA_BgStruct newsselection = {
	PA_BgNormal,
	256, 192,

	newsselection_Tiles,
	newsselection_Map,
	{newsselection_Pal},

	10624,
	{1536}
};
