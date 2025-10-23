#include <curses.h>  // библиотека для отрисовки графики
#include <unistd.h>  // библиотека для установки таймера

void init();
void finish();

int field(int x, int y, int f_racket, int s_racket, int f_score, int s_score);

int main() {
    init();  // задаем параметры

    int x = 39;
    int y = 12;

    int step_x = 1;
    int step_y = 1;

    int f_racket = 11;
    int s_racket = 11;

    int f_score = 0;
    int s_score = 0;

    field(x, y, f_racket, s_racket, f_score, s_score);
    do {
        char c;
        if (f_score == 21) {
            field(x, y, f_racket, s_racket, f_score, s_score);  // обновлем счет до 21
            refresh();                                          // обновляем экран
            clear();                                            //очищаем

            addstr("Finish. First player win!!!");  //выводим финальную надпись
            usleep(80000);                          //ожидаем
            refresh();

            return 21;
        } else if (s_score == 21) {
            field(x, y, f_racket, s_racket, f_score, s_score);
            refresh();
            clear();

            addstr("Finish. Second player win!!!");
            usleep(80000);
            refresh();

            return 21;
        }

        c = getch();  // считываем символ с клавиатуры

        if (c == 27) {  // если вводят esc - выход
            return 0;
        }
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

        x += step_x;
        y += step_y;

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
        clear();
        field(x, y, f_racket, s_racket, f_score, s_score);  //обновляем экран
        usleep(40000);
    } while (TRUE);

    finish();  // возвращаем настройки терминала
    return 0;
}

void init() {
    initscr();  // инициализация функций библиотеки
    savetty();  // сохраняет текущую конфигурацию терминала, чтоб потом восстановить ее
    nonl();     // отключает автоматический перенос на новую строку
    cbreak();   // сразу считываем символы без ожидания ввода
    noecho();   // не выводим символы в терминал
    timeout(0);             // ввод сразу доступен программе
    leaveok(stdscr, TRUE);  // оптимизирует вывод данных
    curs_set(0);            // курсор становится невидимым
}

void finish() {
    curs_set(1);  // возвращаем курсор
    clear();      // очищаем окно
    refresh();    // обновляем экран
    resetty();    // возвращаем настройки терминала
}

int field(int x1, int y1, int f_racket, int s_racket, int f_score, int s_score) {
    int height1 = 0;
    int height2 = 0;

    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            if (y == 0 || y == 24) {
                move(y, x);  //перемещаем курсор в позицию у,х (левый край имеет координаты 0,0)
                addch('-');  // добовляем символ
            } else if (x == 0 && y == f_racket && height1 != 3) {
                move(y, x);
                addch(']');
                f_racket++;
                height1++;
            } else if (x == 79 && y == s_racket && height2 != 3) {
                move(y, x);
                addch('[');
                s_racket++;
                height2++;
            } else if (x == x1 && y == y1) {
                move(y, x);
                addch('*');

            } else {
                move(y, x);
                addch(' ');
            }
        }
    }
    move(25, 38);
    printw("%d | %d", f_score, s_score);
    return 0;
}
