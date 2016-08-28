// Includes
#include <PA9.h>       // Include for PA_Lib

#include "sound.h"
#include "gfxsys.h"
#include "variables.h"
#include "INIParsing.h"


#define TEMPODIVISION 0.15

#define TEMPOSLIDPOS 96

#define TEXTX 20
#define TEXTY 18

#define MARIOSPEED 5

void spritepicker(void);
void spriteplotting(void);

void PlayBack(void);
void UpdateStampPos(bool sound);
void TempoControl(void);
void InitFatSys(char *directory, char *ext);
void PageSlider(void);

bool PageView=0;
s8 spritetouched=0;
s8 OldStamp;
u16 previewpage=0;

float OldTempo=0;

void CheckSleep(void){
	if(PA_LidClosed()==TRUE && Sleep==0){
		Sleep=1;
		powerOff(POWER_LCD);
	}
	else if(Sleep==1 && PA_LidClosed()==FALSE){
		powerOn(POWER_LCD);
		Sleep=0;
	}
}
void CheckLoadNewSong(void){
	if(Sleep==1){
		if(Play==0){
			s16 newsong=rand()%FileNumber;
			loadSavedata(location,newsong);
			Page=0;
			Play=1;
		}		
	}
}


inline u16 FindLastPage(void){
	u16 temppage;
	u8 sprite=0;
	u8 count=0;
	u8 pagecount=0;
	for(temppage=0;temppage<=256;++temppage){
		count=0;
		for(sprite=0;sprite<35;++sprite){
			if(MPCFile[temppage][sprite].used==0)count++;
			if(count==35)pagecount++;
		}
		if(count<35)pagecount=0;
		if(temppage>=256&&pagecount<5)return 256;
		if(pagecount==5)return temppage-5;
	}
	return 0;
}
s16 FindLastNotePos(u16 page){
	s16 sprite=0,tempsprite=0;
	s16 tempX=0;
	for(sprite=0;sprite<35;++sprite){
		if(MPCFile[page][sprite].used==1){
			if(MPCFile[page][sprite].x>=tempX){
				tempX=MPCFile[page][sprite].x;
				tempsprite=sprite;
			}
		}
	}
	return MPCFile[page][tempsprite].x;
}

void SetIconLimits(void){
	int iconnum;
	s16 iconxpos=0;
	for(iconnum=0;iconnum<21;iconnum++){
		Stamps[iconnum].x=iconxpos;
		Stamps[iconnum].x2=iconxpos+12;
		Stamps[iconnum].y=0;
		Stamps[iconnum].y2=13;
		iconxpos+=13;
	}
}
//top screen
void UpdatePageView(s16 page){
	PA_OutputText(1, 12, 0, "Page %d ",page+1);
	PA_EasyBgScrollXY(1,2,page*256,0); // and Y scroll
	DisplayViewPage(page);
}	
//bottom screen
void SwitchPage(u16 Pagenum){
	if(Pagenum!=0 && DynamicTempo[Pagenum]==0)DynamicTempo[Pagenum]=DynamicTempo[Pagenum-1];
	PA_EasyBgScrollXY(0,2,Pagenum*256,0); // and Y scroll
	DisplayPage(Pagenum);

	if(Pagenum>EndPage)EndPage=Pagenum;
	PA_SetSpriteX(0,PAGESLIDER,PAGESLIDPOS+(46*Pagenum/EndPage));
	UpdateCurrentSprite();
	SetTempo();
	//UpdatePageView();
}
	
void SetTempo(void){
	if(DynamicTempo[Page]<0.5)DynamicTempo[Page]=0.5;
	if(DynamicTempo[Page]>10.0)DynamicTempo[Page]=10.0;
	temposlider=TEMPOSLIDPOS+(36*DynamicTempo[Page]/10);
	PA_SetSpriteX(0,TEMPOSLIDER,(int)temposlider);
	if(Play==1 && OldTempo!=DynamicTempo[Page]){
		PA_StartSpriteAnim (0,NOTECURS,0,1,DynamicTempo[Page]*MARIOSPEED);
	}	
	OldTempo=DynamicTempo[Page];
}
//for holding L or R for faster page switching
s16 HoldTimer=0;

