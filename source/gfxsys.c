#include <PA9.h>       // Include for PA_Lib
#include "all_gfx.h"
#include "gfxsys.h"
#include "variables.h"
#include "BAGKeyboard.h"


//====================================================================================================================================================
//Setting Up the Gui
//====================================================================================================================================================
void DisplaySongInfo(void){
	PA_ClearTextBg(1);
	if(Original==0){
		PA_OutputText(1,6,14+5,"%c1Please save song \nto update data");
	}
	else if(Original==1){
		PA_OutputText(1,4,14+5,"%c1Title : %s ",LastFile);
		PA_OutputText(1,4,15+5,"%c1Author: %s ",Author);
		PA_OutputText(1,4,16+5,"%c1Pages : %d ",EndPage+1);
		//PA_OutputText(1,4,17+5,"%c1Tempo : %f1 ",Tempo);
	}
}

void FadeIn(s8 screen){
	s8 brightness;
	if(screen<2){
		for(brightness=-31;brightness<0;brightness++){
			PA_SetBrightness (screen,brightness);
			PA_WaitForVBL();
		}
	}
	else if(screen==2){
		for(brightness=-31;brightness<0;brightness++){
			PA_SetBrightness (0,brightness);
			PA_SetBrightness (1,brightness);
			PA_WaitForVBL();
		}	
	}
}
void FadeOut(s8 screen){
	s8 brightness;
	if(screen<2){
		for(brightness=0;brightness>-31;brightness--){
			PA_SetBrightness (0,brightness);
			PA_WaitForVBL();
		}
	}
	else if(screen==2){
		for(brightness=0;brightness>-31;brightness--){
			PA_SetBrightness (0,brightness);
			PA_SetBrightness (1,brightness);
			PA_WaitForVBL();
		}
	}
}
void DualFadeOut(void){
	s8 brightness;
	for(brightness=0;brightness>-31;brightness--){
		PA_SetBrightness (0,brightness);
		PA_SetBrightness (1,brightness);
		PA_WaitForVBL();
	}

}
	
void InitText(bool screen){
	PA_LoadText(screen,0,&fbfont); //font name
}
void LoadMainScreens(void){
	PA_SetBrightness (0,-31);
	PA_SetBrightness (1,-31);
	LoadTopScreen();
	PA_LoadBackground(0,3,&background);//map to plot too
	PA_LoadBackground(0,2,&measures);//map to plot too
	PA_LoadText(1,0,&fbfont); //font name
	//PA_SetTextCol (1,0,0,0);
	Original=0;
	DisplaySongInfo();
	PA_LoadText(0,0,&fbfont); //font name
	FadeIn(2);
}	
void LoadTitle(void){//loads the splash, titles and fades
	PA_ResetBgSys();
	PA_SetBrightness (0,-31);
	PA_SetBrightness (1,-31);
	PA_LoadBackground(1,3,&title);//map to plot too
	//PA_LoadBackground(0,3,&forumsplash);//map to plot too

	//FadeIn(2);
	//PA_WaitFor(Pad.Newpress.Anykey || Stylus.Newpress);
	//FadeOut(1);
	//credits
	PA_LoadBackground(0,3,&credits);//map to plot too
	FadeIn(2);
	PA_WaitFor(Pad.Newpress.Anykey || Stylus.Newpress);
	FadeOut(2);
	//main screens
	LoadMainScreens();
}

