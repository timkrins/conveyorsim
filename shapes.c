/*|_|_|_ __ _(c)|2| ___ __|_|_ __  ___ 
| _|| | '_ ` _ \|0|/ / '__|@|a'_ \/ __|
| |_| | | | | | |1  <| |  |g|i| | \__ \
 \__|_|_| |_| | |2|\ \ |  |m|l| |_|__*/

// prototype generic drawing routines. these start at (0,0,0) centered and in the -Y.

void draw_sphere(float radius);
void draw_cuboid(float width, float height, float thick);
void draw_closed_cylinder(float radius, float thick);
void draw_centered_closed_cylinder(float radius, float thick);

//prototype generic coloring routines

void color_darken(void);

void color_darken(void){
// ###################################
// Darkens the current drawing colour.
// ###################################
glGetFloatv(GL_CURRENT_COLOR, colors);
glColor3f(colors[0]*0.95f, colors[1]*0.95f, colors[2]*0.95f);
};

void draw_closed_cylinder(float radius, float thick){
// ###################################
// Draws a closed cylinder from [zero] extending [thick]
// ###################################
glPushMatrix();
glRotatef(90,1,0,0);
gluCylinder(quadCylinder, radius, radius, thick, 32, 16);
color_darken();
glRotatef(180,0,1,0);
gluDisk(quadDisk, 0, radius, 32, 1);
glRotatef(-180,0,1,0);
glTranslatef(0,0,thick);
color_darken();
gluDisk(quadDisk, 0, radius, 32, 1);
glPopMatrix();
};

void draw_centered_closed_cylinder(float radius, float thick){
// ###################################
// Draws a [centered on zero] closed cylinder. Relys on closed_cylinder.
// ###################################
glPushMatrix();
glTranslatef(0,0,-(thick/2));
draw_closed_cylinder(radius, thick);
glPopMatrix();
}


void draw_sphere(float radius){
// ###################################
// Draws a [centered on zero] sphere.
// ###################################
gluSphere(quadSphere, radius, 32, 16);
}

void draw_cuboid(float width, float height, float thick){
// ###################################
// Draws a [centered on zeros] cubic thing, extending from [zero].
// ###################################
glPushMatrix();
 glBegin(GL_TRIANGLES);
   glVertex3f( (width/2), (height/2),0); //V1
   glVertex3f( (width/2),-(height/2),0); //V2
   glVertex3f( (width/2),-(height/2),thick); //V3
   glVertex3f( (width/2), (height/2),0); //V1
   glVertex3f( (width/2),-(height/2),thick); //V3
   glVertex3f( (width/2), (height/2),thick); //V4
   glVertex3f(-(width/2), (height/2),0); //V5
   glVertex3f( (width/2), (height/2),0); //V1
   glVertex3f( (width/2), (height/2),thick); //V4
   glVertex3f(-(width/2), (height/2),0); //V5
   glVertex3f( (width/2), (height/2),thick); //V4
   glVertex3f(-(width/2), (height/2),thick); //V8
   glVertex3f(-(width/2), (height/2),thick); //V8
   glVertex3f(-(width/2),-(height/2),thick); //V7
   glVertex3f(-(width/2),-(height/2),0); //V6
   glVertex3f(-(width/2), (height/2),thick); //V8
   glVertex3f(-(width/2),-(height/2),0); //V6
   glVertex3f(-(width/2), (height/2),0); //V5
   glVertex3f(-(width/2),-(height/2),thick); //V7
   glVertex3f( (width/2),-(height/2),0); //V2
   glVertex3f( (width/2),-(height/2),thick); //V3
   glVertex3f(-(width/2),-(height/2),thick); //V7
   glVertex3f(-(width/2),-(height/2),0); //V6
   glVertex3f( (width/2),-(height/2),0); //V2
  glEnd();
  glPopMatrix();
}

