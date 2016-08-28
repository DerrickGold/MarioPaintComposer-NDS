#include <PA9.h>       // Include for PA_Lib
#include "INIParsing.h"
bool seekLine(char *line, char *param)
{
   int i;
   fseek(readINI, 0, SEEK_SET);
   memset(line, 0, 256);
   while(fgets(line, 256, readINI)!=NULL)
   {
      if(strlen(line)>strlen(param)) // check if there's a param
      {
         if(strlen(line)>0&&line[0]!='#') // not a comment line
         {
            bool foundLine = true;
            for(i=0;i<(int)strlen(param);i++)
            {
               if(line[i]!=param[i])
                  foundLine = false;
            }
            if(foundLine)
               return true;
         }
      }
      memset(line, 0, 256);
   }
   
   return false;
}
void ResetStream(void){
	fseek(readINI, 0, SEEK_SET);
}
bool ContseekLine(char *line, char *param)
{
   int i;
   fseek(readINI, 0, SEEK_CUR);
   memset(line, 0, 256);
   while(fgets(line, 256, readINI)!=NULL)
   {
      if(strlen(line)>strlen(param)) // check if there's a param
      {
         if(strlen(line)>0&&line[0]!='#') // not a comment line
         {
            bool foundLine = true;
            for(i=0;i<(int)strlen(param);i++)
            {
               if(line[i]!=param[i])
                  foundLine = false;
            }
            if(foundLine)
               return true;
         }
      }
      memset(line, 0, 256);
   }
   
   return false;
}
// example: int Testnum= readIniFileInt("Testnum")
int readIniFileInt(char *file,char *param)//reminder it only search the first letter so testas would be read as test
{
   int i,j;
   if(readINI==NULL) return -1;
   char line[256];
   
   if(!seekLine(line, param))return -1;  
   char value[16]; memset(value, 0, 16);
   bool parse = false;
   bool strip = false;
   j=0;
   for(i=0;i<(int)strlen(line);i++)
   {
      if(parse)
      {
         if(line[i]!=' ')
            strip = true;
         
         if(strip && line[i] > 0x13)
         {
            value[j] = line[i];
            j++;
         }
      }
      if(line[i]=='=')
         parse = true;
   }
   return atoi(value);
} 

char* readIniFileString(char *file,char *param)//reminder it only search the first letter so testas would be read as test
{
   int i,j;
   if(readINI==NULL) return NULL;
   char line[256];

   char *value = (char*)malloc(256);memset(value, 0, 256);
   if(!seekLine(line, param))return NULL;    
   bool parse = false;
   bool strip = false;
   j=0;
   for(i=0;i<256;i++)
   {
      if(parse)
      {
         if(line[i]!=' ')
            strip = true;
         
         if(strip && line[i] > 0x13)
         {
            value[j] = line[i];
            j++;
         }
      }
      if(line[i]=='=')
      {
         parse = true;
      }   
   }
   return value;
}
//continuous reading 
// example: int Testnum= readIniFileInt("Testnum")
int ContreadIniFileInt(char *file,char *param)//reminder it only search the first letter so testas would be read as test
{
   int i,j;
   if(readINI==NULL) return -1;
   char line[256];
   fsetpos (readINI,&LevelIniPos);
   if(!ContseekLine(line, param))return -1;  
   fgetpos (readINI,&LevelIniPos);
   char value[16]; memset(value, 0, 16);
   bool parse = false;
   bool strip = false;
   j=0;
   for(i=0;i<(int)strlen(line);i++)
   {
      if(parse)
      {
         if(line[i]!=' ')
            strip = true;
         
         if(strip && line[i] > 0x13)
         {
            value[j] = line[i];
            j++;
         }
      }
      if(line[i]=='=')
         parse = true;
   }
   return atoi(value);
} 

char* ContreadIniFileString(char *file,char *param)//reminder it only search the first letter so testas would be read as test
{
   int i,j;
   if(readINI==NULL) return NULL;
   char line[256];

   char *value = (char*)malloc(256);memset(value, 0, 256);
   fsetpos (readINI,&LevelIniPos);
   if(!ContseekLine(line, param))return NULL;    
   fgetpos (readINI,&LevelIniPos);
   bool parse = false;
   bool strip = false;
   j=0;
   for(i=0;i<256;i++)
   {
      if(parse)
      {
         if(line[i]!=' ')
            strip = true;
         
         if(strip && line[i] > 0x13)
         {
            value[j] = line[i];
            j++;
         }
      }
      if(line[i]=='=')
      {
         parse = true;
      }   
   }
   return value;
}

