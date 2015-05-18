#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/freeglut.h>
#include <GL/glu.h>

#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <Vfw.h>
using namespace std;

#define PI			3.14159265358979323846
#define MAXOBJECTS	200
enum PointLocation {PLANEFRONT, PLANEBACK, ONPLANE};

typedef struct mycolor {
	float r, g, b;
} RGB;

const int MAXTRIANGLES	=	20;
const int BOXSIZE		=	40;
const int FLOORSIZE		=	50;
const int BALLRADIUS	=	5;
const int BALLMAXCOUNT	=	20;
const float e			=	1.0;
const float k			=	0.05;
const float mass		=	10;
const float gravity		=	-9.8;
const float dt			=	0.01;

int floorCounter		=	0;
int floorNum			=	2;
int floorVertices[][3][3]	= {{{-FLOORSIZE, -10, FLOORSIZE}, {-FLOORSIZE, -10, -FLOORSIZE}, {FLOORSIZE, -10, -FLOORSIZE}},
							   {{FLOORSIZE, -10, -FLOORSIZE}, {FLOORSIZE, -10, FLOORSIZE},   {-FLOORSIZE, -10, FLOORSIZE}}};


// angle of rotation for the camera direction
float angle_camera=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x_camera=0.0f,z_camera=5.0f;

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle_camera -= 0.01f;
			lx = sin(angle_camera);
			lz = -cos(angle_camera);
			break;
		case GLUT_KEY_RIGHT :
			angle_camera += 0.01f;
			lx = sin(angle_camera);
			lz = -cos(angle_camera);
			break;
		case GLUT_KEY_UP :
			x_camera += lx * fraction;
			z_camera += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x_camera -= lx * fraction;
			z_camera -= lz * fraction;
			break;
	}
}

class Vector3 {
	float x, y, z;
public:
	Vector3() { x=0; y=0; x=0; }
	Vector3(float _x, float _y, float _z) { x=_x; y=_y; z=_z;}
	void init(float _x, float _y, float _z) { x=_x; y=_y; z=_z; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	void setX(const float _x) { x = _x; }
	void setY(const float _y) { y = _y; }
	void setZ(const float _z) { z = _z; }

	float dot(Vector3 a) {
          return( x * a.getX() + y * a.getY() + z * a.getZ() );
     }

	Vector3 operator -(const Vector3& a) {
        Vector3 temp;
		temp.x = x - a.x;
		temp.y = y - a.y;
		temp.z = z - a.z;
		return temp;
     }

	Vector3 operator *(const Vector3& a) {
        Vector3 cross;
		cross.x = y * a.z - z * a.y;
		cross.y = z * a.x - x * a.z;
		cross.z = x * a.y - y * a.x;
		return cross;
     }

	Vector3 operator *(float num) {
		Vector3 result;
		result.x = x * num;
		result.y = y * num;
		result.z = z * num;
		return result;
	}

	Vector3 operator +(const Vector3& a) {
		Vector3 sum;
		sum.x = x + a.x;
		sum.y = y + a.y;
		sum.z = z + a.z;
		return sum;
	}

	Vector3 normalize() {
		float mag = sqrtf(x * x + y * y + z * z);
		x /= mag;
		y /= mag;
		z /= mag;
		Vector3 vec(x,y,z);
		return vec;
	}
};

class Object3 {
private:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	Vector3 axis;
	RGB color;
	float alpha;
	float mass;
	float bodyrot;
public:
	Vector3 getPosition() const { return position; }
	Vector3 getVelocity() const { return velocity; }
	Vector3 getAcceleration() const { return acceleration; }
	Vector3 getAxis() const { return axis; }

	void setPosition(const Vector3& a) { position = a;}
	void setVelocity(const Vector3& a) { velocity = a;}
	void setAcceleration(const Vector3& a) { acceleration = a;}
	void setAxis(const Vector3& a) { axis = a;}

