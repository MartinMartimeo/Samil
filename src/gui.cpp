#include "gui.h"

#ifdef __gui_h

Gui *Gui::m_this;

Gui::~Gui()
{
    
}

Gui::Gui(int argc, char **argv, World *pWorld) {
    SetWidth(pWorld->GetWidth());
    SetHeight(pWorld->GetHeight());
    Gui::m_this = this;
    init(argc, argv);
}

void Gui::SetHeight(unsigned int i) {
    m_iHeight = i;
}

void Gui::SetWidth(unsigned int i) {
    m_iWidth = i;
}

unsigned int Gui::GetHeight() {
    return m_iHeight;
}

unsigned int Gui::GetWidth() {
    return m_iWidth;
}

void Gui::init(int argc, char **argv) {
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
    stCamOrient.afVectEye[2] = 0.0f;
    stCamOrient.afVectDest[0] = 0.0f;
    stCamOrient.afVectDest[1] = 0.0f;
    stCamOrient.afVectDest[2] = 0.0f;
    stCamOrient.afVectUp[0] = 0.0f;
    stCamOrient.afVectUp[1] = 1.0f;
    stCamOrient.afVectUp[2] = 0.0f;

    //glutTimerFunc(40,Timer,0);

    glutMainLoop();

}

void Gui::idle(void) {
    Gui::render();
}

void Gui::render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix(); // rendering shall not influence the scene.
    //glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    gluLookAt(
            Gui::m_this->stCamOrient.afVectEye[0], 
            Gui::m_this->stCamOrient.afVectEye[1], 
            Gui::m_this->stCamOrient.afVectEye[2],
            Gui::m_this->stCamOrient.afVectDest[0], 
            Gui::m_this->stCamOrient.afVectDest[1], 
            Gui::m_this->stCamOrient.afVectDest[2],
            Gui::m_this->stCamOrient.afVectUp[0], 
            Gui::m_this->stCamOrient.afVectUp[1], 
            Gui::m_this->stCamOrient.afVectUp[2]
    );

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex3f(-Gui::m_this->m_iWidth*3/2, -Gui::m_this->m_iHeight*3/2, -5.0f);
    glColor3f(0, 1, 0);
    glVertex3f(-Gui::m_this->m_iWidth*3/2, Gui::m_this->m_iHeight*3/2, -5.0f);
    glColor3f(0, 0, 1);
    glVertex3f(Gui::m_this->m_iWidth*3/2, -Gui::m_this->m_iHeight*3/2, -5.0f);
    glColor3f(1, 1, 0);
    glVertex3f(Gui::m_this->m_iWidth*3/2, Gui::m_this->m_iHeight*3/2, -5.0f);
    glEnd();
    
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

void Gui::resize(int w, int h) {
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
    gluPerspective(10, ratio, 0.01, 100);
    //gluOrtho2D(0, 800, 500, 0);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);

}

void Gui::processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    if (key == 'q'){
        Gui::m_this->stCamOrient.afVectEye[2] += 0.1f;
    }
    
    if (key == 'e'){
        Gui::m_this->stCamOrient.afVectEye[2] -= 0.1f;
    }
    std::cout<<Gui::m_this->stCamOrient.afVectEye[2]<<"\n";
}

#endif
