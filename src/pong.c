#include <stdio.h>

int field(int x, int y, int f_racket, int s_racket, int f_score, int s_score);

int main() {
    int x = 39;
    int y = 12;

    int step_x = 1;
    int step_y = 1;

    int f_racket = 11;
    int s_racket = 11;

    int f_score = 0;
    int s_score = 0;

    char c, c1;

    field(x, y, f_racket, s_racket, f_score, s_score);
    scanf("%c%c", &c, &c1);
    do {
        if (!(c == ' ' || c == 'A' || c == 'Z' || c == 'K' || c == 'M' || c == 'a' || c == 'z' || c == 'm' ||
              c == 'k')) {
            printf("n/a");
            return 0;
        }

        x += step_x;
        y += step_y;

        if ((c == 'A' || c == 'a') && f_racket > 1) {
            f_racket--;
        } else if ((c == 'Z' || c == 'z') && f_racket <= 20) {
            f_racket++;
        }

        if ((c == 'K' || c == 'k') && s_racket > 1) {
            s_racket--;
        } else if ((c == 'M' || c == 'm') && s_racket <= 20) {
            s_racket++;
        }

        if (y == 0 || y == 24) {
            step_y = -step_y;
            x += step_x;
            y += step_y;
        }
        if ((x == 0 && (f_racket <= y && f_racket + 3 >= y))) {
            step_x = -step_x;
            x += step_x;
            y += step_y;
        } else if (x == 0 && (f_racket >= y || f_racket + 3 <= y)) {
            s_score++;
            x = 39;
            y = 12;
        }

        if ((x == 79 && (s_racket <= y && s_racket + 3 >= y))) {
            step_x = -step_x;
            x += step_x;
            y += step_y;
        } else if (x == 79 && (s_racket >= y || s_racket + 3 <= y)) {
            f_score++;
            x = 39;
            y = 12;
        }

        if (f_score == 21) {
            field(x, y, f_racket, s_racket, f_score, s_score);
            printf("Finish. First player win!!!");
            break;
        } else if (s_score == 21) {
            field(x, y, f_racket, s_racket, f_score, s_score);
            printf("Finish. Second player win!!!");
            break;
        }
        printf("\33[0d\33[2J");
        field(x, y, f_racket, s_racket, f_score, s_score);
        scanf("%c%c", &c, &c1);
    } while (c == ' ' || c == 'A' || c == 'Z' || c == 'K' || c == 'M' || c == 'a' || c == 'z' || c == 'm' ||
             c == 'k');
    return 0;
}

int field(int x1, int y1, int f_racket, int s_racket, int f_score, int s_score) {
    int height1 = 0;
    int height2 = 0;

    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            if (y == 0 || y == 24) {
                printf("-");
            } else if (x == 0 && y == f_racket && height1 != 3) {
                printf("]");
                f_racket++;
                height1++;
            } else if (x == 79 && y == s_racket && height2 != 3) {
                printf("[");
                s_racket++;
                height2++;
            } else if (x == x1 && y == y1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int x = 0; x <= 37; x++) {
        printf(" ");
    }
    printf("%d | %d\n", f_score, s_score);
    return 0;
}
