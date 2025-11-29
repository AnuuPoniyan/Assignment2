#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

// I am keeping these sizes small so things don't break
#define MAX_BULLETS 20

// Player position
int px = 5;
int py = 10;

// Two normal enemies
int ex1 = 40, ey1 = 10;
int ex2 = 55, ey2 = 15;

// Bullet storage
int bx[MAX_BULLETS];
int by[MAX_BULLETS];
int bflag[MAX_BULLETS];

// Boss details
int bossX = 80;
int bossY = 8;
int bossHP = 5;
int bossOn = 0;

// Game indicators
int score = 0;
int lives = 3;
int speedDelay = 90;
int over = 0;


// Move cursor function
void moveCursor(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


// just a simple hit check
int hit(int a1, int b1, int a2, int b2) {
    return (a1 == a2 && b1 == b2);
}


// draw everything on screen
void draw() {
    system("cls");
    printf("Score : %d      Lives : %d\n\n", score, lives);

    // player <^>
    moveCursor(px, py);
    printf("<^>");

    // normal enemies
    moveCursor(ex1, ey1);
    printf("[-X-]");

    moveCursor(ex2, ey2);
    printf("[-X-]");

    // bullets
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bflag[i]){
            moveCursor(bx[i], by[i]);
            printf("-->");
        }
    }

    // boss
    if(bossOn){
        moveCursor(bossX, bossY);
        printf("[=BOSS=] HP:%d", bossHP);
    }
}


// reset enemies randomly
void resetEnemy1(){
    ex1 = 40;
    ey1 = (rand() % 15) + 4;
}

void resetEnemy2(){
    ex2 = 55;
    ey2 = (rand() % 15) + 4;
}


// when boss comes
void spawnBoss(){
    bossOn = 1;
    bossHP = 5;
    bossX = 80;
    bossY = (rand() % 12) + 4;

    // just some alert sound
    Beep(400, 200);
    Beep(600, 200);
}


// bullet physics
void updateBullets(){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bflag[i] == 1){

            bx[i]++;

            // if bullet goes too far
            if(bx[i] > 100){
                bflag[i] = 0;
                continue;
            }

            // hits enemy 1
            if(hit(bx[i], by[i], ex1, ey1)){
                score++;
                resetEnemy1();
                bflag[i] = 0;
                Beep(900, 40);
                continue;
            }

            // hits enemy 2
            if(hit(bx[i], by[i], ex2, ey2)){
                score++;
                resetEnemy2();
                bflag[i] = 0;
                Beep(900, 40);
                continue;
            }

            // hits boss
            if(bossOn){
                if(bx[i] >= bossX && by[i] == bossY){
                    bossHP--;
                    bflag[i] = 0;
                    Beep(1200, 50);

                    if(bossHP <= 0){
                        bossOn = 0;
                        score += 5;
                        Beep(200, 350);
                        Beep(100, 350);
                    }
                }
            }
        }
    }
}


// enemy movements
void updateEnemies(){

    // enemy 1
    ex1--;
    if(rand() % 6 == 0) ey1 += (rand() % 3) - 1;
    if(ex1 <= 0){
        score++;
        resetEnemy1();
    }

    // enemy 2 (faster)
    ex2 -= 2;
    if(rand() % 4 == 0) ey2 += (rand() % 3) - 1;
    if(ex2 <= 0){
        score++;
        resetEnemy2();
    }

    // boss movement
    if(bossOn){
        bossX--;

        if(rand() % 3 == 0)
            bossY += (rand() % 3) - 1;

        if(bossX < 0)
            bossOn = 0;
    }
}


// if enemy touches player
void checkPlayerHit(){

    if(hit(px, py, ex1, ey1)){
        lives--;
        resetEnemy1();
        Beep(250, 250);
    }

    if(hit(px, py, ex2, ey2)){
        lives--;
        resetEnemy2();
        Beep(250, 250);
    }

    if(bossOn && hit(px, py, bossX, bossY)){
        lives--;
        bossOn = 0;
        Beep(200, 400);
    }

    if(lives <= 0){
        over = 1;
    }
}


// boss appears after certain score
void difficultyCheck(){
    if(score >= 10 && bossOn == 0){
        spawnBoss();
    }
}


// ================== MAIN GAME LOOP ==================
void playGame(){

    px = 5;
    py = 10;

    resetEnemy1();
    resetEnemy2();

    score = 0;
    lives = 3;
    speedDelay = 90;
    over = 0;

    for(int i = 0; i < MAX_BULLETS; i++)
        bflag[i] = 0;

    srand(time(NULL));

    while(!over){

        draw();
        updateBullets();
        updateEnemies();
        checkPlayerHit();
        difficultyCheck();

        Sleep(speedDelay);

        if(kbhit()){
            char key = getch();

            if(key == 'w' && py > 3) py--;
            if(key == 's' && py < 20) py++;

            if(key == ' '){
                // shoot a bullet (find an empty one)
                for(int i = 0; i < MAX_BULLETS; i++){
                    if(bflag[i] == 0){
                        bflag[i] = 1;
                        bx[i] = px + 3;
                        by[i] = py;
                        Beep(700, 40);
                        break;
                    }
                }
            }
        }
    }

    system("cls");
    printf("\n\n GAME OVER!\n");
    printf("Your Score : %d\n", score);
    Beep(180, 500);
}


// ====================== MENU ======================
void menu(){
    while(1){
        system("cls");
        printf("====== ASCII SHOOTER GAME ======\n");
        printf("Player : <^>\nEnemy : [-X-]\nBoss : [=BOSS=]\n\n");
        printf("1. Start Game\n");
        printf("2. Help\n");
        printf("3. Exit\n\n");
        printf("Choose : ");

        char choice = getch();

        if(choice == '1'){
            playGame();
            printf("\nPlay Again? (y/n): ");
            char again = getch();
            if(again != 'y') break;
        }
        else if(choice == '2'){
            system("cls");
            printf("Controls:\n");
            printf("W/S = Move Up/Down\n");
            printf("SPACE = Shoot (multiple bullets)\n");
            printf("Enemies = [-X-]\n");
            printf("Boss appears after score 10\n\n");
            printf("Press any key...");
            getch();
        }
        else if(choice == '3'){
            exit(0);
        }
    }
}


// ====================== MAIN ======================
int main(){
    menu();
    return 0;
}
