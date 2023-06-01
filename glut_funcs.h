void display() {
  if (menu) { glClearColor(204.0/255.0/1.5, 192.0/255.0/1.5, 179.0/255.0/1.5, 1.0); }
  else      { glClearColor(204.0/255.0,     192.0/255.0,     179.0/255.0,     1.0); }

  glClear(GL_COLOR_BUFFER_BIT);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int value = board[i][j];
      if (value == 0) continue;
      
      Color bcolor = colors[(int)log2(value) - 1];
      int r = bcolor.r, g = bcolor.g, b = bcolor.b;
      
      // Draw blocks
      float cr = r, cg = g, cb = b;
      if (menu) cr /= 1.5, cg /= 1.5, cb /= 1.5;
      
      color(cr/1.25, cg/1.25, cb/1.25);
      drawRoundedRectangle((j + 0.1) / N, (i + 0.1) / N-0.0125, 0.8 / N, 0.8 / N, 0.1 / N);
      color(cr, cg, cb);
      drawRoundedRectangle((j + 0.1) / N, (i + 0.1) / N+0.0125, 0.8 / N, 0.8 / N, 0.1 / N);
      
      // Draw text on blocks
               float tcr = 119.0, tcg = 110.0, tcb = 101.0;
      if (value > 9) tcr = 249.0, tcg = 246.0, tcb = 242.0;
      
      if (menu) tcr /= 1.5, tcg /= 1.5, tcb /= 1.5;
      color(tcr, tcg, tcb);
      
      sprintf(str, "%d", value);
      if      (value < 10)   { text((j + 0.3) / N,   (i + 0.325) / N+0.0125, 10.0, 10.0, 4.0); }
      else if (value < 100)  { text((j + 0.15) / N,  (i + 0.35) / N+0.0125,  7.5,  7.5,  4.0); }
      else if (value < 1000) { text((j + 0.175) / N, (i + 0.4) / N+0.0125,   5.0,  5.0,  4.0); }
      else                   { text((j + 0.16) / N,  (i + 0.425) / N+0.0125, 4.0,  4.0,  4.0); }
    }
  }
  
  // Menu
  if (menu) {
    color(238.0/1.25, 228.0/1.25, 218.0/1.25);
    drawRoundedRectangle(0.1, 0.25, 0.8, 0.5, 0.05);
    color(238.0,      228.0,      218.0);
    drawRoundedRectangle(0.1, 0.275, 0.8, 0.5, 0.05);
        
    drawCloseButton(0.825, 0.69, 0.05);
        
    if (showkey) {
      color(159.0, 150.0, 141.0);
      sprintf(str, "esc");
      text(0.74, 0.715, 2.0, 2.0, 2.0);
    }
    
    glColor3f(119.0/255.0, 110.0/255.0, 101.0/255.0);
    glPushMatrix();
    if (gameover) {
      sprintf(str, "Game over!");
      text(0.3, 0.65, 4.0, 4.0, 3.5);
    } else {
      sprintf(str, "2048");
      text(0.41, 0.65, 4.0, 4.0, 3.5);
    }
    
    sprintf(str, "Play again");
    drawMenuButton(0.1775, 0.426, 0.3, 0.05);
    sprintf(str, "Quit");
    drawMenuButton(0.1775, 0.326, 0.15, 0.05);
    
    if (showkey) {
      color(159., 150., 141.);
      sprintf(str, "p");
      text(0.5, 0.455, 2.0, 2.0, 2.0);
      sprintf(str, "q");
      text(0.35, 0.355, 2.0, 2.0, 2.0);
    }
    
    // Draw line between score number and menu buttons
    color(119.0, 110.0, 101.0);
    glLineWidth(lineWidth);
    glTranslatef(0.0, 0.0, 0);
    glScalef(1.0, 1.0, 0);
    glBegin(GL_LINES);
    glVertex2d(0.1775, 0.525);
    glVertex2d(0.825, 0.525);
    glEnd();
    
    sprintf(str, "Score: %d", score);
    text(0.1775, 0.575, 2.5, 2.5, 2.0);
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
      if (isGameOver()) gameover = true, menu = true;
    } else {
      if (isGameOver()) gameover = true, menu = true;
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
    if (menu) {
      float dist = sqrt(dx*dx + dy*dy);
      // Check if mouse click is inside...
      
      // Menu close button
      if (dist <= 0.025f) menu = false;
      
      // Play again button
      if (xf >= 0.1775 && xf <= 0.4775 && yf >= 0.426 && yf <= 0.486) { init(); menu = false; }
      
      // Quit button
      if (xf >= 0.1775 && xf <= 0.3275 && yf >= 0.326 && yf <= 0.386) exit(0);
    }
  }
  glutPostRedisplay();
}
