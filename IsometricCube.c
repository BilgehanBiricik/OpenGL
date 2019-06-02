
// This code is compiled on Ubuntu 18.04
// 
// gcc IsometricCube.c -o IsometricCube -lglut -lGLU -lGL

#include <GL/glut.h>

// x, y, z coordinates of cut cube
double X[10][4] = {
    {0,   0,   1,   1},     // A 0
    {1,   0,   1,   1},     // B 1
    {1,   0.5, 1,   1},     // C 2
    {0.5, 1,   1,   1},     // D 3
    {0,   1,   1,   1},     // E 4
    {0,   0,   0,   1},     // F 5
    {1,   0,   0,   1},     // G 6
    {1,   1,   0,   1},     // H 7
    {0,   1,   0,   1},     // I 8
    {1,   1,   0.5, 1}      // J 9
};

// Matrix that contains which points depend on which point
int combination_matrix[10][3] = {
    {1, 4, 5},      // A -> B, E, F
    {0, 2, 6},      // B -> A, C, G
    {1, 3, 9},      // C -> B, D, J
    {2, 4, 9},      // D ...
    {0, 3, 8},      // E ...
    {0, 6, 8},      // F ...
    {1, 5, 7},      // G ...
    {6, 8, 9},      // H ...
    {4, 5, 7},      // I ...
    {2, 3, 7}       // J ...
};

void drawIsometricCube()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);        // Select Projection Mode
    glLoadIdentity();                   // Load idenity matrix
                                        
    double dist = (1 / 3.0);            // Adjusting distance

    glRotated(35.26, 1.0, 0.0, 0.0);    // Rotating projection matrix about 35.26 degree around the x-axis
    glRotated(-45, 0.0, 1.0, 0.0);      // Rotating projection matrix about -45 degree around the y-axis
    glTranslated(-dist, -dist, -dist);  // Translationing the projection matrix about dist variable on minus y-axis

    glMatrixMode(GL_MODELVIEW);         // Select Model-View Mode
    glBegin(GL_LINES);
        
        // x-axis
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(2.0, 0.0, 0.0);

        // y-axis
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 2.0, 0.0);

        // z-axis
        glColor3d(0.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 2.0);      

        // drawing cut cube
        glColor3d(1.0, 1.0, 1.0);
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                glVertex3d(X[i][0], X[i][1], X[i][2]);
                glVertex3d(X[combination_matrix[i][j]][0], X[combination_matrix[i][j]][1], X[combination_matrix[i][j]][2]);
            }
            
        }

    glEnd();
    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Isometric Cube");
    glutDisplayFunc(drawIsometricCube);
    glutMainLoop();
    return 0;
}
