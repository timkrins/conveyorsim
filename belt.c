/*|_|_|_ __ _(c)|2| ___ __|_|_ __  ___ 
| _|| | '_ ` _ \|0|/ / '__|@|a'_ \/ __|
| |_| | | | | | |1  <| |  |g|i| | \__ \
 \__|_|_| |_| | |2|\ \ |  |m|l| |_|__*/

// ###################################
// This is a belt simulator.
// Implements OpenGL, GLFW and GLU.
// Use the controls WASDQE for viewpoint.
// ###################################

#include <limits.h>

#define PI 3.14159265
                        
#define color_chunk(c) if(i == 0) { glColor3f(c, 0, 0); } \
                       if(i == 1) { glColor3f(0, c, 0); } \
                       if(i == 2) { glColor3f(0, 0, c); }
                       

typedef struct {
    int status;
    int type;
    float x;
    float y;
    float z;
    float width;
    float thick;
    int color;
    int r_y;
    int r_x;
    int order;
} item;

typedef struct {
    int all;
    int dispenser;
    float dispenser_height;
    int conveyor;
    int end_conveyor;
    int picked;
    int falling;
    int fallen;
    float fallen_height;
} count;

count counts;

item items[200];
int items_made = 0;
float swivel = 0;
double first_timer, second_timer, third_timer;

void add_item(int status,int type, int color, float width, float thick,  float x, float y, float z,int r_y, int r_x) {
items[items_made].status = status;
int order = 0;
if(status == 1) { order = counts.dispenser++; counts.dispenser_height += thick;}
if(status == 2) { order = counts.conveyor++; }
if(status == 3) { counts.picked++; }
if(status == 5) { order = counts.fallen++; counts.fallen_height += thick;}
items[items_made].type = type;
items[items_made].color = color;
items[items_made].width = width;
items[items_made].thick = thick;
items[items_made].x = x;
items[items_made].y = y;
items[items_made].z = z;
items[items_made].r_y = r_y;
items[items_made].r_x = r_x;
items[items_made].order = order;
items_made++;
};

void init_items(void){
//add_item(status,type,color,width,thick,x,y,z,rx,ry,order)
//too annoying to create a variadic function.
add_item(1,1,1,5,2,5,0,0,0,0); // red circle on dispenser
add_item(1,2,2,5,2,11,0,0,90,0); // green triangle on dispenser
add_item(1,3,3,5,2,17,0,0,0,0); // blue square on dispenser
add_item(1,2,3,5,2,0,0,0,0,0); // blue circle in dispenser
add_item(1,3,2,5,2,0,0,0,0,0); // green square in dispenser
add_item(1,3,1,5,2,0,0,0,0,0); // red square in dispenser
add_item(1,1,2,5,2,0,0,0,0,0); // green circle in dispenser
add_item(1,1,3,5,2,0,0,0,0,0); // blue circle in dispenser
}

float dispenser_y = 5.0f;
float dispenser_x = 5.0f;
float dispenser_z = 5.0f;
float belt_y = 0.0f;
float picker_y = 10.0f;
float table_width = 10;
float table_radius = 5;
float table_length = 50;
float table_thick = 1;
float conveyor_speed = -0.1;
float floor_y = -20;

void fill_dispenser(void){ // grab stacked items on floor and fill dispenser
for (int j = 0; j < items_made; j++){
//if(items[j].status != 1){
if(items[j].status == 5){
if(items[j].status == 5){ // was stacked on floor
counts.fallen_height -= items[j].thick;
counts.fallen--;
printf("Stack Height Now:%f\n", counts.fallen_height);
}
items[j].status = 1;
items[j].order = counts.dispenser;
counts.dispenser++;
counts.dispenser_height += items[j].thick;
}
}
}

void fill_dispenser_single(void){ // grab stacked items on floor and fill dispenser
for (int j = 0; j < items_made; j++){
if(items[j].order == 0){
if(items[j].status == 5){
if(items[j].status == 5){ // was stacked on floor
counts.fallen_height -= items[j].thick;
counts.fallen--;
//printf("Stack Height Now:%f\n", counts.fallen_height);
}
items[j].status = 1;
items[j].order = counts.dispenser;
counts.dispenser++;
counts.dispenser_height += items[j].thick;
}
} else {
items[j].order--;
}
}
}

