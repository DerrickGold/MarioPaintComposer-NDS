#ifndef __SPRISYS__
#define __SPRISYS_
//sprite numbers for gui
#define STOP 10
#define PLAY 1
#define LOOP 2
#define NOTECURS 3
#define REWIND 4
#define PAGESLIDER 5
#define TEMPOSLIDER 6
#define ERASERBUT 7

#define STAMPSRPITE 8
#define STAMPSIGN 9
#define BARSPRITE 11
#define STARTSPRITE 13
#define PICKEDSPRITE 12
//spacing
#define SPRITEYOFFSET 8

#define PAGESLIDPOS 92

s8 FindUnusedSprite(u16 page);
s8 FindUnusedSign(u16 page);
s8 CountSpriteColumn (u8 xposition);
void PreLoadSpriteGfx(void);
void CreateSprite(int page,int number,int frame,int x,int y, s8 sign);
void CreateSign(int page,int number,int x,int y);
void DisplayPage(int pagenumber);
void DisplayStamp(int sprite, s8 sign, u16 page);
void DeleteSprite(int page,int sprite);
void ClearSprites(void);
void LoadGuiSprites(void);
void HideSprite(bool screen, u8 sprite,bool hide);
void LoadTitle(void);
void LoadSpritePals(void);
void ClearSong(void);
void InitText(bool screen);
void DisplayViewPage(int pagenumber);
void UpdatePageView(s16 page);
void LoadMainScreens(void);
#endif
