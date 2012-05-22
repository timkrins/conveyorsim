/*|_|_|_ __ _(c)|2| ___ __|_|_ __  ___ 
| _|| | '_ ` _ \|0|/ / '__|@|a'_ \/ __|
| |_| | | | | | |1  <| |  |g|i| | \__ \
 \__|_|_| |_| | |2|\ \ |  |m|l| |_|__*/

// set up bitmap font

#include "bitmap.c"


#define red glColor3f(0.9, 0.1, 0.1)
#define green glColor3f(0.1, 0.9, 0.1)
#define blue glColor3f(0.1, 0.1, 0.9)


void makeBitmapFonts(void){
// ########################
// Create the bitmap fonts.
// ########################
GLint i;
glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
fontOffset = glGenLists(128);
for (i = 32; i < 127; i++) {
    glNewList(i+fontOffset, GL_COMPILE);
        glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, bitmap_font[i-32]);
    glEndList();
};
};

void printString(char *s){
// #############################################################
// Prints a string using bitmap fonts at current raster location
// #############################################################
glPushAttrib (GL_LIST_BIT);
glListBase(fontOffset);
glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
glPopAttrib();
};

int line_pos(int lines){
int margin = 6;
return (lines*13)+margin;
}

void left_align_text(int pos, char *charlies){
glRasterPos2f(6 ,line_pos(pos));   printString(charlies);
}

void right_align_text(int pos, char *charlies){
int index = 0;
for(index = 0; charlies[index] != 0; index++);
int text_width = index * 10;
int xpos = window_width - text_width;
glRasterPos2f(xpos - 6 ,line_pos(pos));   printString(charlies);
}

void centre_align_text(int pos, char *charlies){
int index = 0;
for(index = 0; charlies[index] != 0; index++);
int text_width = index * 10;
int xpos = (window_width/2) - (text_width/2);
glRasterPos2f(xpos ,line_pos(pos));   printString(charlies);
}

char * make_text(int number_int){
memset(sprinter, 0, sizeof(sprinter));
sprintf(sprinter, "%d", number_int);
return sprinter;
}

void draw_text_layers(void) {
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
glOrtho(0,window_width,0,window_height,0,1);
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();

    glColor3f(0.2, 0.9, 0.2);
    left_align_text(0, "OpenGL Conveyor Simulator");
    
    glColor3f(0.5, 0.9, 0.5);
    right_align_text(0, "(c) 2012 TimKrins. For personal use only.");
    
    int current_line_height = 40;
    
    char text_str[50];
    memset(text_str, 0, sizeof(text_str));
    
    current_line_height = 15;
    
    glColor3f(0.8, 0.8, 0.8);
    right_align_text(current_line_height--, "[W,A,S,D] to orbit");
    right_align_text(current_line_height--, "[Q,E] to zoom");
    right_align_text(current_line_height--, "[Z,X] to change vertical orbit position");
     
    
    
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
};