void LoadFileBrowser(void){
	PA_ResetBgSysScreen (1);
	PA_ResetSpriteSysScreen(1);
	PA_LoadText(1,1,&fbfont); //font name
	PA_LoadBackground(1,3,&topscreenfb);//map to plot too
	PA_LoadBackground(1,2,&bar);//map to plot too
	PA_LoadBackground(1,0,&header);//map to plot too
	PA_SwitchScreens();
}
void ReloadFB(void){
	PA_ResetBgSysScreen (1);
	PA_ResetSpriteSysScreen(1);
	PA_LoadText(1,1,&fbfont); //font name
	PA_LoadBackground(1,3,&topscreenfb);//map to plot too
	PA_LoadBackground(1,2,&bar);//map to plot too
	PA_LoadBackground(1,0,&header);//map to plot too
}
void LoadKeyBoardScreen(void){
	PA_ResetBgSysScreen (1);
	PA_ResetSpriteSysScreen(1);
	PA_SwitchScreens();
	PA_LoadBackground(1,3,&topscreensd);//map to plot too
	PA_LoadBackground(1,1,&bar);//map to plot too
	PA_BGScrollXY(1,1,0,-9<<3);
	PA_LoadText(1,0,&fbfont); //font name
	if(Original==1)PA_OutputSimpleText(1, 3, 9, "Save as:"); 
	else PA_OutputSimpleText(1, 3, 9, "Author:"); 
	PA_Init16cBg  (1,2);
	SetKeyBoardBgMode(KB_BG_16c);
	SetKeyBoardScreen(1);
	SetKeyBoardFont(0);
	SetKeyBoardColors(PA_RGB(31,0,0),PA_RGB(31,31,31), PA_RGB(0,31,0),PA_RGB(0,0,31));
	BAG_InitKeyBoard(32,96,16,8);
	//PA_SetKeyboardScreen(1);
	//PA_LoadKeyboard(2,&keyboard1); // Load the keyboard on background 2...
	//PA_KeyboardIn(10, 95); // This scrolls the keyboard from the bottom, until it's at the right position
	
}

void LoadTopScreen(void){
	PA_BGScrollY(1,2,0);
	PA_ResetBgSysScreen (1);
	PA_LoadBackground(1,3,&topscreen);//map to plot too
	PA_LoadBackground(1,2,&measures);//map to plot too
	PA_LoadText(1,0,&fbfont); //font name
	//PA_SetTextCol (1,0,0,0);
	PA_LoadSpritePal(1,0,(void*)mapsprites_Pal);//pallete for the sprites
	PA_LoadSpritePal(1,4,(void*)signs_Pal);
	PA_LoadSpritePal(1,7,(void*)notebar_Pal);
	DisplaySongInfo();
	UpdatePageView(0);
	
}
//loads sprite pallets
void LoadSpritePals(void){
	PA_LoadSpritePal(0,0,(void*)mapsprites_Pal);//pallete for the sprites
	PA_LoadSpritePal(0,1,(void*)buttons_Pal);
	PA_LoadSpritePal(0,2,(void*)sliders_Pal);
	PA_LoadSpritePal(0,3,(void*)picked_Pal);
	PA_LoadSpritePal(0,4,(void*)signs_Pal);
	PA_LoadSpritePal(0,6,(void*)mario_Pal);
	PA_LoadSpritePal(0,7,(void*)notebar_Pal);
}
//loads the sprites for the gui
void LoadGuiSprites(void){
	//stop
	PA_CreateSprite(0,STOP,(void*)buttons_Sprite,OBJ_SIZE_16X16,1,1,11,151);
	PA_SetSpriteAnim(0,STOP,0);
	if(Play==0)HideSprite(0,STOP,0);
	else HideSprite(0,STOP,1);
	//play
	PA_CreateSprite(0,PLAY,(void*)buttons_Sprite,OBJ_SIZE_16X16,1,1,52,151);
	PA_SetSpriteAnim(0,PLAY,1);
	if(Play==0)HideSprite(0,PLAY,1);
	//loop
	PA_CreateSprite(0,LOOP,(void*)buttons_Sprite,OBJ_SIZE_16X16,1,1,49,177);
	PA_SetSpriteAnim(0,LOOP,2);
	if(loop==0)HideSprite(0,LOOP,1);
	else HideSprite(0,LOOP,0);
	//play cursor
	PA_CreateSprite(0,NOTECURS,(void*)mario_Sprite,OBJ_SIZE_16X32,1,6,77,0);
	PA_SetSpriteAnim(0,NOTECURS,0);
	if(Play==0)HideSprite(0,NOTECURS,1);
	else HideSprite(0,NOTECURS,0);
	//rewind
	PA_CreateSprite(0,REWIND,(void*)buttons_Sprite,OBJ_SIZE_16X16,1,1,9,176);
	PA_SetSpriteAnim(0, REWIND,4);
	HideSprite(0,REWIND,1);
	//create the big sprite thats picked
	PA_CreateSprite(0,PICKEDSPRITE,(void*)picked_Sprite,OBJ_SIZE_16X16,1,3,-32,-32);
	PA_SetSpriteAnim(0, PICKEDSPRITE,0);
	PA_SetSpriteDblsize(0, PICKEDSPRITE, 1); 
	PA_SetSpriteRotEnable(0, PICKEDSPRITE, 0); // Same rotset as the other sprite... it'll be zoomed the same way
	PA_SetRotsetNoAngle(0,0,256,256); 
	//slider
	PA_CreateSprite(0,PAGESLIDER,(void*)sliders_Sprite,OBJ_SIZE_8X8,1,2,PageBar,154);//108
	PA_SetSpriteAnim(0, PAGESLIDER,0);
	if(EndPage==0)EndPage++;
	PA_SetSpriteX(0,PAGESLIDER,PAGESLIDPOS+(46*Page/EndPage));
	//tempo
	PA_CreateSprite(0,TEMPOSLIDER,(void*)sliders_Sprite,OBJ_SIZE_8X8,1,2,temposlider,178);//108
	PA_SetSpriteAnim(0, TEMPOSLIDER,1);
	
	PA_CreateSprite(0,STAMPSRPITE,(void*)mapsprites_Sprite,OBJ_SIZE_16X16,1,0,Stylus.X-8,Stylus.Y-8);
	PA_SetSpriteAnim(0,STAMPSRPITE,spritepicked);
	HideSprite(0,STAMPSRPITE,1);
	
	PA_CreateSprite(0,STAMPSIGN,(void*)signs_Sprite,OBJ_SIZE_8X16,1,4,Stylus.X-16,Stylus.Y-8);
	PA_SetSpriteAnim(0,STAMPSIGN,0);
	HideSprite(0,STAMPSIGN,1);	

	PA_CreateSprite(0,BARSPRITE,(void*)notebar_Sprite,OBJ_SIZE_32X8,1,7,Stylus.X-16,Stylus.Y-8);
	PA_SetSpriteAnim(0,BARSPRITE,0);
	HideSprite(0,BARSPRITE,1);	
	PA_WaitForVBL();
}

