#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define COL 50
#define LINES 20

int draw(char board[LINES][COL], int score, int snakex) {
    clear();
    mvprintw(0, 0, "Score: %d %d", score, snakex);
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COL; j++) {
            mvaddch(i + 1, j, board[i][j]);
        }
    }
    refresh();
    usleep(80000); 
    return 0;
}

int main() {
    int quit = 0;
    int score = 0;
    int gameOver=0;
    char board[LINES][COL];
    int** snake;
    snake = (int **)malloc(200*sizeof(int *));
    for (size_t i = 0; i < 200; i++)
    {
        snake[i]=(int *)malloc(2);
    }
    for (size_t i = 0; i < 200; i++)
    {
        snake[i][0]=100;
        snake[i][1]=100;
    }
    snake[0][0]=LINES / 2;
    snake[0][1]=COL / 2;  
    
    char move='r';
    srand(time(0));

    // Initialize ncurses
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COL; j++) {
            board[i][j] = '-';
        }
    }

    int fruitex = rand() % LINES;
    int fruitey = rand() % COL;

    while (!quit) {
        for (size_t i = 0; i <200; i++)
        {
            int shouldBreak=0;
            for (size_t j = i+1; j <200; j++)
            {
                if (snake[i][0]==snake[j][0] && snake[i][1]==snake[j][1] && snake[i][0]!=100)
                    {
                        gameOver=1;
                        shouldBreak=1;
                        break;
                    }
            }
            if (shouldBreak)
            {
                break;
            }
            
        }

        if (snake[0][0] == fruitex && snake[0][1] == fruitey) {
            score++;
            do {
                fruitex = rand() % LINES;
                fruitey = rand() % COL;
            } while (board[fruitex][fruitey] == 'O');

            for (size_t i = 0; i <200; i++)
            {
                if (snake[i][0]==100)
                    {
                        snake[i][0]=snake[i-1][0];
                        snake[i][1]=(snake[i-1][1] + 1) % COL;
                        break;
                    }
            }
        }

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                move = 'u';
                break;

            case KEY_DOWN:
                move='d';
                break;

            case KEY_RIGHT:
                move='r';
                break;

            case KEY_LEFT:
                move='l';
                break;
            case 'q':  // Quit the game when 'q' is pressed
                quit = 1;
                break;
            case 'r':  // replay the game when 'q' is pressed
                score=0;
                for (size_t i = 0; i < 200; i++)
                {
                    snake[i][0]=100;
                    snake[i][1]=100;
                }
                snake[0][0]=LINES / 2;
                snake[0][1]=COL / 2;
                gameOver=0;
                break;

            default:
                break;
        }
        for (size_t i = 49; i >0; i--)
        {
            if (snake[i][0]!=100)
            {
                snake[i][0]=snake[i-1][0];
                snake[i][1]=snake[i-1][1];
            }
            
        }
        switch (move) {
            case 'u':
                snake[0][0] = (snake[0][0] - 1 + LINES) % LINES;
                break;

            case 'd':
                snake[0][0] = (snake[0][0] + 1) % LINES;
                break;

            case 'r':
                snake[0][1] = (snake[0][1] + 1) % COL;
                break;

            case 'l':
                snake[0][1] = (snake[0][1] - 1 + COL) % COL;
                break;
        }

        
        for (int i = 0; i < LINES; i++) {
            for (int j = 0; j < COL; j++) {
                board[i][j] = '-';
            }
        }
        if (!gameOver)
        {
            for (size_t i = 0; i <200; i++)
            {
                if (snake[i][0]!=100)
                {
                    board[snake[i][0]][snake[i][1]] = 'O';
                }
                
            }
            board[fruitex][fruitey] = '*';
        }
        else{
            board[LINES/2][COL/2-4]='G';
            board[LINES/2][COL/2-3]='A';
            board[LINES/2][COL/2-2]='M';
            board[LINES/2][COL/2-1]='E';
            board[LINES/2][COL/2]=' ';
            board[LINES/2][COL/2+1]='O';
            board[LINES/2][COL/2+2]='V';
            board[LINES/2][COL/2+3]='E';
            board[LINES/2][COL/2+4]='R';
        }
        draw(board, score, gameOver);
    }

    endwin();
    free(snake);
    return 0;
}
