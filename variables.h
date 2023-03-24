#define PI acos(-1.0)

#define N 4

float lineWidth = 1.0;
bool menu, gameover;
int board[N][N], score, viewportWidth, viewportHeight, xOffset, yOffset;

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
    {0, 0, 0}          // Other blocks
};
