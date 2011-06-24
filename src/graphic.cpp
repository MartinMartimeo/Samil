#include <GL/glut.h>
#include "graphic.h"
#include "world.h"

CameraOrientation stCamOrient;

void init_gui(int argc, char **argv, World *pWorld) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 500);
    glutCreateWindow("samil");

    //glutFullScreen();				// Fulllscreenmode if wanted...
    glEnable(GL_DEPTH_TEST);


    glutDisplayFunc(render);
    glutIdleFunc(idle);
    glutReshapeFunc(resize);

    glutKeyboardFunc(processNormalKeys); // Exit(0) when ESC is pressed



    stCamOrient.afVectEye[0] = 0.0f;
    stCamOrient.afVectEye[1] = 0.0f;
    stCamOrient.afVectEye[2] = -10.0f;
    stCamOrient.afVectDest[0] = 0.0f;
    stCamOrient.afVectDest[1] = 0.0f;
    stCamOrient.afVectDest[2] = 0.0f;
    stCamOrient.afVectUp[0] = 0.0f;
    stCamOrient.afVectUp[1] = 1.0f;
    stCamOrient.afVectUp[2] = 0.0f;

    //glutTimerFunc(40,Timer,0);

    glutMainLoop();

}

void resize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(108, ratio, 1, 100);
    //gluOrtho2D(0, 800, 500, 0);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void render(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); // rendering shall not influence the scene.
    //glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    gluLookAt(stCamOrient.afVectEye[0], stCamOrient.afVectEye[1], stCamOrient.afVectEye[2],
            stCamOrient.afVectDest[0], stCamOrient.afVectDest[1], stCamOrient.afVectDest[2],
            stCamOrient.afVectUp[0], stCamOrient.afVectUp[1], stCamOrient.afVectUp[2]);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex3f(-2.0f, -2.0f, -5.0f);
    glColor3f(0, 1, 0);
    glVertex3f(2.0f, -2.0f, -5.0f);
    glColor3f(0, 0, 1);
    glVertex3f(2.0f, 2.0f, -5.0f);
    glColor3f(1, 1, 0);
    glVertex3f(-2.0f, 2.0f, -5.0f);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void idle(void) {
    sleep(0.5);
    stCamOrient.afVectEye[0] -= 0.1;
    render(); // verursacht 100% load, sollte man sich also überlegen.
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}