void draw_closed_cuboid(float width, float height, float thick){
// ###################################
// Draws a [centered on zeros] cubic thing, extending from [zero].
// ###################################
glPushMatrix();
glGetFloatv(GL_CURRENT_COLOR, colors);
 glBegin(GL_TRIANGLES);
 /*
   glVertex3f(-(width/2),0,(height/2)); //V1
   glVertex3f((width/2),0,(height/2)); //V2
   glVertex3f((width/2),0,-(height/2)); //V3
   glVertex3f(-(width/2),0,-(height/2)); //V4
   glVertex3f(-(width/2),0-thick,(height/2)); //V5
   glVertex3f((width/2),0-thick,(height/2)); //V6
   glVertex3f((width/2),0-thick,-(height/2)); //V7
   glVertex3f(-(width/2),0-thick,-(height/2)); //V8
   */
   
   //top
   glVertex3f(-(width/2),0, (height/2)); //V1
   glVertex3f(-(width/2),0,-(height/2)); //V4
   glVertex3f( (width/2),0, (height/2)); //V2
   glVertex3f(-(width/2),0,-(height/2)); //V4
   glVertex3f( (width/2),0,-(height/2)); //V3
   glVertex3f( (width/2),0, (height/2)); //V2
   
   //color_darken();
   
   glColor3f(colors[0]*0.95f, colors[1]*0.95f, colors[2]*0.95f);
   
   //side1
   glVertex3f(-(width/2),0,(height/2)); //V1
   glVertex3f( (width/2),0,(height/2)); //V2
   glVertex3f(-(width/2),0-thick,(height/2)); //V5
   glVertex3f( (width/2),0-thick,(height/2)); //V6
   glVertex3f(-(width/2),0-thick,(height/2)); //V5
   glVertex3f( (width/2),0,(height/2)); //V2
   
   glColor3f(colors[0]*0.85f, colors[1]*0.85f, colors[2]*0.85f);
   
   //side2
   glVertex3f( (width/2),0,(height/2)); //V2
   glVertex3f( (width/2),0,-(height/2)); //V3
   glVertex3f( (width/2),0-thick,(height/2)); //V6
   glVertex3f( (width/2),0,-(height/2)); //V3
   glVertex3f( (width/2),0-thick,-(height/2)); //V7
   glVertex3f( (width/2),0-thick,(height/2)); //V6

   glColor3f(colors[0]*0.75f, colors[1]*0.75f, colors[2]*0.75f);

   //side3

   glVertex3f( (width/2),0,-(height/2)); //V3
   glVertex3f(-(width/2),0-thick,-(height/2)); //V8
   glVertex3f( (width/2),0-thick,-(height/2)); //V7
   glVertex3f( (width/2),0,-(height/2)); //V3
   glVertex3f(-(width/2),0,-(height/2)); //V4
   glVertex3f(-(width/2),0-thick,-(height/2)); //V8

   glColor3f(colors[0]*0.65f, colors[1]*0.65f, colors[2]*0.65f);

   //side4
   glVertex3f(-(width/2),0,-(height/2)); //V4
   glVertex3f(-(width/2),0-thick,(height/2)); //V5
   glVertex3f(-(width/2),0-thick,-(height/2)); //V8
   glVertex3f(-(width/2),0,-(height/2)); //V4
   glVertex3f(-(width/2),0,(height/2)); //V1
   glVertex3f(-(width/2),0-thick,(height/2)); //V5
   
   glColor3f(colors[0]*0.55f, colors[1]*0.55f, colors[2]*0.55f);
   
   //bottom
   glVertex3f( (width/2),0-thick,-(height/2)); //V7
   glVertex3f(-(width/2),0-thick,-(height/2)); //V8
   glVertex3f( (width/2),0-thick, (height/2)); //V6
   glVertex3f(-(width/2),0-thick,-(height/2)); //V8
   glVertex3f(-(width/2),0-thick, (height/2)); //V5
   glVertex3f( (width/2),0-thick, (height/2)); //V6
   
  glEnd();
  glPopMatrix();
}

void draw_closed_triangle(float width, float height, float thick){
// ###################################
// Draws a [centered on zeros] cubic thing, extending from [zero].
// ###################################
glPushMatrix();

glGetFloatv(GL_CURRENT_COLOR, colors);

 glBegin(GL_TRIANGLES);
 /*
   glVertex3f(-(width/2),0,(height/3)); //V1
   glVertex3f((width/2),0,(height/3)); //V2
   glVertex3f(0,0,-((2*height)/3)); //V3
   glVertex3f(-(width/2),0-thick,(height/3)); //V4
   glVertex3f((width/2),0-thick,(height/3)); //V5
   glVertex3f(0,0-thick,-((2*height)/3)); //V6
   */
   
   //top
   glVertex3f(-(width/2),0,(height/2)); //V1
   glVertex3f(0,0,-((height)/2)); //V3
   glVertex3f((width/2),0,(height/2)); //V2

   glColor3f(colors[0]*0.95f, colors[1]*0.95f, colors[2]*0.95f);
   
   //side1
   glVertex3f(-(width/2),0,(height/2)); //V1
   glVertex3f((width/2),0,(height/2)); //V2
   glVertex3f(-(width/2),0-thick,(height/2)); //V4
   glVertex3f(-(width/2),0-thick,(height/2)); //V4
   glVertex3f((width/2),0,(height/2)); //V2
   glVertex3f((width/2),0-thick,(height/2)); //V5

   glColor3f(colors[0]*0.85f, colors[1]*0.85f, colors[2]*0.85f);


   //side2
   glVertex3f((width/2),0,(height/2)); //V2
   glVertex3f(0,0,-((height)/2)); //V3
   glVertex3f(0,0-thick,-((height)/2)); //V6
   glVertex3f(0,0-thick,-((height)/2)); //V6
   glVertex3f((width/2),0-thick,(height/2)); //V5
   glVertex3f((width/2),0,(height/2)); //V2

   glColor3f(colors[0]*0.75f, colors[1]*0.75f, colors[2]*0.75f);

   //side3
   glVertex3f(0,0,-((height)/2)); //V3
   glVertex3f(-(width/2),0,(height/2)); //V1
   glVertex3f(-(width/2),0-thick,(height/2)); //V4
   glVertex3f(-(width/2),0-thick,(height/2)); //V4
   glVertex3f(0,0-thick,-((height)/2)); //V6
   glVertex3f(0,0,-((height)/2)); //V3
   
   glColor3f(colors[0]*0.65f, colors[1]*0.65f, colors[2]*0.65f);
   
   //bottom
   glVertex3f(0,0-thick,-((height)/2)); //V6
   glVertex3f(-(width/2),0-thick,(height/2)); //V4
   glVertex3f((width/2),0-thick,(height/2)); //V5
   
  glEnd();
  glPopMatrix();
}