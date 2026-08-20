#include <stdio.h>
#include <assert.h>
#include <math.h>


#define MAX_DEG 2 /*максимальная степень уравнения, которе мы решаем*/

#define PROBLEM -1
#define NO_SOLUTIONS 0
#define ONE_SOLUTION 1
#define TWO_SOLUTIONS 2
#define INFINITY_SOLUTIONS MAX_DEG + 1


int solving_equation(float a, float b, float c, float* x1, float* x2);
float finding_desc(float a, float b, float c);
int solving_eq_deg2(float a, float b, float c, float* x1, float* x2);
int solving_eq_deg1(float b, float c, float* x1);
void printing_solutions(int amount_solution, float x1, float x2);
void entering_coefs(float a, float b, float c);
// char is_appealing();


int main(){
    float a = NAN, b = NAN, c = NAN;
    float x1 = NAN, x2 = NAN;

    int amount_solution = solving_equation(a, b, c, &x1, &x2);

    printing_solutions(amount_solution, x1, x2);
}


int solving_equation(float a, float b, float c, float* x1, float* x2) {
    entering_coefs(a, b, c);

    int amount_solutions = solving_eq_deg2(a, b, c, x1, x2);

    return amount_solutions;
}


int solving_eq_deg2(float a, float b, float c, float* x1, float* x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    if (a == 0) {
        solving_eq_deg1(b, c, x1);
    }

    float desc = finding_desc(a, b, c);

    if (desc < 0) {
        return 0;

    } else if (desc == 0) {
        *x1 = *x2 = -b / (2 * a);
        return 1;

    } else if (desc > 0){
        float sqr_desc = sqrt(desc);

        *x1 = (-b + sqr_desc) / (2 * a);
        *x2 = (-b - sqr_desc) / (2 * a);
        return 2;

    } else{
        return -1;

    }
}


int solving_eq_deg1(float b, float c, float* x1) {
    if (b == 0 && c == 0){
        return MAX_DEG + 1; /*при max степени уравнения n <= n корней*/

    } else if (b == 0 && c != 0){
        return 0;

    }else{
        *x1 = (-c / b);
        return 1;

    }
}


float finding_desc(float a, float b, float c) {
    return (b * b) - (4 * a * c);

}

void printing_solutions(int amount_solution, float x1, float x2) {
    switch(amount_solution){
            case (PROBLEM):
                printf("ПРОИЗОШЛА ОШИБКА/n");
                break;

            case (NO_SOLUTIONS):
                printf("У уравнения нет решений :(\n");
                break;

            case (ONE_SOLUTION):
                printf("У уравнения 1 корень %.2f\n", x1);
                break;

            case (TWO_SOLUTIONS):
                printf("У уравнения 2 корня %.2f и %.2f\n", x1, x2);
                break;

            case (INFINITY_SOLUTIONS):
                printf("У уравнения бесконечное количество решений\n");
                break;

            default:
                printf("ПРОИЗОШЛА ОШИБКА\n");
                break;
        }
}


void entering_coefs(float* a, float b, float* c) {
    printf("Привет, будем решать ax^2 + bx + c = 0! \nПрисылай коэффициенты через пробел ");

    scanf("%f %f %f", a, b, c);

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
}


bool is_equal(float a, float b) {
    return (fabs(a - b) < 1e-6f)
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
