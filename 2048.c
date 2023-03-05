#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <GL/glut.h>

#define PI acos(-1.0)

#define N 4

bool menu = false;
int score = 0;

int board[N][N];

void init() {
    int i, j;
    
    score = 0;

    srand(time(NULL));

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    int x = rand() % 4;
    int y = rand() % 4;
    board[x][y] = (rand() % 2 == 0) ? 2 : 4;
}

void drawCircle(float x, float y, float radius, int num_segments) {
    glBegin(GL_TRIANGLE_FAN); // Begin drawing a triangle fan

    // Center of the circle
    glVertex2f(x, y);

    // Vertices of the circle
    for (int i = 0; i <= num_segments; i++) {
        float angle = i * 2.0f * PI / num_segments; // Angle of the current vertex
        float dx = radius * cosf(angle); // X-coordinate of the current vertex
        float dy = radius * sinf(angle); // Y-coordinate of the current vertex
        glVertex2f(x + dx, y + dy); // Set the current vertex
    }

    glEnd(); // End drawing the triangle fan
}

void renderRoundedRectangle(float x, float y, float width, float height, float radius) {
    int i;
    int triangleAmount = 20; // increase for more roundness

    drawCircle(x + width - radius, y + radius, radius, triangleAmount);
    drawCircle(x + radius, y + radius, radius, triangleAmount);
    drawCircle(x + width - radius, y + height - radius, radius, triangleAmount);
    drawCircle(x + radius, y + height - radius, radius, triangleAmount);

    glRectf(x, y + radius, x + width, y + height - radius);
    glRectf(x + radius, y, x + width - radius, y + height);
}

