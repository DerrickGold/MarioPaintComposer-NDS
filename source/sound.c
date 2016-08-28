#include <PA9.h>       // Include for PA_Lib
#include "variables.h"
#include "sound.h"
//assigns the stamp icons on the top their own sound
void AssignStampSounds(void){
	u8 stamp;
	for(stamp=0;stamp<21;stamp++)MPCFile[257][stamp].SoundFile=stamp;
}
u8 NoteToNum(u16 note, u8 scale){
	switch(scale){
		case SCALED:
			switch(note){
				case LOWDS:return 24;break;
				case LOWLOWG: return 23;break;
				case LOWLOWFS: return 29;break;
				case LOWAS: return 1;break;
				case LOWB:return 2;break;
				case LOWC:return 3;break;
				case LOWCS:return 4;break;
				case LOWD:return 5;break;
				case LOWE:return 6;break;
				case LOWF:return 7;break;
				case LOWFS:return 8;break;
				case LOWG:return 9;break;
			}
		break;
		case SCALEG:
			switch(note){
				case MIDGS:return 10;break;
				case MIDA:return 11;break;
				case MIDAS:return 12;break;
				case MIDB:return 13;break;
				case MIDC:return 14;break;
				case MIDCS:return 15;break;
			}
		break;
		case SCALEG2:
			switch(note){
				case HIGHD:return 16;break;
				case HIGHDS:return 17;break;
				case HIGHE:return 18;break;
				case HIGHF:return 19;break;
				case HIGHFS:return 20;break;
				case HIGHG:return 21;break;
				case HIGHGS:return 22;break;
				case HIGHA:return 25;break;
				case HIGHAS:return 26;break;
				case HIGHB:return 27;break;
				case HIGHBS:return 28;break;
			}
		break;
	}
	return 0;
	
}
u16 NumToNote(u8 number){
	switch(number){	
		case 1:return LOWAS;break;
		case 2:return LOWB;break;
		case 3:return LOWC;break;
		case 4:return LOWCS;break;
		case 5:return LOWD;break;
		case 6:return LOWE;break;
		case 7:return LOWF;break;
		case 8:return LOWFS;break;
		case 9:return LOWG;break;
		case 10:return MIDGS;break;
		case 11:return MIDA;break;
		case 12:return MIDAS;break;
		case 13:return MIDB;break;
		case 14:return MIDC;break;
		case 15:return MIDCS;break;
		case 16:return HIGHD;break;
		case 17:return HIGHDS;break;
		case 18:return HIGHE;break;
		case 19:return HIGHF;break;
		case 20:return HIGHFS;break;
		case 21:return HIGHG;break;
		case 22:return HIGHGS;break;
		case 23:return LOWLOWG;break;
		case 24:return LOWDS;break;
		case 25:return HIGHA;break;
		case 26:return HIGHAS;break;
		case 27:return HIGHB;break;
		case 28:return HIGHBS;break;
		case 29:return LOWLOWFS;break;
	}
	return 0;	
}

void SetNoteProperties(u16 Page,u8 sprite, u8 scale, u16 note,u8 soundfile,bool sound){
	MPCFile[Page][sprite].Note=NoteToNum(note,scale);
	MPCFile[Page][sprite].Pitch=scale;
	MPCFile[Page][sprite].SoundFile=soundfile;
	if(sound==TRUE){
		PickSoundFile(sprite,Page);
		AS_SetSoundRate(lastsfx,note);
	}
}
//picks a sound file based on the note
void PickSoundFile(int note, int page){
	switch(MPCFile[page][note].SoundFile){
		case MARIO:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(mario1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(mario2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(mario3);break;
			}
		break;
		case MUSHROOM:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(mushroom1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(mushroom2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(mushroom3);break;
			}
		break;
		case YOSHI:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(yoshi1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(yoshi2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(yoshi3);break;
			}
		break;
		case STAR:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(star1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(star2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(star3);break;
			}
		break;
		case FLOWER:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(flower1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(flower2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(flower3);break;
			}
		break;
		case GAMEBOY:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(gameboy1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(gameboy2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(gameboy3);break;
			}
		break;
		case DOG:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(dog1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(dog2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(dog3);break;
			}
		break;
		case CAT:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(cat1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(cat2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(cat3);break;
			}
		break;
		case PIG:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(pig1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(pig2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(pig3);break;
			}
		break;
		case SWAN:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(swan1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(swan2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(swan3);break;
			}
		break;
		case FACE:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(face1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(face2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(face3);break;
			}
		break;
		case PLANE:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(plane1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(plane2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(plane3);break;
			}
		break;
		case SHIP:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(boat1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(boat2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(boat3);break;
			}
		break;
		case CAR:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(car1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(car2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(car3);break;
			}
		break;
		case HEART:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(heart1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(heart2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(heart3);break;
			}
		break;
		case BOWSER:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(bowser1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(bowser2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(bowser3);break;
			}
		break;
		case UMBRELLA:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(umbrella1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(umbrella2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(umbrella3);break;
			}
		break;
		case ORCHESTRAL:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(orchestral1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(orchestral2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(orchestral3);break;
			}
		break;
		case HARP:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(harp1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(harp2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(harp3);break;
			}
		break;
		case KICK:
			switch(MPCFile[page][note].Pitch){
				case SCALED:lastsfx = AS_SoundQuickPlay(kick1);break;
				case SCALEG: lastsfx = AS_SoundQuickPlay(kick2);break;
				case SCALEG2: lastsfx = AS_SoundQuickPlay(kick3);break;
			}
		break;
	}
}
