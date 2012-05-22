/*|_|_|_ __ _(c)|2| ___ __|_|_ __  ___ 
| _|| | '_ ` _ \|0|/ / '__|@|a'_ \/ __|
| |_| | | | | | |1  <| |  |g|i| | \__ \
 \__|_|_| |_| | |2|\ \ |  |m|l| |_|__*/

// ###################################
// This is a conveyor belt simulator.
// Implements OpenGL, GLFW and GLU.
// Use the controls WASDQE for viewpoint.
// ###################################

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <math.h>
#define   MAXZERO  0.0
#define neg 0.00001f

// protoype software functions

void quit(void);
void variables_init(void);
void graphics_init(void);
void graphics_draw(void);
void graphics_loop(void);
void handleMouseClick(int button, int action);
void handleKeypress(int theKey, int theAction);
int calculate_delta(void);

// prototype the drawing functions

void draw_text_layers(void);
void draw_conveyor(void);

//##################################################
// Bring in external source files.
// I have orginised these to make it easier to code.
// #################################################
#include "constants.c"
#include "shapes.c"
#include "text.c"
#include "belt.c"

 
void quit(void){
// #####################
// Quits the application
// #####################
glfwTerminate();
exit(0);
}

void graphics_init(void) {
// ###############################
// Initialise the graphics window.
// ###############################
if (glfwInit() != GL_TRUE) {
  quit();
}
glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4);
if(glfwOpenWindow( window_width,window_height,8,8,8,8,24,8,GLFW_WINDOW ) != GL_TRUE) {
  quit();
}
glfwOpenWindowHint( GLFW_FSAA_SAMPLES, 4);
glEnable( GL_MULTISAMPLE );
glEnable( GL_BLEND );
glEnable( GL_DEPTH_TEST );
glfwSetWindowTitle("Conveyor Belt Simulator by Tim K");
glMatrixMode(GL_PROJECTION);
glFrontFace(GL_CW);
glPolygonMode(GL_FRONT, GL_FILL);
//glPolygonMode(GL_FRONT, GL_LINE);
//glPolygonMode(GL_BACK, GL_LINE);

glLoadIdentity();
float aspect_ratio = ((float)window_height) / window_width;

glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 500);

glMatrixMode(GL_MODELVIEW);
glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); // Preset color
makeBitmapFonts();
quadCylinder=gluNewQuadric();
quadSphere=gluNewQuadric();
quadDisk=gluNewQuadric();
glfwSetKeyCallback(handleKeypress);
};


void handleKeypress(int theKey, int theAction){
// #################################################
// Process the keyboard callback and set key states.
// #################################################
if (theAction == GLFW_PRESS){
    switch(theKey){
    case 'A': holdingA = 1; break;
    case 'B': holdingB = 1; break;
    case 'C': holdingC = 1; break;
    case 'D': holdingD = 1; break;
    case 'E': holdingE = 1; break;
    case 'F': holdingF = 1; break;
    case 'G': holdingG = 1; break;
    case 'H': holdingH = 1; break;
    case 'I': holdingI = 1; break;
    case 'J': holdingJ = 1; break;
    case 'K': holdingK = 1; break;
    case 'L': holdingL = 1; break;
    case 'M': holdingM = 1; break;
    case 'N': holdingN = 1; break;
    case 'O': holdingO = 1; break;
    case 'P': holdingP = 1; break;
    case 'Q': holdingQ = 1; break;
    case 'R': holdingR = 1; break;
    case 'S': holdingS = 1; break;
    case 'T': holdingT = 1; break;
    case 'U': holdingU = 1; break;
    case 'V': holdingV = 1; break;
    case 'W': holdingW = 1; break;
    case 'X': holdingX = 1; break;
    case 'Y': holdingY = 1; break;
    case 'Z': holdingZ = 1; break;
    case '1': holding1 = 1; break;
    case '2': holding2 = 1; break;
    case '3': holding3 = 1; break;
    case '4': holding4 = 1; break;
    case '5': holding5 = 1; break;
    case '6': holding6 = 1; break;
    case '7': holding7 = 1; break;
    case '8': holding8 = 1; break;
    case '9': holding9 = 1; break;
    case '0': holding0 = 1; break;
    case 257: quit(); break;
    
    default: printf("%d key not used\n", theKey); break;
    }
  } else {
    switch(theKey){
    case 'A': holdingA = 0; break;
    case 'B': holdingB = 0; break;
    case 'C': holdingC = 0; break;
    case 'D': holdingD = 0; break;
    case 'E': holdingE = 0; break;
    case 'F': holdingF = 0; break;
    case 'G': holdingG = 0; break;
    case 'H': holdingH = 0; break;
    case 'I': holdingI = 0; break;
    case 'J': holdingJ = 0; break;
    case 'K': holdingK = 0; break;
    case 'L': holdingL = 0; break;
    case 'M': holdingM = 0; break;
    case 'N': holdingN = 0; break;
    case 'O': holdingO = 0; break;
    case 'P': holdingP = 0; break;
    case 'Q': holdingQ = 0; break;
    case 'R': holdingR = 0; break;
    case 'S': holdingS = 0; break;
    case 'T': holdingT = 0; break;
    case 'U': holdingU = 0; break;
    case 'V': holdingV = 0; break;
    case 'W': holdingW = 0; break;
    case 'X': holdingX = 0; break;
    case 'Y': holdingY = 0; break;
    case 'Z': holdingZ = 0; break;
    case '1': holding1 = 0; break;
    case '2': holding2 = 0; break;
    case '3': holding3 = 0; break;
    case '4': holding4 = 0; break;
    case '5': holding5 = 0; break;
    case '6': holding6 = 0; break;
    case '7': holding7 = 0; break;
    case '8': holding8 = 0; break;
    case '9': holding9 = 0; break;
    case '0': holding0 = 0; break;
    
    default: break;
    };
  };
};

