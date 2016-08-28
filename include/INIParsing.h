#ifndef _inistuff_h_
#define _inistuff_h_
FILE* readINI;

fpos_t LevelIniPos,LevelIniPos2;
bool seekLine(char *line, char *param);
int readIniFileInt(char *file, char *param);
char* readIniFileString(char *file,char *param);
bool ContseekLine(char *line, char *param);
void ResetStream(void);
int ContreadIniFileInt(char *file,char *param);
char* ContreadIniFileString(char *file,char *param);
#endif
