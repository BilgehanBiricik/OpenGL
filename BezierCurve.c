// This code is compiled on Ubuntu 18.04
// 
// gcc BezierCurve.c -o BezierCurve -lglut -lGLU -lGL

#include <GL/glut.h>
#include <math.h>

// B(x, y) points
double B[4][2] = {
    {0.2, 0.2}, // B0
	{0.5, 0.2}, // B3
	{0.4, 0.7}, // B1
	{0.7, 0.7}  // B2
};
 
void drawBezier()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

        // Drawing x and y axis
        glVertex2d(0, 1);
        glVertex2d(0, -1);
        glVertex2d(1, 0);
        glVertex2d(-1, 0);

        // Drawing rectangle
        for (int i = 0; i < 4; i++) {
            glVertex2d(B[i][0], B[i][1]);
        }
        glVertex2d(B[0][0], B[0][1]);
        glVertex2d(B[2][0], B[2][1]);
        glVertex2d(B[1][0], B[1][1]);
        glVertex2d(B[3][0], B[3][1]);

        // Drawing bezier curve
        double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;
        for (double t = 0.0; t <= 1.0; t += 0.02)
        {
            if (t == 0.0)
            {
                x0 = pow((1 - t), 3) * B[0][0] + 3 * t * pow((1 - t), 2) * B[2][0] + 3 * pow(t, 2) * (1 - t) * B[3][0] + pow(t, 3) * B[1][0];
                y0 = pow((1 - t), 3) * B[0][1] + 3 * t * pow((1 - t), 2) * B[2][1] + 3 * pow(t, 2) * (1 - t) * B[3][1] + pow(t, 3) * B[1][1];
            }
            x1 = pow((1 - t), 3) * B[0][0] + 3 * t * pow((1 - t), 2) * B[2][0] + 3 * pow(t, 2) * (1 - t) * B[3][0] + pow(t, 3) * B[1][0];
            y1 = pow((1 - t), 3) * B[0][1] + 3 * t * pow((1 - t), 2) * B[2][1] + 3 * pow(t, 2) * (1 - t) * B[3][1] + pow(t, 3) * B[1][1];
            glVertex2d(x0, y0);
            glVertex2d(x1, y1);
            x0 = x1;
            y0 = y1;
        }


    glEnd();
    glFlush();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(drawBezier);
    glutMainLoop();
    return 0;
}
