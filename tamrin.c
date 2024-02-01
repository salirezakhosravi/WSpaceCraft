#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 30000
#define SPACECRAFT '^'
#define OBSTACLE 'O'

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point position;
} Spacecraft;

typedef struct {
    Point position;
    int active;
} Obstacle;

void initialize() {
    initscr();             // Initialize ncurses
    raw();                 // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();              // Do not display typed characters
    curs_set(0);           // Hide the cursor
    timeout(0);            // Non-blocking getch()

    srand(time(NULL));
}

void cleanup() {
    endwin();  // Restore terminal settings
}

void drawEntity(Point position, char symbol) {
    mvprintw(position.y, position.x, "%c", symbol);
}

int checkCollision(Point a, Point b) {
    return (a.x == b.x && a.y == b.y);
}

int main() {
    initialize();

    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    Spacecraft spacecraft = {.position = {maxX / 2, maxY - 2}};
    int isGameOver = 0;

    int obstacleFrequency = 5;  // Increase for fewer obstacles
    int obstacleTimer = 0;

    Obstacle obstacles[10];

    while (!isGameOver) {
        clear();

        // User input
        int ch = getch();
        switch (ch) {
            case KEY_LEFT:
                spacecraft.position.x--;
                break;
            case KEY_RIGHT:
                spacecraft.position.x++;
                break;
            case 'q':
                isGameOver = 1;
                break;
        }

        // Update obstacles
        obstacleTimer++;
        if (obstacleTimer >= obstacleFrequency) {
            obstacleTimer = 0;

            for (int i = 0; i < 10; i++) {
                if (!obstacles[i].active) {
                    obstacles[i].active = 1;
                    obstacles[i].position.x = rand() % maxX;
                    obstacles[i].position.y = 0;
                    break;
                }
            }
        }

        // Move and draw obstacles
        for (int i = 0; i < 10; i++) {
            if (obstacles[i].active) {
                obstacles[i].position.y++;
                drawEntity(obstacles[i].position, OBSTACLE);

                // Check for collision with spacecraft
                if (checkCollision(spacecraft.position, obstacles[i].position)) {
                    isGameOver = 1;
                }

                // Check if obstacle is out of bounds
                if (obstacles[i].position.y >= maxY) {
                    obstacles[i].active = 0;
                }
            }
        }

        // Draw spacecraft
        drawEntity(spacecraft.position, SPACECRAFT);

        refresh();
        usleep(DELAY);
    }

    cleanup();
    return 0;
}
