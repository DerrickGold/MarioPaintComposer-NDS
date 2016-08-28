#include <PA9.h>       // Include for PA_Lib
#include "BAGKeyboard.h"

/*==========================================================================================
Keyboard and keypad structs
==========================================================================================*/
const u8 BAG_KeyBoard[2][5][12]={
	{
		{'1','2','3','4','5','6','7','8','9','0','-','='},
		{'q','w','e','r','t','y','u','i','o','p',NO_KEY,NO_KEY},
		{'a','s','d','f','g','h','j','k','l',NO_KEY,NO_KEY,NO_KEY},
		{NO_KEY,'z','x','c','v','b','n','m',',','.','/','\\'},
		{NO_KEY,';','\'',NO_KEY,NO_KEY,NO_KEY,NO_KEY,NO_KEY,NO_KEY,'[',']',NO_KEY},
	},
	{	
		{'!','@','#','$','%','^','&','*','(',')','_','+'},
		{'Q','W','E','R','T','Y','U','I','O','P',NO_KEY,NO_KEY},
		{'A','S','D','F','G','H','J','K','L',NO_KEY,NO_KEY,NO_KEY},
		{NO_KEY,'Z','X','C','V','B','N','M','<','>','?','|'},
		{NO_KEY,':','"',NO_KEY,NO_KEY,NO_KEY,NO_KEY,NO_KEY,NO_KEY,'{','}',NO_KEY},
	},
};
const u8 BAG_KeyPad[4][3]={
	{'7','8','9'},
	{'4','5','6'},
	{'1','2','3'},
	{'0',NO_KEY,NO_KEY},
};
/*==========================================================================================
drawing routines not included in palib)
==========================================================================================*/
void PA_16bitClearZone(u8 screen,s16 x1,s16 y1,s16 x2,s16 y2){
	int i=0;
	s16 width=abs(x2-x1);
	s16 height=abs(y2-y1);
	for(i=0;i<height;i++){
		DC_FlushRange((u16*)&PA_DrawBg[screen][x1+((y1+i)*SCREEN_WIDTH)],width*2);
		dmaFillHalfWords (0, (u16*)&PA_DrawBg[screen][x1+((y1+i)*SCREEN_WIDTH)],width*2);
	}
}
void PA_8bitClearZone(u8 screen,s16 x1,s16 y1,s16 x2,s16 y2){
	//int i=0;
	s16 width=abs(x2-x1);
	s16 height=abs(y2-y1);
	//for(i=0;i<height;i++)dmaFillWords (0,(u16*) &PA_DrawBg[screen][x1+((y1+i)*SCREEN_WIDTH)],width*2);
	int x=0,y=0;
	for(x=x1;x<x1+width;x++){
		for(y=y1;y<y1+height;y++)PA_Put8bitPixel  (screen, x, y, 0);
	}
}
#ifdef USE_16cFUNCTIONS
void PA_Draw16cLine(u8 screen, u16 x1, u16 y1, u16 x2, u16 y2, u8 color) {
	int i, dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;
	dx = x2 - x1;  /* the horizontal distance of the line */
	dy = y2 - y1;  /* the vertical distance of the line */
	dxabs = dx;
	sdx = 1;

	if (dx < 0) {
		dxabs = -dx;
		sdx = -1;
	}

	dyabs = dy;
	sdy = 1;

	if (dy < 0) {
		dyabs = -dy;
		sdy = -1;
	}

	x = dyabs >> 1;
	y = dxabs >> 1;
	px = x1;
	py = y1;
	PA_16cPutPixel(screen, px,py, color);

	if (dxabs >= dyabs) {
		for (i = 0; i < dxabs; i++)  {
			y += dyabs;

			if (y >= dxabs)  {
				y -= dxabs;
				py += sdy;
			}

			px += sdx;
			PA_16cPutPixel(screen, px, py, color);
		}
	} else {
		for (i = 0; i < dyabs; i++) {
			x += dxabs;

			if (x >= dyabs)  {
				x -= dyabs;
				px += sdx;
			}

			py += sdy;
			PA_16cPutPixel(screen, px, py, color);
		}
	}
}
void PA_Draw16cLineEx(u8 screen, s16 basex, s16 basey, s16 endx, s16 endy, u8 color, s8 size) {
	s8 low = (size >> 1) - size + 1;
	s8 high = (size >> 1) + 1;
	s16 i, j;
	s16 x1, x2, y1, y2;

	for (i = low; i < high; i++) {
		for (j = low; j < high; j++) {
			if ((basex + i >= 0) && (basey + j >= 0) && (basex + i < 256) && (basey + j < 192)) {
				PA_16cPutPixel(screen, basex + i, basey + j, color);
			}
		}
	}

	for (i = low; i < high; i++) {
		j = low;
		x1 = basex + i; x2 = endx + i; y1 = basey + j; y2 = endy + j;

		while (x1 < 0) x1++;	while (x1 > 255) x1--;

		while (x2 < 0) x2++;	while (x2 > 255) x2--;

		while (y1 < 0) y1++;	while (y1 > 191) y1--;

		while (y2 < 0) y2++;	while (y2 > 191) y2--;

		PA_Draw16cLine(screen, x1, y1, x2, y2, color);
		j = high - 1;
		x1 = basex + i; x2 = endx + i; y1 = basey + j; y2 = endy + j;

		while (x1 < 0) x1++;	while (x1 > 255) x1--;

		while (x2 < 0) x2++;	while (x2 > 255) x2--;

		while (y1 < 0) y1++;	while (y1 > 191) y1--;

		while (y2 < 0) y2++;	while (y2 > 191) y2--;

		PA_Draw16cLine(screen, x1, y1, x2, y2, color);
	}

	for (j = low; j < high; j++) {
		i = low;
		x1 = basex + i; x2 = endx + i; y1 = basey + j; y2 = endy + j;

		while (x1 < 0) x1++;	while (x1 > 255) x1--;

		while (x2 < 0) x2++;	while (x2 > 255) x2--;

		while (y1 < 0) y1++;	while (y1 > 191) y1--;

		while (y2 < 0) y2++;	while (y2 > 191) y2--;

		PA_Draw16cLine(screen, x1, y1, x2, y2, color);
		i = high - 1;
		x1 = basex + i; x2 = endx + i; y1 = basey + j; y2 = endy + j;

		while (x1 < 0) x1++;	while (x1 > 255) x1--;

		while (x2 < 0) x2++;	while (x2 > 255) x2--;

		while (y1 < 0) y1++;	while (y1 > 191) y1--;

		while (y2 < 0) y2++;	while (y2 > 191) y2--;

		PA_Draw16cLine(screen, x1, y1, x2, y2, color);
	}
}
#endif

