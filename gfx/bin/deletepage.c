#include <PA_BgStruct.h>

extern const char deletepage_Tiles[];
extern const char deletepage_Map[];
extern const char deletepage_Pal[];

const PA_BgStruct deletepage = {
	PA_BgNormal,
	256, 192,

	deletepage_Tiles,
	deletepage_Map,
	{deletepage_Pal},

	9984,
	{1536}
};