void TopScreenControls(void){
	if(Pad.Newpress.L){
		PageView=0;
		HoldTimer=0;
		if(previewpage>0)previewpage--;
		UpdatePageView(previewpage);
	}
	else if(Pad.Newpress.R){
		PageView=1;
		HoldTimer=0;
		if(previewpage<EndPage)previewpage++;
		UpdatePageView(previewpage);
	}
	if(Pad.Held.R){
		HoldTimer++;
		if(HoldTimer>=45){
			if(previewpage<EndPage)previewpage++;
			UpdatePageView(previewpage);
			PA_OutputText(1, 12, 0, "Page %d ",previewpage+1);
		}
	}
	else if(Pad.Held.L){
		HoldTimer++;
		if(HoldTimer>=45){
			if(previewpage>0)previewpage--;
			UpdatePageView(previewpage);
			PA_OutputText(1, 12, 0, "Page %d ",previewpage+1);
		}
	}
	if(Pad.Released.R || Pad.Released.L)HoldTimer=0;
}
bool skipsplash=0;
extern void loadFile(char * file);
void LoadArg(char * mpcfile){
	Original=0;
	MPCFileType=0;
	char File[512];
	strcpy(File, "fat:");
	strcat(File, mpcfile);
	loadFile(File);
}

bool GetRomPath(char* pathbuf, const char * path){
	bool test=0;
	s16 length=strlen(path);
	if(length>0){
		test=1;
		while(path[length]!='/')length--;
		strncpy(pathbuf,path, length+1);
	}
	return test;
}
void ReadIni(void){
	char IniFile[256];
	sprintf(IniFile,"%smpcds.ini", RomPath);
	readINI= fopen (IniFile, "rb"); //rb = read
	if(!readINI){
		InitText(0);
		PA_OutputText(0,1,12,"Ini file not found!");
		while(1);	
	}
	sprintf(location,"fat:%s", readIniFileString(IniFile,"SongDir"));
	fclose(readINI);
//	sprintf(location,"nitro:/");
}
bool CheckDir(char* path){
	DIR_ITER* dir = diropen(path);
	if(dir){
		dirclose(dir);
		return 1;
	}
	return 0;
}