/*==========================================================================================
Drawing Wrappers
==========================================================================================*/	
void _BAG_KB_DrawLine(s16 x1, s16 y1, s16 x2, s16 y2, u16 color){
	switch(_BAG_KB.BgMode){
		case KB_BG_16c:PA_Draw16cLine(_BAG_KB.Screen,x1,y1,x2,y2,color);break;
		case KB_BG_8bit:PA_Draw8bitLine(_BAG_KB.Screen,x1,y1,x2,y2,color);break;
		case KB_BG_16bit:PA_Draw16bitLine(_BAG_KB.Screen,x1,y1,x2,y2,color);break;
	}
}

void _BAG_KB_DrawLineEX(s16 x1, s16 y1, s16 x2, s16 y2, u16 color, s8 size){
	switch(_BAG_KB.BgMode){
		case KB_BG_16c:PA_Draw16cLineEx(_BAG_KB.Screen,x1,y1,x2,y2,color,size);break;
		case KB_BG_8bit:PA_Draw8bitLineEx(_BAG_KB.Screen,x1,y1,x2,y2,color,size);break;
		case KB_BG_16bit:PA_Draw16bitLineEx(_BAG_KB.Screen,x1,y1,x2,y2,color,size);break;
	}
}

void _BAG_KB_Text(s16 x1, s16 y1, char *text,u16 color, s8 lim){
	switch(_BAG_KB.BgMode){
		case KB_BG_16c:PA_16cText(_BAG_KB.Screen,x1,y1,255, 192,(char*)text, color,_BAG_KB.FontSlot,lim);break;
		case KB_BG_8bit:PA_8bitText(_BAG_KB.Screen,x1,y1, 255,192,(char*)text,color, _BAG_KB.FontSlot, 1, lim);break;
		case KB_BG_16bit:PA_16bitText(_BAG_KB.Screen,x1,y1, 255,192,(char*)text,color, _BAG_KB.FontSlot, 1, lim);break;
	}
}

/*==========================================================================================
Setup for both keypad and keyboard
==========================================================================================*/
void SetKeyBoardScreen(s8 screen){
	_BAG_KB.Screen=screen;
}

void SetKeyBoardBgMode(s8 Mode){
	_BAG_KB.BgMode=Mode;
}

void SetKeyBoardFont(s8 font){
	_BAG_KB.FontSlot=font;
}


void SetKeyBoard16BitCol(u16 Keys, u16 Letter, u16 PressedKey, u16 PressedLetter){
	_BAG_KB.KeyCol=Keys;
	_BAG_KB.LetterCol=Letter;
	_BAG_KB.PressedKeyCol=PressedKey;
	_BAG_KB.PressedLetterCol=PressedLetter;
}

