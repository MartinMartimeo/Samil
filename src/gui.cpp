#include "gui.h"

#ifdef __gui_h

Gui::Gui(int argc, char **argv, World *pWorld) {
    SetWidth(pWorld->GetWidth());
    SetHeight(pWorld->GetHeight());
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

void Gui::idle(void){
    
}

void Gui::render(void){
    
}

void Gui::resize(int w, int h){
    
}

void Gui::processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

#endif
