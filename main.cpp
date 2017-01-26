#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define KEY_ESC 27
#define pi 3.141592

int prayerX;

//回転角度theta
double theta = 0.0;
//視点の移動量
float dist = 0.0;

/*床　表面属性*/
float diffusePST[] = { 0.1, 0.35, 0.1, 1.0 };
float specularPST[] = { 0.45, 0.55, 0.45, 1.0 };
float ambientPST[] = { 0.0, 0.0, 0.0, 1.0 };
float shininessPST = 32;


//キーボードイベント
void myKeyboard(unsigned char key, int x, int y) {
	if (key == KEY_ESC)
		exit(0);
}

void specialkeydown(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		prayerX -= x*0.01;
	}

	else if (key == GLUT_KEY_RIGHT){
		prayerX += x*0.01;
	}
	else if (key == GLUT_KEY_LEFT && prayerX== -3){
		prayerX = -3;
	}
	else if (key == GLUT_KEY_RIGHT && prayerX == 3){
		prayerX = 3;
	}
}

//床を描く
void myfloor() {
	int i, j;

	glColor3d(1.0, 1.0, 1.0);
	/*glBegin(GL_LINES);
	for (i = -15; i<36; i += 2) {
	glVertex3i(i, 0, -35.0);
	glVertex3i(i, 0, 35.0);
	glVertex3i(-50.0, 0, i);
	glVertex3i(50.0, 0, i);
	}*/
	for (i = -100; i < 100; i++) {
		//x0 = 0.04 * (float)i;
		glBegin(GL_QUAD_STRIP);
		glNormal3f(0.0, 0.0, 1.0);
		for (j = -100; j < 100; j++) {
			//y0 = 0.04 * (float)j;
			glVertex3i(i, 0, -35.0);
			glVertex3i(i, 0, 35.0);
			glVertex3i(-50.0, 0, i);
			glVertex3i(50.0, 0, i);
			/*glVertex3f(x0, y0, 0.0);
			glVertex3f(x0 + 0.04, y0, 0.0);*/
		}
		glEnd();
	}
}

/*赤ポール*/
void redPorl(){
	glColor3d(1.0,0.8,0.4);
	//glTranslated(-3.0,3.0,10.0);
	glutSolidCone(20,3,20,10);

}

//描画関数
void display() {
	/*光関係*/
	GLfloat light0[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light1[] = { 0.0, 2.0, 1.0, 1.0 };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_POSITION, light0);
	glLightfv(GL_LIGHT1, GL_POSITION, light1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	

	glPushMatrix();
	gluLookAt(0.0, 1.0, dist, 0.0, 1.0, dist + 1.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(1.5, 2.0, 10.0);
	glRotatef(theta, 1.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(1.0);
	glPopMatrix();

	/*glPushMatrix();
	glRotatef(0.5*theta, 1.0, 0.0, 0.0);
	redPorl();
	glPopMatrix();
	*/

	glPushMatrix();
	glTranslatef(-1.5, 2.0, 20.0);
	glRotatef(2.0*theta, 1.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glutWireTorus(0.2, 1.0, 15, 30);
	
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 1.0, 30.0);
	glRotatef(3.0*theta, 0.2, -1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(1.0, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusePST);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularPST);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientPST);
	glMaterialf(GL_FRONT, GL_SHININESS, shininessPST);

	myfloor();

	glPopMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

//idle関数
void idle() {
	//  theta = fmod(theta+0.5, 360.0);
	//dist = fmod(dist + 0.05, 32.0); // 視点位置を前進
	glutPostRedisplay();
}

void initLighting(void){
	GLfloat  light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat  light0_specular[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat  light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat  light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat  spot_exp = 0;
	GLfloat  spot_cutoff = 30.0;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exp);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

//初期化
void myInit(char *progname) {
	int width = 640, height = 480;
	double aspect = (double)width / (double)height;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(progname);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(myKeyboard);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, aspect, 0.1, 40.0);

	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	initLighting();
	glLoadIdentity();

}

//メイン
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	myInit(argv[0]);
	glutDisplayFunc(display);
	glutSpecialFunc(specialkeydown);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