/*void Splash(void){
	PA_SetBrightness(1,-31);
	PA_SetBrightness(0,-31);
	PA_Init8bitBg(0, 3); 	// Init a 16 bit Bg on screen 0
	PA_Init8bitBg(1, 3); 	// Init a 8 bit Bg on screen 1	
	PA_LoadGifXY(1,0,0,(void*)splashtop); // Gif File
	PA_LoadGifXY(0,0,0,(void*)splashbottom); // Gif File
	FadeIn(1);
	FadeIn(0);
}*/
// Function: mSpriten()
int main(int argc, char ** argv)
{
	PA_Init();    // Initializes PA_Lib
	//Splash();	
	if(!nitroFSInit()){
		InitText(0);
		PA_OutputText(0,0,12,"Failed to initialize filesystem.\n\n View readme.txt for further instructions");
		while (1);
	}
	GetRomPath(RomPath, argv[0]);
	if(argc > 1)
		skipsplash = 1;
		
	ReadIni();
	PA_SetAutoCheckLid (0);
	//init ASlib
	PA_VBLFunctionInit(AS_SoundVBL);
	AS_Init(AS_NO_DELAY| AS_MODE_16CH);
	AS_SetDefaultSettings(AS_PCM_8BIT, 44100,AS_NO_DELAY);
	//Set volume for every channel to max
	int chan=0;
	for(chan=0;chan<17;chan++)AS_SetSoundVolume(chan,127);
	
	if(!CheckDir(location)){
		InitText(0);
		PA_OutputText(0,0,12,"Failed To Find Songs folder");
		while(1);
	}
	InitFatSys(location,"mpc");
	DualFadeOut();
	//load graphics
	if(skipsplash==0)LoadTitle();
	else LoadMainScreens();
	
	LoadSpritePals();
	SetIconLimits();
	
	DynamicTempo[Page]=3.0;
	temposlider=(DynamicTempo[Page]/TEMPODIVISION)+TEMPOSLIDPOS;
	PageBar=PAGESLIDPOS;
	
	LoadGuiSprites();
	AssignStampSounds();

	PA_InitAllSpriteDraw();  
	PA_SetTextCol (0,0,0,0);
	PA_VBLFunctionInit(CheckSleep);
	if(argc > 1)
		 LoadArg(argv[1]);
		 
	if(skipsplash==1)PlayBack();
	
	while (1)
	{ 

		if(Pad.Newpress.Start)InsertPage();
		if(Pad.Newpress.Select)ClearPage();
		if(Pad.Newpress.Up || Pad.Newpress.X){
			if(NoteSign==0){
				NoteSign=1;
				PA_SetSpriteAnim(0,STAMPSIGN,0);
				if(Stylus.Held)HideSprite(0,STAMPSIGN,0);
			}
			else if(NoteSign==-1){
				NoteSign=0;
				PA_SetSpriteAnim(0,STAMPSIGN,0);
				if(Stylus.Held)HideSprite(0,STAMPSIGN,1);
			}
		}
		if(Pad.Newpress.Down || Pad.Newpress.B){
			if(NoteSign==0){
				NoteSign=-1;
				PA_SetSpriteAnim(0,STAMPSIGN,1);
				if(Stylus.Held)HideSprite(0,STAMPSIGN,0);
			}
			else if(NoteSign==1){
				NoteSign=0;
				PA_SetSpriteAnim(0,STAMPSIGN,0);
				if(Stylus.Held)HideSprite(0,STAMPSIGN,1);
			}
		}
		TopScreenControls();
		PA_OutputText(0,TEXTX,TEXTY,"Page:%d  ",Page+1);
		PA_OutputText(0,TEXTX-1,TEXTY+1,"Tempo:%f1  ",DynamicTempo[Page]);
		spriteplotting();
		TempoControl();
		PageSlider();
		PA_WaitForVBL();
	}
	
	return 0;
} // End of mSpriten()
int OldPage=0;
void PageSlider(void){
	//Arrow pictures
	if(Stylus.Newpress){
		//page down
		if(PA_StylusInZone(PAGESLIDPOS-8,153,PAGESLIDPOS-1,161)){
			Page--;
			if(Page<0)Page=0;
			if(OldPage!=Page){
				SwitchPage(Page);
				OldPage=Page;
			}
		}
		//page up
		else if(PA_StylusInZone(PAGESLIDPOS+50,153,PAGESLIDPOS+56,161)){
			Page++;
			if(Page>256)Page=256;
			if(OldPage!=Page){
				SwitchPage(Page);
				OldPage=Page;
			}
		}	
	}
	//page slider
	if(Stylus.Held && PA_StylusInZone(PAGESLIDPOS,153,PAGESLIDPOS+49,161)){
		Page=(((Stylus.X-PAGESLIDPOS)*EndPage)/46);
		if(Page>EndPage)Page=EndPage;
		if(Page<0)Page=0;
		if(Page>=256)Page=256;
		if(OldPage!=Page){
			SwitchPage(Page);
			OldPage=Page;
		}
	}
	
	//Buttons
	if((Pad.Newpress.Left ||Pad.Newpress.Y) && (!Page<=0) ){
		Page--;
		if(Page<0)Page=0;
		if(OldPage!=Page){
			SwitchPage(Page);
			OldPage=Page;
		}
	}
	if((Pad.Newpress.Right || Pad.Newpress.A)&&(Page!=256)){
		Page++;
		if(Page>256)Page=256;
		if(OldPage!=Page){
			SwitchPage(Page);
			OldPage=Page;
		}
	}
	
}


