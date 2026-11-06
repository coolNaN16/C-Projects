#include <stdio.h>
#include <string.h>

#define WIDTH 13
#define HEIGHT 13

int map[HEIGHT][WIDTH] = {
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
    {0, 2, 0, 2, 2, 2, 0, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0},
    {0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 0, 0, 0, 0, 2, 2, 2, 2, 0, 2, 2},
    {0, 2, 2, 2, 2, 0, 2, 0, 0, 0, 2, 0, 2},
    {0, 2, 2, 2, 2, 0, 0, 0, 2, 0, 0, 0, 2}
};

int currentpos[2] = {2, 2};

void move(int dir) {
    if (dir == 1) {
        if (currentpos[1] > 0 && map[currentpos[1] - 1][currentpos[0]] != 2) {
            currentpos[1]--;
        }
    } else if (dir == 2) {
        if (currentpos[1] < HEIGHT - 1 && map[currentpos[1] + 1][currentpos[0]] != 2) {
            currentpos[1]++;    
        }
    
    } else if (dir == 3) {
        if (currentpos[0] > 0 && map[currentpos[1]][currentpos[0] - 1] != 2) {
            currentpos[0]--;    
        }
    } else if (dir == 4) {
        if (currentpos[0] < WIDTH - 1 && map[currentpos[1]][currentpos[0] + 1] != 2) {
            currentpos[0]++;    
        }
    }
}

void draw() {
    for (int i = 0; i < WIDTH * 3; i++) {
        printf("=");
    }
    printf("\n");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == currentpos[0] && y == currentpos[1]) {
                printf("@");
                continue;
            }
            if (map[y][x] == 0) {
                printf(" ");
            } else if (map[y][x] == 2) {
                printf("#");
            } else if (map[y][x] == 1) {
                printf("@");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < WIDTH * 3; i++) {
        printf("=");
    }
    printf("\n");

    printf(" ▵   ▿   ◃   ▹\n");
    printf("[1] [2] [3] [4]\n");
    
}

int main() {
    // printf("%d", map[1][1]);
    draw();
    int input;
    // printf("%d", input);
    while (1) {
        scanf("%d", &input);
        move(input);
        draw();
    }
}