void HideSprite(bool screen,u8 sprite,bool hide){
	#define ATTR0_DISABLED   (2<<8) 
	switch(hide){
		case 0://show sprite
			PA_obj[screen][sprite].atr0 &= ~ATTR0_DISABLED;
		break;
		case 1://hide sprite
			PA_obj[screen][sprite].atr0 |= ATTR0_DISABLED;
		break;
	}
}
//====================================================================================================================================================
//Sprite Page System
//====================================================================================================================================================
void CreateLedgerBar(s32 page, u8 sprite){
	//the bar sprites
	switch(MPCFile[Page][sprite].y){
		default:break;
		case 14:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,28);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 21:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,28);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 22:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,28);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 116:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 117:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 124:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 125:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
		case 131:
			gfx[sprite+STARTSPRITE+72]=PA_CreateGfx (0,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+72,gfx[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,139);
			PA_SetSpritePrio(0,sprite+STARTSPRITE+72,3); 
		break;
	}
}
void DisplayStamp(int sprite,s8 sign, u16 page){//displays a single stamp 
	gfx[sprite+STARTSPRITE]=PA_CreateGfx (0,(void *)mapsprites_Sprite,OBJ_SIZE_16X16,1);
	PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE,gfx[sprite+STARTSPRITE],OBJ_SIZE_16X16,1, 0,MPCFile[Page][sprite].x,MPCFile[Page][sprite].y); // The rest is like normal sprites
	PA_SetSpriteAnimEx (0,sprite+STARTSPRITE,16,16, 1, MPCFile[Page][sprite].frame);	
	PA_SetSpritePrio(0,sprite+STARTSPRITE,2); 
	
	if(sign!=0){
		gfx[sprite+STARTSPRITE+36]=PA_CreateGfx (0,(void *)signs_Sprite,OBJ_SIZE_8X16,1);
		PA_CreateSpriteFromGfx(0,sprite+STARTSPRITE+36,gfx[sprite+STARTSPRITE+36],OBJ_SIZE_8X16,1, 4,MPCFile[Page][sprite].x-8,MPCFile[Page][sprite].y); // The rest is like normal sprites
		if(sign==1)PA_SetSpriteAnimEx (0,sprite+STARTSPRITE+36,8,16, 1,0);//sharp
		else if(sign==-1)PA_SetSpriteAnimEx (0,sprite+STARTSPRITE+36,8,16, 1,1);//flat
		PA_SetSpritePrio(0,sprite+STARTSPRITE+36,2); 
	}
	CreateLedgerBar(Page,sprite);
}

