#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define N 4

bool menu = false;
int score = 0;

int board[N][N];

void init() {
    int i, j;

    srand(time(NULL));

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    int x = rand() % 4;
    int y = rand() % 4;
    board[x][y] = 2;
}

void renderRoundedRectangle(float x, float y, float width, float height, float radius) {
    int i;
    int triangleAmount = 20; // increase for more roundness
    float twicePi = 2.0f * acos(-1.0);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + width - radius, y + radius); // top right corner
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(x + width - radius + (radius * cos(i * twicePi / triangleAmount)), y + radius + (radius * sin(i * twicePi / triangleAmount)));
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + radius, y + radius); // top left corner
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(x + radius + (radius * cos(i * twicePi / triangleAmount)), y + radius + (radius * sin(i * twicePi / triangleAmount)));
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + width - radius, y + height - radius); // bottom right corner
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(x + width - radius + (radius * cos(i * twicePi / triangleAmount)), y + height - radius + (radius * sin(i * twicePi / triangleAmount)));
        }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + radius, y + height - radius); // bottom left corner
        for(i = 0; i <= triangleAmount; i++) {
            glVertex2f(x + radius + (radius * cos(i * twicePi / triangleAmount)), y + height - radius + (radius * sin(i * twicePi / triangleAmount)));
        }
    glEnd();
    
    glRectf(x, y + radius, x + width + 1./500., y + height - radius);
    glRectf(x + radius, y - 1./500., x + width - radius, y + height);
}

void display() {
    int i, j;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int value = board[i][j];
            if (value == 0) continue;

            int r = 255, g = 255, b = 255;
            switch (value) {
                case 2:
                    r = 238;
                    g = 228;
                    b = 218;
                    break;
                case 4:
                    r = 237;
                    g = 224;
                    b = 200;
                    break;
                case 8:
                    r = 242;
                    g = 177;
                    b = 121;
                    break;
                case 16:
                    r = 245;
                    g = 149;
                    b = 99;
                    break;
                case 32:
                    r = 246;
                    g = 124;
                    b = 95;
                    break;
                case 64:
                    r = 246;
                    g = 94;
                    b = 59;
                    break;
                case 128:
                    r = 237;
                    g = 207;
                    b = 114;
                    break;
                case 256:
                    r = 237;
                    g = 204;
                    b = 97;
                    break;
                case 512:
                    r = 237;
                    g = 204;
                    b = 80;
                    break;
                case 1024:
                    r = 237;
                    g = 197;
                    b = 63;
                    break;
                case 2048:
                    r = 237;
                    g = 194;
                    b = 46;
                    break;
                default:
                    r = 0;
                    g = 0;
                    b = 0;
                    break;
            }

            glColor3f(r/255.0, g/255.0, b/255.0);
            //glRectf((j + 0.1) / N, (i + 0.1) / N, (j + 0.9) / N, (i + 0.9) / N);
            
            if (menu) {
                //start screen background
                glColor3f(238./255., 228./255., 218./255.);
                renderRoundedRectangle(0.1, 0.3, 0.8, 0.4, 0.15 / N);
                
                //text color
                glColor3f(119./255., 110./255., 101./255.);
                char str[21];
                int len;
                
                glLineWidth(4.0);
                sprintf(str, "2048 v0.7");
                glPushMatrix();
                glTranslatef(0.1+0.15, 0.3+0.25, 0);
                glScalef(0.0005, 0.0005, 0);
                len = strlen(str);
                for (int k = 0; k < len; k++) {
                    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
                }
                glPopMatrix();
                glLineWidth(2.0);
                sprintf(str, "Press x to play again");
                glPushMatrix();
                glTranslatef(0.1+0.11, 0.3+0.15, 0);
                glScalef(0.00025, 0.00025, 0);
                len = strlen(str);
                for (int k = 0; k < len; k++) {
                    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
                }/*
                glPopMatrix();
                sprintf(str, "Press q to quit");
                glPushMatrix();
                glTranslatef(0.1+0.185, 0.3+0.1, 0);
                glScalef(0.00025, 0.00025, 0);
                len = strlen(str);
                for (int k = 0; k < len; k++) {
                    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
                }
                glPopMatrix();*/
            } else if (!menu) {
                glLineWidth(4.0);
                renderRoundedRectangle((j + 0.1) / N, (i + 0.1) / N, 0.8 / N, 0.8 / N, 0.15 / N);
                
                // set the color of the text
                if (value < 9) {
                    glColor3f(119./255., 110./255., 101./255.);
                } else {
                    glColor3f(249./255., 246./255., 242./255.);
                }
                // convert the value to a string
                char str[10];
                sprintf(str, "%d", value);
                // position the text
                glPushMatrix();
                //glTranslatef((j + 0.3) / N, (i + 0.325) / N, 0);
                if (value < 10) {
                    glTranslatef((j + 0.3) / N, (i + 0.325) / N, 0);
                    glScalef(0.001, 0.001, 0);
                } else if (value > 9 && value < 100) {
                    glTranslatef((j + 0.15) / N, (i + 0.35) / N, 0);
                    glScalef(0.00075, 0.00075, 0);
                }
                else if (value > 99 && value < 1000){
                    glTranslatef((j + 0.175) / N, (i + 0.4) / N, 0);
                    glScalef(0.0005, 0.0005, 0);
                }
                else {
                    glTranslatef((j + 0.16) / N, (i + 0.425) / N, 0);
                    glScalef(0.0004, 0.0004, 0);
                }
                int len = strlen(str);
                for (int k = 0; k < len; k++) {
                    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
                }
            }
            
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}