void display() {
    int i, j;
    
    if(menu) { glClearColor(204./255./1.5, 192./255./1.5, 179./255./1.5, 1.0); }
    else { glClearColor(204./255., 192./255., 179./255., 1.0); }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int value = board[i][j];
            if (value == 0) continue;

            int r = 255, g = 255, b = 255;
            switch (value) {
                case 2:
                    r = 238, g = 228, b = 218; break;
                case 4:
                    r = 237, g = 224, b = 200; break;
                case 8:
                    r = 242,  g = 177, b = 121; break;
                case 16:
                    r = 245, g = 149, b = 99;  break;
                case 32:
                    r = 246, g = 124, b = 95;  break;
                case 64:
                    r = 246, g = 94,  b = 59;  break;
                case 128:
                    r = 237, g = 207, b = 114; break;
                case 256:
                    r = 237, g = 204, b = 97;  break;
                case 512:
                    r = 237, g = 204, b = 80;  break;
                case 1024:
                    r = 237, g = 197, b = 63;  break;
                case 2048:
                    r = 237, g = 194, b = 46;  break;
                default:
                    r = 0,   g = 0,   b = 0;   break;
            }
            
            glLineWidth(4.0);
            float cr = r/255.0, cg = g/255.0, cb = b/255.0;
            if (menu) { cr = r/255.0/1.5; cg = g/255.0/1.5; cb = b/255.0/1.5; }
            glColor3f(cr/1.25, cg/1.25, cb/1.25);
            renderRoundedRectangle((j + 0.1) / N, (i + 0.1) / N-0.0125, 0.8 / N, 0.8 / N, 0.1 / N);
            glColor3f(cr, cg, cb);
            renderRoundedRectangle((j + 0.1) / N, (i + 0.1) / N+0.0125, 0.8 / N, 0.8 / N, 0.1 / N);
                
            // set the color of the text
            float tcr, tcg, tcb;
            if (value < 9) {
                tcr = 119./255.; tcg = 110./255.; tcb = 101./255.;
            } else {
                tcr = 249./255.; tcg = 246./255.; tcb = 242./255.;
            }
            if (menu) {  tcr /= 1.5; tcg /= 1.5; tcb /= 1.5; }
            glColor3f(tcr, tcg, tcb);
            
            // convert the value to a string
            char str[10];
            sprintf(str, "%d", value);
            // position the text
            glPushMatrix();
            //glTranslatef((j + 0.3) / N, (i + 0.325) / N, 0);
            if (value < 10) {
                glTranslatef((j + 0.3) / N, (i + 0.325) / N+0.0125, 0);
                glScalef(0.001, 0.001, 0);
            } else if (value > 9 && value < 100) {
                glTranslatef((j + 0.15) / N, (i + 0.35) / N+0.0125, 0);
                glScalef(0.00075, 0.00075, 0);
            } else if (value > 99 && value < 1000){
                glTranslatef((j + 0.175) / N, (i + 0.4) / N+0.0125, 0);
                glScalef(0.0005, 0.0005, 0);
            } else {
                glTranslatef((j + 0.16) / N, (i + 0.425) / N, 0);
                glScalef(0.0004, 0.0004, 0);
            }
            for (int k = 0; k < strlen(str); k++) {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
            }
            glPopMatrix();
        }
    }
    
    //menu
    if (menu) {
        glColor3f(238.0/255.0/1.25, 228.0/255.0/1.25, 218.0/255.0/1.25);
        renderRoundedRectangle(0.1, 0.275, 0.8, 0.4, 0.15 / N);
        glColor3f(238.0/255.0, 228.0/255.0, 218.0/255.0);
        renderRoundedRectangle(0.1, 0.3, 0.8, 0.4, 0.15 / N);
        
        //text color
        glColor3f(119./255., 110./255., 101./255.);
        
        glLineWidth(4.0);
        char str[21];
        sprintf(str, "2048 v0.9");
        glPushMatrix();
        glTranslatef(0.1+0.15, 0.3+0.275, 0);
        glScalef(0.0005, 0.0005, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
        glColor3f(68./255./1.5, 58./255./1.5, 48./255./1.5);
        glRectf(0.1775, 0.336, 0.1775+0.05, 0.336-0.01);
        glRectf(0.597, 0.336, 0.597+0.05, 0.336-0.01);
        glColor3f(68./255., 58./255., 48./255.);
        glRectf(0.1775, 0.336, 0.1775+0.05, 0.336+0.05);
        glRectf(0.597, 0.336, 0.597+0.05, 0.336+0.05);
        glColor3f(119./255., 110./255., 101./255.);
        
        glColor3f(238.0/255.0/1.25, 128.0/255.0/1.25, 118.0/255.0/1.25);
        drawCircle(0.85, 0.64, 0.025, 20);
        glColor3f(238.0/255.0, 128.0/255.0, 118.0/255.0);
        drawCircle(0.85, 0.65, 0.025, 20);
        
        glLineWidth(2.5);
        glColor3f(238.0/255.0/1.5, 128.0/255.0/1.5, 118.0/255.0/1.5);
        glTranslatef(0.0, 0.0, 0);
        glScalef(1.0, 1.0, 0);
        glBegin(GL_LINES);
        glVertex2d(0.84, 0.64);
        glVertex2d(0.86, 0.66);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(0.84, 0.66);
        glVertex2d(0.86, 0.64);
        glEnd();
        
        glColor3f(119./255., 110./255., 101./255.);
        glLineWidth(2.0);
        sprintf(str, "X - play again  Q - quit");
        glPushMatrix();
        glTranslatef(0.19, 0.35, 0);
        glScalef(0.00025, 0.00025, 0);
        for (int k = 0; k < strlen(str); k++) {
            if (k == 0 || k == 16) glColor3f(219./255., 210./255., 201./255.);
            else glColor3f(119./255., 110./255., 101./255.);
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
        
        glLineWidth(2.5);
        glTranslatef(0.0, 0.0, 0);
        glScalef(1.0, 1.0, 0);
        glBegin(GL_LINES);
        glVertex2d(0.1775, 0.425);
        glVertex2d(0.825, 0.425);
        glEnd();
        
        sprintf(str, "Score: %d", score);
        glPushMatrix();
        glLineWidth(2.0);
        glTranslatef(0.1+0.0775, 0.475, 0);
        glScalef(0.00025, 0.00025, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
    }
    
    glutSwapBuffers();
}

int move_up(){
    int i, j, k;
    int moved = 0;
    for (j = 0; j < N; j++) {
        for (i = N-1, k = N-2; k >= 0; k--) {
            if (board[k][j] == 0) continue;
            if (board[i][j] == 0) {
                board[i][j] = board[k][j];
                board[k][j] = 0;
                moved = 1;
            } else if (board[i][j] == board[k][j]) {
                board[i][j] *= 2;
                board[k][j] = 0;
                score += board[i][j];
                i--;
                moved = 1;
            } else if (i-1 != k) {
                board[i-1][j] = board[k][j];
                board[k][j] = 0;
                i--;
                moved = 1;
            } else {
                i--;
            }
        }
    }
    return moved;
}

int move_down() {
    int i, j, k;
    int moved = 0;
    for (j = 0; j < N; j++) {
        for (i = 0, k = 1; k < N; k++) {
            if (board[k][j] == 0) continue;
            if (board[i][j] == 0) {
                board[i][j] = board[k][j];
                board[k][j] = 0;
                moved = 1;
            } else if (board[i][j] == board[k][j]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[k][j] = 0;
                i++;
                moved = 1;
            } else if (i+1 != k) {
                board[i+1][j] = board[k][j];
                board[k][j] = 0;
                i++;
                moved = 1;
            } else {
                i++;
            }
        }
    }
    return moved;
}

int move_left() {
    int i, j, k;
    int moved = 0;
    for (i = 0; i < N; i++) {
        for (j = 0, k = 1; k < N; k++) {
            if (board[i][k] == 0) continue;
            if (board[i][j] == 0) {
                board[i][j] = board[i][k];
                board[i][k] = 0;
                moved = 1;
            } else if (board[i][j] == board[i][k]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][k] = 0;
                j++;
                moved = 1;
            } else if (j+1 != k) {
                board[i][j+1] = board[i][k];
                board[i][k] = 0;
                j++;
                moved = 1;
            } else {
                j++;
            }
        }
    }
    return moved;
}

int move_right() {
    int i, j, k;
    int moved = 0;
    for (i = 0; i < N; i++) {
        for (j = N-1, k = N-2; k >= 0; k--) {
            if (board[i][k] == 0) continue;
            if (board[i][j] == 0) {
                board[i][j] = board[i][k];
                board[i][k] = 0;
                moved = 1;
            } else if (board[i][j] == board[i][k]) {
                board[i][j] *= 2;
                score += board[i][j];
                board[i][k] = 0;
                j--;
                moved = 1;
            } else if (j-1 != k) {
                board[i][j-1] = board[i][k];
                board[i][k] = 0;
                j--;
                moved = 1;
            } else {
                j--;
            }
        }
    }
    return moved;
}

void add_and_check() {
    // add a random value to the board
    int x = rand() % 4;
    int y = rand() % 4;
    while (board[x][y] != 0) {
        x = rand() % 4;
        y = rand() % 4;
    }
    board[x][y] = (rand() % 2 == 0) ? 2 : 4;
    
    int i, j;
    // check if there are any possible moves
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if ((i < N - 1 && board[i][j] == board[i + 1][j]) ||
                (j < N - 1 && board[i][j] == board[i][j + 1])) return;
        }
    }
    
    // check if board is full
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j] == 0) return;
        }
    }
    // No possible moves and board is full, game over
    menu = true;
}