void UpdateCurrentSprite(void){
	CurrentSprite=(FindUnusedSprite(Page));	
}

s8 FindUnusedSprite(u16 page){//finds and unused sprite in hardware for note
	u16 i;
	for(i=0;i<35;++i){
		if(MPCFile[page][i].used==0)return i;
	}
	return 0;
}
s8 CountSpriteColumn (u8 xposition){//counts how many notes there are percolum, helps to limit it
	u16 sprite;
	s8 count=0;
	for(sprite=0;sprite<35;sprite++){
		if(MPCFile[Page][sprite].x==xposition)count++;
	}
	return count;
}

void CreateSprite(int page,int number,int frame,int x,int y,s8 sign){//adds a sprite into the page struct to be created later for notes
	MPCFile[page][number].x=x;
	MPCFile[page][number].y=y;
	MPCFile[page][number].frame=frame;
	MPCFile[page][number].used=1;
	MPCFile[page][number].Sign=sign;
}

void DisplayPage(int pagenumber){//displays a page worth of notes and symbols
	int spritenum;
	ClearSprites();
	for(spritenum=0;spritenum<=35;++spritenum){
		if(MPCFile[pagenumber][spritenum].used==1){
			DisplayStamp(spritenum,MPCFile[Page][spritenum].Sign,pagenumber);
		}
	}
}

//stamp creation to be shown on top screen
void CreateViewLedgers(s32 Page, u8 sprite){
	switch(MPCFile[Page][sprite].y){
		default:break;
		case 14:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,28);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 21:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,28);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 22:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,28);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 116:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 117:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 124:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 125:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,124);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
		case 131:
			gfx2[sprite+STARTSPRITE+72]=PA_CreateGfx (1,(void *)notebar_Sprite,OBJ_SIZE_32X8,1);
			PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+72,gfx2[sprite+STARTSPRITE+72],OBJ_SIZE_32X8,1, 7,MPCFile[Page][sprite].x-4,139);
			PA_SetSpritePrio(1,sprite+STARTSPRITE+72,3); 
		break;
	}
}
void CreateViewStamp(int sprite,s8 sign, u16 page){//displays a single stamp 
	gfx2[sprite+STARTSPRITE]=PA_CreateGfx (1,(void *)mapsprites_Sprite,OBJ_SIZE_16X16,1);
	PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE,gfx2[sprite+STARTSPRITE],OBJ_SIZE_16X16,1, 0,MPCFile[page][sprite].x,MPCFile[page][sprite].y); // The rest is like normal sprites
	PA_SetSpriteAnimEx (1,sprite+STARTSPRITE,16,16, 1, MPCFile[page][sprite].frame);	
	PA_SetSpritePrio(1,sprite+STARTSPRITE,2); 
	
	if(sign!=0){
		gfx2[sprite+STARTSPRITE+36]=PA_CreateGfx (1,(void *)signs_Sprite,OBJ_SIZE_8X16,1);
		PA_CreateSpriteFromGfx(1,sprite+STARTSPRITE+36,gfx2[sprite+STARTSPRITE+36],OBJ_SIZE_8X16,1, 4,MPCFile[page][sprite].x-8,MPCFile[page][sprite].y); // The rest is like normal sprites
		if(sign==1)PA_SetSpriteAnimEx (1,sprite+STARTSPRITE+36,8,16, 1,0);//sharp
		else if(sign==-1)PA_SetSpriteAnimEx (1,sprite+STARTSPRITE+36,8,16, 1,1);//flat
		PA_SetSpritePrio(1,sprite+STARTSPRITE+36,2); 
	}
	
}
//Top screen
void DisplayViewPage(int pagenumber){//displays a page worth of notes and symbols
	s8 spritenum;
	PA_ResetSpriteSysScreen(1);
	PA_WaitForVBL();
	for(spritenum=0;spritenum<=35;++spritenum){
		if(MPCFile[pagenumber][spritenum].used==1){
			CreateViewStamp(spritenum,MPCFile[pagenumber][spritenum].Sign,pagenumber);
			CreateViewLedgers(pagenumber,spritenum);
		}
	}
}


