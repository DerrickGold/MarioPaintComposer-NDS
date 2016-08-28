#include <PA_BgStruct.h>

extern const char header_Tiles[];
extern const char header_Map[];
extern const char header_Pal[];

const PA_BgStruct header = {
	PA_BgNormal,
	256, 192,

	header_Tiles,
	header_Map,
	{header_Pal},

	3328,
	{1536}
};
