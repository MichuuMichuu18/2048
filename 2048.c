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
bool gameover = false;
int score = 0;

float lineWidth = 1.0;

int board[N][N];

typedef struct {
    int r, g, b;
} Color;

Color colors[] = {
    {238, 228, 218},   // 2
    {237, 224, 200},   // 4
    {242, 177, 121},   // 8
    {245, 149, 99},    // 16
    {246, 124, 95},    // 32
    {246, 94, 59},     // 64
    {237, 207, 114},   // 128
    {237, 204, 97},    // 256
    {237, 204, 80},    // 512
    {237, 197, 63},    // 1024
    {237, 194, 46},    // 2048
    {0, 0, 0}          // Default
};

void init() {
    int i, j;
    
    score = 0;
    gameover = false;

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

void drawRoundedRectangle(float x, float y, float width, float height, float radius) {
    int i;
    int triangleAmount = 20;
    
    //draw corners
    drawCircle(x + width - radius, y + radius, radius, triangleAmount);
    drawCircle(x + radius, y + radius, radius, triangleAmount);
    drawCircle(x + width - radius, y + height - radius, radius, triangleAmount);
    drawCircle(x + radius, y + height - radius, radius, triangleAmount);
    
    //fill with rectangles
    glRectf(x, y + radius, x + width, y + height - radius);
    glRectf(x + radius, y, x + width - radius, y + height);
}

void drawX(float x, float y, float size) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    glBegin(GL_LINES);
    glVertex2f(-1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glVertex2f(1, -1);
    glEnd();

    glPopMatrix();
}

void drawCloseButton(float x, float y, float size){
    glColor3f(238.0/255.0/1.25, 128.0/255.0/1.25, 118.0/255.0/1.25);
    drawCircle(x+size/2, y+size/2, size/2, 20);
    glColor3f(238.0/255.0, 128.0/255.0, 118.0/255.0);
    drawCircle(x+size/2, y+size/2+0.01, size/2, 20);
    
    // clone line width
    GLfloat prevLineWidth;
    glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);

    // draw X
    glLineWidth(lineWidth*3.0);
    glColor3f(238.0/255.0/1.5, 128.0/255.0/1.5, 118.0/255.0/1.5);
    drawX(x+size/2, y+size/2+0.01, size/5);
    
    // Use previous line width
    glLineWidth(prevLineWidth);
}

void drawMenuButton(float x, float y, float xsize, float ysize){
    //darker part of button
    glColor3f(68./255./1.5, 58./255./1.5, 48./255./1.5);
    glRectf(x, y, x+xsize, y-0.01+ysize);
    
    //brighter part of button
    glColor3f(68./255., 58./255., 48./255.);
    glRectf(x, y+0.01, x+xsize, y+0.01+ysize);
}