void SetKeyBoard8BitCol(u16 Keys, u16 Letter, u16 PressedKey, u16 PressedLetter){
	int temp=0;
	if(_BAG_KB.PalOffset==0)_BAG_KB.PalOffset++;
	_BAG_KB.KeyCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,_BAG_KB.KeyCol, Keys); temp++;

	_BAG_KB.LetterCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,_BAG_KB.LetterCol, Letter); temp++;

	_BAG_KB.PressedKeyCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,_BAG_KB.PressedKeyCol, PressedKey); temp++;

	_BAG_KB.PressedLetterCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,_BAG_KB.PressedLetterCol, PressedLetter); temp++;	
}
void SetKeyBoard16cCol(u16 Keys, u16 Letter, u16 PressedKey, u16 PressedLetter){
	int temp=0;
	if(_BAG_KB.PalOffset==0)_BAG_KB.PalOffset++;
	s8 npalette=0;
	
	_BAG_KB.KeyCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,(npalette<<4)+_BAG_KB.KeyCol, Keys); temp++;

	_BAG_KB.LetterCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,(npalette<<4)+_BAG_KB.LetterCol, Letter); temp++;

	_BAG_KB.PressedKeyCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,(npalette<<4)+_BAG_KB.PressedKeyCol, PressedKey); temp++;

	_BAG_KB.PressedLetterCol= _BAG_KB.PalOffset + temp;
	PA_SetBgPalCol(_BAG_KB.Screen,(npalette<<4)+_BAG_KB.PressedLetterCol, PressedLetter); temp++;	
}


void SetKeyBoardColors(u16 Keys, u16 Letter, u16 PressedKey, u16 PressedLetter){
	switch(_BAG_KB.BgMode){
		case KB_BG_16c:SetKeyBoard16cCol(Keys,Letter,PressedKey,PressedLetter);break;
		case KB_BG_8bit:SetKeyBoard8BitCol(Keys,Letter,PressedKey,PressedLetter);break;
		case KB_BG_16bit:SetKeyBoard16BitCol(Keys,Letter,PressedKey,PressedLetter);break;
	}
}
	
/*==========================================================================================
KeyBoard
==========================================================================================*/
void Draw8bitKeyboard(bool type, s32 x,s32 y,s8 keywidth, s8 keyheight, s8 fontsize);


void RefreshKeyboard(void){
	if(_BAG_KB.Mode[BAG_KB].Pressed==1){
		//clear the zone first
		switch(_BAG_KB.BgMode){	
			case KB_BG_16c:
				PA_16cClearZone(_BAG_KB.Screen,_BAG_KB.Mode[BAG_KB].X,_BAG_KB.Mode[BAG_KB].Y,_BAG_KB.Mode[BAG_KB].X+(_BAG_KB.Mode[BAG_KB].TxtWd*12),_BAG_KB.Mode[BAG_KB].Y+(_BAG_KB.Mode[BAG_KB].TxtHt*5));
			break;
			case KB_BG_8bit:
				PA_8bitClearZone(_BAG_KB.Screen,_BAG_KB.Mode[BAG_KB].X,_BAG_KB.Mode[BAG_KB].Y,_BAG_KB.Mode[BAG_KB].X+(_BAG_KB.Mode[BAG_KB].TxtWd*12),_BAG_KB.Mode[BAG_KB].Y+(_BAG_KB.Mode[BAG_KB].TxtHt*5));
			break;
			case KB_BG_16bit:
				PA_16bitClearZone(_BAG_KB.Screen,_BAG_KB.Mode[BAG_KB].X,_BAG_KB.Mode[BAG_KB].Y,_BAG_KB.Mode[BAG_KB].X+(_BAG_KB.Mode[BAG_KB].TxtWd*12),_BAG_KB.Mode[BAG_KB].Y+(_BAG_KB.Mode[BAG_KB].TxtHt*5));
			break;
		}
		Draw8bitKeyboard(_BAG_KB.type,_BAG_KB.Mode[BAG_KB].X,_BAG_KB.Mode[BAG_KB].Y,_BAG_KB.Mode[BAG_KB].TxtWd,_BAG_KB.Mode[BAG_KB].TxtHt,_BAG_KB.Mode[BAG_KB].FontSize);
		_BAG_KB.Mode[BAG_KB].Pressed=0;
	}
}	

void BAG_InitKeyBoard(s32 x, s32 y, s8 size, s8 fontsize){
	_BAG_KB.Mode[BAG_KB].X=x;
	_BAG_KB.Mode[BAG_KB].Y=y;
	_BAG_KB.Mode[BAG_KB].TxtWd=size;
	_BAG_KB.Mode[BAG_KB].TxtHt=size;
	_BAG_KB.Mode[BAG_KB].FontSize = fontsize;
	_BAG_KB.Mode[BAG_KB].Pressed=1;
	RefreshKeyboard();
}