void keyboard(unsigned char key, int x, int y) {
    int moved = 0;
    switch (tolower(key)) {
        case 'w':
            if(!menu) moved = move_up();
            break;
        case 's':
            if(!menu) moved = move_down();
            break;
        case 'a':
            if(!menu) moved = move_left();
            break;
        case 'd':
            if(!menu) moved = move_right();
            break;
        case 'm':
            menu = true;
            break;
        case 'x':
            if (menu) menu = false;
            init();
            break;
        case 'q':
            if (menu) exit(0);
            break;
    }
    if (!moved) {
        int i, j;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N-1; j++) {
                if (board[i][j] == board[i][j+1]) break;
            }
            if (board[i][j] == board[i][j+1]) break;
        }
        if (i == N && j == N-1) menu = true;
    } 
    if (moved) add_and_check();
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        // Convert pixel coordinates to (0.0, 1.0) format
        float xf = (float)x / (float)glutGet(GLUT_WINDOW_WIDTH);
        float yf = 1.0f - ((float)y / (float)glutGet(GLUT_WINDOW_HEIGHT));

        // Calculate distance from mouse click to center of button
        float dx = xf - 0.85f;
        float dy = yf - 0.65f;
        float dist = sqrt(dx*dx + dy*dy);

        // Check if mouse click is inside button circle
        if (dist <= 0.025f) {
            if(menu) menu = false;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2048 v0.9");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    init();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    
    glutMainLoop();

    return 0;
}
