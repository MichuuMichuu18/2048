void init() {
    int i, j;
    
    gamenum++;
    if(gamenum > 1) showkey = false;
    score = 0, menu = false, gameover = false;

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

void add() {
    int x, y;
    do {
        x = rand() % N;
        y = rand() % N;
    } while (board[x][y] != 0);
    board[x][y] = (rand() % 2 == 0) ? 2 : 4;
}

bool isGameOver() {
    // Check for any empty tile
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    // Check for any adjacent tiles with the same value
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

    // If there is no empty tile and no adjacent tiles with the same value, game is over
    return true;
}
