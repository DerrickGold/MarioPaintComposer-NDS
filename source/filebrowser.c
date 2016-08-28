#include <PA9.h>       // Include for PA_Lib
#include <fat.h>
#include <sys/dir.h> 
#include "variables.h"
#include "BAGKeyboard.h"

u16 FindLastPage(void);
extern inline char PA_GetSmall(char letter){
   if((letter >= 'A')&&(letter <= 'Z')) return (letter-'A'+'a');
   return letter;
}   

s16 PA_FATSearchExt(char *directory, PAfiletype *filelist, char *ext){
  s16 number=0;
  bool filesfound=0;
   u8 i, j;
   struct stat st;
   	DIR_ITER* dir = diropen(directory);
   	filesfound=1;
	
	while (dirnext(dir, filelist[number].filename, &st) == 0 && filesfound==1) {
	   if(!(st.st_mode & S_IFDIR)){// Is a file...
	   	// Check if right extension...
	   	i = 0;
	   	while( filelist[number].filename[i]) i++; // go to end of name
	   	while( filelist[number].filename[i-1] != '.') i--; // get to extension
	   	
	   	u8 same = 1; // same by default
	   	for(j = 0; ext[j]; j++) if(PA_GetSmall(ext[j]) !=  PA_GetSmall(filelist[number].filename[i+j])) same = 0; // not right extension
	   	
	   	if(same){ // Ok, register file
	   	
		   	for(j = 0; j < i-1; j++) filelist[number].name[j] = filelist[number].filename[j];
		   	filelist[number].name[j] = 0;
		   	
		   	for(i = 0; ext[i]; i++) filelist[number].ext[i] = ext[i];
		   	filelist[number].ext[i] = 0;
		   	number++;
		 	}  	
	   
		}   
	}
   return number;
}  

void ClearLastFileName(void){
	s8 index;
	for(index=0;index<49;index++)LastFile[index] = '\0';
}

void InitFatSys(char *directory, char *ext){
	FileNumber = PA_FATSearchExt(directory, files,ext);
}
s16 filenum=0;
void ListDirectory(char *directory,s16 page, bool screen,s16 x, s16 y){
	PA_ClearTextBg(1);
	filenum=20*page;
	s16 endfile=filenum+20;
	s16 ypos=0;
	int i;
	for(i=filenum;i<endfile;++i){
		PA_OutputText(screen,x,y+ypos,files[i].name);
		ypos++;
	}
	PA_OutputText(screen,13,23,"Page:%d ",page+1);
}

void savepos(char *file){
	MPCFileType=2;
	char tempfilename[256];
	ClearLastFileName();
	strncpy (LastFile,file,strlen (file));
	sprintf(tempfilename,"%s%s.mpc",location,file);	
	FILE* savefile = fopen(tempfilename, "wb");	
	PA_WaitForVBL();
	fwrite(&MPCFileType,sizeof(MPCFileType), 1, savefile);
	PA_WaitForVBL();
	fwrite(&MPCFile,sizeof(MPCFile), 1, savefile);
	PA_WaitForVBL();
	fwrite(&DynamicTempo, sizeof(DynamicTempo), 1, savefile);
	PA_WaitForVBL();
	fwrite(&Original, sizeof(Original), 1, savefile);
	PA_WaitForVBL();	
	fwrite(&Author, sizeof(Author), 1, savefile);
	PA_WaitForVBL();	
	fclose(savefile);
}
void ConvertTempo(void){
	int pages;
	for(pages=0;pages<=256;++pages)DynamicTempo[pages]=Tempo;
}
		
void ConvertToFileType1(void){
	int pages;
	s8 note;
	ConvertTempo();
	for(pages=0;pages<258;++pages){
		for(note=0;note<30;++note){
			MPCFile[pages][note].frame=Sprite[pages][note].frame;
			MPCFile[pages][note].x=Sprite[pages][note].x;
			MPCFile[pages][note].y=Sprite[pages][note].y;
			MPCFile[pages][note].Note=Sprite[pages][note].Note;
			MPCFile[pages][note].Pitch=Sprite[pages][note].Pitch;
			MPCFile[pages][note].SoundFile=Sprite[pages][note].SoundFile;
			MPCFile[pages][note].Sign=Sprite[pages][note].Sign;
			MPCFile[pages][note].used=Sprite[pages][note].used;
			//clear sprites
			Sprite[pages][note].frame=0;
			Sprite[pages][note].x=0;
			Sprite[pages][note].y=0;
			Sprite[pages][note].Note=0;
			Sprite[pages][note].Pitch=0;
			Sprite[pages][note].SoundFile=0;
			Sprite[pages][note].Sign=0;
			Sprite[pages][note].used=0;
		}
	}
}

