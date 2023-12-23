#include <iostream>
#include <cstdlib>
#include <ncurses.h> 

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = (rand() % width) + 1;
    fruitY = (rand() % height) + 1;
    score = 0;
}

void Draw() {
    clear();

    for (int i = 0; i < width + 2; i++) {
        mvprintw(0, i, "+");
    }

    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (i == 0 | i == 21)
                mvprintw(i, j, "+");
            else if (j == 0 | j == 21)
                mvprintw(i, j, "+");
            else if (i == y && j == x)
                mvprintw(i, j, "D");
            else if (i == fruitY && j == fruitX)
                mvprintw(i, j, "8==0");
            else
                for (int k = 0; k < ntail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        mvprintw(i, j, "0");
                    }
                }
        }
    }
    mvprintw(23, 0, "Score: %d", score); 
    refresh();
}

void Input() {

    keypad(stdscr, TRUE);
    halfdelay(1);

    int c = getch();

    switch (c)
    {
    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 'x':
        gameOver = true;
        break;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < ntail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
        case STOP:
            break;
    }

    if (x >= width) x = 1; else if (x < 1) x = width - 1;
    if (y >= height) y = 1; else if (y < 1) y = height - 1;

    if (x == fruitX && y == fruitY) {
        score++;
        fruitX = (rand() % (width - 2)) + 1; 
        fruitY = (rand() % (height - 2)) + 1;
        ntail++;
    }

    for (int i = 0; i < ntail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }
    getch();
    endwin();
}
