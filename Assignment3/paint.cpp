/*
* CSCI 325 - Computer Graphics
* Aline Lais Gomes Tavares
* Assignment 3: User Interaction (Painting with Pixels)
*/


#include <cstdlib>
#include <ctime>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else		       
#include <GL/glut.h>         
#endif


int WIDTH = 700, HEIGHT = 700; //default window size
int square_x , square_y; //global for initial point where square is being drawn
int size = 10;
float color[3], bgcolor[3] = { 0.0, 0.0, 0.0 }; //vector with parameters that define brush color and bg color
bool TOGGLE_KEYBOARD = false, ERASE = false, DRAW_LINES = false, BLACKFLAG = true;
int previous_x, previous_y, initialx, initialy;
int polCount = 0;

/*Required empty display function*/
void display (void) {

}


/**/
void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WIDTH , 0.0, HEIGHT , -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glFlush();
}

/*Function to handle menu options: basically just change flags to modify program's behavior*/
void menuHandler (int option) {
	if (option == 1) {
		size = size + 5;
	} else if (option == 2) {
		size = size - 5;
	} else if (option == 3) {
		if (TOGGLE_KEYBOARD == false)
			TOGGLE_KEYBOARD = true;
		else 
			TOGGLE_KEYBOARD = false;
	} else if (option == 4) {
		if (ERASE == false) {
			ERASE = true;
		} else {
			ERASE  = false;
		}
			
	} else if (option == 6) {
		if (DRAW_LINES == true)
			DRAW_LINES = false;
		else if (DRAW_LINES == false)
			DRAW_LINES = true;

	} else if (option == 5) {
		exit(0);

	}
}

/*Menu Creator as seen in class*/
void createMenu(void){ 


	glutCreateMenu(menuHandler);

    glutAddMenuEntry("Larger", 1);
    glutAddMenuEntry("Smaller", 2);
    glutAddMenuEntry("Toggle Mode", 3);
    glutAddMenuEntry("Erase - On/Off", 4);
    glutAddMenuEntry("Draw Lines - On/Off", 6); 
    glutAddMenuEntry("Quit", 5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    //glutPostRedisplay();

}

/* Provide random colors */
void randomizeColors (){
	float r, a = 1.0;
	for (int i = 0; i< 3; i++) {
		r = (float)rand()/(float)(RAND_MAX) * a;
		color[i] = r;
	}
}

/* Function that draws the square (brush) */
void drawSquare (int x, int y) {
	/* Adjust y according to height of the screen */
	square_x = x;
	square_y = HEIGHT - y;

	/*check if it is going to use erase mode or not*/
	if (ERASE == false)
		randomizeColors();
	else {
		for (int i = 0; i< 3; i++)
			color[i] = bgcolor[i];
	}

	glColor3f (color[0], color[1], color[2]);

	glBegin(GL_POLYGON);
		glVertex2f(square_x, square_y);
		glVertex2f(square_x , square_y + size);
		glVertex2f(square_x + size, square_y + size );
		glVertex2f(square_x + size, square_y);
	glEnd();
	
	glFlush();

	glutPostRedisplay();

}

/* Function that draw lines in sequence */
void drawLines(int x, int y) {
	if (polCount == 0) {
		polCount++;
		initialx = x;
		initialy = HEIGHT - y;
		previous_x = x;
		previous_y = HEIGHT - y;
	} else if (polCount > 0) {
		polCount++;
 
		glLineWidth(3.0f);
		randomizeColors();
		glColor3f (color[0], color[1], color[2]);
		glBegin(GL_LINES);
	   	 	glVertex2i(previous_x, previous_y);
	    	glVertex2i(x, HEIGHT - y);
		glEnd();
		glFlush();

		previous_x = x;
		previous_y = HEIGHT - y;

		/* if it reached the initial point, the polygon will close and end line-mode */
		if (initialx == x || initialy == (HEIGHT - y)) {
			DRAW_LINES = false;
			polCount = 0;
		}
	}
	
	glutPostRedisplay();
}

/*Motion Callback */
void mouseMotion(int x, int y) {
	if (TOGGLE_KEYBOARD == false && DRAW_LINES == false) {
		drawSquare(x, y);
	}
}

/*Mouse Callback*/
void mouse(int button, int state, int x, int y) {
	/*If left button and square mode */
   	if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && DRAW_LINES == false) {
  		glutMotionFunc(mouseMotion);

  	/*If left button and line mode */
   	} else if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && DRAW_LINES == true) {
   		drawLines(x, y);

	/*If left button and toggle mode */
   	} else if (button == GLUT_LEFT_BUTTON && TOGGLE_KEYBOARD == true && DRAW_LINES == false) {
		drawSquare(x, y);
	}

}

/* Keyboard callback*/
void keyboard(unsigned char key, int x, int y) {
	/*Key C = clear screen */
	if (key == 'C' || key == 'c') {
		glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();		
	}
	/*Key B, clear + change background color */
	if (key == 'B' || key == 'b') {
		if (BLACKFLAG == true) {
		 bgcolor[0] = 1.0;
		 bgcolor[1] = 1.0;
		 bgcolor[2] = 1.0;
		 BLACKFLAG = false;
		} else {
			bgcolor[0] = 0.0;
			bgcolor[1] = 0.0;
			bgcolor[2] = 0.0;
			BLACKFLAG = true;
		}
		glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();		
	}

	/*Key E  = activate erase mode */
	if (key == 'e' || key == 'E' ) {
		if (ERASE == false) {
			ERASE = true;
		} else {
			ERASE  = false;
		}
	}
	
	glutPostRedisplay();
}
 

/**/
void reshape (int w, int h) {
	//fix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
	//
	WIDTH = w;
	HEIGHT = h;
	glViewport(0, 0, WIDTH, HEIGHT);
	glutPostRedisplay(); 
}
 
/**/
int main (int argc, char** argv) {
	

	srand (static_cast <unsigned> (time(0)));

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(0,0);

	glutCreateWindow("Basic Paint");

	glutReshapeFunc(reshape);

	

	//Functions with callbacks for interaction

	glutMouseFunc(mouse);

	glutKeyboardFunc(keyboard);

	glutDisplayFunc(display);


	createMenu();

	init();

	glutMainLoop();


	return 0;
}