bool loadFile(char * file)
{
	FILE* savefile = fopen(file, "rb");	//"rb" = read binary file
	if(savefile){
		//get file size
		u32 FileSize;
		fseek (savefile, 0 , SEEK_END);
		FileSize = ftell (savefile);
		rewind (savefile);
		if(FileSize<=61955){//if File type is 0
			fread((void*)&Sprite,1,sizeof(Sprite),savefile);	//Copy the notes
			fread((void*)&Tempo,1, sizeof(Tempo), savefile);	// Copy temp
			ConvertToFileType1();
		}
		else fread((void*)&MPCFileType,1,sizeof(MPCFileType),savefile);	//if type is not 0, get correct file type
		if(MPCFileType==1){
			fread((void*)&MPCFile,1,sizeof(MPCFile),savefile);//Copy the notes
			fread((void*)&Tempo,1, sizeof(Tempo), savefile);	// Copy temp
			ConvertTempo();
		}
		if(MPCFileType==2){
			fread((void*)&MPCFile,1,sizeof(MPCFile),savefile);//Copy the notes
			fread((void*)&DynamicTempo,1, sizeof(DynamicTempo), savefile);	// Copy temp	
		}
		fread((void*)&Original,1, sizeof(Original), savefile);	// checks if file is already authorized
		fread((void*)&Author,1, sizeof(Author), savefile);	// checks if file is already authorized
		fclose(savefile);

		SetTempo();
		Page=0;
		
		SwitchPage(Page);
		EndPage=FindLastPage();

		return true;
	} else {
		fclose(savefile);
		return false;
	}
}
bool loadSavedata(char *directory,s16 filenumber){
	Original=0;
	MPCFileType=0;
	char filename[256];
	ClearLastFileName();
	strncpy (LastFile,files[filenumber].name,strlen (files[filenumber].name));
	sprintf(filename,"%s%s.%s",directory,files[filenumber].name,files[filenumber].ext);
	
	return  loadFile(filename);
}
s16 nfile=0;
s16 fileCount=0;

