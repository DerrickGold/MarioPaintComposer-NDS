
#ifndef __BAGKEYB_H__
#define __BAGKEYB_H__


//Uncomment this if you don't have a line function for 16c backgrounds
//#define USE_16cFUNCTIONS

extern const u8 BAG_KeyBoard[2][5][12];

//Some important key values
typedef enum{
	SPACE, BACKSPACE, CAPS, TAB, SHIFT
}KEYVALUES;

#define NO_KEY '~'
#define ENTER	'\n'


//stores positions for all keys
typedef struct{
	//global key settings
	s8 Screen,BgMode, PalOffset,FontSlot;
	u16 KeyCol, LetterCol, PressedKeyCol, PressedLetterCol;
	//only keyboard uses these
	bool type, capslock;
	//vars used by both keypad and keyboard
	struct{
		s16 X,Y;
		 struct{
			u8 KeyX,KeyY,KeyX2,KeyY2;
		} Ltrs[5][12];
		u8 ExtraX[6],ExtraX2[6],ExtraY[6],ExtraY2[6];	
		s16 TxtWd,TxtHt,FontSize;
		bool Pressed;
	}Mode[2];
	
}BAGKEYSINFO;
BAGKEYSINFO _BAG_KB;

typedef enum{
	BAG_KB, BAG_KP
}_BAG_Keyboard_Mode;

typedef enum{
	KB_BG_16c, KB_BG_8bit, KB_BG_16bit
}_BAG_KeyBoard_BG_Mode;

typedef enum{
	Key_Shift, Key_Enter, Key_Space, Key_Back, Key_Tab, Key_Caps
}_BAG_Extra_Keys;
	
//keyboard
extern void BAG_InitKeyBoard(s32 x, s32 y, s8 size, s8 fontsize);
extern void RefreshKeyboard(void);
extern char CheckKeyboard(void);
//keypad
extern void BAG_InitKeyPad(s32 x, s32 y, s8 size, s8 fontsize);
extern void RefreshKeyPad(void);
extern char CheckKeyPad(void);
//general setup
extern void SetKeyBoardScreen(s8 screen);
extern void SetKeyBoardBgMode(s8 Mode);
extern void SetKeyBoardColors(u16 Keys, u16 Letter, u16 PressedKey, u16 PressedLetter);
extern void SetKeyBoardFont(s8 font);
#endif