void dispense(void){
for (int j = 0; j < items_made; j++){
if(items[j].status == 1){ // in dispensor only duh
if(items[j].order == 0){
items[j].status = 2; // place on conveyor
counts.dispenser--; // decrease if it is dispensed.
counts.dispenser_height -= items[j].thick;
} else {
items[j].order--;
}
}
}

}

void process_items(void){
//Process all positions here.
int possible_items = sizeof(items);
//calculate the counts

//counts.all = 0;
//counts.dispenser = 0;
//counts.dispenser_height = 0;
//counts.conveyor = 0;
//counts.end_conveyor = 0;
//counts.picked = 0;
//counts.falling = 0;
//counts.fallen = 0;
//counts.fallen_height = 0;

for(int i = 0; i < items_made; i++){


if(items[i].status == 1) {
// ##### in the dispenser #######

items[i].r_x = 0;
items[i].r_y = 0;
items[i].x = dispenser_x;
items[i].z = dispenser_z;
items[i].y = dispenser_y + (items[i].order*items[i].thick);
//printf("ahaha y%f-%f-%f\n", items[i].y, items[i].x, items[i].z);
};


if(items[i].status == 2) {
// ####### on the conveyor ##########
if(items[i].x < -(table_length/2)){
//rolled off the flat
items[i].status = 6;
counts.end_conveyor++;
items[i].order = counts.end_conveyor;
} else {
//still on conveyor
counts.conveyor++;
items[i].x += conveyor_speed;
items[i].y = belt_y;
};
};


if(items[i].status == 3) {
// ###### picked by picker ###########
//counts.picked++;
items[i].y = belt_y + picker_y;
};


if(items[i].status == 4) {
// ######### falling through the air #########
if(items[i].y > (floor_y+(counts.fallen_height)+items[i].thick)) {
//counts.falling++;
// fall
items[i].y -= 0.5f;
} else {
//fallen
items[i].order = counts.fallen;
items[i].r_x = 0;
items[i].status = 5;
counts.fallen++;
counts.fallen_height += items[i].thick;
};
};


if(items[i].status == 5) {
// ######### fallen to ground - aka. stacked ##########
items[i].y = floor_y + items[i].order*items[i].thick;
};


if(items[i].status == 6) {
// ######## rolling off conveyor ###########
if((items[i].x <= -((table_length/2)+table_radius))||(items[i].y <= 0-table_radius)) {
//rolled off the edge, now is falling
counts.falling++;
items[i].order = counts.falling;
items[i].status = 4;
} else {
//rotating around the radius


// a:  -(table_length/2) is the negative position of the crossover
// b: items[i].x is going to be a negative position, greater than a.
// the x movement will be 1.0* at (x = a), and the angle 0degrees
// the x movement will be zero at (x = a-r), and the angle -90degrees.
// the y movement will be 0.0* at (x = a)
// the y movement will be 1.0* at (x = a-r)
//
//      x
//      a
//      __________________________________
//    /    \
//   |_r_   |       all in the x (x-a = 0)
//    \    /

//   x
//      a
//      __________________________________
//    /    \
//   |_r_   |       all in the y (x-a = r)
//    \    /

// So I will want to use ((x-a)/r). zero when up top, one when at bottom.

// use atan2.
// use the cosine for x and sine for y

// cos(0degrees) = 1
// find the zero angle though.
// tan(angle) = o / a
// atan((x-a)/r)
// atan(0) = 0

// cos(-90degrees) = 0
// tan(angle) = o / a
// tan(-90degrees) = undefined
// atan((x-a)/r)
// atan(-1) = -1

//atan2(opposite, adjacent) = angle_to_use

//      ____
//     |\
//    e| \c
//     |  \
//     |   \
//       d
//


items[i].x += conveyor_speed*cos(atan2((items[i].x-(-(table_length/2))),items[i].y+table_radius));
items[i].y -= conveyor_speed*sin(atan2((items[i].x-(-(table_length/2))),items[i].y+table_radius));
items[i].r_x = atan2((items[i].x-(-(table_length/2))),items[i].y+table_radius)/(PI/180);
}
counts.all = counts.dispenser+counts.conveyor+counts.picked+counts.falling+counts.fallen;
};



}
}