inline void UpdateCursor(bool screen,s16 x, s16 y){
	PA_OutputSimpleText(screen,x,nfile-1," ");
	PA_OutputSimpleText(screen,x,nfile,">");
	PA_OutputSimpleText(screen,x,nfile+1," ");
}
void DeleteFileFun(int filenumber){
	char filename[256];
	sprintf(filename,"%s%s.%s",location,files[filenumber].name,files[filenumber].ext);
	remove (filename);
	files[filenumber].name[0]='\0';
	files[filenumber].ext[0]='\0';
	//clear the menu	
	PA_WaitFor(Stylus.Released);
	PA_DeleteBg(1,1);
	//show file list
	ReloadFB();
	InitFatSys(location,"mpc");
	ListDirectory(location,0,1,1,2);
	nfile=0;
	fileCount=(filenum+nfile);
	PA_BGScrollXY(1,2,0,-16);
}
void returntofileb(void){
	
	PA_WaitFor(Stylus.Released);
	PA_DeleteBg(1,1);
	//show file list
	ReloadFB();
	ListDirectory(location,0,1,1,2);
	fileCount=(filenum+nfile);
	PA_BGScrollXY(1,2,0,-16);
	nfile=0;
}
void FileBrowserMenu(bool screen){
	LoadFileBrowser();
	InitFatSys(location,"mpc");
	ListDirectory(location,0,screen,1,2);
	s16 fbpage=0;
	fileCount=(filenum+nfile);
	PA_BGScrollXY(screen,2,0,-16);
	nfile=0;
	bool filebrowser=1;
	if(FileNumber==0){
		PA_BGScrollXY(screen,2,0,-6<<3);
		PA_OutputSimpleText(screen,6,6,"No Files Found");
		PA_WaitFor(Pad.Newpress.Anykey || Stylus.Newpress);
		LoadTopScreen();
		PA_SwitchScreens();
		filebrowser=0;
	}
	PA_WaitForVBL();PA_WaitForVBL();PA_WaitForVBL();PA_WaitForVBL();
	while(filebrowser==1){

		if(Pad.Newpress.B || (Stylus.Newpress && PA_StylusInZone(50,176,70,191))){
			LoadTopScreen();
			PA_SwitchScreens();
			filebrowser=0;
		}
		if(Stylus.Newpress){
			if(PA_StylusInZone(185,176,207,191)){
				fbpage-=1;
				nfile=0;
				if(fbpage<0)fbpage=0;
				PA_BGScrollXY(screen,2,0,-16);
				ListDirectory(location,fbpage,screen,1,2);
				fileCount=(filenum+nfile);
			}
			if(PA_StylusInZone(227,176,246,191) && (FileNumber/(fbpage+1))>20){
				fbpage+=1;
				nfile=0;
				PA_BGScrollXY(screen,2,0,-16);
				ListDirectory(location,fbpage,screen,1,2);
				fileCount=(filenum+nfile);
			}
		}
			
	
		if (Pad.Newpress.Down){
			nfile+=1;
			if (nfile>=FileNumber-(20*fbpage))nfile=FileNumber-(20*fbpage)-1;
			else if(nfile%20==0){
				fbpage+=1;
				nfile=0;
				//PA_BGScrollXY(screen,2,0,-16);
				ListDirectory(location,fbpage,screen,1,2);
				fileCount=(filenum+nfile);
			}
			PA_BGScrollXY(screen,2,0,-(nfile*8)-16);
		}
		else if (Pad.Newpress.Up){
			nfile-=1;
			if (nfile<0 && fbpage==0)nfile=0;
			else if(nfile<0 &&fbpage>0){
				fbpage-=1;
				nfile=19;
				ListDirectory(location,fbpage,screen,1,2);
				fileCount=(filenum+nfile);
			}
			PA_BGScrollXY(screen,2,0,-(nfile*8)-16);
		}
		if(Stylus.Held && Stylus.Y<175 &&Stylus.Y>16){
			nfile =(Stylus.Y >> 3)-2;
			PA_BGScrollXY(screen,2,0,-((nfile+2)<<3));
			fileCount=(filenum+nfile);
			if(fileCount>=FileNumber-2){
				u16 i;
				for(i=fileCount;i>=FileNumber;--i){
					nfile--;
					PA_BGScrollXY(screen,2,0,-((nfile+2)<<3));
				}
			}
		}
		//if(Pad.Newpress.Select)DeleteFile(nfile);
		if(Pad.Newpress.A || (Stylus.Newpress && PA_StylusInZone(10,176,30,191))||(Stylus.DblClick && PA_StylusInZone(0,16,256,176)) ){	
			int page;
			s8 sprite;
			for(page=0;page<256;++page){
				for(sprite=0;sprite<35;++sprite){
					MPCFile[page][sprite].x=0;
					MPCFile[page][sprite].y=0;
					MPCFile[page][sprite].Note=0;
					MPCFile[page][sprite].Pitch=0;
					MPCFile[page][sprite].SoundFile=0;
					MPCFile[page][sprite].used=0;
					MPCFile[page][sprite].Sign=0;
				}
			}
			loadSavedata(location,filenum+nfile);
			PA_WaitForVBL();
			LoadTopScreen();
			PA_SwitchScreens();
			filebrowser=0;
		}	
		PA_WaitForVBL();
	}
}
void SavingMenu(void){
	bool saving=1;

	LoadKeyBoardScreen();
	s32 nletter=0;
	char text[200]; // This will be our text...
	memset(text, 0,200);
	if(Original==1){
		strncpy (text,LastFile,strlen (LastFile));
		nletter = strlen (LastFile); // Next letter to right. 0 since no letters are there yet
	}
	char letter = 0; // New letter to write.
	Stylus.X=0;
	Stylus.Y=0;

	while(saving==1){
		PA_OutputSimpleText(1, 12, 9, text); // Write the text
		if(Original==1)PA_OutputSimpleText(1, 12+nletter, 9,".mpc "); // Write the text
		
		if(Stylus.Newpress){
			letter = CheckKeyboard();
			if(nletter<15){
				if (letter > 31) { // there is a new letter
					if(letter!=0 && letter!=SHIFT && letter!=BACKSPACE && letter!=TAB && letter!=CAPS){
						if(letter!='/' && letter!='"' && letter!=':'&& letter!='?' && letter!='>'&& letter!='<'&& letter!='|'&&letter!='\\'){
							text[nletter] = letter;
							nletter++;
						}
					}
				}
				else if(letter == TAB){// TAB Pressed...
					u8 i;
					for (i = 0; i < 4; i++){ // put 4 spaces...
						text[nletter] = ' ';
						nletter++;
					}
			
				}
			}
			if ((letter == BACKSPACE)&&nletter) { // Backspace pressed
				nletter--;
				text[nletter] = ' '; // Erase the last letter
			}
			else if (letter == ENTER && nletter>0){ // Enter pressed
				PA_WaitForVBL();
				if(Original==1){
					savepos(text);
					PA_ClearTextBg(1);
					LoadTopScreen();
					PA_SwitchScreens();
					saving=0;
				}
				else if(Original==0){
					strcpy (Author,text);
					Original=1;
					PA_ClearTextBg(1);
					PA_OutputSimpleText(1, 3, 9, "Save as:"); 
					s16 index;
					for(index=0;index<199;index++)text[index] = '\0';
					strncpy (text,LastFile,strlen (LastFile));
					nletter = strlen (LastFile);;
				}

			}
		}
		else if(Stylus.Released)RefreshKeyboard();

		if(Pad.Newpress.B){
			PA_SwitchScreens();
			PA_ClearTextBg(1);
			LoadTopScreen();
			saving=0;
		}

		PA_WaitForVBL();
	}
}









