#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*
#define SOLID_CLOSED_CYLINDER(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS) \
gluCylinder(QUAD, BASE, TOP, HEIGHT, SLICES, STACKS); \
glRotatef(180, 1,0,0); \
gluDisk(QUAD, 0.0f, BASE, SLICES, 1); \
glRotatef(180, 1,0,0); \
glTranslatef(0.0f, 0.0f, HEIGHT); \
gluDisk(QUAD, 0.0f, TOP, SLICES, 1); \
glTranslatef(0.0f, 0.0f, -HEIGHT);
*/

// angle of rotation for the camera direction
float angle = 0.0f;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;
    float ratio =  w * 1.0 / h;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void drawGround() {
    glPushMatrix();
    
    GLfloat qaWhite[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaWhite);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaWhite);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f(100.0f, 0.0f,  100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();
    
    glPopMatrix();
}

void drawSnowMan() {
    glPushMatrix();
    
    // Draw Body
    GLfloat qaWhite[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaWhite);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaWhite);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glTranslatef(0.0f, 0.4f, 0.0f);
    glutSolidSphere(0.5f, 20, 20); //bottom
    glTranslatef(0.0f, 0.7f, 0.0f);
    glutSolidSphere(0.375f, 20, 20); //middle
    glTranslatef(0.0f, 0.55f, 0.0f);
    glutSolidSphere(0.25f, 20, 20); //head
    
    // Draw Eyes
    glPushMatrix();
    GLfloat qaBlack[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlack);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 32.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();
    
    // Draw Nose
    //glPushMatrix();
    GLfloat qaOrange[] = {4.0f, 0.6f , 0.4f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaOrange);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaOrange);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
    //glPopMatrix();
    
    // Draw Mouth
    //glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlack);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT, GL_SHININESS, 32.0f);
    glTranslatef(-0.03f, -0.1f, 0.22f);
    glutSolidSphere(0.025f, 10, 10);
    glTranslatef(0.06f, 0.0f, 0.0f);
    glutSolidSphere(0.025f, 10, 10);
    glTranslatef(-0.12f, 0.02f, -0.02f);
    glutSolidSphere(0.025f, 10, 10);
    glTranslatef(0.18f, 0.0f, 0.0f);
    glutSolidSphere(0.025f, 10, 10);
    //glPopMatrix();
    
    glPopMatrix();
}

void drawPineTree() {
    glPushMatrix();
    
    //glPushMatrix();
    //GLfloat qaWhite[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat qaBrown[] = {0.25f, 0.1f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaBrown);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBrown);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaBrown);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.25f, 3.5f, 10, 2);
    //glPopMatrix();
    
    GLfloat qaGreen[] = {0.1f, 0.25f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaGreen);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaGreen);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaGreen);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
    glTranslatef(0.0f, 0.0f, 0.5f);
    for (int i = 0; i < 5; ++i) {
        glutSolidCone(1.0f - 0.15f * i, 2.0f - 0.25f * i, 10, 2);
        glTranslatef(0.0f, 0.0f, 0.5f);
    }
    
    glPopMatrix();
}

void computePos(float deltaMove) {
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {
    angle += deltaAngle;
    lx = sin(angle);
    lz = -cos(angle);
}

void renderScene(void) {
    if (deltaMove) {
        computePos(deltaMove);
        glutPostRedisplay();
    }
    if (deltaAngle) {
        computeDir(deltaAngle);
        glutPostRedisplay();
    }
    
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(x, 1.0f, z, x + lx, 1.0f,  z + lz, 0.0f, 1.0f,  0.0f);
    
    // Draw stuff
    drawGround();
    
     for(int i = -3; i < 3; i++) {
        for(int j = -3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i * 10.0f, 0.0f, j * 10.0f);
            drawSnowMan();
            glTranslatef(5.0f, 0.0f, 5.0f);
            drawPineTree();
            glPopMatrix();
        }
     }
    
    /*
    GLfloat qaBlack[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlack);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
    glMaterialfv(GL_FRONT, GL_SPECULAR, qaBlack);
    glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);
    
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricOrientation(quadric, GLU_INSIDE);
    SOLID_CLOSED_CYLINDER(quadric, 0.25, 0.25, 1, 20, 20);
    gluDeleteQuadric(quadric);
    */
    
    glutSwapBuffers();
}

// -----------------------------------
//             KEYBOARD
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy) {
    if (key == 27)
        exit(0);
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT:
            deltaAngle = -0.025f;
            break;
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.025f;
            break;
        case GLUT_KEY_UP:
            deltaMove = 1.5f;
            break;
        case GLUT_KEY_DOWN:
            deltaMove = -1.5f;
            break;
    }
    glutPostRedisplay();
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            deltaAngle = 0.0f;
            break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            deltaMove = 0;
            break;
    }
}

// -----------------------------------
//             MOUSE
// -----------------------------------

void mouseMove(int x, int y) {
    // this will only be true when the left button is down
    if (xOrigin >= 0) {
        // update deltaAngle
        //deltaAngle = (x - xOrigin) * 0.005f;
        
        // update camera's direction
        lx = sin(angle + (x - xOrigin) * 0.005f);
        lz = -cos(angle + (x - xOrigin) * 0.005f);
        
        glutPostRedisplay();
    }
}

void mouseButton(int button, int state, int x, int y) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is released
        if (state == GLUT_UP) {
            angle += (x - xOrigin) * 0.005f;
            xOrigin = -1;
        } else {// state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

// -----------------------------------
//             MAIN and INIT
// -----------------------------------

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    // Lighting set up
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Set lighting intensity and color
    GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
    GLfloat qaDiffuseLight[]    = {0.8, 0.8, 0.8, 1.0};
    GLfloat qaSpecularLight[]    = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    
    // Set the light position
    GLfloat qaLightPosition[]    = {.5, .5, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
}

int main(int argc, char **argv) {
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Doom: Attack of the Killer Snowmen");
    
    init();
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 0;
}
