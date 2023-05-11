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
            
            // Drawing blocks
            float cr = r/255.0, cg = g/255.0, cb = b/255.0;
            if (menu) { cr = r/255.0/1.5; cg = g/255.0/1.5; cb = b/255.0/1.5; }
            glColor3f(cr/1.25, cg/1.25, cb/1.25);
            drawRoundedRectangle((j + 0.1) / N, (i + 0.1) / N-0.0125, 0.8 / N, 0.8 / N, 0.1 / N, 20);
            glColor3f(cr, cg, cb);
            drawRoundedRectangle((j + 0.1) / N, (i + 0.1) / N+0.0125, 0.8 / N, 0.8 / N, 0.1 / N, 20);
                
            // Set the color of the text
            float tcr, tcg, tcb;
            if (value < 9) {
                tcr = 119./255.; tcg = 110./255.; tcb = 101./255.;
            } else {
                tcr = 249./255.; tcg = 246./255.; tcb = 242./255.;
            }
            if (menu) {  tcr /= 1.5; tcg /= 1.5; tcb /= 1.5; }
            glColor3f(tcr, tcg, tcb);
            
            // Draw block value
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
    
    // Menu
    if (menu) {
        char str[21];
        glColor3f(238.0/255.0/1.25, 228.0/255.0/1.25, 218.0/255.0/1.25);
        drawRoundedRectangle(0.1, 0.25, 0.8, 0.5, 0.05, 20);
        glColor3f(238.0/255.0, 228.0/255.0, 218.0/255.0);
        drawRoundedRectangle(0.1, 0.275, 0.8, 0.5, 0.05, 20);
        
        drawCloseButton(0.825, 0.69, 0.05);
        
        if(showkey) {
            glColor3f(159./255., 150./255., 141./255.);
            glLineWidth(lineWidth*2.0);
            glPushMatrix();
            glTranslatef(0.71, 0.71, 0);
            glScalef(0.00025, 0.00025, 0);
            sprintf(str, "esc");
            for (int k = 0; k < strlen(str); k++) {
                glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
            }
            glPopMatrix();
        }
        
        glColor3f(119./255., 110./255., 101./255.);
        glLineWidth(lineWidth*4.0);
        glPushMatrix();
        if(gameover) {
          sprintf(str, "Game over!");
          glTranslatef(0.25, 0.65, 0);
        } else {
          sprintf(str, "2048");
          glTranslatef(0.4, 0.65, 0);
        }
        glScalef(0.0005, 0.0005, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
        
        drawMenuButton(0.1775, 0.426, 0.3, 0.05, "Play again  p");
        drawMenuButton(0.1775, 0.326, 0.15, 0.05, "Quit  q");

        glColor3f(119./255., 110./255., 101./255.);
        
        // Draw line between score number and menu buttons
        glLineWidth(lineWidth);
        glTranslatef(0.0, 0.0, 0);
        glScalef(1.0, 1.0, 0);
        glBegin(GL_LINES);
        glVertex2d(0.1775, 0.525);
        glVertex2d(0.825, 0.525);
        glEnd();
        
        sprintf(str, "Score: %d", score);
        glPushMatrix();
        glLineWidth(lineWidth*2.0);
        glTranslatef(0.1775, 0.575, 0);
        glScalef(0.00025, 0.00024, 0);
        for (int k = 0; k < strlen(str); k++) {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, str[k]);
        }
        glPopMatrix();
    }
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (menu) {
        switch (tolower(key)) {
            case 'p':  // play again
                init();
                menu = false;
                break;
            case 'q':  // exit the game
                exit(0);
                break;
            case 0x1B:  // close menu
                menu = false;
                break;
        }
    } else {
        int moved = 0;
        switch (tolower(key)) {
            case 'w':  // Move up
                moved = move_up();
                break;
            case 's':  // Move down
                moved = move_down();
                break;
            case 'a':  // Move left
                moved = move_left();
                break;
            case 'd':  // Move right
                moved = move_right();
                break;
            case 27:  // Open menu
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
            if (isGameOver()) {
                gameover = true;
                menu = true;
            }
        }
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
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
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    
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
        float dy = yf - 0.725f;
        
        // if menu is opened
        if(menu){
            float dist = sqrt(dx*dx + dy*dy);
            // Check if mouse click is inside X button
            if (dist <= 0.025f) {
                menu = false;
            }
            // Check if mouse click is inside menu button
            if (xf >= 0.1775 && xf <= 0.4775 && yf >= 0.426 && yf <= 0.486) {
                // Play again
                init();
                menu = false;
            } else if (xf >= 0.1775 && xf <= 0.3275 && yf >= 0.326 && yf <= 0.386) {
                // Quit
                exit(0);
            }
        }
    }
    glutPostRedisplay();
}