void update_view(void){
// #############################################################
// These functions implement the momentum of the camera.
//
// In a perfect world where I have infinity time and motivation,
// I would like to have used the Boost Preprocessor library
// and create these functions using a macro.
// but for now, and for simplicitys sake, copy and paste yeah!
// #############################################################
view_lookfrom_x_linear += view_momentum_x;
if((view_momentum_x > 0.01)||(view_momentum_x < -0.01)) {
  view_momentum_x = view_momentum_x/1.05;
} else {
  view_momentum_x = 0.0;
};

view_lookfrom_y_linear += view_momentum_y;
if((view_momentum_y > 0.01)||(view_momentum_y < -0.01)) {
  view_momentum_y = view_momentum_y/1.05;
} else {
  view_momentum_y = 0.0;
};

view_distance_from_model += view_momentum_z;
if((view_momentum_z > 0.01)||(view_momentum_z < -0.01)) {
  view_momentum_z = view_momentum_z/1.05;
} else {
  view_momentum_z = 0.0;
};
    
// ##########################
// Don't get too close now...
// ##########################
    
if(view_distance_from_model < 10){
  view_momentum_z = 0;
  view_distance_from_model = 10;
};
// #######################
// These keys add momentum
// #######################
if(holdingA) { view_momentum_x += 0.1; };
if(holdingD) { view_momentum_x -= 0.1; };
if(holdingS) { view_momentum_y += 0.1; };
if(holdingW) { view_momentum_y -= 0.1; };
if(holdingQ) { view_momentum_z +=0.1; };
if(holdingE) { view_momentum_z -=0.1; };
    
// ##########################################################
// This code here flips the up direction so the model doesn't
// spaz out when you pass directly over it.
// ##########################################################
if((view_lookfrom_y_linear > 90)||(view_lookfrom_y_linear < -90)){
  view_orientation = -1;
} else {
  view_orientation = 1;
};

if(view_lookfrom_y_linear > 180){
  view_orientation = -1;
  view_lookfrom_y_linear = -179.9;
} else {
  if(view_lookfrom_y_linear < -180){
    view_orientation = -1;
    view_lookfrom_y_linear = 179.9;
  };
};
if(view_lookfrom_x_linear > 180){
  view_lookfrom_x_linear = -179.9;
} else {
  if(view_lookfrom_x_linear < -180){
    view_lookfrom_x_linear = 179.9;
  };
};

if(holdingZ) {y_view += 0.5;};
if(holdingX) {y_view -= 0.5;};

//if(holdingESC) {quit();};

// ###################################
// Calculate the camera's coordinates.
// ###################################
view_lookfrom_x = cos(view_lookfrom_x_linear*pion180)*cos(view_lookfrom_y_linear*pion180)*view_distance_from_model;
view_lookfrom_y = sin(view_lookfrom_y_linear*pion180)*view_distance_from_model;
view_lookfrom_z = cos(view_lookfrom_y_linear*pion180)*sin(view_lookfrom_x_linear*pion180)*view_distance_from_model;
};

void graphics_draw(void) {
// ###############################################
// Positions the camera and renders to the buffer.
// ###############################################
glLoadIdentity();
update_view();

gluLookAt(view_lookfrom_x, view_lookfrom_y - y_view, view_lookfrom_z,view_lookat_x, view_lookat_y - y_view, view_lookat_z,0.0f, view_orientation, 0.0f);

// !!!!!!!!!!!!!!!!!!!!!!
// Draw all things here.
// !!!!!!!!!!!!!!!!!!!!!!

draw_conveyor();
draw_text_layers();

// !!!!!!!!!!!!!!!!!!!!!!!!!
// Stop drawing things here.
// !!!!!!!!!!!!!!!!!!!!!!!!!

};

void graphics_loop(void) {
// #############################################################
// This is the loop that swaps the buffers and draws the screen.
// #############################################################
while(glfwGetWindowParam(GLFW_OPENED)){
  glfwSleep(0.01);
  if(glfwGetWindowParam(GLFW_ACTIVE) == GL_FALSE){
  glfwSleep(0.5);
  };
  frame++;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  graphics_draw();
  glfwSwapBuffers();
  };
};

int main(void){
// ######################################################
// This is the main loop, the entry point of the program.
// ######################################################
init_items();
graphics_init();
graphics_loop();
quit();
};


