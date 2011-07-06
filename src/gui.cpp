#include "math.h"
#include "gui.h"


#ifdef __gui_h

Gui *Gui::m_this;

Gui::~Gui() {

}

Gui::Gui(int argc, char **argv, Game *m_pGame) {
    Gui::m_this = this;
    Gui::m_this->m_pGame = m_pGame;
    SetWidth(Gui::m_this->m_pGame->GetWorldPointer()->GetWidth());
    SetHeight(Gui::m_this->m_pGame->GetWorldPointer()->GetHeight());
    Gui::m_this->m_fFovyAngle = 100;
    init(argc, argv);
}

void Gui::SetHeight(unsigned int i) {
    std::cout<<"[gui] " << "setter: " << i << "\n";
    m_iHeight = i;
}

void Gui::SetWidth(unsigned int i) {
    std::cout<<"[gui] " << "setter: " << i << "\n";
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
    stCamOrient.afVectEye[2] = 30.0f;
    stCamOrient.afVectDest[0] = 0.0f;
    stCamOrient.afVectDest[1] = 0.0f;
    stCamOrient.afVectDest[2] = -1.0f;
    stCamOrient.afVectUp[0] = 0.0f;
    stCamOrient.afVectUp[1] = 1.0f;
    stCamOrient.afVectUp[2] = 0.0f;

    glutMainLoop();

}

void Gui::idle(void) {
    //Gui::m_this->m_pGame->ProcessRound();
    render();
    
}


void Gui::render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    updatePerspective();

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

    float fDifWidth = Gui::m_this->m_iWidth / 2.0f;
    float fDifHeight = Gui::m_this->m_iHeight / 2.0f;

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(-fDifWidth, -fDifHeight, 0.0f);
    glColor3f(1, 1, 1);
    glVertex3f(fDifWidth, -fDifHeight, 0.0f);
    glColor3f(1, 1, 1);
    glVertex3f(fDifWidth, fDifHeight, 0.0f);
    glColor3f(1, 1, 1);
    glVertex3f(-fDifWidth, fDifHeight, 0.0f);
    glEnd();
    
    WorldMapView oWorldView = Gui::m_this->m_pGame->GetWorldPointer()->GetViewPort();
    for (WorldMapView::iterator it = oWorldView.begin(); it != oWorldView.end(); it++){
        switch (it->second){
            case FieldStone:
                Gui::m_this->renderMountain(it->first.first-fDifWidth, it->first.second-fDifHeight);
                break;
            case FieldSea:
                Gui::m_this->renderWater(it->first.first-fDifWidth, it->first.second-fDifHeight);
                break;
            case FieldTree:
                Gui::m_this->renderTree(it->first.first-fDifWidth, it->first.second-fDifHeight);
                break;
                
        }
    }

//    for (int y = -16; y < 16; y++) {
//        for (int x = -16; x < 16; x++) {
//             Gui::m_this->renderMountain(x, y);
//        }
//    }
    

    //    glBegin(GL_QUADS);
    //    glColor3f(1, 0, 0);
    //    glVertex3f(-2.0f, -2.0f, -5.0f);
    //    glColor3f(0, 1, 0);
    //    glVertex3f(2.0f, -2.0f, -5.0f);
    //    glColor3f(0, 0, 1);
    //    glVertex3f(2.0f, 2.0f, -5.0f);
    //    glColor3f(1, 1, 0);
    //    glVertex3f(-2.0f, 2.0f, -5.0f);
    //    glEnd();

    glPopMatrix();

    glutSwapBuffers();

}

void Gui::renderWater(float x, float y) {
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(x, y, 0.125f);
    glVertex3f(x, y + 1.0f, 0.125f);
    glVertex3f(x + 1.0f, y + 1.0f, 0.125f);
    glVertex3f(x + 1.0f, y, 0.125f);
    glEnd();

}

void Gui::renderTree(float x, float y) {
    float z = 0.25*1.5f + fabs(sin(x / 3.0f) + sin(x / 1.0f) + cos(y / 3.0f) + cos(y / 2.0f));
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0, 1, 0);
    glVertex3f(x + 0.5f, y + 0.5f, z);
    glColor3f(0.54, 0.27, 0.074);
    glVertex3f(x, y, 0.0f);
    glVertex3f(x, y + 1.0f, 0.0f);
    glVertex3f(x + 1.0f, y + 1.0f, 0.0f);
    glVertex3f(x + 1.0f, y, 0.0f);
    glVertex3f(x, y, 0.0f);
    glEnd();

}

void Gui::renderMountain(float x, float y) {
    float z = 1.5f + fabs(sin(x / 3.0f) + sin(x / 1.0f) + cos(y / 3.0f) + cos(y / 2.0f));
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 1);
    glVertex3f(x + 0.5f, y + 0.5f, z);
    glColor3f(0, 0, 0);
    glVertex3f(x, y, 0.0f);
    glVertex3f(x, y + 1.0f, 0.0f);
    glVertex3f(x + 1.0f, y + 1.0f, 0.0f);
    glVertex3f(x + 1.0f, y, 0.0f);
    glVertex3f(x, y, 0.0f);
    glEnd();
}

static void renderEmpty() {

}

void Gui::resize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    Gui::m_this->m_iWindowWidth = w;
    Gui::m_this->m_iWindowHeight = h;

    Gui::m_this->m_fWindowRatio = w * 1.0 / h;

    updatePerspective();


}

void Gui::updatePerspective() {
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    gluPerspective(Gui::m_this->m_fFovyAngle, Gui::m_this->m_fWindowRatio, 0.01, 200);

    // Set the viewport to be the entire window
    glViewport(0, 0, Gui::m_this->m_iWindowWidth, Gui::m_this->m_iWindowHeight);

    //gluOrtho2D(0, 800, 500, 0);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);

}

void Gui::processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    if (key == 'q') {
        Gui::m_this->m_fFovyAngle += 0.5f;
    }
    if (key == 'e') {
        Gui::m_this->m_fFovyAngle -= 0.5f;
    }
    if (key == 'w') {
        Gui::m_this->stCamOrient.afVectEye[1] += 0.5;
        //Gui::m_this->stCamOrient.afVectDest[1] += 0.5;
    }

    if (key == 's') {
        Gui::m_this->stCamOrient.afVectEye[1] -= 0.5;
        //Gui::m_this->stCamOrient.afVectDest[1] -= 0.5;
    }
    if (key == 'a') {
        Gui::m_this->stCamOrient.afVectEye[0] -= 0.5;
        //Gui::m_this->stCamOrient.afVectDest[0] -= 0.5;
    }
    if (key == 'd') {
        Gui::m_this->stCamOrient.afVectEye[0] += 0.5;
        //Gui::m_this->stCamOrient.afVectDest[0] += 0.5;
    }
}

#endif
