#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SNAKE_MAX_LENGTH 100
#define FOOD_CHAR '@'
#define BORDER_CHAR '*'
#define EMPTY_CHAR ' ' 
#define SNAKE_BODY 'O'

typedef struct {
    int x, y;
} SnakeSegment;

typedef struct {
    char name[30];
    int score;
} RankingEntry;

RankingEntry ranking[3];

SnakeSegment* snake;
int snakeLength = 1;
int snakeDirection = 1;

int score = -10;

int foodX, foodY;

void loadRanking() {
    FILE *file = fopen("ranking.dat", "rb");
    if (file != NULL) {
        fread(ranking, sizeof(RankingEntry), 3, file);
        fclose(file);
    }
}

void saveRanking() {
    FILE *file = fopen("ranking.dat", "wb");
    if (file != NULL) {
        fwrite(ranking, sizeof(RankingEntry), 3, file);
        fclose(file);
    }
}

void addPlayerToRanking(const char *name, int score) {
    for (int i = 0; i < 3; ++i) {
        if (score > ranking[i].score) {
            for (int j = 2; j > i; --j) {
                strcpy(ranking[j].name, ranking[j - 1].name);
                ranking[j].score = ranking[j - 1].score;
            }
            strcpy(ranking[i].name, name);
            ranking[i].score = score;
            break;
        }
    }
}

void showRanking() {
    printf("\n ----- RANKING -----\n");
    for(int i = 0; i<3; ++i) {
        printf("%d. %s - %d\n", i + 1, ranking[i].name, ranking[i].score);
    }
    printf("\n");
}

void updateScore() {
    screenGotoxy(MINX, MAXY);
    printf("Pontuação: %d\n", score);
}

void initializeGame() {
    screenInit(0);
    keyboardInit();
    timerInit(60);
    score = -10;
}

void endGame() {
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
}

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
    score += 10;
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
            case 27: 
                snakeLength = 0; 
                break;
        }
    }
}

int checkCollision() {
    if (snake[0].x <= MINX || snake[0].x >= MAXX || snake[0].y <= MINY || snake[0].y >= MAXY) {
        return 1; 
    }

    for (int i = 1; i < snakeLength; i++) {
        if (i < SNAKE_MAX_LENGTH && snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1; 
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
    updateScore();
    screenUpdate();

    if (checkCollision()) {
        snakeLength = 0; 
    }
}

void gameLoop() {
    int playAgain = 1;

    while(playAgain) {
        while (snakeLength > 0) {
            handleInput();

            if (timerTimeOver() == 1) {
                checkCollisionAndMove();
            }
        }

        printf("GAME OVER!!! Pontuação final: %d\n", score);
        showRanking();
        printf("Digite seu nome para o ranking: ");
        char name[30];
        scanf("%s", name);
        addPlayerToRanking(name, score);
        saveRanking();
        printf("Deseja jogar novamente? (1-SIM, 0-NÃO): ");
        scanf("%d",&playAgain);

        if(playAgain == 1) {
            snakeLength = 1;
            endGame();
            initializeGame();
            score = 0;
        }
    
    }
}

int showMenu() {
    int menuChoice;
    printf("1. Iniciar Jogo\n");
    printf("2. Sair\n");
    scanf("%d",&menuChoice);
    return menuChoice;
}

int main() {
    initializeGame();
    loadRanking();

    int choice;

    do {
        choice = showMenu();

        switch (choice) {
            case 1:
			    screenClear();
                initializeSnake();
                generateFood();
                gameLoop();
                freeSnake();
                break;
            case 2:
                snakeLength = 0;
                break;
            default:
                printf("Opção Inválida.\n\n");
        }

    } while (snakeLength > 0);

    endGame();

    return 0;
}