void display() {
    int i, j;
    
    if(menu) { glClearColor(204./255./1.5, 192./255./1.5, 179./255./1.5, 1.0); }
    else { glClearColor(204./255., 192./255., 179./255., 1.0); }

    glClear(GL_COLOR_BUFFER_BIT);

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int value = board[i][j];
            if (value == 0) continue;
            
            Color color = colors[(int)log2(value) - 1];
            int r = color.r, g = color.g, b = color.b;
            
            glLineWidth(lineWidth*4.0);
            
            // drawing rectangles
            float cr = r/255.0, cg = g/255.0, cb = b/255.0;
            if (menu) { cr = r/255.0/1.5; cg = g/255.0/1.5; cb = b/255.0/1.5; }
            glColor3f(cr/1.25, cg/1.25, cb/1.25);
            drawRoundedRectangle((j + 0.1) / N, (i + 0.1) / N-0.0125, 0.8 / N, 0.8 / N, 0.1 / N);
            glColor3f(cr, cg, cb);
            drawRoundedRectangle((j + 0.1) / N, (i + 0.1) / N+0.0125, 0.8 / N, 0.8 / N, 0.1 / N);
                
            // set the color of the text
            float tcr, tcg, tcb;
            if (value < 9) {
                tcr = 119./255.; tcg = 110./255.; tcb = 101./255.;
            } else {
                tcr = 249./255.; tcg = 246./255.; tcb = 242./255.;
            }
            if (menu) {  tcr /= 1.5; tcg /= 1.5; tcb /= 1.5; }
            glColor3f(tcr, tcg, tcb);
            
            // draw block value
            char str[10];
            sprintf(str, "%d", value);
            glPushMatrix();
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
    
    // menu
    if (menu) {
        glColor3f(238.0/255.0/1.25, 228.0/255.0/1.25, 218.0/255.0/1.25);
        drawRoundedRectangle(0.1, 0.2, 0.8, 0.5, 0.15 / N);
        glColor3f(238.0/255.0, 228.0/255.0, 218.0/255.0);
        drawRoundedRectangle(0.1, 0.225, 0.8, 0.5, 0.15 / N);
        
        drawCloseButton(0.825, 0.635, 0.05);
        
        glColor3f(119./255., 110./255., 101./255.);
        glLineWidth(lineWidth*4.0);
        char str[21];
        glPushMatrix();
        if(gameover) {
          sprintf(str, "Game over!");
          glTranslatef(0.25, 0.325+0.275, 0);
        } else {
          sprintf(str, "2048");
          glTranslatef(0.4, 0.325+0.275, 0);
        }
        glScalef(0.0005, 0.0005, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
        
        //menu buttons
        glColor3f(1,0,0);
        drawMenuButton(0.1775, 0.376, 0.3, 0.05);
        drawMenuButton(0.1775, 0.276, 0.15, 0.05);
        //drawMenuButton(0.597, 0.326, 0.05, 0.05);
        
        glColor3f(219./255., 210./255., 201./255.);
        glLineWidth(lineWidth*2.0);
        //sprintf(str, "X - play again  Q - quit");
        sprintf(str, "Play again");
        glPushMatrix();
        glTranslatef(0.2, 0.4, 0);
        glScalef(0.00025, 0.00025, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
        //sprintf(str, "X - play again  Q - quit");
        sprintf(str, "Quit");
        glPushMatrix();
        glTranslatef(0.2, 0.3, 0);
        glScalef(0.00025, 0.00025, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
        glColor3f(119./255., 110./255., 101./255.);
        
        //line between score and menu buttons
        glLineWidth(lineWidth*2.0);
        glTranslatef(0.0, 0.0, 0);
        glScalef(1.0, 1.0, 0);
        glBegin(GL_LINES);
        glVertex2d(0.1775, 0.475);
        glVertex2d(0.825, 0.475);
        glEnd();
        
        sprintf(str, "Score: %d", score);
        glPushMatrix();
        glLineWidth(lineWidth*2.0);
        glTranslatef(0.1+0.0775, 0.525, 0);
        glScalef(0.00025, 0.00024, 0);
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

// add a random value to an empty tile on the board
void add() {
    int x, y;
    do {
        x = rand() % N;
        y = rand() % N;
    } while (board[x][y] != 0);
    board[x][y] = (rand() % 2 == 0) ? 2 : 4;
}

// check if the game is over
bool isGameOver() {
    // check for any empty tile
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    // check for any adjacent tiles with the same value
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = board[i][j];
            if ((i > 0 && board[i-1][j] == val) ||
                (i < N-1 && board[i+1][j] == val) ||
                (j > 0 && board[i][j-1] == val) ||
                (j < N-1 && board[i][j+1] == val)) {
                return false;
            }
        }
    }

    // no empty tile and no adjacent tiles with the same value, game over
    return true;
}

// handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    if (menu) {
        //will probably be removed in the future
        switch (tolower(key)) {
            /*case 'x':  // restart the game
                init();
                menu = false;
                break;
            case 'q':  // exit the game
                exit(0);
                break;*/
            case 27:  // close menu
                menu = false;
                break;
        }
    } else {
        int moved = 0;
        switch (tolower(key)) {
            case 'w':  // move up
                moved = move_up();
                break;
            case 's':  // move down
                moved = move_down();
                break;
            case 'a':  // move left
                moved = move_left();
                break;
            case 'd':  // move right
                moved = move_right();
                break;
            case 27:  // open menu
                menu = true;
                break;
        }
        if (moved) {
            add();
            if (isGameOver()) {
                gameover = true;
                menu = true;
            }
        } else {
            // check for game over
            if (isGameOver()) {
                gameover = true;
                menu = true;
            }
        }
    }
    glutPostRedisplay();
}

int viewportWidth, viewportHeight, xOffset, yOffset;

void resize(int width, int height) {
    // Calculate the largest square that fits within the window
    if (width < height) {
        viewportWidth = viewportHeight = width;
        xOffset = 0;
        yOffset = (height - width) / 2;
    } else {
        viewportWidth = viewportHeight = height;
        xOffset = (width - height) / 2;
        yOffset = 0;
    }

    // Set the viewport and orthographic projection matrix
    glViewport(xOffset, yOffset, viewportWidth, viewportHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    
    // Scale the line width based on the window size
    lineWidth = viewportWidth/480.0f;
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        // Convert pixel coordinates to (0.0, 1.0) format
        float xf = ((float)x - xOffset) / (float)viewportWidth;
        float yf = 1.0f - (((float)y - yOffset) / (float)viewportHeight);
        
        // Calculate distance from mouse click to center of X button
        float dx = xf - 0.85f;
        float dy = yf - 0.67f;
        
        // if menu is opened
        if(menu){
            float dist = sqrt(dx*dx + dy*dy);
            // Check if mouse click is inside X button
            if (dist <= 0.025f) {
                if(menu) menu = false;
            }
            // Check if mouse click is inside menu button
            if (xf >= 0.1775 && xf <= 0.1775+0.3 && yf >= 0.376 && yf <= 0.376+0.06) {
                //Play again
                init();
                menu = false;
            } else if (xf >= 0.1775 && xf <= 0.1775+0.15 && yf >= 0.276 && yf <= 0.276+0.06) {
                //Quit
                exit(0);
            }
        }
    }
    glutPostRedisplay();
}

void idle() {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2048");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);

    init();
    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    
    glutMainLoop();

    return 0;
}
