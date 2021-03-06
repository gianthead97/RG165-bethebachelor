#include <cstdio>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "callbackfuncs.hpp"


float ind_for_colors = 0, u = 0, v = 3.14, y_pos = 1.4, x_pos = 0, z_pos = -0.1, lracceleration = 0.08;
bool downing = false;
int look_id = 1, timer_activeX = 0, timer_activeZ = 0, jump_active = 0, colour_counter = 0, direction_keeper = 0;

Camera camera;
extern GLuint names[40];
extern GLuint parquet;
extern GLfloat diffuse_coeffs[7][4];
extern GLfloat specular_coeffs[4];
extern unsigned courses_left;
extern bool on_head;




void Student::draw() {

    glPushMatrix();

    z_front = z_pos;
    x_front = x_pos;
    y_front = 0.71;

	//Kretanje u jump modu
    if (jump_active) {
        y_front += 1.3 * sin(u);
        glTranslatef(x_pos, y_pos + 3 * sin(u), z_pos);
        u += .1;
    } else if (downing) {
		//Kretanje u delu kada se pada sa grede
		y_pos -= .1;
		glTranslatef(x_pos, y_pos, z_pos);	
		if (y_pos <= 1.4 + 0.1 and y_pos >= 1.4 - 0.1) {
			downing = false;
			y_pos = 1.4;
		}
	}
    else {
		//Klasicno kretanje
        y_front = 0;
        glTranslatef(x_pos, y_pos, z_pos);
    }




    angle += 6;
    GLfloat head_col[4] = {0, .1, 1, 0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, head_col);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, head_col);
    glLightfv(GL_LIGHT0, GL_SPECULAR, head_col);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs[colour_counter]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);


    glutSolidSphere(.15, 100, 100);



    GLfloat body_col[4] = {.4, 1, 1, 0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, body_col);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, body_col);
    glLightfv(GL_LIGHT0, GL_SPECULAR, body_col);


    //Iscrtavanje trupa
    glTranslatef(0, -0.4, 0);
    glScalef(3/4., 1, .8);
    glutSolidCube(0.5);
    glScalef(4/3., 1, 10/8);




    glLightfv(GL_LIGHT0, GL_AMBIENT, head_col);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, head_col);
    glLightfv(GL_LIGHT0, GL_SPECULAR, head_col);


    //Iscrtavanje ekstrimiteta
    //Ceo ovaj deo koda je bio potpuno stelovanje
	//da se sve sklopi jedno sa drugim i da kretanje
	//deluje sto prirodnije
	if (legs_angle > 70)
        direction = -1;
    else if (legs_angle < -70)
        direction = 1;


    legs_angle += (5.8 * direction);
    glRotatef(legs_angle/3, 1, 0, 0);

    glTranslatef(0, -0.55, 0);
    glTranslatef(-0.125, 0, 0);
    glScalef(1, 3, 1);
    glutSolidCube(0.2);
    glScalef(1, 1/3., 1);

    glTranslatef(0.25, 0, 0);

    glTranslatef(0, 0.55, 0);

    glRotatef(-2*legs_angle/3, 1, 0, 0);
    glTranslatef(0, -0.55, 0);

    glScalef(1, 3, 1);
    glutSolidCube(0.2);
    glScalef(1, 1/3., 1);


    //Iscrtavanje ruku
    glTranslatef(-.4, .65, -0.2);
    glScalef(.35, .3, .8);
    glutSolidCube(0.5);
    glScalef(10/3.5, 10/3.0, 10/8.0);
    glTranslatef(.55, 0, 0);
    glTranslatef(0, 0, 0.2);
    glRotatef(legs_angle, 1, 0, 0);
    glTranslatef(0, 0, -0.2);
    glScalef(.35, .3, .8);

    glutSolidCube(0.5);

    glPopMatrix();

	//KRAJ KRITICNOG DELA



	//Provera da li je zavrsen skok i da l i je moguce se vratiti
	//u regularno kretanje
    if (!on_head and (jump_active == 1 and u >= 3.14)) {

        jump_active = 0;
        u = 0;
        timer_activeX = direction_keeper;
        glutTimerFunc(50, on_timer, 0);
    } else if (on_head and jump_active == 1 ) {
		//Obezbednjivanje ostajanja na gredi u slucaju skoka na nju
        jump_active = 0;
        u = 0;
        timer_activeX = direction_keeper;
        glutTimerFunc(50, on_timer, 0);
	}

}