void TempoControl(void){
	if(Stylus.Newpress){
		//Tempos--------------------------------------------------------------------------------------
		//minus tempo
		if(PA_StylusInZone(85,176,93,187)){
			DynamicTempo[Page]-=0.1;
			SetTempo();
		}
		//tempo++
		if(PA_StylusInZone(140,176,148,187)){
			DynamicTempo[Page]+=0.1;
			SetTempo();
		}		
	}
	//Tempo Bar
	if(Stylus.Held && PA_StylusInZone(TEMPOSLIDPOS,178,TEMPOSLIDPOS+45,187)){
		DynamicTempo[Page]=((Stylus.X-TEMPOSLIDPOS)*10)/36;
		SetTempo();

	}
	else if(Stylus.Released&& PA_StylusInZone(TEMPOSLIDPOS,178,TEMPOSLIDPOS+45,187)){
		OldTempo=DynamicTempo[Page];
	}
}
void CheckControls(void){

	if(Stylus.Y<146 && Stylus.Y>30 && delete==0)UpdateStampPos(1);
	if(PA_SpriteTouched(STOP)){//stop button
		HideSprite(0,STOP,0);//stop
		HideSprite(0,PLAY,1);//play
	}
	else if(PA_SpriteTouched(PLAY)){//play button
		HideSprite(0,STOP,1);//stop
		HideSprite(0,PLAY,0);//play
		PlayBack();
	}
	else if(PA_SpriteTouched(LOOP)){//loop button
		HideSprite(0,LOOP,loop);
		loop++;
		if(loop>=2)loop=0;
	}
	//clear button
	if(PA_StylusInZone(178,170,211,183))ClearSong();
	if(PA_StylusInZone(9,175,23,189)){//rewind
		HideSprite(0,REWIND,0);
		PA_WaitFor(Stylus.Released);
		Page=0;
		SwitchPage(Page);	
		HideSprite(0,REWIND,1);
	}
	//loading 
	//saving
	else if(PA_StylusInZone(233,146,245,162))SavingMenu();

	else if(PA_StylusInZone(233,168,253,185)){
		FileBrowserMenu(1);
		AssignStampSounds();
	}
}
s8 StampTouched(void){
	s8 sprite=0;
	for(sprite=0;sprite<21;sprite++){
		if(Stylus.X>=Stamps[sprite].x && Stylus.X<=Stamps[sprite].x2)return sprite;
	}
	return 0;
}
void spriteplotting(void){
	
	if(Stylus.Newpress){
		u8 sprite=0;
		OldStamp=-1;
		if(Stylus.Y<142 && Stylus.Y>17){
			for(sprite=0;sprite<35;++sprite){
				if(PA_SpriteTouched(sprite+STARTSPRITE))delete=1;
				
				if(Stylus.DblClick&&PA_SpriteTouched(sprite+STARTSPRITE)){
					DeleteSprite(Page,sprite);
					PA_WaitForVBL();PA_WaitForVBL();
					delete=2;
				}
			}
		}
		CheckControls();
	}
	
	else if(Stylus.Held){
		if(Stylus.Y<17){
			//hide cursor sprites
			HideSprite(0,STAMPSRPITE,1);
			HideSprite(0,STAMPSIGN,1);	
			
			spritetouched=StampTouched();
			if(spritetouched!=OldStamp){
				//set the sprite double sized when selected
				PA_SetSpriteXY(0,PICKEDSPRITE,Stamps[spritetouched].x-8,Stamps[spritetouched].y-5);
				PA_SetSpriteAnim(0,PICKEDSPRITE,spritetouched);
				PA_SetRotsetNoAngle(0,0,168,168); 
				//do normal stuff for setting up the sprite
				spritepicked=spritetouched;
				PA_SetSpriteAnim(0,STAMPSRPITE,spritetouched);
				tempframe=spritetouched;
				PickSoundFile(spritetouched,257);
				AS_SetSoundRate(lastsfx,LOWF);
				delete=0;
				PA_SetSpriteAnim(0,ERASERBUT,delete);
			}	
			OldStamp=spritetouched;
		}
		//Actual placement of sprite - the stamp
		else if(delete==0 && Stylus.Y<138 && Stylus.Y>17){
			if(OldStamp==spritetouched){
				PA_SetSpriteXY(0,PICKEDSPRITE,-32,-32);
				PA_SetRotsetNoAngle(0,0,256,256); 
			}
			
			u8 tempspritey=tempy-7;
			u8 tempspritex=tempx-7;
			if(playsound==FALSE)UpdateStampPos(0);
			if(tempspritey!=tempy-7 || tempspritex!=tempx-7 )playsound=TRUE;
			if(playsound==TRUE){
				UpdateStampPos(1);
				playsound=FALSE;
			}
		}
	}
	
	if(Stylus.Released){
		if(delete==0 && CountSpriteColumn(tempx)<5&&Stylus.Y<138 && Stylus.Y>17){
			UpdateStampPos(0);
			spriteplaced=TRUE;
			CreateSprite(Page,CurrentSprite,tempframe,tempx,tempy,NoteSign);
			DisplayStamp(CurrentSprite,NoteSign,Page);
		}
		else if(CountSpriteColumn(tempx)>5 && Stylus.Y<138 && Stylus.Y>17)DeleteSprite(Page,CurrentSprite);
		HideSprite(0,STAMPSRPITE,1);
		HideSprite(0,STAMPSIGN,1);
		HideSprite(0,BARSPRITE,1);
		PA_SetRotsetNoAngle(0,0,256,256); 
		PA_SetSpriteXY(0,PICKEDSPRITE,Stamps[tempframe].x-32,Stamps[tempframe].y-32);
		spriteplaced=FALSE;
		UpdateCurrentSprite();
		//NoteSign=0;
		PA_UpdateStylus ();
		PA_WaitForVBL();PA_WaitForVBL();
		if(delete==1){
			delete=0;
			Stylus.DblClick=0;
			PA_UpdateStylus ();
		}
		else if(delete==2){
			delete=0;
			Stylus.DblClick=0;
			Stylus.Downtime=0;
			Stylus.Uptime=0;
			PA_WaitForVBL();PA_WaitForVBL();
		}
	}
}
void StopMusic(void){
	s8 chan;
	for(chan=0;chan<16;chan++)AS_SoundStop(chan);
	//PA_StopSound(chan);
}
s32 marioy,mariovy;
bool jump=0;
void PlayBack(void){
	Play=1;
	BarX=0.0;
	u8 spritenumbers;
	HideSprite(0,3,0);

	HideSprite(0,STAMPSRPITE,1);
	HideSprite(0,STAMPSIGN,1);
	EndPage=FindLastPage();
	s16 LastX=FindLastNotePos(EndPage);
	PA_StartSpriteAnim (0,NOTECURS,0,1,DynamicTempo[Page]*MARIOSPEED);

	marioy=0;
	mariovy=0;
	jump=0;
	StopMusic();
	while(Play==1){
		//TempoControl();
		for(spritenumbers=0;spritenumbers<35;++spritenumbers){
			if(MPCFile[Page][spritenumbers].used!=0 && (BarX+8>=MPCFile[Page][spritenumbers].x-(DynamicTempo[Page]/2)-(6*DynamicTempo[Page]) && BarX+8<=MPCFile[Page][spritenumbers].x+(DynamicTempo[Page]/2)-(6*DynamicTempo[Page]))){
					jump=0;
					marioy=0;
					mariovy=0;
					jump=1;
					mariovy=-880*(DynamicTempo[Page]);
					PA_SpriteAnimPause(0, NOTECURS, 1);
					PA_SetSpriteAnim(0, NOTECURS, 2); 
			}
			if(MPCFile[Page][spritenumbers].used!=0 && BarX+8>=MPCFile[Page][spritenumbers].x-(DynamicTempo[Page]/2) && BarX+8<=MPCFile[Page][spritenumbers].x+(DynamicTempo[Page]/2)){
				PickSoundFile(spritenumbers,Page);
				AS_SetSoundRate(lastsfx,NumToNote(MPCFile[Page][spritenumbers].Note));
			}
		}
		if(jump==1){
			if(DynamicTempo[Page]<=4.0)mariovy += 80*(DynamicTempo[Page]*2);
			else mariovy += 80*(DynamicTempo[Page]*4);
			marioy += mariovy;
			if(marioy>=0){
				jump=0;
				mariovy=0;
				marioy=0;
				PA_SpriteAnimPause(0, NOTECURS, 0);
			}
		}
		
		BarX+=DynamicTempo[Page];
		PA_SetSpriteXY(0,NOTECURS,BarX,marioy>>8);
		if(Page<EndPage&&BarX+8>=225){
			Page++;
			OldPage=Page;
			BarX=-8;
			SwitchPage(Page);
			PA_StartSpriteAnim (0,NOTECURS,0,1,DynamicTempo[Page]*MARIOSPEED);
		}
		else if(Page>=EndPage){
			if(loop==1 && BarX+8>=LastX+38){
				BarX=-8;
				Page=0;
				SwitchPage(Page);
				PA_StartSpriteAnim (0,NOTECURS,0,1,DynamicTempo[Page]*MARIOSPEED);
			}
			else if(loop==0&&BarX+8>=225){
				HideSprite(0,STOP,0);//stop
				HideSprite(0,PLAY,1);//play
				HideSprite(0,NOTECURS,1);
				Play=0;	
			}
		}

				//CheckLoadNewSong();
		if(Stylus.Newpress){
			if(PA_SpriteTouched(STOP)){//stop button
				HideSprite(0,STOP,0);//stop
				HideSprite(0,PLAY,1);//play
				HideSprite(0,NOTECURS,1);
				Play=0;
				StopMusic();
			}
			else if(PA_SpriteTouched(LOOP)){//loop button
				HideSprite(0,LOOP,loop);
				loop++;
				if(loop>=2)loop=0;
			}
		}
	
		PA_OutputText(0,TEXTX,TEXTY,"Page:%d  ",Page+1);
		PA_OutputText(0,TEXTX-1,TEXTY+1,"Tempo:%f1  ",DynamicTempo[Page]);
		PA_WaitForVBL();
	}
}

