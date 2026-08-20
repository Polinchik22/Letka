#include <stdio.h>
#include <assert.h>
#include <math.h>



#define PROBLEM -1
#define NO_SOLUTIONS 0
#define ONE_SOLUTION 1
#define TWO_SOLUTIONS 2
#define INFINITY_SOLUTIONS 3

void entering_coefs(float* a, float* b, float* c);
int solving_equation(float a, float b, float c, float* x1, float* x2);
int solving_eq_deg2(float a, float b, float c, float* x1, float* x2);
float finding_desc(float a, float b, float c);
int solving_eq_deg1(float b, float c, float* x1);
void printing_solutions(int amount_solution, float a, float b, float c, float x1, float x2);
bool is_equal(float a, float b);
// char is_appealing();


int main(){
    float a = NAN, b = NAN, c = NAN;
    float x1 = NAN, x2 = NAN;

    entering_coefs(&a, &b, &c);

    int amount_solution = solving_equation(a, b, c, &x1, &x2);

    printing_solutions(amount_solution, a, b, c, x1, x2);
}


int solving_equation(float a, float b, float c, float* x1, float* x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);

    int amount_solutions = 0;

    if (is_equal(a, 0)) {
        amount_solutions = solving_eq_deg1(b, c, x1);

    }else{
        amount_solutions = solving_eq_deg2(a, b, c, x1, x2);
    }

    return amount_solutions;
}


int solving_eq_deg2(float a, float b, float c, float* x1, float* x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);

    float desc = finding_desc(a, b, c);

    if (desc < 0) {
        return NO_SOLUTIONS;

    } else if (is_equal(desc, 0)) {
        *x1 = *x2 = -b / (2 * a);
        return ONE_SOLUTION;

    } else if (desc > 0){
        float sqr_desc = sqrt(desc);

        *x1 = (-b + sqr_desc) / (2 * a);
        *x2 = (-b - sqr_desc) / (2 * a);
        return TWO_SOLUTIONS;

    } else{
        return PROBLEM;

    }
}


int solving_eq_deg1(float b, float c, float* x1) {
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    if (is_equal(b, 0) && is_equal(c, 0)){
        return INFINITY_SOLUTIONS; /*при max степени уравнения n <= n корней*/

    } else if (is_equal(b, 0) && !is_equal(c, 0)){
        return NO_SOLUTIONS;

    }else{
        *x1 = (-c / b);
        return ONE_SOLUTION;

    }
}


float finding_desc(float a, float b, float c) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    return (b * b) - (4 * a * c);

}

void printing_solutions(int amount_solution, float a, float b, float c, float x1, float x2) {
    switch(amount_solution){
            case (PROBLEM):
                printf("ПРОИЗОШЛА ОШИБКА/n");
                break;

            case (NO_SOLUTIONS):
                printf("У уравнения %.2fx^2 + %.2fx + %.2f = 0  нет решений :(\n", a, b, c);
                break;

            case (ONE_SOLUTION):
                printf("У уравнения %.2fx^2 + %.2fx + %.2f = 0 \n1 корень %.2f\n", a, b, c, x1);
                break;

            case (TWO_SOLUTIONS):
                printf("У уравнения %.2fx^2 + %.2fx + %.2f = 0 \n2 корня %.2f и %.2f\n", a, b, c, x1, x2);
                break;

            case (INFINITY_SOLUTIONS):
                printf("ВАУ! У уравнения %.2fx^2 + %.2fx + %.2f = 0 \nбесконечное количество решений\n", a, b, c);
                break;

            default:
                printf("ПРОИЗОШЛА ОШИБКА\n");
                break;
        }
}


void entering_coefs(float* a, float* b, float* c) {
    printf("Привет, будем решать ax^2 + bx + c = 0! \nВписывай коэффициенты через пробел ");

    scanf("%f %f %f", a, b, c);

    assert(isfinite(*a));
    assert(isfinite(*b));
    assert(isfinite(*c));
}


bool is_equal(float a, float b) {
    assert(isfinite(a));
    assert(isfinite(b));

    return (fabs(a - b) < 1e-6f);
}

// char is_appealing(){
//     printf("К тебе Можно обращаться 'бро'? [Y/N]\n");
//     if (getchar() == 'Y'){
//         return 'Бро\0';
//
//     }else{
//         return 'Не бро\0';
//
//     }
// }
