#include "StdAfx.h"
#include "CollisionDetect.h"
#include <gl/glut.h> 
#include <iostream>
#include <fstream> 
  
using namespace std;  
  
const int g_window_size = 512;    
const char* g_app_string = "collision test";  

enum ShowCase {obb, sector, empty}g_showcase = empty;
enum ChgType {chgdir, chgsize, chgpos}g_chgtype = chgpos;
bool SelectCircle = true;
bool markDown = false;

int64 Cpos;
Vector2 Cpoint;
bool isCollide = false;

OBB g_obb;
Sector g_sector;
Vector2 g_circle = Vector2(200, 200);
int64 g_circleRadius = 50;
Vector2 g_firstptr, g_preptr;

int sampleFq = 10;
int sampleNum = 1;
ofstream Save("CollisionTestData.txt");
  
void Init(void)   
{     
    //glEnable(GL_CULL_FACE);  
}

void getObb(Vector3 ct, Vector2 aright, Vector2 afront, Vector2 ahalfSize)
{
	g_obb.center = ct;
	g_obb.right = aright;
	g_obb.front = afront;
	g_obb.halfSize = ahalfSize;
	g_obb.CalculatePoint();
}

void getSector(Vector2 ct, Vector2 d, int64 ta, int64 base, int64 r, int sf)
{
	g_sector.center = ct;
	g_sector.dir = d;
	g_sector.theta = ta;
	g_sector.thetaBase = base;
	g_sector.radius = r;
	g_sector.sampleFreq = sf;
	g_sector.CalculatePoint();
}

void drawOBB(void)
{
	glPointSize(1.0f);
	glBegin(GL_LINE_STRIP);
		glVertex2i(g_obb.A.x, g_obb.A.z);
		glVertex2i(g_obb.B.x, g_obb.B.z);
		glVertex2i(g_obb.C.x, g_obb.C.z);
		glVertex2i(g_obb.D.x, g_obb.D.z);
		glVertex2i(g_obb.A.x, g_obb.A.z);
    glEnd();
	//glFlush();
}

void drawSector(void)
{
	glPointSize(1.0f);
	glBegin(GL_LINE_STRIP);
		//glColor3f(1.0, 1.0, 1.0);  //white
		glVertex2i(g_sector.center.x, g_sector.center.z);
		for(list<Vector2*>::iterator iter = g_sector.arc.begin(); iter != g_sector.arc.end(); ++iter){
			glVertex2i((*iter)->x, (*iter)->z);
		}
		glVertex2i(g_sector.center.x, g_sector.center.z);
	glEnd();
	//glFlush();
}

void  plot_circle_points(int xc,int yc,int x,int y)
{
      glBegin(GL_POINTS);
      glVertex3f(xc+x,yc+y,0); 
      glVertex3f(xc-x,yc+y,0);
      glVertex3f(xc+x,yc-y,0);
      glVertex3f(xc-x,yc-y,0);
      glVertex3f(xc+y,yc+x,0);
      glVertex3f(xc-y,yc+x,0);
      glVertex3f(xc+y,yc-x,0);
      glVertex3f(xc-y,yc-x,0);
      glEnd();     
}

void drawcircle()
{
	 glPointSize(1.0f);
	 int xc = int(g_circle.x);
	 int yc = int(g_circle.z);
	 int radius = int(g_circleRadius);
     int x,y,p;
     x=0;
     y=radius;
     p=3-2*radius;
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POINTS);
     while(x<y)
     {
          plot_circle_points(xc,yc,x,y);
          if(p<0)
                 p=p+4*x+6;
          else
          {
                 p=p+4*(x-y)+10;
                 y-=1;                 
          }
          x+=1;          
     }     
     if(x==y)
          plot_circle_points(xc,yc,x,y);
}

void drawDot(){
	glColor3f(1.0, 0, 0);
	glPointSize(3.0f);
    glBegin(GL_POINTS);
	{
        glVertex2f(Cpoint.x, Cpoint.z);
	}
    glEnd();
}

void Render(void)  
{  
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  
    glClearDepth(0.0f);  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	if (isCollide){
		glColor3f(0, 1, 0);
	} else {
		glColor3f(1.0, 1.0, 1.0);  //white
	}

	drawcircle();

	switch (g_showcase)
	{
	case obb:
		drawOBB();
		break;
	case sector:
		drawSector();
		break;
	case empty:
		break;
	default:
		break;
	}

	if( isCollide ){
		drawDot();
	}

    glutSwapBuffers();  
}

