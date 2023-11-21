#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#include <sys/time.h>
#include <stdlib.h>

#define SNAKE_MAX_LENGTH 100
#define FOOD_CHAR 'F'
#define BORDER_CHAR '#'
#define EMPTY_CHAR ' ' 
#define SNAKE_BODY 'O'

typedef struct {
    int x, y;
} SnakeSegment;

SnakeSegment* snake;
int snakeLength = 1;
int snakeDirection = 1; // 1: direita, 2: esquerda, 3: cima, 4: baixo

int foodX, foodY;

int startTime;

void initializeSnake() {
    snake = (SnakeSegment*)malloc(SNAKE_MAX_LENGTH * sizeof(SnakeSegment));
    snake[0].x = MAXX / 2;
    snake[0].y = MAXY / 2;
}

void freeSnake() {
    free(snake);
}

void generateFood() {
	
	foodX = rand() % (MAXX - MINX -1) + MINX + 1;
	foodY = rand() % (MAXY - MINY -1) + MINY + 1;
}

void drawFood() {
	screenGotoxy(foodX, foodY);
	printf("%c", FOOD_CHAR);
}

void clearSnakeTail() {
	for (int i = snakeLength; i < SNAKE_MAX_LENGTH; i++) {
		snake[i].x = 0;
		snake[i].y = 0;
	}
}

void drawSnake() {
	for(int i = 0; i < snakeLength; i++) {
        screenGotoxy(snake[i].x, snake[i].y);
        printf("%c", SNAKE_BODY);
	}
}

void drawBorders() {
	screenSetColor(WHITE, BLACK);
	for(int i = MINX; i <= MAXX; i++) {
		screenGotoxy(i, MINY);
		printf("%c", BORDER_CHAR);
		screenGotoxy(i, MAXY);
		printf("%c", BORDER_CHAR);
	}

	for(int i = MINY; i <= MAXY; i++) {
		screenGotoxy(MINX, i);
		printf("%c", BORDER_CHAR);
		screenGotoxy(MAXX, i);
		printf("%c", BORDER_CHAR);
	}
}


void moveSnake() {

	int tailX = snake[snakeLength - 1].x;
	int tailY = snake[snakeLength - 1].y;

	for(int i = snakeLength - 1; i > 0; i--) {
		snake[i] = snake[i-1];
	}

    switch (snakeDirection) {
        case 1:
            snake[0].x = (snake[0].x + 1 > MAXX - 1) ? MINX + 1 : snake[0].x + 1;
            break;
        case 2:
            snake[0].x = (snake[0].x - 1 < MINX + 1) ? MAXX - 1 : snake[0].x - 1;
            break;
        case 3:
            snake[0].y = (snake[0].y - 1 < MINY + 1) ? MAXY - 1 : snake[0].y - 1;
            break;
        case 4:
            snake[0].y = (snake[0].y + 1 > MAXY - 1) ? MINY + 1 : snake[0].y + 1;
            break;
    }

	screenGotoxy(tailX, tailY);
	printf("%c", EMPTY_CHAR);
}

void handleInput() {
    if (keyhit()) {
        int ch = readch();
        switch (ch) {
            case 'w':
                if (snakeDirection != 4) snakeDirection = 3;
                break;
            case 's':
                if (snakeDirection != 3) snakeDirection = 4;
                break;
            case 'a':
                if (snakeDirection != 1) snakeDirection = 2;
                break;
            case 'd':
                if (snakeDirection != 2) snakeDirection = 1;
                break;
            case 27: // Escape key
                snakeLength = 0; // End the game
                break;
        }
    }
}

int checkCollision() {
    if (snake[0].x <= MINX || snake[0].x >= MAXX || snake[0].y <= MINY || snake[0].y >= MAXY) {
        return 1; // Collision with screen borders
    }

    for (int i = 1; i < snakeLength; i++) {
        if (i < SNAKE_MAX_LENGTH && snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1; // Collision with itself
        }
    }

	if (snake[0].x == foodX && snake[0].y == foodY) {
		if(snakeLength < SNAKE_MAX_LENGTH) {
			snake[snakeLength].x = snake[snakeLength - 1].x;
			snake[snakeLength].y = snake[snakeLength - 1].y;
			snakeLength++;	
		}
		generateFood();
	}
	

    return 0;
}

void checkCollisionAndMove() {
    moveSnake();
    drawBorders();
    drawFood();
    drawSnake();
    screenUpdate();

    if (checkCollision()) {
        snakeLength = 0; // End the game
    }
}

void showMenu() {
    screenClear();
    printf("1. Iniciar Jogo\n");
    printf("2. Sair\n");
}

void gameLoop() {
    startTime = timerTimeOver();

    while (snakeLength > 0) {
        handleInput();

        if (timerTimeOver() == 1) {
                checkCollisionAndMove();
                startTime = timerTimeOver();
        }
    }
}

int main() {
    screenInit(0);
    keyboardInit();
    timerInit(100);

    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
			screenClear();
                initializeSnake();
                generateFood();
                gameLoop();
                freeSnake();
                break;
            case 2:
                snakeLength = 0; // Encerra o jogo
                break;
            default:
                printf("Opção Inválida.");
        }

    } while (snakeLength > 0);

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}