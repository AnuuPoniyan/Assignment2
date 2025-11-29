# 🕹️ ASCII Shooter Game – C Project (Assignment 2)

---

## About This Project

This is my version of the console game we had to modify for Assignment 2.  
The original game was very simple with just one obstacle and no extra features.  
So I tried to improve it and make it more fun. Now it feels more like a small shooter game.

I added my own ASCII icons, shooting, multiple enemies, and even a boss enemy.

---

## What the Game Has Now

Here are the improvements I made:

### ✔ Player Movement
The player (shown as `<^>`) can move up and down using:
- W → move up  
- S → move down  

### ✔ Shooting (multiple bullets)
Press SPACE to shoot bullets (`-->`).  
You can shoot several bullets at once.

### ✔ Two Enemies
There are two normal enemies:
[-X-]

They move randomly and get faster as the game continues.

### ✔ Boss Enemy
After reaching score 10, a boss enemy appears:
[=BOSS=]


The boss has HP, and you have to shoot it multiple times to defeat it.

### ✔ Sound Effects
Different beeps play when:
- You shoot  
- A bullet hits an enemy  
- Boss gets hit  
- Game over sound  

### ✔ Random Movement & Difficulty
Enemies don’t move in a straight line.  
They shift up and down randomly, which makes the game unpredictable and harder.

---

## How to Play

Controls:
W – move up
S – move down
SPACE – shoot


Avoid colliding with enemies.  
Shoot enemies to score.  
Boss appears after you reach 10 points.

---

## Modifications I Added (as per assignment)

These are the three main changes I implemented:

1. Shooting system (multiple bullets)
2. Two obstacles (two enemies)
3. Boss enemy with HP + increasing difficulty

These satisfy the assignment requirements.

---

## What I Learned

While making this game, I learned and practiced:
- Handling arrays (for bullets)
- Basic collision detection
- Random movement with rand()
- Creating a proper game loop
- Adding sound effects using Beep()
- Improving console visuals using ASCII
- Writing a slightly larger C program

---

## How to Run

Use GCC in Windows:
gcc shooter_game.c -o game
game.exe


---

## Note

This is an ASCII console-based game made in C.  
It works best in CMD or PowerShell on Windows.


Made by: Aneesh Poniyan(B.Tech CSE)