void chgObb(GLint x, GLint y)
{
	switch (g_chgtype)
	{
	case chgdir:
		g_obb.right = Vector2(x, y);
		g_obb.front = Vector2(-y, x);
		g_obb.CalculatePoint();
		//cout << "chgdir: " << x << ", " << y << endl; 
		break;
	case chgsize:
		g_obb.halfSize.x = g_preptr.x + (x - g_firstptr.x)/10;
		g_obb.halfSize.z = g_preptr.z + (y - g_firstptr.z)/10;
		if(g_obb.halfSize.x <= 0){
			g_obb.halfSize.x = 1;
		}
		if(g_obb.halfSize.z <= 0){
			g_obb.halfSize.z = 1;
		}
		g_obb.CalculatePoint();
		break;
	case chgpos:
		g_obb.center.x = g_preptr.x + (x - g_firstptr.x);
		g_obb.center.z = g_preptr.z + (y - g_firstptr.z);
		g_obb.CalculatePoint();
		break;
	default:
		break;
	}
}

void chgCircle(GLint x, GLint y)
{
	switch (g_chgtype)
	{
	case chgsize:
		g_circleRadius = g_preptr.x + (x - g_firstptr.x)/10;
		if(g_circleRadius <= 0){
			g_circleRadius = 1;
		}
		break;
	case chgpos:
		g_circle.x = g_preptr.x + (x - g_firstptr.x);
		g_circle.z = g_preptr.z + (y - g_firstptr.z);
		break;
	default:
		break;
	}
}

void chgSector(GLint x, GLint y)
{
	switch (g_chgtype)
	{
	case chgdir:
		g_sector.dir = Vector2(x, y);
		g_sector.CalculatePoint();
		//cout << "chgdir: " << x << ", " << y << endl; 
		break;
	case chgsize:
		g_sector.radius = g_preptr.x + (x - g_firstptr.x)/10;
		if (g_sector.radius <= 0 ){
			g_sector.radius = 1;
		}
		g_sector.theta = g_preptr.z + ((y - g_firstptr.z)/10) * g_sector.thetaBase;
		if (g_sector.theta >= 180 * g_sector.thetaBase) {
			//cout << "theta too large!: " << g_sector.theta<< endl; 
			g_sector.theta = 179 * g_sector.thetaBase;
		}else if(g_sector.theta <= 0) {
			//cout << "theta too small!: " << g_sector.theta<< endl; 
			g_sector.theta = 1 * g_sector.thetaBase;
		}
		//cout<< "cur theta = " << g_sector.theta <<endl;
		g_sector.CalculatePoint();
		break;
	case chgpos:
		g_sector.center.x = g_preptr.x + (x - g_firstptr.x);
		g_sector.center.z = g_preptr.z + (y - g_firstptr.z);
		g_sector.CalculatePoint();
		break;
	default:
		break;
	}
}

void checkIntersection()
{
	if (markDown && g_showcase == obb){
		sampleFq--;
		isCollide = IntersectOBBSphere2D( g_circle, g_circleRadius, &g_obb, Cpoint, Cpos);
		cout << "run check obb, res: " << isCollide << endl;
		if (sampleFq == 0){
			Save << "Test " << sampleNum++ << endl;
			Save << "type " << 0 << " ObbSphere" << endl;
			Save << "res " << isCollide << endl;
			Save << "collidePos " << Cpoint.x << " " << Cpoint.z << endl; 
			Save << "obbCenter " << g_obb.center.x << " " << g_obb.center.z << endl;
			Save << "obbRight " << g_obb.right.x << " " << g_obb.right.z << endl;
			Save << "obbFront " << g_obb.front.x << " " << g_obb.front.z << endl;
			Save << "obbHalfSize " << g_obb.halfSize.x << " " << g_obb.halfSize.z << endl;

			Save << "sphereCenter " << g_circle.x << " " << g_circle.z << endl;
			Save << "sphereRadius " << g_circleRadius << endl;
			Save << endl;
		}
	} else if (markDown && g_showcase == sector){
		sampleFq--;
		isCollide = IntersectSectorSphere2D(g_sector.center, g_sector.dir, g_sector.theta, g_sector.thetaBase, g_sector.radius, g_circle, g_circleRadius, Cpoint, Cpos);
		cout << "run check sector, res: " << isCollide << endl;
		if (sampleFq == 0){
			Save << "Test " << sampleNum++ << endl;
			Save << "type " << 1 << " SectorShpere" << endl;
			Save << "res " << isCollide << endl;
			Save << "collidePos " << Cpoint.x << " " << Cpoint.z << endl; 

			Save << "sectorCenter " << g_sector.center.x << " " << g_sector.center.z << endl;
			Save << "sectorDir " << g_sector.dir.x << " " << g_sector.dir.z << endl;
			Save << "sectorRadius " << g_sector.radius << endl;
			Save << "sectorTheta " << g_sector.theta << endl;
			Save << "sectorThetaBase " << g_sector.thetaBase << endl;

			Save << "sphereCenter " << g_circle.x << " " << g_circle.z << endl;
			Save << "sphereRadius " << g_circleRadius << endl;
			Save << endl;
		}
	}
	if(sampleFq == 0){
		sampleFq = 10;
	}
}

