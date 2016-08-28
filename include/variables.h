#ifndef __VARS__
#define __VARS_

#define MARIO 0
#define MUSHROOM 1
#define YOSHI 2
#define STAR 3
#define FLOWER 4
#define GAMEBOY 5
#define DOG 6
#define CAT 7
#define PIG 8
#define SWAN 9
#define FACE 10
#define PLANE 11
#define SHIP 12
#define CAR 13
#define HEART 14
#define BOWSER 15
#define UMBRELLA 16
#define ORCHESTRAL 17
#define HARP 18
#define KICK 19

//MPC File Struct
typedef struct{
	u8 frame;
	u8 x;
	u8 y;	
	u8 Note;
	s8 Pitch;
	s8 SoundFile;
	s8 Sign;
	bool used;
}spriteinfos;
spriteinfos TempFile[258][36];//temp buffer for deleting a page

//File Type Data
spriteinfos MPCFile[258][36];//new file type
s8 MPCFileType;
char Author[30];
bool Original;
char LastFile[50];
float DynamicTempo[258];

//Old file type stuff - keep for backwards compatibility
spriteinfos Sprite[258][30];//old file type
float Tempo;

typedef struct{
	s16 x,y,y2,x2;
	u8 sound;
}iconsinfos;
iconsinfos Stamps[21];

//file browser
typedef struct{
	char filename[100];
	char name[100];
	char ext[10];  
}  PAfiletype;
PAfiletype files[256];

u16 FileNumber;
char RomPath[256];
char location[256];	

u16 gfx[128];
u16 gfx2[128];
u8 spritepicked;
bool spriteplaced;
u8 delete;
u8 CurrentSprite;
s8 tempframe;
u8 tempy;
u8 tempx;
s16 Page;
bool Play;

float temposlider;
int PageBar;
u16 EndPage;
u8 loop;
s8 lastsfx;
bool playsound;
float BarX;//playback bar
s8 NoteSign;//sign -1 =flat 1 = sharp 0 = nothing

u8 Sleep;//decides if to close the DS or not
void FadeIn(s8 screen);
void DualFadeOut(void);
void ConvertTempo(void);
void ConvertToFileType1(void);
void AssignStampSounds(void);
void InsertPage(void);
void DeleteFile(int filenumber);
void DeleteFileFun(int filenumber);
void returntofileb(void);
void ClearPage(void);
void savepos(char *file);
bool loadSavedata(char *directory,s16 filenumber);
void SwitchPage(u16 Pagenum);
void SetTempo(void);
void FileBrowserMenu(bool screen);
void ReloadFB(void);
void LoadFileBrowser(void);
void LoadTopScreen(void);
void LoadKeyBoardScreen(void);
void SavingMenu(void);
void UpdateUndo(void);
void Undo(void);
void file_compress(char *file,char *mode);
u16 NumToNote(u8 number);
void UpdateCurrentSprite(void);
void DisplaySongInfo(void);
void UpdateNews(void);
#endif