void DeleteSprite(int page,int sprite){//delete a note
	PA_SetSpriteXY(0,sprite+STARTSPRITE,-32,-32);
	if(MPCFile[page][sprite].Sign!=0)PA_SetSpriteXY(0,sprite+STARTSPRITE+36,-32,-32);
	PA_SetSpriteXY(0,sprite+STARTSPRITE+72,-32,-32);
	MPCFile[page][sprite].x=0;
	MPCFile[page][sprite].y=0;
	MPCFile[page][sprite].Note=0;
	MPCFile[page][sprite].Pitch=0;
	MPCFile[page][sprite].SoundFile=0;
	MPCFile[page][sprite].used=0;
	MPCFile[page][sprite].Sign=0;
}

void ClearSprites(void){//clears the screen of sprites and relodes the gui
	PA_ResetSpriteSysScreen(0);
	//PA_WaitForVBL();
	LoadGuiSprites();
}
void ShiftPagesDown(int page){
	int pages;
	s8 note;
	//copy data
	for(pages=page;pages<257;++pages){
		for(note=0;note<35;++note){
			TempFile[pages][note].frame=MPCFile[pages][note].frame;
			TempFile[pages][note].x=MPCFile[pages][note].x;
			TempFile[pages][note].y=MPCFile[pages][note].y;
			TempFile[pages][note].Note=MPCFile[pages][note].Note;
			TempFile[pages][note].Pitch=MPCFile[pages][note].Pitch;
			TempFile[pages][note].SoundFile=MPCFile[pages][note].SoundFile;
			TempFile[pages][note].Sign=MPCFile[pages][note].Sign;
			TempFile[pages][note].used=MPCFile[pages][note].used;
		}
	}
	//paste data
	for(pages=page;pages<257;++pages){
		for(note=0;note<35;++note){
			MPCFile[pages][note].frame=TempFile[pages+1][note].frame;
			MPCFile[pages][note].x=TempFile[pages+1][note].x;
			MPCFile[pages][note].y=TempFile[pages+1][note].y;
			MPCFile[pages][note].Note=TempFile[pages+1][note].Note;
			MPCFile[pages][note].Pitch=TempFile[pages+1][note].Pitch;
			MPCFile[pages][note].SoundFile=TempFile[pages+1][note].SoundFile;
			MPCFile[pages][note].Sign=TempFile[pages+1][note].Sign;
			MPCFile[pages][note].used=TempFile[pages+1][note].used;
		}
	}
	SwitchPage(Page);
	UpdatePageView(0);
}
void InsertBlankPage(int page){
	int pages;
	s8 note;
	//copy data
	for(pages=page;pages<257;++pages){
		for(note=0;note<35;++note){
			TempFile[pages][note].frame=MPCFile[pages][note].frame;
			TempFile[pages][note].x=MPCFile[pages][note].x;
			TempFile[pages][note].y=MPCFile[pages][note].y;
			TempFile[pages][note].Note=MPCFile[pages][note].Note;
			TempFile[pages][note].Pitch=MPCFile[pages][note].Pitch;
			TempFile[pages][note].SoundFile=MPCFile[pages][note].SoundFile;
			TempFile[pages][note].Sign=MPCFile[pages][note].Sign;
			TempFile[pages][note].used=MPCFile[pages][note].used;
		}
	}	
	//paste data one page ahead
	for(pages=page+1;pages<256;++pages){
		for(note=0;note<35;++note){
			MPCFile[pages][note].frame=TempFile[pages-1][note].frame;
			MPCFile[pages][note].x=TempFile[pages-1][note].x;
			MPCFile[pages][note].y=TempFile[pages-1][note].y;
			MPCFile[pages][note].Note=TempFile[pages-1][note].Note;
			MPCFile[pages][note].Pitch=TempFile[pages-1][note].Pitch;
			MPCFile[pages][note].SoundFile=TempFile[pages-1][note].SoundFile;
			MPCFile[pages][note].Sign=TempFile[pages-1][note].Sign;
			MPCFile[pages][note].used=TempFile[pages-1][note].used;
		}
	}
	//clear the current page
	for(note=0;note<35;++note){
		MPCFile[page][note].frame=0;
		MPCFile[page][note].x=0;
		MPCFile[page][note].y=0;
		MPCFile[page][note].Note=0;
		MPCFile[page][note].Pitch=0;
		MPCFile[page][note].SoundFile=0;
		MPCFile[page][note].Sign=0;
		MPCFile[page][note].used=0;
	}
	//
	AssignStampSounds();
	EndPage++;
	SwitchPage(page);
	UpdatePageView(page);
}

