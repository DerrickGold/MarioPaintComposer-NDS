#include <PA_BgStruct.h>

extern const char mpcdownload_Tiles[];
extern const char mpcdownload_Map[];
extern const char mpcdownload_Pal[];

const PA_BgStruct mpcdownload = {
	PA_BgNormal,
	256, 192,

	mpcdownload_Tiles,
	mpcdownload_Map,
	{mpcdownload_Pal},

	512,
	{1536}
};
