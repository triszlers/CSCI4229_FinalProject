#include "../HeaderFiles/Tools.h"
#include "../HeaderFiles/Import.h"


#define LEN 200  //  Maximum length of text string
void Tools::Print(const char* text, ...){
    char    buf[LEN];
    char*   ch=buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args,text);
    vsnprintf(buf,LEN,text,args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}