	float getMass() const { return mass; }
	void setMass(const float a) { mass = a; }

};

class Plane3 {
	Vector3 normal;
	float distfromOrigin;
public:
	Vector3 getNormal() const { return normal; }
	void setNormal(const Vector3& a) { normal = a; }
	float getDistfromOrigin() const { return distfromOrigin; }
	void setDistfromOrigin(const float a) { distfromOrigin = a; }
};

class Polygon3 {
	Vector3 topleft;
	Vector3 topright;
	Vector3 botright;
public:
	Polygon3() {
		topleft.init(0.0, 0.0, 0.0);
		topright.init(0.0, 0.0, 0.0);
		botright.init(0.0, 0.0, 0.0);
	}

	Polygon3(Vector3 _topleft, Vector3 _topright, Vector3 _botright ) {
		topleft = _topleft;
		topright = _topright;
		botright = _botright;
	}

	Vector3 getTopLeft() const { return topleft; }
	Vector3 getTopRight() const { return topright; }
	Vector3 getBotRight() const { return botright; }

	void setTopLeft(const Vector3& _topleft) { topleft = _topleft; }
	void setTopRight(const Vector3& _topright) { topright = _topright; }
	void setBotRight(const Vector3& _botright) { botright = _botright; }


};

Polygon3 myfloor[MAXTRIANGLES];
Object3 bola;
Object3 bola1;
Object3 bola2;
Vector3 windvelocity;

void determinePointLocation(Plane3 plane, Vector3 pStart, Vector3 pDest, PointLocation &pStartLoc, PointLocation &pDestLoc) {
	/////////////////////////////////////////////////////////////////////////
	// Now we are going to start comparing on which side is the starting point
	// and the destination point. If they are not on the same side, that means
	// the point crossed over to the other side of the plane.
	/////////////////////////////////////////////////////////////////////////
	float beforecollision = pStart.dot(plane.getNormal()) + plane.getDistfromOrigin();
	if(beforecollision > 0)
		pStartLoc = PLANEFRONT;
	else if(beforecollision < 0)
		pStartLoc = PLANEBACK;
	else if(beforecollision == 0)
		pStartLoc = ONPLANE;

	////////////////////////////////////////////////////////////////////////
	// The value of this last collision is actually enough to check for
	// collision. If (aftercollision > 0), then ball is infront of plane (crossed over)
	// and there is a collision with plane.
	////////////////////////////////////////////////////////////////////////
	float aftercollision = pDest.dot(plane.getNormal()) + plane.getDistfromOrigin();
	if(aftercollision > 0)
		pDestLoc = PLANEFRONT;
	else if(aftercollision < 0)
		pDestLoc = PLANEBACK;
	else
		pDestLoc = ONPLANE;

}

Vector3 findVectorFrom2Points(Vector3 vec1, Vector3 vec2) {
	return vec2 - vec1;
}

void findTwoVectorsOfPlane(Polygon3 pol, Vector3 &vec1, Vector3 &vec2) {
	vec1 = findVectorFrom2Points(pol.getTopLeft(), pol.getBotRight());
	vec2 = findVectorFrom2Points(pol.getTopRight(), pol.getBotRight());
}

//////////////////////////////////////////////////////////////////////////////////////
//
// Functions below are used for Collision Detection
//
// I would like to acknowledge this site:
// http://gamedeveloperjourney.blogspot.com/2009/04/point-plane-collision-detection.html
// for the algorithm of collision detection, that helped me a lot with the 3 functions
// below. I think this is the best blog
// that clearly explains the physics and math behind polygon collision.
// I can say that this is the ONLY site that made me understand the concept
// behind collision detection. It helped me a lot!!!
//
///////////////////////////////////////////////////////////////////////////////////////

void findPlaneAttributes(Polygon3 poly, Plane3 &plane){
	///////////////////////////////////////////////////////////////////
	// Below is all about our Plane
	// Ax + By + Cz + D = 0
	// 1. Find two vectors on a plane			-- use three vertices of polygon
	// 2. Find cross product of those 2 vectors -- values of A,B,C
	// 3. Normalize the cross product			-- unit length of 1
	// 4. Find the distance of Plane from origin -- value of D
	//////////////////////////////////////////////////////////////////

	Vector3 planeVec1, planeVec2;
	findTwoVectorsOfPlane(poly, planeVec1, planeVec2);
	Vector3 cross = (planeVec1 * planeVec2);
	plane.setNormal(cross.normalize());

	float distFromOrigin = -(poly.getTopLeft().dot(plane.getNormal()));
	plane.setDistfromOrigin(distFromOrigin);
}


////////////////////////////////////////////////////////////////////////////
//
// Function to check if point is actually inside polygon
//
////////////////////////////////////////////////////////////////////////////
bool isPointBounded(Polygon3 poly, Vector3 pStart, Vector3 pDest, Plane3 plane){
		//////////////////////////////////////////////////////////////////////////
		// Now find the bounds of poylgon
		// Use formula intersect = pStart + ray * t
		// 1. Calculate the ray = pDest - pStart
		// 2. Normalize ray
		// 3. Find t = -(DotProduct(N, pStart) + D)/ DotProduct(N, ray)
		// 4. Find intersection with plane --> pointOfIntersection
		// 5. Determine if intersection hit the collision surface of polygon
		////////////////////////////////////////////////////////////////////////
		Vector3 ray = findVectorFrom2Points(pDest, pStart);
		Vector3 rayNormal = ray.normalize();

		float t = -(pStart.dot(plane.getNormal()) + plane.getDistfromOrigin())/ray.dot(plane.getNormal());
		Vector3 pointOfIntersection = pStart + (ray * t);

		Vector3 v1 = pointOfIntersection - poly.getTopLeft();
		Vector3 v2 = pointOfIntersection - poly.getTopRight();
		Vector3 v3 = pointOfIntersection - poly.getBotRight();

		Vector3 v1Normal = v1.normalize();
		Vector3 v2Normal = v2.normalize();
		Vector3 v3Normal = v3.normalize();

		// Angles around intersection should total 360 degrees (2 PI)
		float angle1 = acos(v1Normal.dot(v2Normal));
		float angle2 = acos(v2Normal.dot(v3Normal));
		float angle3 = acos(v3Normal.dot(v1Normal));
		float thetaSum = angle1 + angle2 + angle3;

		if (fabs(thetaSum - (2 * PI)) < 0.1)
			return true; //cout << "Point lies in plane" << endl;
		else
			return false; //cout << "Point lies NOT in plane" << endl; //
}

////////////////////////////////////////////////////////////
//
// Function to compute velocity after collision between
// two points. e is elasticity coefficient whose value
// is from 0 to 1.
//
////////////////////////////////////////////////////////////
Vector3 collisionVelocity(Vector3 normal, Vector3 velocity, float e) {
    Vector3 velocityTemp = velocity * (-1);

	//calculate the projection.
	float projection = velocityTemp.dot(normal);

    //Take the length of the projection against the normal.
	Vector3 lengthVector = normal * projection;

    ///////////////////////////////////////////////////////////////////////
	// Lets obtain the final velocity vector.
	// We can stop here because we found the final velocity after collision.
	// But this is the collision on the plane of the polygon and not the
	// polygon itself! We still need to figure out if the ball actually hit
	// the polygon itself.
	////////////////////////////////////////////////////////////////////////
	Vector3 reflection = lengthVector *(1+e);
	Vector3 velocityFinal = reflection + velocity;
	return velocityFinal;

}

////////////////////////////////////////////////////////////////////////////
//
// Function combining detection and reflection functions, returns new velocity
//
////////////////////////////////////////////////////////////////////////////
void detectAndReflect(Polygon3 poly, Vector3 pStart, Vector3 pDest, Vector3 &vel, float e) {
			Plane3 plane;
		    PointLocation pStartLoc, pDestLoc;
			findPlaneAttributes(poly, plane);
			determinePointLocation(plane, pStart, pDest, pStartLoc, pDestLoc);

			if(pDestLoc == PLANEBACK) {}
			else if(pStartLoc != pDestLoc &&  isPointBounded(poly, pStart, pDest, plane))
			{
				// Compute the new velocity after object collides with polygon
				 Vector3 finalVelocity =  collisionVelocity(plane.getNormal(), vel, e);
				 vel = finalVelocity;
			}
}

void drawFloor() {
	for(int i=0; i<floorCounter; i++) {
		//drawTri(myfloor[i].topleft, myfloor[i].topright, myfloor[i].botright);
		glPushMatrix();
		glBegin(GL_TRIANGLES);
			glColor4f(0.2, 0.2, 0.7, 1.0);
			glVertex3f(myfloor[i].getTopLeft().getX(), myfloor[i].getTopLeft().getY()-4, myfloor[i].getTopLeft().getZ());
			glVertex3f(myfloor[i].getTopRight().getX(), myfloor[i].getTopRight().getY()-4,myfloor[i].getTopRight().getZ());
			glVertex3f(myfloor[i].getBotRight().getX(), myfloor[i].getBotRight().getY()-4,myfloor[i].getBotRight().getZ());
		glEnd();
		glPopMatrix();
	}
}

void buildTriangle(int count, Polygon3 *tri, Vector3 tl, Vector3 tr, Vector3 br) {
		tri[count-1].setTopLeft(tl);
		tri[count-1].setTopRight(tr);
		tri[count-1].setBotRight(br);
}

void buildFloorDimensions(int &count, int num, Polygon3 *tri, int vert1[][3][3]) {
	Vector3 vrtx[3];
	for(int i=0; i<num; i++) {
		count++;
		for(int j=0; j<3; j++) {

				vrtx[j].setX(vert1[i][j][0]);
				vrtx[j].setY(vert1[i][j][1]);
				vrtx[j].setZ(vert1[i][j][2]);
		}

		buildTriangle(count, tri, vrtx[0],  vrtx[1],  vrtx[2]);
	}
}

void drawBall() {
		glPushMatrix();
			glColor3f(1.0f,0.0f,0.0f);
			glTranslatef(bola.getPosition().getX(), bola.getPosition().getY(), bola.getPosition().getZ());
			glutSolidSphere(BALLRADIUS,50,50);
			//glutSolidCube(6);
		glPopMatrix();

}
void drawBall1() {
		glPushMatrix();
			glColor3f(1.0f,0.0f,0.0f);
			glTranslatef(bola1.getPosition().getX(), bola1.getPosition().getY(), bola1.getPosition().getZ());
			glutSolidSphere(BALLRADIUS,50,50);
			//glutSolidCube(6);
		glPopMatrix();

}
void drawBall2() {
		glPushMatrix();
			glColor3f(1.0f,0.0f,0.0f);
			glTranslatef(bola2.getPosition().getX(), bola2.getPosition().getY(), bola2.getPosition().getZ());
			glutSolidSphere(BALLRADIUS,50,50);
			//glutSolidCube(6);
		glPopMatrix();

}

void display (void) {
	glClearDepth (1);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	gluLookAt(0.0, 20.0, 100.0,		// eyeX, eyeY, eyeZ
              0.0, 0.0, 0.0,		// centerX, centerY, centerZ
              0.0, 1.0, 0.0);		// upX, upY, upZ

	glEnable (GL_BLEND);
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE);

