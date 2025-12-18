#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>
#include "func.h"



input_params_t get_input_params() {
    input_params_t params;

    printf("Введите начало отсчёта: ");
    scanf("%lf", &params.start);

    printf("Введите конец отсчёта: ");
    scanf("%lf", &params.finish);

    printf("Введите шаг (если он не нужен введите 0): ");
    scanf("%lf", &params.step);

    printf("Введите точность (Например 0.0001): ");
    scanf("%lf", &params.precision);

    return params;
}











double sigma(double x, int n) {
    double sumx = 0.0;
    for (int i = 0; i <= n; i++) {
        sumx += (pow(-1, i) * pow(x, 2 * i + 1)) / ((2 * i + 1) * sqrt(i + 2));
    }
    return sumx;
}






double f(double x) {
    if (x < (-2.0)) {
        return (1.0 / (x * tan(x)));
    }
    else if ((-2.0) <= x && x < (2.0)) {
        return sigma(x, 16);
    }
    else if (x > (2.0)) {
        return (pow(x, 4.0) - (16.0)) / (x - (2.0));
    }
    else {
        return NAN;
    }
}






int build_table(input_params_t params) {
    int valid_count = 0;

    printf("\n| %-10s | %-15s |\n", "x", "f(x)");
    printf("|%-12s|%-17s|\n", "------------", "-----------------");


    for (double x = params.start; x <= params.finish; x += params.step) {
        double result = f(x);
        if (x == 2) {
            printf("| %-10.2lf | %-15s |\n", x, "не определена");
        }
        else {
            printf("| %-10.2lf | %-15.6lg |\n", x, result);
            valid_count++;
        }
    }
    printf("\n");


    if (valid_count > 0) {
        return 1;
    }
    else
    {
        return 0;
    }

}








double find_x_by_y(input_params_t params, double y) {
    double found_x = 0.0;


    for (double x = params.start; x <= params.finish; x += params.precision) {
        double result = f(x);
        if (x != 2 && fabs(result - y) < params.precision) {
            found_x = x;
            break;
        }
    }

    return found_x;
}


int count_x_by_y(input_params_t params, double y) {
    int count = 0;


    for (double x = params.start; x <= params.finish; x += params.precision) {
        double result = f(x);


        if (x != 2 && fabs(result - y) < params.precision) {
            count++;
        }
    }

    return count;
}







double calculate_derivative(double x, double precision) {
    double fx = f(x);
    double fx_plus_h = f(x + precision);

    if (x == 2 || (x + precision) == 2) {
        return 0;
    }

    double derivative = (fx_plus_h - fx) / precision;
    return derivative;
}







double calculate_integral(input_params_t params) {
    double h = (params.finish - params.start) * params.precision;
    double sum = 0.0;

    for (int i = 0; i < pow(params.precision, (-1.0)); i++) {
        double x = params.start + (h / 2) + i * h;
        double result = f(x);
        if (x != 2) {
            sum += result;
        }
    }


    double integral = sum * h;
    return integral;
}








