#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include "func.h"


int main() {
    setlocale(LC_CTYPE, "RUS");
    int choice;

    printf("\n");
    printf("                              *************************************************************\n");
    printf("                              *                                                           *\n");
    printf("                              *                      Курсовой проект                      *\n");
    printf("                              *          Конструирование программы анализа функции        *\n");
    printf("                              *                  Выполнил: Капустин А. И.                 *\n");
    printf("                              *              Руководитель: Минакова О. В.                 *\n");
    printf("                              *                    Группа: бИЦ-252                        *\n");
    printf("                              *                                                           *\n");
    printf("                              *************************************************************\n");
    printf("\n\n");

    printf("                              *************************************************************\n");
    printf("                              *                      АНАЛИЗ ФУНКЦИИ                       *\n");
    printf("                              *           __                                              *\n");
    printf("                              *          |   1 / (x * tan(x)),              x < -2        *\n");
    printf("                              *   f(x) = |                                                *\n");
    printf("                              *          |   (x^4 - 16) / (x-2),            x >= 2        *\n");
    printf("                              *          |                                                *\n");
    printf("                              *          |    16                                          *\n");
    printf("                              *          |    ___    ((-1)^n * x^(2n+1))                  *\n");
    printf("                              *          |    \\     ______________________, -2 <= x < 2   *\n");
    printf("                              *          |    /__    ((2n+1) * sqrt(n+2))                 *\n");
    printf("                              *          |__  n = 0                                       *\n");
    printf("                              *                                                           *\n");
    printf("                              *************************************************************\n");
    printf("\n\n");

    do {
        printf("\n\n");
        printf("                              *************************************************************\n");
        printf("                              *                                                           *\n");
        printf("                              *                       ГЛАВНОЕ МЕНЮ                        *\n");
        printf("                              *                                                           *\n");
        printf("                              *        1. Значение функции в точке                        *\n");
        printf("                              *        2. Таблица значений                                *\n");
        printf("                              *        3. Поиск X по Y                                    *\n");
        printf("                              *        4. Производная в точке                             *\n");
        printf("                              *        5. Вычисление интеграла                            *\n");
        printf("                              *        6. Выход                                           *\n");
        printf("                              *                                                           *\n");
        printf("                              *************************************************************\n");
        printf("\n\n");
        printf("Выберите пункт: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }

        // Переменные для ввода в main
        double x, y, precision4;
        int result;
        input_params_t params;


        switch (choice) {

        case 1: // Значение функции в точке
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            {

                if (x == 2) {
                    printf("Ошибка! Функция не определена в точке x = %lf\n", x);
                }
                else {
                    printf("f(%lf) = %lf\n", x, f(x));
                }
            }
            break;



        case 2: // Таблица значений
            params = get_input_params();
            if (params.start >= params.finish) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }
            if (params.step <= 0) {
                printf("Ошибка! Шаг должен быть больше 0.\n");
                break;
            }
            result = build_table(params);
            if (result == 0) {
                printf("В таблице нет ни одного определенного значения функции.\n");
            }
            break;



        case 3: // Поиск X по Y
            printf("Введите Y: ");
            if (scanf("%lf", &y) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            params = get_input_params();
            if (params.start >= params.finish) {
                printf("Ошибка! Начало должно быть меньше конца.\n");
                break;
            }
            if (params.precision <= 0) {
                printf("Ошибка! Точность должна быть положительной.\n");
                break;
            }

            int total_count = count_x_by_y(params, y);
            if (total_count == 0) {
                printf("Не удалось найти значение Х для Y = %lf на отрезке [%lf, %lf]\n", y, params.start, params.finish);
                break;
            }
            printf("\nНайдено %d значений Х для Y = %lf на отрезке [%lf, %lf]\n", total_count, y, params.start, params.finish);
            printf("Первое значение Х для Y = %lf на отрезке [%lf, %lf]:  %lf\n", y, params.start, params.finish, find_x_by_y(params, y));
            printf("\n   Список всех значений Х для Y = %lf на отрезке [%lf, %lf]\n", y, params.start, params.finish);
            printf("=============================================================================================\n");


            int found = 0;
            while (found < total_count) {
                double x_solution = find_x_by_y(params, y);
                printf("Решение %d: X ~ %lf\n", found + 1, x_solution);
                found++;
                params.start = x_solution + params.precision;
                if (params.start > params.finish) break;
            }
            printf("============================================================\n");
            break;



        case 4: // Производная в точке
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }

            printf("Введите точность (Например 0.00001): ");
            if (scanf("%lf", &precision4) != 1 || precision4 <= 0) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                break;
            }
            if (x != 2 && (x + precision4) != 2) {
                printf("f'(%lf) ~ %lf\n", x, calculate_derivative(x, precision4));
            }
            else {
                printf("Ошибка! Нельзя вычислить производную - функция не определена\n");
            }

            break;



        case 5: // Интеграл

            params = get_input_params();
            if (params.start >= params.finish) {
                printf("Ошибка! Начало интервала должно быть меньше конца.\n");
                break;
            }
            if (params.precision < 0) {
                printf("Ошибка! Точность должна быть больше 0.\n");
                break;
            }
            printf("Интеграл ~ %lf\n", calculate_integral(params));
            break;




        case 6:
            printf("Выход из программы.\n");
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
            break;
        }
    } while (choice != 6);

    return 0;
}