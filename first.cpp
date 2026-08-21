#include <stdio.h>
#include <assert.h>
#include <math.h>


#define PROBLEM -1
#define NO_SOLUTIONS 0
#define ONE_SOLUTION 1
#define TWO_SOLUTIONS 2
#define INFINITY_SOLUTIONS 3
#define CRITICAL 2
#define EPSILON 1e-6f


void entering(float* coef, char litera);
int solving_equation(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2);
int solving_eq_deg2(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2);
float finding_desc(float coef_2, float coef_1, float coef_0);
int solving_eq_deg1(float coef_1, float coef_0, float* solution_1);
void printing_solutions(int amount_solution, float coef_2, float coef_1, float coef_0, float solution_1, float solution_2);
bool is_equal(float coef_2, float coef_1);
// char is_appealing();


int main(){
    float coef_2 = NAN, coef_1 = NAN, coef_0 = NAN;
    float solution_1 = NAN, solution_2 = NAN;

    printf("Привет! будем решать ax^2 + bx + c = 0\n");
    entering(&coef_2, 'a');
    entering(&coef_1, 'b');
    entering(&coef_0, 'c');

    int amount_solution = solving_equation(coef_2, coef_1, coef_0, &solution_1, &solution_2);

    printing_solutions(amount_solution, coef_2, coef_1, coef_0, solution_1, solution_2);
}



void entering(float* coef, char litera){
    // char input[100];
    // int i = 0;
    // bool not_number_input_flag = false;
    // int amount_dots = 0;

    printf("Введи коэффициент %c ", litera);
//     fgets(input, sizeof(input), stdin);
//
//     while (input[i] != '\0' && amount_dots <= 1){
//         if ((input[i] - '0') > 9) {
//             not_number_input_flag = true;
//             break;
//         } else if (input[i] == '.') {
//             amount_dots++;
//         }
//         i++;
//     }
//
//     if (not_number_input_flag || (amount_dots > 1)) {
//         entering(coef, litera);
//     } else {
//         *coef = atof(input);
//     }

    if (scanf("%f", coef) != 1 || getchar() != '\n'){
        while (getchar() != '\n') {;}
        entering(coef, litera);
    }
}


int solving_equation(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2) {
    assert(isfinite(coef_2));
    assert(isfinite(coef_1));
    assert(isfinite(coef_0));
    assert(solution_1 != NULL);
    assert(solution_2 != NULL);

    int amount_solutions = 0;

    if (is_equal(coef_2, 0)) {
        amount_solutions = solving_eq_deg1(coef_1, coef_0, solution_1);

    }else{
        amount_solutions = solving_eq_deg2(coef_2, coef_1, coef_0, solution_1, solution_2);
    }

    return amount_solutions;
}


int solving_eq_deg2(float coef_2, float coef_1, float coef_0, float* solution_1, float* solution_2) {
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

    } else if (desc > 0){
        float sqr_desc = sqrt(desc);

        *solution_1 = (-coef_1 + sqr_desc) / (2 * coef_2);
        *solution_2 = (-coef_1 - sqr_desc) / (2 * coef_2);
        return TWO_SOLUTIONS;

    } else{
        return PROBLEM;

    }
}


float finding_desc(float coef_2, float coef_1, float coef_0) {
    assert(isfinite(coef_2));
    assert(isfinite(coef_1));
    assert(isfinite(coef_0));
    return (coef_1 * coef_1) - (4 * coef_2 * coef_0);

}


int solving_eq_deg1(float coef_1, float coef_0, float* solution_1) {
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


void printing_solutions(int amount_solution, float coef_2, float coef_1, float coef_0, float solution_1, float solution_2) {
    switch(amount_solution){
            case (PROBLEM):
                printf("ПРОИЗОШЛА ОШИБКА/n");
                break;

            case (NO_SOLUTIONS):
                printf("У уравнения %.2lgx^2 + %.2lgx + %.2lg = 0  нет решений :(\n", coef_2, coef_1, coef_0);
                break;

            case (ONE_SOLUTION):
                printf("У уравнения %.2lgx^2 + %.2lgx + %.2lg = 0 \n1 корень: %.2lg\n", coef_2, coef_1, coef_0, solution_1);
                break;

            case (TWO_SOLUTIONS):
                printf("У уравнения %.2lgx^2 + %.2lgx + %.2lg = 0 \n2 корня %.2lg и %.2lg\n", coef_2, coef_1, coef_0, solution_1, solution_2);
                break;

            case (INFINITY_SOLUTIONS):
                printf("ВАУ! У уравнения %.2lgx^2 + %.2lgx + %.2lg = 0 \nбесконечное количество решений\n", coef_2, coef_1, coef_0);
                break;

            default:
                printf("ПРОИЗОШЛА ОШИБКА\n");
                break;
        }
}


bool is_equal(float a, float b) {
    assert(isfinite(a));
    assert(isfinite(b));

    return (fabs(a - b) < EPSILON);
}

// char is_appealing(){
//     printf("К тебе Можно обращаться 'бро'? [Y/N]\n");
//     if (getchar() == 'Y'){
//         return {'Б', 'р', 'о', 0};
//
//     }else{
//         return {'Б', 'р', 'о', 0};
//
//     }
// }