void ClearPage(void){
	bool clearmenu=1;
	PA_LoadBackground(0,1,&deletepage);
	PA_LoadSpritePal(0,5,(void*)invbutton_Pal);
	//yes button
	PA_CreateSprite(0,0,(void*)invbutton_Sprite,OBJ_SIZE_64X32,1,5,76,99);
	PA_SetSpriteAnim(0,0,0);
	HideSprite(0,0,1);

	//nos button
	PA_CreateSprite(0,7,(void*)invbutton_Sprite,OBJ_SIZE_64X32,1,5,143,99);
	PA_SetSpriteAnim(0, 7,1);
	HideSprite(0,7,1);		
	while(clearmenu==1){
		if(Stylus.Newpress){
			if(PA_StylusInZone(76,99,114,118)){//yes
				//clear the menu
				HideSprite(0,0,0);	
				PA_WaitForVBL();
				PA_WaitFor(Stylus.Released);
				ShiftPagesDown(Page);
				PA_DeleteBg(0,1);
				PA_DeleteBg(0,2);
				PA_LoadBackground(0,2,&measures);//map to plot too
				PA_EasyBgScrollXY(0,2,Page*256,0); // and Y scroll
				PA_SetSpriteX(0,0,-64); 
				PA_SetSpriteX(0,7,-64); 
				UpdateCurrentSprite();
				LoadSpritePals();
				clearmenu=0;
			}
			else if(PA_StylusInZone(143,99,179,118)){//no
				HideSprite(0,7,0);
				PA_WaitForVBL();				
				PA_WaitFor(Stylus.Released);
				PA_DeleteBg(0,1);
				PA_DeleteBg(0,2);
				PA_LoadBackground(0,2,&measures);//map to plot too
				PA_EasyBgScrollXY(0,2,Page*256,0); // and Y scroll
				PA_SetSpriteX(0,0,-64); 
				PA_SetSpriteX(0,7,-64); 
				UpdateCurrentSprite();
				LoadSpritePals();
				clearmenu=0;
			}
		}
		PA_WaitForVBL();
	}
}
void InsertPage(void){
	bool clearmenu=1;
	PA_LoadBackground(0,1,&insertpage);
	PA_LoadSpritePal(0,5,(void*)invbutton_Pal);
	//yes button
	PA_CreateSprite(0,0,(void*)invbutton_Sprite,OBJ_SIZE_64X32,1,5,76,99);
	PA_SetSpriteAnim(0,0,0);
	HideSprite(0,0,1);

	//nos button
	PA_CreateSprite(0,7,(void*)invbutton_Sprite,OBJ_SIZE_64X32,1,5,143,99);
	PA_SetSpriteAnim(0, 7,1);
	HideSprite(0,7,1);		
	while(clearmenu==1){
		if(Stylus.Newpress){
			if(PA_StylusInZone(76,99,114,118)){//yes
				//clear the menu
				HideSprite(0,0,0);	
				PA_WaitForVBL();
				PA_WaitFor(Stylus.Released);
				InsertBlankPage(Page);
				PA_DeleteBg(0,1);
				PA_DeleteBg(0,2);
				PA_LoadBackground(0,2,&measures);//map to plot too
				PA_EasyBgScrollXY(0,2,Page*256,0); // and Y scroll
				PA_SetSpriteX(0,0,-64); 
				PA_SetSpriteX(0,7,-64); 
				UpdateCurrentSprite();
				LoadSpritePals();
				clearmenu=0;
			}
			else if(PA_StylusInZone(143,99,179,118)){//no
				HideSprite(0,7,0);	
				PA_WaitForVBL();
				PA_WaitFor(Stylus.Released);
				PA_DeleteBg(0,1);
				PA_DeleteBg(0,2);
				PA_LoadBackground(0,2,&measures);//map to plot too
				PA_EasyBgScrollXY(0,2,Page*256,0); // and Y scroll
				PA_SetSpriteX(0,0,-64); 
				PA_SetSpriteX(0,7,-64); 
				UpdateCurrentSprite();
				LoadSpritePals();
				clearmenu=0;
			}
		}
		PA_WaitForVBL();
	}
}