void change_colour(void) {
    colour_counter = (colour_counter + 1) % 6;
}

void Plane::draw(){
    glPushMatrix();
	
	  
    glTranslatef(0, 0, z_pos/3);
  
	glScalef(1.5, 0.05, 1);

	
	float tmp_y = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, parquet);
	//300 puta se staticki iscrtava podloga
	//jer nije dovoljno velika rezolucija slike 
	//za teksturu kako bi mogli iz jednog dela
	for (int i = 0; i < 300; i++) {
		glBegin(GL_POLYGON);
			glTexCoord2f(0, 0);
			glVertex3f(-3, tmp_y, 15 - i * 25);
			glTexCoord2f(1, 0);
			glVertex3f(3, tmp_y, 15 - i * 25);
			glTexCoord2f(1, 1);
			glVertex3f(3, tmp_y, -10 - i * 25);
			glTexCoord2f(0, 1);
			glVertex3f(-3, tmp_y, -10 - i * 25);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();    
	
}


//Iscrtvanje tokena koji se sastoji iz jednog valjka
//i dva diska kao poklopac
void Coin::draw() {
    GLfloat coin_color[4] = {1, 1, 0, 0};

	glEnable(GL_TEXTURE_2D);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, coin_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, coin_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, coin_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, coin_color);

    glPushMatrix();
    GLUquadric* gluQ = gluNewQuadric();

    glShadeModel(GL_SMOOTH);
    glTranslatef(x_position, 0.42, z_position);
    x_front = x_position;
    y_front = 0;
    z_front = z_position;
    glRotatef(angle, 0, 1, 0);
    angle += 6;
    gluCylinder(gluQ, cyl_base, cyl_top, cyl_height, cyl_slices, cyl_stacks);


    glBindTexture(GL_TEXTURE_2D, names[inx]);
    gluQuadricDrawStyle(gluQ, GL_FILL);
    gluQuadricTexture(gluQ, GL_TRUE);
    gluQuadricNormals(gluQ, GLU_SMOOTH);

    gluDisk(gluQ, disk_inner, disk_outer, disk_slices, disk_loops);

    glTranslatef(0, 0, cyl_height);

    gluDisk(gluQ, disk_inner, disk_outer, disk_slices, disk_loops);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

Coin::Coin(const std::string &name, GLdouble disk_inner, GLdouble disk_outer, GLuint disk_slices,
                  GLuint disk_loops, GLdouble cyl_base, GLdouble cyl_top, GLdouble cyl_height, GLuint cyl_slices,
                  GLuint cyl_stacks, float z, float x, std::string s, unsigned u)
        : name(name), disk_inner(disk_inner),
           disk_outer(disk_outer), disk_slices(disk_slices), disk_loops(disk_loops), cyl_base(cyl_base),
           cyl_top(cyl_top), cyl_height(cyl_height), cyl_slices(cyl_slices), cyl_stacks(cyl_stacks),
            z_position(z), x_position(x), professor(s), inx(u){}


//Ovo je u sustini glavna provera da li je doslo do kolizije
//izmedju studenta i tokena
bool Coin::touched(GLdouble student_x_front, GLdouble student_x_back, GLdouble student_y_front,
              GLdouble student_y_back, GLdouble student_z_front, GLdouble studnet_z_back) const {
    double epsilon_x = 0.20;
    double epsilon_y = 0.05;
    double epsilon_z = 0.30;
    bool A = student_x_front > x_front - epsilon_x and student_x_front < x_front + epsilon_x;
    bool B = student_y_front > y_front - epsilon_y and student_y_front < y_front + epsilon_y;
    bool C = student_z_front > z_front - epsilon_z and student_z_front < z_front + epsilon_z;

    if (A and B and C and !passed) {
        courses_left--;
        return true;
    }
    else
        return false;
}