void calculate(void);

void conveyor_base(void);
void conveyor_sections(void);

//void drop_item(void);

void conveyor_left(void){
conveyor_speed = -0.1;
}

void conveyor_right(void){
conveyor_speed = 0.1;
}

void conveyor_stop(void){
conveyor_speed = 0.0;
}

void list_items(void){
for (int j = 0; j < items_made; j++){
printf("Item:%d | Type:%d | Status:%d | Order: %d | Position: X%.2f,Y%.2f,Z%.2f\n", j,items[j].type,items[j].status,items[j].order,items[j].x,items[j].y,items[j].z);
}
printf("_______________________\n");

}

void draw_items(void){
for (int j = 0; j < items_made; j++){
glPushMatrix();{
glColor3f(0, 0, 1);
glTranslated(items[j].z, items[j].y, items[j].x);
glRotatef(items[j].r_x,1,0,0);
glRotated(items[j].r_y,0,1,0);
//printf("item:%d, zrotation%f\n", j, items[j].r_x);


switch(items[j].color){
    case 1: glColor3f(1, 0, 0); break;
    case 2: glColor3f(0, 1, 0); break;
    case 3: glColor3f(0, 0, 1); break;
    default: break;
    }

switch(items[j].type){
    case 1: draw_closed_cylinder(items[j].width/2.0, items[j].thick); break;
    case 2: draw_closed_triangle(items[j].width*0.866025404,items[j].width,items[j].thick); break;
    case 3: draw_closed_cuboid(items[j].width,items[j].width,items[j].thick); break;
    default: break;
    }
    
glPopMatrix();}
}
}

void draw_table(void){
glPushMatrix();
glColor3f(0.5, 0.5, 0.5);
glTranslated(0, -(table_thick*2), 0);
draw_closed_cuboid(table_width,table_length,table_thick);
glPopMatrix();
}


/*
void drop_item(void){
int k = 0;
if(item_count < 40) {
items[item_count][0] = 1;
items[item_count][1] = k;
items[item_count][2] = item_count ;
items[item_count][3] = (rand()/(int)(((unsigned)RAND_MAX + 1) / 10))-5;
items[item_count][4] = 0;
if(k++ > 2) {k = 0;}
printf("item %d dropped. item type:%d, position: x%d,y%d,z%d\n", item_count,items[item_count][1],items[item_count][2],items[item_count][3],items[item_count][4]);
item_count++;
} else {
printf("overflow!\n");
item_count = 0;
}
}
*/

void move_dispenser(void){
//nada
}

void every_second(void){
if((glfwGetTime() - first_timer) > 1){
dispense();
first_timer = glfwGetTime();
}

if((glfwGetTime() - second_timer) > 0.02){
swivel += 0.06;
dispenser_z = 4*sin(swivel);
second_timer = glfwGetTime();
}

if((glfwGetTime() - third_timer) > 15){
fill_dispenser();
third_timer = glfwGetTime();
}
}

void draw_conveyor(void){
// ######################
// Called from other function.
// Draws the conveyor.
// ######################
/*
if(holdingC == 1) {
drop_item();
}
*/

process_items();

if(holdingN == 1) {
conveyor_left();
}

if(holdingM == 1) {
conveyor_right();
}

if(holdingB == 1) {
conveyor_stop();
}

if(holdingR == 1){
fill_dispenser();
}



if(holdingT == 1){

//double current_time = glfwGetTime();

dispense();

}

if(holdingP == 1) {
list_items();
}

glPushMatrix();{

move_dispenser();
draw_table();
draw_items();
every_second();

glPopMatrix();}
}