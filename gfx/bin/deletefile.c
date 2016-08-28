#include <PA_BgStruct.h>

extern const char deletefile_Tiles[];
extern const char deletefile_Map[];
extern const char deletefile_Pal[];

const PA_BgStruct deletefile = {
	PA_BgNormal,
	256, 192,

	deletefile_Tiles,
	deletefile_Map,
	{deletefile_Pal},

	9920,
	{1536}
};
