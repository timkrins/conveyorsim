/*|_|_|_ __ _(c)|2| ___ __|_|_ __  ___ 
| _|| | '_ ` _ \|0|/ / '__|@|a'_ \/ __|
| |_| | | | | | |1  <| |  |g|i| | \__ \
 \__|_|_| |_| | |2|\ \ |  |m|l| |_|__*/

//  define window constants

#define pion180 0.0174532925

const int window_width = 1300, window_height = 600;

// set up software variables

float colors[4];
int frame = 0;
char sprinter[50];
int holdingA, holdingB, holdingC, holdingD, holdingE, holdingF, holdingG, holdingH, holdingI, holdingJ, holdingK, holdingL, holdingM, holdingN, holdingO, holdingP, holdingQ, holdingR, holdingS, holdingT, holdingU, holdingV, holdingW, holdingX, holdingY, holdingZ;
int holding0, holding1, holding2, holding3, holding4, holding5, holding6, holding7, holding8, holding9, holding0;

GLUquadric *quadSphere;
GLUquadric *quadCylinder;
GLUquadric *quadDisk;
GLint slices, stacks;
GLint nsides, rings;
GLint fontOffset;

// set up robot variables

float conveyor_end_radius = 10.0f;
float conveyor_belt_thickness = 1.0f;
float conveyor_belt_width = 50.0f;
float conveyor_length = 200.0f;


//float multi = 1.0f;
float y_view = 10;

// set view variables
float view_lookat_x = 0.0f;
float view_lookat_y = 0;
float view_lookat_z = 0.0f;
float view_lookfrom_divide_x = -5.0f;
float view_lookfrom_divide_y = 5.0f;
float view_lookfrom_x = 0.0f;
float view_lookfrom_y = 0.0f;
float view_lookfrom_z = 12.0f;
float view_lookfrom_x_linear = 0.0f;
float view_lookfrom_y_linear = 20.0f;
float view_lookfrom_z_linear = 0.0f;
float view_distance_from_model = 90.0f;
float view_orientation = -1;

float view_momentum_x = 0.0f;
float view_momentum_y = 0.0f;
float view_momentum_z = 0.0f;