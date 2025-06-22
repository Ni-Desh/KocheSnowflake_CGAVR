#include <GL/glut.h>
#include <math.h>
#include <unistd.h>

int maxDepth = 4;
int currentDepth = 0;

void delay(int ms) {
    usleep(ms * 1000);  // milliseconds
}

void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    float xA = x1 + dx;
    float yA = y1 + dy;

    float xB = x1 + 2 * dx;
    float yB = y1 + 2 * dy;

    // Peak of the triangle
    float angle = atan2(y2 - y1, x2 - x1) - M_PI / 3;
    float xC = xA + cos(angle) * sqrt(dx * dx + dy * dy);
    float yC = yA + sin(angle) * sqrt(dx * dx + dy * dy);

    drawKoch(x1, y1, xA, yA, depth - 1);
    drawKoch(xA, yA, xC, yC, depth - 1);
    drawKoch(xC, yC, xB, yB, depth - 1);
    drawKoch(xB, yB, x2, y2, depth - 1);
}

void drawSnowflake(int depth) {
    float x1 = -0.6, y1 = -0.35;
    float x2 =  0.6, y2 = -0.35;
    float x3 =  0.0, y3 =  0.6;

    glBegin(GL_LINES);
    drawKoch(x1, y1, x2, y2, depth);
    drawKoch(x2, y2, x3, y3, depth);
    drawKoch(x3, y3, x1, y1, depth);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.5, 1.0);
    drawSnowflake(currentDepth);
    glFlush();

    if (currentDepth < maxDepth) {
        currentDepth++;
        delay(1000);  // 1 second between each level
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Koch Snowflake Animation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

