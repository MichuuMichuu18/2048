void drawCircle(float x, float y, float radius) {
  glBegin(GL_TRIANGLE_FAN);

  // Center of the circle
  glVertex2f(x, y);

  // Vertices of the circle
  for (int i = 0; i <= num_segments; i++) {
    float angle = i * 2.0f * PI / num_segments; // Angle of the current vertex
    float dx = radius * cosf(angle); // X-coordinate of the current vertex
    float dy = radius * sinf(angle); // Y-coordinate of the current vertex
    glVertex2f(x + dx, y + dy); // Set the current vertex
  }

  glEnd();
}

void drawRoundedRectangle(float x, float y, float width, float height, float radius) {
  int i;
  
  // Draw corners
  drawCircle(x + width - radius, y + radius, radius);
  drawCircle(x + radius, y + radius, radius);
  drawCircle(x + width - radius, y + height - radius, radius);
  drawCircle(x + radius, y + height - radius, radius);
  
  // Fill empty space with rectangles
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

void drawCloseButton(float x, float y, float size) {
  glColor3f(238.0/255.0/1.25, 128.0/255.0/1.25, 118.0/255.0/1.25);
  drawCircle(x+size/2, y+size/2, size/2);
  glColor3f(238.0/255.0, 128.0/255.0, 118.0/255.0);
  drawCircle(x+size/2, y+size/2+0.01, size/2);
  
  // Clone line width
  GLfloat prevLineWidth;
  glGetFloatv(GL_LINE_WIDTH, &prevLineWidth);

  // Draw X
  glLineWidth(lineWidth*3.0);
  glColor3f(238.0/255.0/1.5, 128.0/255.0/1.5, 118.0/255.0/1.5);
  drawX(x+size/2, y+size/2+0.01, size/5);
  
  // Set previous line width
  glLineWidth(prevLineWidth);
}

void drawMenuButton(float x, float y, float xsize, float ysize, char* text) {
  // Darker part of the button
  glColor3f(68./255./1.5, 58./255./1.5, 48./255./1.5);
  drawRoundedRectangle(x, y, xsize, -0.01+ysize, 0.015);
  
  // Brighter part of the button
  glColor3f(68./255., 58./255., 48./255.);
  drawRoundedRectangle(x, y+0.01, xsize, 0.01+ysize, 0.015);
  
  // Text on top of the button
  glColor3f(219./255., 210./255., 201./255.);
  glLineWidth(lineWidth*2.0);
  glPushMatrix();
  glTranslatef(x+0.025, y+ysize/2, 0);
  glScalef(0.00025, 0.00025, 0);
  int textlen = strlen(text);
  for (int k = 0; k < textlen; k++) {
    if(showkey && k > textlen-2) { glColor3f(159./255., 150./255., 141./255.); }
    else { glColor3f(238.0/255.0, 228.0/255.0, 218.0/255.0); }
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[k]);
  }
  glPopMatrix();
}