void DrawKey(u8 character, s32 x,s32 y,s8 fontsize,u16 col1,u16 col2, s8 Mode){
	s16 tempwidth=_BAG_KB.Mode[Mode].TxtWd,TempFont=fontsize;
	//draw key box
	if(character=='\\' || character=='|'){
		tempwidth=(tempwidth>>1);
		TempFont=(TempFont>>1);
	}
	//horizontal lines
	_BAG_KB_DrawLine(x,y,x+tempwidth,y,col1);
	_BAG_KB_DrawLine(x,y+_BAG_KB.Mode[Mode].TxtHt,x+tempwidth,y+_BAG_KB.Mode[Mode].TxtHt,col1);
	//vertical lines
	_BAG_KB_DrawLine(x,y,x,y+_BAG_KB.Mode[Mode].TxtHt,col1);
	_BAG_KB_DrawLine(x+tempwidth,y,x+tempwidth,y+_BAG_KB.Mode[Mode].TxtHt,col1);

	_BAG_KB_Text(x+(TempFont>>1),y+(fontsize>>1),(char*)&character,col2, 1);	
}
void DrawShiftEnterKey(u8 character,s32 x,s32 y,u16 col1,u16 col2){
	if(character==SHIFT){
		//hor lines
		_BAG_KB_DrawLine(x,y,_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Shift],y,col1);
		_BAG_KB_DrawLine(x,_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Shift],_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Shift],_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Shift],col1);
		//vert lines
		_BAG_KB_DrawLine(x,y,x,_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Shift],col1);
		_BAG_KB_DrawLine(_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Shift],y,_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Shift],_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Shift],col1);
		
		s32 arrowY= y+(_BAG_KB.Mode[BAG_KB].TxtHt>>2);
		s32 arrowX= x+(_BAG_KB.Mode[BAG_KB].TxtWd>>2)+4;
		//draw shift arrow
		_BAG_KB_DrawLineEX(arrowX,arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),arrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),col2,1);//bottom
		_BAG_KB_DrawLineEX(arrowX,arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),arrowX,arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>2),col2,1);//left line
		_BAG_KB_DrawLineEX(arrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),arrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>2),col2,1);//right line
		_BAG_KB_DrawLineEX(arrowX-2,arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>2),arrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>2),arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>2)-3,col2,1);//left slant line
		_BAG_KB_DrawLineEX(arrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>1)+2,arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>2),arrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>2),arrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>2)-3,col2,1);//right slant line
 	}
	if(character==ENTER){
		int tempy = y;
		//hor lines
		_BAG_KB_DrawLine(x,y,x+(_BAG_KB.Mode[BAG_KB].TxtWd*2)+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),y,col1);
		_BAG_KB_DrawLine(x,y+_BAG_KB.Mode[BAG_KB].TxtHt,x+(_BAG_KB.Mode[BAG_KB].TxtWd*2)+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),y+_BAG_KB.Mode[BAG_KB].TxtHt,col1);
		//vert lines
		_BAG_KB_DrawLine(x,y,x,y+_BAG_KB.Mode[BAG_KB].TxtHt,col1);
		_BAG_KB_DrawLine(x+(_BAG_KB.Mode[BAG_KB].TxtWd*2)+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),y,x+(_BAG_KB.Mode[BAG_KB].TxtWd*2)+(_BAG_KB.Mode[BAG_KB].TxtWd>>1),y+_BAG_KB.Mode[BAG_KB].TxtHt,col1);
		//draw return arrow
		s32 ArrowX= x+(_BAG_KB.Mode[BAG_KB].TxtWd*2)-(_BAG_KB.Mode[BAG_KB].TxtWd>>1);
		s32 ArrowY= tempy;
		
		_BAG_KB_DrawLineEX(ArrowX,ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-4,ArrowX,ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-2,col2,2);//down line
		_BAG_KB_DrawLineEX(ArrowX,ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,col2,2);//horizontal line
		//arrow tip
		_BAG_KB_DrawLineEX(ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1)-(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-3,col2,1);
		_BAG_KB_DrawLineEX(ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1)-(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)+2,col2,1);
 	}
	if(character==SPACE){
		//hor lines	
		_BAG_KB_DrawLine(x,y,x+(_BAG_KB.Mode[BAG_KB].TxtWd*6),y,col1);
		_BAG_KB_DrawLine(x,y+(_BAG_KB.Mode[BAG_KB].TxtHt),x+(_BAG_KB.Mode[BAG_KB].TxtWd*6),y+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		//vert lines
		_BAG_KB_DrawLine(x,y,x,y+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		_BAG_KB_DrawLine(x+(_BAG_KB.Mode[BAG_KB].TxtWd*6),y,x+(_BAG_KB.Mode[BAG_KB].TxtWd*6),y+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
	}
	if(character == BACKSPACE){
		int tempy = y;
		int tempwidth= _BAG_KB.Mode[BAG_KB].TxtWd*2;
		int tempx = x;

		//key outline
		//horizontal lines
		_BAG_KB_DrawLine(tempx,tempy,tempx+tempwidth,tempy,col1);
		_BAG_KB_DrawLine(tempx,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),tempx+tempwidth,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		//vertical lines
		_BAG_KB_DrawLine(tempx,tempy,tempx,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		_BAG_KB_DrawLine(tempx+tempwidth,tempy,tempx+tempwidth,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		//backspace arrow
		s32 ArrowX= x+(_BAG_KB.Mode[BAG_KB].TxtWd)+(_BAG_KB.Mode[BAG_KB].TxtWd>>2);
		s32 ArrowY= tempy;
		_BAG_KB_DrawLineEX(ArrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,col2,2);//mid line
		_BAG_KB_DrawLineEX(ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-3,col2,1);
		_BAG_KB_DrawLineEX(ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,ArrowX-(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)+2,col2,1);
	}
	if(character == TAB){
		int tempy = y;
		int tempwidth= _BAG_KB.Mode[BAG_KB].TxtWd>>1;
		int tempx = x;
		//key outline
		//horizontal lines
		_BAG_KB_DrawLine(tempx,tempy,tempx+tempwidth,tempy,col1);
		_BAG_KB_DrawLine(tempx,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),tempx+tempwidth,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		//vertical lines
		_BAG_KB_DrawLine(tempx,tempy,tempx,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		_BAG_KB_DrawLine(tempx+tempwidth,tempy,tempx+tempwidth,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		//backspace arrow
		s32 ArrowX= x+1;
		s32 ArrowY= tempy;
		_BAG_KB_DrawLineEX(ArrowX,ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,ArrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,col2,2);//mid line
		
		_BAG_KB_DrawLineEX(ArrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>3),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-3,ArrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1),col2,1);
		_BAG_KB_DrawLineEX(ArrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>3),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)+2,ArrowX+(_BAG_KB.Mode[BAG_KB].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KB].TxtHt>>1)-1,col2,1);	
	}
	if(character == CAPS){
		int tempy = y;
		int tempwidth= _BAG_KB.Mode[BAG_KB].TxtWd*2;
		int tempx = x;
		//key outline
		//horizontal lines
		_BAG_KB_DrawLine(tempx,tempy,tempx+tempwidth,tempy,col1);
		_BAG_KB_DrawLine(tempx,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),tempx+tempwidth,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		//vertical lines
		_BAG_KB_DrawLine(tempx,tempy,tempx,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		_BAG_KB_DrawLine(tempx+tempwidth,tempy,tempx+tempwidth,tempy+(_BAG_KB.Mode[BAG_KB].TxtHt),col1);
		_BAG_KB_Text(x+(_BAG_KB.Mode[BAG_KB].FontSize>>1),y+(_BAG_KB.Mode[BAG_KB].FontSize>>1),"caps",col2,10);	
	}
}

void Draw8bitKeyboard(bool type, s32 x,s32 y,s8 keywidth, s8 keyheight, s8 fontsize){

	int y1=0,x1=0;
	for(y1=0;y1<5;y1++){
		for(x1=0;x1<12;x1++){
			if(BAG_KeyBoard[type][y1][x1]!='~'){
				
				_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyY= y+(keywidth*y1);
				_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyY2= y+(keyheight*y1)+keyheight;
				switch(y1){
					case 0:
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX= x+(keywidth*x1);
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX2= x+(keywidth*x1)+keywidth;
						DrawKey(BAG_KeyBoard[type][y1][x1],_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX,y+(keyheight*y1),_BAG_KB.Mode[BAG_KB].FontSize,_BAG_KB.KeyCol,_BAG_KB.LetterCol,BAG_KB);
					break;
					case 1:
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX= x+(keywidth*x1);
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX2= x+(keywidth*x1)+keywidth;
						DrawKey(BAG_KeyBoard[type][y1][x1],_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX,y+(keyheight*y1),_BAG_KB.Mode[BAG_KB].FontSize,_BAG_KB.KeyCol,_BAG_KB.LetterCol,BAG_KB);
					break;
					case 2:
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX= x+(keywidth*x1)+(keyheight>>1);
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX2= x+(keywidth*x1)+(keyheight>>1)+(keywidth);
						DrawKey(BAG_KeyBoard[type][y1][x1],_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX,y+(keyheight*y1),_BAG_KB.Mode[BAG_KB].FontSize,_BAG_KB.KeyCol,_BAG_KB.LetterCol,BAG_KB);
					break;
					case 3:
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX= x+(keywidth*x1)+(keywidth>>1);
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX2= x+(keywidth*x1)+(keywidth>>1)+(keywidth);
						DrawKey(BAG_KeyBoard[type][y1][x1],_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX,y+(keyheight*y1),_BAG_KB.Mode[BAG_KB].FontSize,_BAG_KB.KeyCol,_BAG_KB.LetterCol,BAG_KB);
					break;
					case 4:
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX= x+(keywidth*x1)+keywidth;
						_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX2= x+(keywidth*x1)+(keywidth<<1);
						DrawKey(BAG_KeyBoard[type][y1][x1],_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX,y+(keyheight*y1),_BAG_KB.Mode[BAG_KB].FontSize,_BAG_KB.KeyCol,_BAG_KB.LetterCol,BAG_KB);
					break;
				}
			}
		}
	}
	//space bar
	_BAG_KB.Mode[BAG_KB].ExtraX[Key_Space]=x+(keywidth*4);
	_BAG_KB.Mode[BAG_KB].ExtraY[Key_Space]=y+(keyheight*4);
	_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Space]=x+(keywidth*10);
	_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Space]=y+(keyheight*4)+keyheight;
	DrawShiftEnterKey(SPACE,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Space],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Space],_BAG_KB.KeyCol,_BAG_KB.LetterCol);
	//enter key
	_BAG_KB.Mode[BAG_KB].ExtraX[Key_Enter]=x+(keywidth*9)+(keywidth>>1);
	_BAG_KB.Mode[BAG_KB].ExtraY[Key_Enter]=y+(keyheight*2);
	_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Enter]=x+(keywidth*12);
	_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Enter]=y+(keyheight*3);	
	DrawShiftEnterKey(ENTER,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Enter],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Enter],_BAG_KB.KeyCol,_BAG_KB.LetterCol);
	//backspace key
	_BAG_KB.Mode[BAG_KB].ExtraX[Key_Back]=x+(keywidth*10);
	_BAG_KB.Mode[BAG_KB].ExtraY[Key_Back]=y+(keyheight);
	_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Back]=x+(keywidth*10)+keywidth*2;
	_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Back]=y+(keyheight*2);	
	DrawShiftEnterKey(BACKSPACE,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Back],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Back],_BAG_KB.KeyCol,_BAG_KB.LetterCol);
	//tab key
	_BAG_KB.Mode[BAG_KB].ExtraX[Key_Tab]=x;
	_BAG_KB.Mode[BAG_KB].ExtraY[Key_Tab]=y+(keyheight*2);
	_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Tab]=x+(keywidth>>1);
	_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Tab]=y+(keyheight*3);	
	DrawShiftEnterKey(TAB,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Tab],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Tab],_BAG_KB.KeyCol,_BAG_KB.LetterCol);	
	
	u16 tempcol[2]={_BAG_KB.KeyCol,_BAG_KB.LetterCol};
	//shift key
	_BAG_KB.Mode[BAG_KB].ExtraX[Key_Shift]=x;
	_BAG_KB.Mode[BAG_KB].ExtraY[Key_Shift]=y+(keyheight*3);
	_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Shift]=x+(keywidth+(keywidth>>1));
	_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Shift]=y+(keyheight*3)+keyheight;
	
	if(_BAG_KB.type && !_BAG_KB.capslock){
		tempcol[0]=_BAG_KB.PressedKeyCol;
		tempcol[1]=_BAG_KB.PressedLetterCol;
	}	
	DrawShiftEnterKey(SHIFT,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Shift],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Shift],tempcol[0],tempcol[1]);
	
	//caps
	_BAG_KB.Mode[BAG_KB].ExtraX[Key_Caps]=x;
	_BAG_KB.Mode[BAG_KB].ExtraY[Key_Caps]=y+(keyheight*4);
	_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Caps]=x+(keywidth*2);
	_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Caps]=y+(keyheight*5);

	if(_BAG_KB.capslock){
		tempcol[0]=_BAG_KB.PressedKeyCol;
		tempcol[1]=_BAG_KB.PressedLetterCol;
	}
	else {
		tempcol[0]=_BAG_KB.KeyCol;
		tempcol[1]=_BAG_KB.LetterCol;	
	}
	DrawShiftEnterKey(CAPS,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Caps],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Caps],tempcol[0],tempcol[1]);		
	_BAG_KB.type=type;
}
char CheckKeyboard(void){
	int y1=0,x1=0;
	_BAG_KB.Mode[BAG_KB].Pressed=1;
	//normal keys
	for(y1=0;y1<5;y1++){
		for(x1=0;x1<12;x1++){
			if(Stylus.X>= _BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX && Stylus.X<=_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX2 &&
				Stylus.Y>=_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyY && Stylus.Y<=_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyY2){
					bool TempType=_BAG_KB.type;
					
					DrawKey(BAG_KeyBoard[TempType][y1][x1],_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyX,_BAG_KB.Mode[BAG_KB].Ltrs[y1][x1].KeyY,_BAG_KB.Mode[BAG_KB].FontSize,_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol,BAG_KB);
					if(!_BAG_KB.capslock && _BAG_KB.type)_BAG_KB.type=0;
					else if(_BAG_KB.capslock && !_BAG_KB.type)_BAG_KB.type=1;
					return BAG_KeyBoard[TempType][y1][x1];
				}
		}
	}
	//shift key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KB].ExtraX[Key_Shift] && Stylus.X<=_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Shift] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KB].ExtraY[Key_Shift] && Stylus.Y<=_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Shift]){
		DrawShiftEnterKey(SHIFT,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Shift],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Shift],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		_BAG_KB.type++;
		if(_BAG_KB.type>1)_BAG_KB.type=0;
		return SHIFT;
	}
	
	//enter key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KB].ExtraX[Key_Enter] && Stylus.X<=_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Enter] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KB].ExtraY[Key_Enter] && Stylus.Y<=_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Enter]){
		DrawShiftEnterKey(ENTER,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Enter],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Enter],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		return ENTER;
	}
	//space key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KB].ExtraX[Key_Space] && Stylus.X<=_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Space] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KB].ExtraY[Key_Space] && Stylus.Y<=_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Space]){
		DrawShiftEnterKey(SPACE,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Space],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Space],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		return ' ';
	}	
	//backspace key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KB].ExtraX[Key_Back] && Stylus.X<=_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Back] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KB].ExtraY[Key_Back] && Stylus.Y<=_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Back]){
		DrawShiftEnterKey(BACKSPACE,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Back],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Back],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		return BACKSPACE;
	}
	//tab key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KB].ExtraX[Key_Tab] && Stylus.X<=_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Tab] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KB].ExtraY[Key_Tab] && Stylus.Y<=_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Tab]){
		DrawShiftEnterKey(TAB,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Tab],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Tab],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		return TAB;
	}
	//caps key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KB].ExtraX[Key_Caps] && Stylus.X<=_BAG_KB.Mode[BAG_KB].ExtraX2[Key_Caps] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KB].ExtraY[Key_Caps] && Stylus.Y<=_BAG_KB.Mode[BAG_KB].ExtraY2[Key_Caps]){
		DrawShiftEnterKey(CAPS,_BAG_KB.Mode[BAG_KB].ExtraX[Key_Caps],_BAG_KB.Mode[BAG_KB].ExtraY[Key_Caps],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		_BAG_KB.type++;
		_BAG_KB.capslock++;
		if(_BAG_KB.type>1){
			_BAG_KB.type=0;
			_BAG_KB.capslock=0;
		}
		return CAPS;
	}
	_BAG_KB.Mode[BAG_KB].Pressed=0;
	return 0;
}

