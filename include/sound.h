#ifndef __SOUND__
#define __SOUND__

#include "plane1.h"
#include "plane2.h"
#include "plane3.h"
#include "car1.h"
#include "car2.h"
#include "car3.h"
#include "boat1.h"
#include "boat2.h"
#include "boat3.h"
#include "flower1.h"
#include "flower2.h"
#include "flower3.h"
#include "gameboy1.h"
#include "gameboy2.h"
#include "gameboy3.h"
#include "heart1.h"
#include "heart2.h"
#include "heart3.h"
#include "mario1.h"
#include "mario2.h"
#include "mario3.h"
#include "star1.h"
#include "star2.h"
#include "star3.h"
#include "cat1.h"
#include "cat2.h"
#include "cat3.h"
#include "dog1.h"
#include "dog2.h"
#include "dog3.h"
#include "face1.h"
#include "face2.h"
#include "face3.h"
#include "pig1.h"
#include "pig2.h"
#include "pig3.h"
#include "swan1.h"
#include "swan2.h"
#include "swan3.h"
#include "yoshi1.h"
#include "yoshi2.h"
#include "yoshi3.h"
#include "mushroom1.h"
#include "mushroom2.h"
#include "mushroom3.h"
#include "bowser1.h"
#include "bowser2.h"
#include "bowser3.h"
#include "umbrella1.h"
#include "umbrella2.h"
#include "umbrella3.h"
#include "orchestral1.h"
#include "orchestral2.h"
#include "orchestral3.h"
#include "harp1.h"
#include "harp2.h"
#include "harp3.h"
#include "kick1.h"
#include "kick2.h"
#include "kick3.h"



//low notes
#define SCALED 0
#define LOWLOWFS 27781
#define LOWLOWG 29433
#define LOWAS 35002
#define LOWB 37083
#define LOWC 39288
#define LOWCS 41624
#define LOWD 44100
#define LOWDS 46722
#define LOWE 49500
#define LOWF 52444
#define LOWFS 55562
#define LOWG 58866
//mid notes
#define SCALEG 1

#define MIDGS 46722
#define MIDA 49500
#define MIDAS 52444
#define MIDB 55562
#define MIDC 58866
#define MIDCS 62366
//high notes
#define SCALEG2 2

#define HIGHD 33037
#define HIGHDS 35002
#define HIGHE 37083
#define HIGHF 39288
#define HIGHFS 41624
#define HIGHG 44100
#define HIGHGS 46722
#define HIGHA 49500
#define HIGHAS 52444
#define HIGHB 55562
#define HIGHBS 58866

void PickSoundFile(int note, int page);

void SetNoteProperties(u16 Page,u8 sprite, u8 scale, u16 note,u8 soundfile,bool sound);

#endif

