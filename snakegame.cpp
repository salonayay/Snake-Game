#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int breadth = 20;
const int height = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;

// Function to set console text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to initialize the game
void Setup() {
    gameOver = false;
    dir = STOP;
    x = breadth / 2;
    y = height / 2;
    fruitx = rand() % breadth;
    fruity = rand() % height;
    score = 0;
    nTail = 0;
}

// Function to draw the game
void Draw() {
    system("cls");

    // Top border
    setColor(0); // black
    for (int i = 0; i < breadth + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < breadth; j++) {
            if (j == 0) {
                setColor(0); // black
                cout << "#";
            }
            if (i == y && j == x) {
                setColor(10); // Green
                cout << "O"; // Snake's head
            } else if (i == fruity && j == fruitx) {
                setColor(12); // Red
                cout << "F"; // Food
            } else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailx[k] == j && taily[k] == i) {
                        setColor(14); // Yellow
                        cout << "o"; // Snake's body
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == breadth - 1) {
                setColor(0); // black
                cout << "#";
            }
        }
        cout << endl;
    }z

    // Bottom border
    setColor(0); // black
    for (int i = 0; i < breadth + 2; i++) cout << "#";
    cout << endl;

    // Score display
    setColor(15); // White
    cout << "Score: " << score << endl;
}

// Function to handle user input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case 'p':
            dir = STOP; // Pause the game
            cout << "Game Paused. Press any key to continue...";
            _getch();
            break;
        }
    }
}

// Function to implement game logic
void Logic() {
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
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
    default:
        break;
    }

    if (x >= breadth) x = 0; else if (x < 0) x = breadth - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailx[i] == x && taily[i] == y) {
            gameOver = true;
        }
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % breadth;
        fruity = rand() % height;
        nTail++;
    }
}

// Function to display the game over screen
void GameOverScreen() {
    system("cls");
    setColor(12); // Red
    cout << "######## GAME OVER ########" << endl;
    setColor(15); // White
    cout << "Your final score: " << score << endl;
    cout << "Press any key to exit..." << endl;
    _getch();
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100 - min(score, 90)); // Increase speed as score grows
    }
    GameOverScreen();
    return 0;
}