int move_up(){
    int i, j, k;
    int moved = 0;
    for (j = 0; j < N; j++) {
        for (i = N-1, k = N-2; k >= 0; k--) {
            if (board[k][j] == 0) {
                continue;
            }
            if (board[i][j] == 0) {
                board[i][j] = board[k][j];
                board[k][j] = 0;
                moved = 1;
            } else if (board[i][j] == board[k][j]) {
                board[i][j] *= 2;
                board[k][j] = 0;
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
            if (board[k][j] == 0) {
                continue;
            }
            if (board[i][j] == 0) {
                board[i][j] = board[k][j];
                board[k][j] = 0;
                moved = 1;
            } else if (board[i][j] == board[k][j]) {
                board[i][j] *= 2;
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
            if (board[i][k] == 0) {
                continue;
            }
            if (board[i][j] == 0) {
                board[i][j] = board[i][k];
                board[i][k] = 0;
                moved = 1;
            } else if (board[i][j] == board[i][k]) {
                board[i][j] *= 2;
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
            if (board[i][k] == 0) {
                continue;
            }
            if (board[i][j] == 0) {
                board[i][j] = board[i][k];
                board[i][k] = 0;
                moved = 1;
            } else if (board[i][j] == board[i][k]) {
                board[i][j] *= 2;
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
    board[x][y] = 2;
    
    int i, j;
    // check if there are any possible moves
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if ((i < N - 1 && board[i][j] == board[i + 1][j]) ||
                (j < N - 1 && board[i][j] == board[i][j + 1])) {
                return;
            }
        }
    }
    
    // check if board is full
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                return;
            }
        }
    }
    // No possible moves and board is full, game over
    menu = true;
    init();
}

void keyboard(unsigned char key, int x, int y) {
    int moved = 0;
    switch (key) {
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
        case 'r':
            if(!menu) {init();}
            break;
        case 'x':
            menu = false;
            break;
        /*case 'q':
            exit(0);
            break;*/
    }
    if (!moved) {
        int i, j;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N-1; j++) {
                if (board[i][j] == board[i][j+1]) {
                    break;
                }
            }
            if (board[i][j] == board[i][j+1]) {
                break;
            }
        }
        if (i == N && j == N-1) {
            menu = true;
            init();
        }
    } 
    if (moved) {
      add_and_check();
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2048 v0.7");
    glClearColor(204./255., 192./255., 179./255., 1.0);
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
    glutMainLoop();

    return 0;
}