/*==========================================================================================
Key Pad
==========================================================================================*/
void DrawKeyPad(s32 x, s32 y, s8 keywidth, s8 keyheight, s8 fontsize);

void RefreshKeyPad(void){
	if(_BAG_KB.Mode[BAG_KP].Pressed==1){
		switch(_BAG_KB.BgMode){	
			case KB_BG_16c:
				PA_16cClearZone(_BAG_KB.Screen,_BAG_KB.Mode[BAG_KP].X,_BAG_KB.Mode[BAG_KP].Y,_BAG_KB.Mode[BAG_KP].X+(_BAG_KB.Mode[BAG_KP].TxtWd*3),_BAG_KB.Mode[BAG_KP].Y+(_BAG_KB.Mode[BAG_KP].TxtHt*4));
			break;
			case KB_BG_8bit:
				PA_8bitClearZone(_BAG_KB.Screen,_BAG_KB.Mode[BAG_KP].X,_BAG_KB.Mode[BAG_KP].Y,_BAG_KB.Mode[BAG_KP].X+(_BAG_KB.Mode[BAG_KP].TxtWd*3),_BAG_KB.Mode[BAG_KP].Y+(_BAG_KB.Mode[BAG_KP].TxtHt*4));
			break;
			case KB_BG_16bit:
				PA_16bitClearZone(_BAG_KB.Screen,_BAG_KB.Mode[BAG_KP].X,_BAG_KB.Mode[BAG_KP].Y,_BAG_KB.Mode[BAG_KP].X+(_BAG_KB.Mode[BAG_KP].TxtWd*3),_BAG_KB.Mode[BAG_KP].Y+(_BAG_KB.Mode[BAG_KP].TxtHt*4));
			break;
		}
		DrawKeyPad(_BAG_KB.Mode[BAG_KP].X,_BAG_KB.Mode[BAG_KP].Y,_BAG_KB.Mode[BAG_KP].TxtWd,_BAG_KB.Mode[BAG_KP].TxtHt,_BAG_KB.Mode[BAG_KP].FontSize);
		_BAG_KB.Mode[BAG_KP].Pressed=0;
	}
}	