void ClearSong(void){//clears the entire song and all the pages
	bool clearmenu=1;
	PA_LoadBackground(0,1,&clearscreen);

	PA_LoadSpritePal(0,5,(void*)invbutton_Pal);
	
	//yes button
	PA_CreateSprite(0,0,(void*)invbutton_Sprite,OBJ_SIZE_64X32,1,5,76,99);
	PA_SetSpriteAnim(0,0,0);
	HideSprite(0,0,1);

	//nos button
	PA_CreateSprite(0,7,(void*)invbutton_Sprite,OBJ_SIZE_64X32,1,5,143,99);
	PA_SetSpriteAnim(0, 7,1);
	HideSprite(0,7,1);	
	while(clearmenu==1){
		
		if(Stylus.Newpress){
			if(PA_StylusInZone(76,99,114,118)){
				HideSprite(0,0,0);	
				PA_WaitForVBL();
				PA_WaitFor(Stylus.Released);
				PA_DeleteBg(0,1);
				PA_SetSpriteX(0,0,-64); 
				PA_SetSpriteX(0,7,-64); 
				u16 sprite,page;
				ClearSprites();
				for(page=0;page<256;++page){
					for(sprite=0;sprite<35;++sprite){
						MPCFile[page][sprite].x=0;
						MPCFile[page][sprite].y=0;
						MPCFile[page][sprite].Note=0;
						MPCFile[page][sprite].Pitch=0;
						MPCFile[page][sprite].SoundFile=0;
						MPCFile[page][sprite].used=0;
						MPCFile[page][sprite].Sign=0;
						DynamicTempo[page]=0;
					}
				}
				DynamicTempo[0]=3.0;
				Page=0;
				SwitchPage(Page);
				UpdatePageView(0);
				EndPage=0;
				UpdateCurrentSprite();
				PA_WaitForVBL();
				PA_LoadBackground(0,2,&measures);//map to plot too
				PA_LoadText(0,0,&fbfont); //font name
				PA_SetTextCol (0,0,0,0);
				LoadSpritePals();
				Original=0;
				DisplaySongInfo();
				clearmenu=0;
			}
			else if(PA_StylusInZone(143,99,179,118)){
				HideSprite(0,7,0);	
				PA_WaitForVBL();
				PA_WaitFor(Stylus.Released);
				PA_WaitForVBL();
				PA_DeleteBg(0,1);
				PA_DeleteBg(0,2);
				PA_LoadBackground(0,2,&measures);//map to plot too
				PA_EasyBgScrollXY(0,2,Page*256,0); // and Y scroll
				PA_SetSpriteX(0,0,-64); 
				PA_SetSpriteX(0,7,-64); 
				UpdateCurrentSprite();
				LoadSpritePals();
				clearmenu=0;
			}
		}
		PA_WaitForVBL();
	}	
}