	drawFloor();
	drawBall();
	drawBall1();
	drawBall2();

    glutSwapBuffers();
}

void setAcceleration(Object3 &bola, Vector3 gravity, Vector3 windvelocity, float k) {
	bola.setAcceleration(gravity);

	float X = bola.getAcceleration().getX() - (k/bola.getMass() * bola.getVelocity().getX() + k/bola.getMass()*windvelocity.getX());
	float Y = bola.getAcceleration().getY() - (k/bola.getMass() * bola.getVelocity().getY() + k/bola.getMass()*windvelocity.getY());
	float Z = bola.getAcceleration().getZ() - (k/bola.getMass() * bola.getVelocity().getZ() + k/bola.getMass()*windvelocity.getZ());

	Vector3 newAcceleration(X, Y, Z);
	bola.setAcceleration(newAcceleration);

}

void eulerIntegrate(Object3 &bola, float dt) {
	Vector3 Pos;
	Vector3 Vel;

	Pos = bola.getPosition() + bola.getVelocity() * dt;
	Vel = bola.getVelocity() + bola.getAcceleration() * dt;

	bola.setVelocity(Vel); // Update object's velocity
	bola.setPosition(Pos); // Update object's position
}


void ballDisplacement() {

    gluLookAt(	x_camera, 1.0f, z_camera,
			x_camera+lx, 1.0f,  z_camera+lz,
			0.0f, 1.0f,  0.0f);

	 Vector3 Ygravity(0, 0, 0);
	 Vector3 pStart = bola.getPosition(); // Save old position for use in collision detection later
	 Vector3 pStart1 = bola1.getPosition(); // Save old position for use in collision detection later
	 Vector3 pStart2 = bola2.getPosition(); // Save old position for use in collision detection later

	 //setAcceleration(bola, Ygravity, windvelocity, k); // Compute total acceleration and then integrate
	 eulerIntegrate(bola, dt);
	 Vector3 pDest = bola.getPosition(); // Save new position

     //setAcceleration(bola1, Ygravity, windvelocity, k); // Compute total acceleration and then integrate
	 eulerIntegrate(bola1, dt);
	 Vector3 pDest1 = bola1.getPosition(); // Save new position

     //setAcceleration(bola2, Ygravity, windvelocity, k); // Compute total acceleration and then integrate
	 eulerIntegrate(bola2, dt);
	 Vector3 pDest2 = bola2.getPosition(); // Save new position

	 Vector3 velocity = bola.getVelocity(); // Save old velocity
	 Vector3 velocity1 = bola1.getVelocity(); // Save old velocity
	 Vector3 velocity2 = bola2.getVelocity(); // Save old velocity

	 for(int pp=0; pp < floorCounter; pp++) {

			 detectAndReflect(myfloor[pp], pStart, pDest, velocity, e); // Detect collision with the floor
	}

	 Polygon3 tiltingFloor;
	 //detectAndReflect(tiltingFloor, pStart, pDest, velocity, e); // Detect collision with other surfaces (if any)
	 bola.setVelocity(velocity); // Save new velocity
	 bola1.setVelocity(velocity1); // Save new velocity
	 bola2.setVelocity(velocity2); // Save new velocity

	glutPostRedisplay();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
    glMatrixMode (GL_MODELVIEW);
}

