#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

#define ALIVE 'o'
#define DEAD '.'

int CountAliveNeighbours(char grid[HEIGHT][WIDTH], int y, int x);
void InitGrid(char grid[HEIGHT][WIDTH]);
void DrawGrid(char grid[HEIGHT][WIDTH]);
void NextGen(char grid[HEIGHT][WIDTH], char grid_next[HEIGHT][WIDTH]);
void SwapGrid(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]);
void Play(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]);
void CheckInput(int *end_game, int *speed);
void ClearGrid(char grid[HEIGHT][WIDTH]);

int CheckIfSomeoneAlive(char grid[HEIGHT][WIDTH]);  // вернет 0 если все умерли 1 если кто-то жив
int CheckIsStillLife(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]);

// TODO 5 файлов
// TODO 2 этап детекция все застыли

int main(void) {
    char grid[HEIGHT][WIDTH];
    ClearGrid(grid);
    InitGrid(grid);

    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    if (freopen("/dev/tty", "r", stdin) != NULL) {
        char next_grid[HEIGHT][WIDTH];
        Play(grid, next_grid);
    }

    refresh();
    endwin();

    return 0;
}

void Play(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]) {
    int end_game = 1, speed = 300;

    timeout(speed);
    while (end_game) {
        NextGen(grid, next_grid);
        DrawGrid(next_grid);
        SwapGrid(grid, next_grid);
        end_game = CheckIfSomeoneAlive(grid);
        //        end_game = CheckIsStillLife(grid, next_grid);
        CheckInput(&end_game, &speed);
    }
}

void CheckInput(int *end_game, int *speed) {
    char ch = getch();
    if (ch == 'q') {
        *end_game = 0;
    } else if (ch == 'f' && *speed > 10) {
        *speed = *speed > 100 ? *speed - 100 : *speed - 10;
        timeout(*speed);
    } else if (ch == 's') {
        *speed += 100;
        timeout(*speed);
    }
}
void ClearGrid(char grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = DEAD;
        }
    }
}
void InitGrid(char grid[HEIGHT][WIDTH]) {
    char buffer[WIDTH + 2];
    int row = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL && row < HEIGHT) {
        for (int col = 0; col < WIDTH && buffer[col] != '\n' && buffer[col] != '\0'; col++) {
            if (col < WIDTH - 2) {
                grid[row][col] = buffer[col];
            }
        }
        row++;
    }
}

void DrawGrid(char grid[HEIGHT][WIDTH]) {
    clear();
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printw("%c", grid[i][j]);
        }
        printw("\n");
    }
    refresh();
}

int CountAliveNeighbours(char arr[HEIGHT][WIDTH], int y, int x) {
    int alive_count = 0;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            int ii = i % HEIGHT;  // костыль
            int jj = j % WIDTH;
            if (arr[ii][jj] == ALIVE) {
                alive_count++;
            }
        }
    }
    if (arr[y][x] == ALIVE) {
        alive_count--;
    }

    return alive_count;
}

void NextGen(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            char cell = grid[i][j];
            int neighbours = CountAliveNeighbours(grid, i, j);
            if (cell == ALIVE) {
                next_grid[i][j] = (neighbours < 2 || neighbours > 3) ? DEAD : ALIVE;
            } else if (cell == ALIVE) {
                next_grid[i][j] = (neighbours == 2 || neighbours == 3) ? ALIVE : DEAD;
            } else if (cell == DEAD) {
                next_grid[i][j] = (neighbours == 3) ? ALIVE : DEAD;
            } else {
                next_grid[i][j] = DEAD;
            }
        }
    }
}

void SwapGrid(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = next_grid[i][j];
        }
    }
}

int CheckIfSomeoneAlive(char grid[HEIGHT][WIDTH]) {
    int alive_count = 0;
    int status = 0;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (grid[i][j] == ALIVE) {
                alive_count += 1;
            }
        }
    }
    if (alive_count > 0) {
        status = 1;
    } else {
        status = 0;
    }
    return status;
}

// int CheckIsStillLife(char grid[HEIGHT][WIDTH], char next_grid[HEIGHT][WIDTH]) {
//     int status = 0;
//     int not_same_count = 0;
//     for (int i = 0; i < HEIGHT; ++i) {
//         for (int j = 0; j < WIDTH; ++j) {
//             if (next_grid[i][j] != grid[i][j]) {
//                 not_same_count += 1;
//             }
//         }
//     }
//     if (not_same_count > 0) {
//         status = 1;
//     } else {
//         status = 0;
//     }
//     return status;
// }