void BAG_InitKeyPad(s32 x, s32 y, s8 size, s8 fontsize){
	_BAG_KB.Mode[BAG_KP].X=x;
	_BAG_KB.Mode[BAG_KP].Y=y;
	_BAG_KB.Mode[BAG_KP].TxtWd=size;
	_BAG_KB.Mode[BAG_KP].TxtHt=size;
	_BAG_KB.Mode[BAG_KP].FontSize = fontsize;
	_BAG_KB.Mode[BAG_KP].Pressed=1;
	RefreshKeyPad();
}

void KeyPadBackSpace(s32 x,s32 y,u16 col1,u16 col2){
	int tempy = y;
	int tempwidth= x+_BAG_KB.Mode[BAG_KP].TxtHt*2;
	int tempx = x;

	//vertical
	_BAG_KB_DrawLine(tempx,tempy,tempx,tempy+(_BAG_KB.Mode[BAG_KP].TxtHt),col1);
	_BAG_KB_DrawLine(tempwidth,tempy,tempwidth,tempy+(_BAG_KB.Mode[BAG_KP].TxtHt),col1);
	//horizontal
	_BAG_KB_DrawLine(tempx,tempy+(_BAG_KB.Mode[BAG_KP].TxtHt),tempwidth,tempy+(_BAG_KB.Mode[BAG_KP].TxtHt),col1);
	_BAG_KB_DrawLine(tempx,tempy,tempwidth,tempy,col1);
	//backspace arrow
	s32 ArrowX= x+(_BAG_KB.Mode[BAG_KP].TxtWd)+(_BAG_KB.Mode[BAG_KP].TxtWd>>4);
	s32 ArrowY= tempy;
	_BAG_KB_DrawLineEX(ArrowX+(_BAG_KB.Mode[BAG_KP].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KP].TxtHt>>1)-1,ArrowX-(_BAG_KB.Mode[BAG_KP].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KP].TxtHt>>1)-1,col2,2);//mid line
	_BAG_KB_DrawLineEX(ArrowX-(_BAG_KB.Mode[BAG_KP].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KP].TxtHt>>1),ArrowX-(_BAG_KB.Mode[BAG_KP].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KP].TxtHt>>1)-3,col2,1);
	_BAG_KB_DrawLineEX(ArrowX-(_BAG_KB.Mode[BAG_KP].TxtWd>>1),ArrowY+(_BAG_KB.Mode[BAG_KP].TxtHt>>1)-1,ArrowX-(_BAG_KB.Mode[BAG_KP].TxtWd>>2),ArrowY+(_BAG_KB.Mode[BAG_KP].TxtHt>>1)+2,col2,1);
}
void DrawKeyPad(s32 x, s32 y, s8 keywidth, s8 keyheight, s8 fontsize){
	int y1=0,x1=0;
	for(y1=0;y1<4;y1++){
		for(x1=0;x1<3;x1++){
			if(BAG_KeyPad[y1][x1]!='~'){
				_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyY= y+(keywidth*y1);
				_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyY2= y+(keyheight*y1)+keyheight;
				_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyX= x+(keywidth*x1);
				_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyX2= x+(keywidth*x1)+keywidth;
				DrawKey(BAG_KeyPad[y1][x1],x+(keywidth*x1),y+(keyheight*y1),_BAG_KB.Mode[BAG_KP].FontSize,_BAG_KB.KeyCol,_BAG_KB.LetterCol,BAG_KP);	
			}
		}
	}
	//backspace key
	_BAG_KB.Mode[BAG_KP].ExtraX[Key_Back]=x+(keywidth);
	_BAG_KB.Mode[BAG_KP].ExtraY[Key_Back]=y+(keyheight*3);
	_BAG_KB.Mode[BAG_KP].ExtraX2[Key_Back]=x+(keywidth*3);
	_BAG_KB.Mode[BAG_KP].ExtraY2[Key_Back]=y+(keyheight*4);	
	KeyPadBackSpace(x+(keywidth),y+(keyheight*3),_BAG_KB.KeyCol,_BAG_KB.LetterCol);
}
char CheckKeyPad(void){
	int y1=0,x1=0;
	_BAG_KB.Mode[BAG_KP].Pressed=1;
	//normal keys
	for(y1=0;y1<4;y1++){
		for(x1=0;x1<3;x1++){
			if(Stylus.X>= _BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyX && Stylus.X<=_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyX2 &&
				Stylus.Y>=_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyY && Stylus.Y<=_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyY2){
					DrawKey(BAG_KeyPad[y1][x1],_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyX,_BAG_KB.Mode[BAG_KP].Ltrs[y1][x1].KeyY,_BAG_KB.Mode[BAG_KP].FontSize,_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol,BAG_KP);
					return BAG_KeyPad[y1][x1];
				}
		}
	}
	//backspace key
	if(Stylus.X>= _BAG_KB.Mode[BAG_KP].ExtraX[Key_Back] && Stylus.X<=_BAG_KB.Mode[BAG_KP].ExtraX2[Key_Back] &&
	Stylus.Y>=_BAG_KB.Mode[BAG_KP].ExtraY[Key_Back] && Stylus.Y<=_BAG_KB.Mode[BAG_KP].ExtraY2[Key_Back]){
		KeyPadBackSpace(_BAG_KB.Mode[BAG_KP].ExtraX[Key_Back],_BAG_KB.Mode[BAG_KP].ExtraY[Key_Back],_BAG_KB.PressedKeyCol,_BAG_KB.PressedLetterCol);
		return BACKSPACE;
	}
	_BAG_KB.Mode[BAG_KP].Pressed=0;
	return NO_KEY;
}