void addBall() {
	Vector3 initAccel(0.0 ,0.0 ,0.0);
	bola.setAcceleration(initAccel);
	bola.setMass(2.5);

	Vector3 initPosition(-10.0 ,40.0 ,0.0);
	bola.setPosition(initPosition);

	Vector3 initVelocity(0.5 ,-1.0 ,0.0);
	bola.setVelocity(initVelocity);
}

void addBall1() {
	Vector3 initAccel(0.0 ,0.0 ,0.0);
	bola1.setAcceleration(initAccel);
	bola1.setMass(2.5);

	Vector3 initPosition(-40.0 ,40.0 ,0.0);
	bola1.setPosition(initPosition);

	Vector3 initVelocity(-0.2 ,-1.0 ,0.5);
	bola1.setVelocity(initVelocity);
}


void addBall2() {
	Vector3 initAccel(0.0 ,0.0 ,0.0);
	bola2.setAcceleration(initAccel);
	bola2.setMass(2.5);

	Vector3 initPosition(20.0 ,40.0 ,0.0);
	bola2.setPosition(initPosition);

	Vector3 initVelocity(1.2 ,-1.0 ,0.3);
	bola2.setVelocity(initVelocity);
}

void keyboard (unsigned char key, int x, int y) {

	if (key=='b') {
		addBall();
		addBall1();
		addBall2();
	}
}

int main(int argc, char **argv) {

	// Initialize Glut and Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("A basic bouncing ball");

	// Initialize Other Stuff
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	buildFloorDimensions(floorCounter, floorNum, myfloor, floorVertices);

	// Start drawing and calculating displacement
	glutDisplayFunc (display);
    glutIdleFunc (ballDisplacement);
    glutReshapeFunc (reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	glutMainLoop ();
    return 0;
}