void onMouseMove(GLint x, GLint y){
	x = x - g_window_size/2, y = g_window_size/2 - y;     //make origin<0,0> at center of screen
	if(SelectCircle){
		chgCircle(x, y);
		checkIntersection();
		glutPostRedisplay();
	} else {
		switch (g_showcase)
		{
		case obb:
			chgObb(x, y);
			glutPostRedisplay();
			break;
		case sector:
			chgSector(x, y);
			glutPostRedisplay();
			break;
		case empty:
			break;
		default:
			break;
		}
	}
}

void onMouseButtonChg(GLint button, GLint action, GLint x, GLint y){
	x = x - g_window_size/2, y = g_window_size/2 - y;  //make origin<0,0> at center of screen
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		g_firstptr.x = x;
		g_firstptr.z = y;
		if(SelectCircle){
			if (g_chgtype == chgsize){
				g_preptr.x = g_circleRadius;
				g_preptr.z = g_circleRadius;
			}else if(g_chgtype == chgpos){
				g_preptr.x = g_circle.x;
				g_preptr.z = g_circle.z;
			}
		}else if (g_showcase == obb && g_chgtype == chgsize){
			g_preptr.x = g_obb.halfSize.x;
			g_preptr.z = g_obb.halfSize.z;
		} else if(g_showcase == obb && g_chgtype == chgpos){
			g_preptr.x = g_obb.center.x;
			g_preptr.z = g_obb.center.z;
		} else if(g_showcase == sector && g_chgtype == chgsize){
			g_preptr.x = g_sector.radius;
			g_preptr.z = g_sector.theta;
		} else if(g_showcase == sector && g_chgtype == chgpos){
			g_preptr.x = g_sector.center.x;
			g_preptr.z = g_sector.center.z;
		}
	}
}

void menu (int value);
  
int main(int argc, char *argv[])  
{  
	remove("CollisionTestData.txt");
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);   
    glutInitWindowSize(g_window_size, g_window_size);  
    glutCreateWindow(g_app_string);  
  
    // set up world space to screen mapping  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();   
    glLoadIdentity();
	gluOrtho2D(-g_window_size/2,g_window_size/2,-g_window_size/2,g_window_size/2);  //2D parllel projection, set base as center of screen
    glShadeModel(GL_FLAT);
  
    glutDisplayFunc(Render);  
    //glutKeyboardFunc(keyboard);
	glutMouseFunc(onMouseButtonChg);  //register call back function
    glutMotionFunc(onMouseMove);
  
    //Init();  
	int id;
		id = glutCreateMenu(menu);
		glutAddMenuEntry("select obb", 1);
		glutAddMenuEntry("select sector", 2);
		glutAddMenuEntry("change dir", 3);
		glutAddMenuEntry("change size", 4);
		glutAddMenuEntry("change pos", 5);
		glutAddMenuEntry("select circle", 6);
		glutAddMenuEntry("enable checking", 7);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
  
    glutMainLoop();  
  
    return 0;  
}  

void menu (int value)
{
	if (value == 1){
		SelectCircle = false;
		getObb(Vector3(0,0,0),Vector2(100,100),Vector2(-100,100), Vector2(100,50));
		g_showcase = obb;
		glutPostRedisplay();
	}
	else if(value == 2){
		SelectCircle = false;
		getSector(Vector2(0,0), Vector2(100,0), 450, 10, 100, 5);
		g_showcase = sector;
		glutPostRedisplay();
	}
	else if(value == 3){
		g_chgtype = chgdir;
		glutPostRedisplay();
	}
	else if(value == 4){
		g_chgtype = chgsize;
		glutPostRedisplay();
	}
	else if(value == 5){
		g_chgtype = chgpos;
		glutPostRedisplay();
	}
	else if(value == 6){
		SelectCircle = !SelectCircle;
	}
	else if(value == 7){
		if (g_showcase == empty) {
			cout << "please select an target obj first! <obb or sector>" << endl;
		}
		else{
			markDown = !markDown;
		}
	}
}