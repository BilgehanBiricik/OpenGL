
// This code is compiled on Ubuntu 18.04
// 
// gcc CubicSpline.c -o CubicSpline -lglut -lGLU -lGL -lm

#include <GL/glut.h>
#include <math.h>

// Points of the curve 
// P(x,y)
double p[4][2] = {
    {0, 0},
    {1, 1},
    {2, -1},
    {3, 0}};

// Derivative points of the curve
// P'(x,y)
double p_prime[4][2] = {
    {1, 1},
    {0.505, -0.148},
    {0.505, -0.148},
    {1, 1}};

// Function that evaluates the distance between of two points.
double t(int k)
{
    return sqrt(pow((p[k][0] - p[k - 1][0]), 2) + pow((p[k][1] - p[k - 1][1]), 2));
}

// F1 function
double f1(double r)
{
    return (2 * pow(r, 3) - 3 * pow(r, 2) + 1);
}

// F2 function
double f2(double r)
{
    return (-2 * pow(r, 3) + 3 * pow(r, 2));
}

// F3 function
double f3(double r, int k)
{
    return (r * (pow(r, 2) - 2 * r + 1) * t(k + 1));
}

// F4 function
double f4(double r, int k)
{
    return (r * (pow(r, 2) - r) * t(k + 1));
}

// Function that multiplies two matrices.
void multiply_matrix(double f[1][4], double p[4][2], double res[1][2])
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                res[i][j] += f[i][k] * p[k][j];
            }
        }
    }
}

void drawCubicSpline()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glScaled(0.3, 0.3, 0.3);    // Scale current matrix to 0.3

    glBegin(GL_LINES);

        // Drawing the points
        glColor3d(1.0, 0.0, 0.0);
        for (int i = 0; i < 4; i++)
        {
            glVertex2d(p[i][0], p[i][1]);
        }
        glVertex2d(p[1][0], p[1][1]);
        glVertex2d(p[2][0], p[2][1]);

        // Drawing x and y axises
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0, -3);
        glVertex2d(0, 3);
        glVertex2d(3, 0);
        glVertex2d(-3, 0);

        // Drawing Cubic-Spline curve
        double x0, y0, x1, y1;
        double res[1][2];
        for (int k = 1; k <= 3; k++)
        {
            for (double r = 0; r <= 1; r += 0.0002)
            {
                // Formula;
                //                                      [Pk  
                // Pk(r) = [F1(r) F2(r) F3(r) F4(r)] *   Pk+1
                //                                       P'k
                //                                       P'k+1]
                double f[1][4] = {f1(r), f2(r), f3(r, k), f4(r, k)};
                double p_inter[4][2] = {{p[k - 1][0], p[k - 1][1]}, 
                                        {p[k][0], p[k][1]}, 
                                        {p_prime[k - 1][0], p_prime[k - 1][1]}, 
                                        {p_prime[k][0], p_prime[k][1]}};
                multiply_matrix(f, p_inter, res);

                if (r == 0.0)
                {
                    x0 = res[0][0];
                    y0 = res[0][1];
                    continue;
                }
                x1 = res[0][0];
                y1 = res[0][1];
                glVertex2d(x0, y0);
                glVertex2d(x1, y1);
                x0 = x1;
                y0 = y1;
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
    glutCreateWindow("Cubic-Spline Curve");
    glutDisplayFunc(drawCubicSpline);
    glutMainLoop();
    return 0;
}