void UpdateStampPos(bool sound){
	HideSprite(0,STAMPSRPITE,0);
	if(spriteplaced==FALSE){
		//x position snap
		if(Stylus.X>=23 && Stylus.X<=48){
			PA_SetSpriteXY(0,STAMPSRPITE,33-8,tempy);
			tempx=33-8;
		}
		else if(Stylus.X>=49 && Stylus.X<=80){
			PA_SetSpriteXY(0,STAMPSRPITE,65-8,tempy);
			tempx=65-8;
		}	
		else if(Stylus.X>=81 && Stylus.X<=111){
			PA_SetSpriteXY(0,STAMPSRPITE,97-8,tempy);
			tempx=97-8;
		}		
		else if(Stylus.X>=112 && Stylus.X<=144){
			PA_SetSpriteXY(0,STAMPSRPITE,129-8,tempy);
			tempx=129-8;
		}				
		else if(Stylus.X>=145 && Stylus.X<=176){
			PA_SetSpriteXY(0,STAMPSRPITE,161-8,tempy);
			tempx=161-8;
		}	
		else if(Stylus.X>=177 && Stylus.X<=209){
			PA_SetSpriteXY(0,STAMPSRPITE,193-8,tempy);
			tempx=193-8;
		}	
		else if(Stylus.X>=210 && Stylus.X<=256){
			PA_SetSpriteXY(0,STAMPSRPITE,225-8,tempy);
			tempx=225-8;
		}				
		//y position snap tool
		if(Stylus.Y>=18 && Stylus.Y<=24){
			HideSprite(0,BARSPRITE,0);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,22-SPRITEYOFFSET);
			PA_SetSpriteXY(0,BARSPRITE,tempx-4,(22-SPRITEYOFFSET)+14);
			tempy=22-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHB,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHBS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHAS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=25 && Stylus.Y<=31){
			HideSprite(0,BARSPRITE,0);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,29-SPRITEYOFFSET);
			PA_SetSpriteXY(0,BARSPRITE,tempx-4,(22-SPRITEYOFFSET)+14);
			tempy=29-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHA,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHAS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHGS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=32 && Stylus.Y<=39){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,37-SPRITEYOFFSET);
			tempy=37-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHG,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHGS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHFS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=40 && Stylus.Y<=47){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,45-SPRITEYOFFSET);
			tempy=45-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHF,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHFS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHE,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=48 && Stylus.Y<=55){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,53-SPRITEYOFFSET);
			tempy=53-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHE,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHF,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHDS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=56 && Stylus.Y<=63){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,61-SPRITEYOFFSET);
			tempy=61-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHD,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG2,HIGHDS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDCS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=64 && Stylus.Y<=71){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,69-SPRITEYOFFSET);
			tempy=69-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDC,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDCS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDB,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=73 && Stylus.Y<=79){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,77-SPRITEYOFFSET);
			tempy=77-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDB,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDC,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDAS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=80 && Stylus.Y<=87){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,85-SPRITEYOFFSET);
			tempy=85-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDA,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDAS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDGS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=88 && Stylus.Y<=95){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,93-SPRITEYOFFSET);
			tempy=93-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWG,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALEG,MIDGS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWFS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=96 && Stylus.Y<=103){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,101-SPRITEYOFFSET);
			tempy=101-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWF,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWFS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWE,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=104 && Stylus.Y<=111){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,109-SPRITEYOFFSET);
			tempy=109-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWE,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWF,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWDS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=112 && Stylus.Y<=119){
			HideSprite(0,BARSPRITE,1);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,117-SPRITEYOFFSET);
			tempy=117-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWD,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWDS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWCS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=120 && Stylus.Y<=128){
			HideSprite(0,BARSPRITE,0);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,124-SPRITEYOFFSET);
			PA_SetSpriteXY(0,BARSPRITE,tempx-4,124-SPRITEYOFFSET+8);
			tempy=124-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWC,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWCS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWB,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=129 && Stylus.Y<=135){
			HideSprite(0,BARSPRITE,0);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,132-SPRITEYOFFSET);
			PA_SetSpriteXY(0,BARSPRITE,tempx-4,124-SPRITEYOFFSET+8);
			tempy=132-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWB,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWB,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWAS,spritepicked,sound);break;
			}
		}
		else if(Stylus.Y>=136 && Stylus.Y<=148){
			HideSprite(0,BARSPRITE,0);
			PA_SetSpriteXY(0,STAMPSRPITE,tempx,139-SPRITEYOFFSET);
			PA_SetSpriteXY(0,BARSPRITE,tempx-4,139-SPRITEYOFFSET+8);
			tempy=139-SPRITEYOFFSET;
			switch(NoteSign){
				default:SetNoteProperties(Page,CurrentSprite,SCALED,LOWLOWG,spritepicked,sound);break;//default
				case 1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWAS,spritepicked,sound);break;//Sharp
				case -1:SetNoteProperties(Page,CurrentSprite,SCALED,LOWLOWFS,spritepicked,sound);break;//flat
			}
		}
		PA_SetSpriteXY(0,STAMPSIGN,tempx-SPRITEYOFFSET,tempy);	
		if(NoteSign!=0){
			switch(NoteSign){
				case 1://sharp
					PA_SetSpriteAnim(0,STAMPSIGN,0);
					HideSprite(0,STAMPSIGN,0);
				break;
				case -1://flat
					PA_SetSpriteAnim(0,STAMPSIGN,1);
					HideSprite(0,STAMPSIGN,0);	
				break;
			}
		}
	}
}


