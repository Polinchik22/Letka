#include <stdio.h>
#include <assert.h>
#include <math.h>


enum AmountSolutions {INITIALIZATION = -2, PROBLEM, NO_SOLUTIONS, ONE_SOLUTION, TWO_SOLUTIONS, INFINITY_SOLUTIONS};
const float EPSILON = 1e-6f;


void entering_coefs     (float* coef_2, float* coef_1, float* coef_0);
void entering           (float* coef, char litera);
bool is_correct_entering(float* coef, char litera);

AmountSolutions solving_equation(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2);
AmountSolutions solving_eq_deg2 (float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2);
float finding_desc              (float coef_2, float coef_1, float coef_0);
AmountSolutions solving_eq_deg1 (float coef_1, float coef_0, float* solution_1);

void printing_solutions(AmountSolutions amount_solution, float coef_2, float coef_1, float coef_0, float solution_1, float solution_2);

bool is_equal(float coef_2, float coef_1);
bool cleaning_buffer();


struct Equation{
    float coef_2, coef_1, coef_0;
    float solution_1, solution_2;
    int amount_solution;
};


// int main() {
//     float coef_2 = NAN, coef_1 = NAN, coef_0 = NAN;
//     float solution_1 = NAN, solution_2 = NAN;
//
//     //  equation problem_book[100];
//
//     entering_coefs(&coef_2, &coef_1, &coef_0);
//
//     AmountSolutions amount_solution = solving_equation(coef_2, coef_1, coef_0, &solution_1, &solution_2);
//
//     printing_solutions(amount_solution, coef_2, coef_1, coef_0, solution_1, solution_2);
//
//     // int i = 0;
//     // printf("Хотите внесу в задачник? [Y/N] ");
//     // if (getchar() == 'Y'){
//     //     problem_book[i].coef_2 = coef_2;
//     //     problem_book[i].coef_1 = coef_1;
//     //     problem_book[i].coef_0 = coef_0;
//     //     problem_book[i].solution_1 = solution_1;
//     //     problem_book[i].solution_2 = solution_2;
//     //     problem_book[i].amount_solution = amount_solution;
//     //     i++;
//     // }
// }


void entering_coefs(float* coef_2, float* coef_1, float* coef_0) {
    printf("Привет! будем решать ax^2 + bx + c = 0 \n");

    entering(coef_2, 'a');
    entering(coef_1, 'b');
    entering(coef_0, 'c');
}


void entering(float* coef, char litera) {
    while (!is_correct_entering(coef, litera)) {
        printf("ЧУВААААК, давай без приколов, ");
    }
}


bool is_correct_entering(float* coef, char litera) {
    printf("введи коэффициент %c: ", litera);

    int amount_scan_numbs = scanf("%f", coef);
    bool is_clean_buffer = cleaning_buffer();

    if (amount_scan_numbs != 1 || !(is_clean_buffer)){
        return false;
    }
    return true;
}


AmountSolutions solving_equation(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2) {
    assert(isfinite(coef_2));
    assert(isfinite(coef_1));
    assert(isfinite(coef_0));
    assert(solution_1 != NULL);
    assert(solution_2 != NULL);

    AmountSolutions amount_solutions = INITIALIZATION;

    if (is_equal(coef_2, 0)) {
        amount_solutions = solving_eq_deg1(coef_1, coef_0, solution_1);

    } else {
        amount_solutions = solving_eq_deg2(coef_2, coef_1, coef_0, solution_1, solution_2);
    }

    return amount_solutions;
}


AmountSolutions solving_eq_deg2(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2) {
    assert(isfinite(coef_2));
    assert(isfinite(coef_1));
    assert(isfinite(coef_0));
    assert(solution_1 != NULL);
    assert(solution_2 != NULL);

    float desc = finding_desc(coef_2, coef_1, coef_0);

    if (desc < 0) {
        return NO_SOLUTIONS;

    } else if (is_equal(desc, 0)) {
        *solution_1 = *solution_2 = -coef_1 / (2 * coef_2);
        return ONE_SOLUTION;

    } else if (desc > 0) {
        float sqr_desc = sqrt(desc);

        *solution_1 = (-coef_1 + sqr_desc) / (2 * coef_2);
        *solution_2 = (-coef_1 - sqr_desc) / (2 * coef_2);
        return TWO_SOLUTIONS;

    } else {
        return PROBLEM;

    }
}


float finding_desc(float coef_2, float coef_1, float coef_0) {
    assert(isfinite(coef_2));
    assert(isfinite(coef_1));
    assert(isfinite(coef_0));
    return (coef_1 * coef_1) - (4 * coef_2 * coef_0);

}


AmountSolutions solving_eq_deg1(float coef_1, float coef_0, float* solution_1) {
    assert(isfinite(coef_1));
    assert(isfinite(coef_0));
    assert(solution_1 != NULL);
    if (is_equal(coef_1, 0) && is_equal(coef_0, 0)){
        return INFINITY_SOLUTIONS; /*при max степени уравнения n <= n корней*/

    } else if (is_equal(coef_1, 0) && !is_equal(coef_0, 0)){
        return NO_SOLUTIONS;

    }else{
        *solution_1 = (-coef_0 / coef_1);
        return ONE_SOLUTION;

    }
}


void printing_solutions(AmountSolutions amount_solution, float coef_2, float coef_1, float coef_0, float solution_1, float solution_2) {
    switch(amount_solution){
            case (PROBLEM):
                printf("ПРОИЗОШЛА ОШИБКА/n");
                break;

            case (NO_SOLUTIONS):
                printf("┐(￣ヘ￣)┌ У уравнения %.2lfx^2 + %.2lfx + %.2lf = 0 нет решений\n", coef_2, coef_1, coef_0);
                break;

            case (ONE_SOLUTION):
                printf("(＾▽＾) У уравнения %.2lfx^2 + %.2lfx + %.2lf = 0 \n"
                       "1 корень: %.2lf\n", coef_2, coef_1, coef_0, solution_1);
                break;

            case (TWO_SOLUTIONS):
                printf("(o˘◡˘o) У уравнения %.2lfx^2 + %.2lfx + %.2lf = 0 \n"
                       "2 корня: %.2lf и %.2lf\n", coef_2, coef_1, coef_0, solution_1, solution_2);
                break;

            case (INFINITY_SOLUTIONS):
                printf("(⊙_⊙) У уравнения %.2lfx^2 + %.2lfx + %.2lf = 0 \n"
                       "бесконечное количество решений\n", coef_2, coef_1, coef_0);
                break;

            // default:
            //     printf("(^_-) ПРОИЗОШЛА ОШИБКА\n");
            //     break;
        }
}


bool is_equal(float a, float b) {
    assert(isfinite(a));
    assert(isfinite(b));

    return (fabs(a - b) < EPSILON);
}


bool cleaning_buffer() {
    char c = getchar();

    while (c != '\n') {
        if (c != ' '){
            while (getchar() != '\n') {;}
            return false;
        }
        c = getchar();
    }
    return true;
}


