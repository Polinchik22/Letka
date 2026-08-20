#include <stdio.h>
#include <assert.h>
#include <math.h>


#define MAX_DEG 2 /*максимальная степень уравнения, которе мы решаем*/


int solving_equation(float a, float b, float c, float* x1, float* x2);
float funding_desc(float a, float b, float c);
int solving_eq_deg2(float a, float b, float c, float* x1, float* x2);
int solving_eq_deg1(float b, float c, float* x1);
void printing_solutions(int amount_solution, float x1, float x2);
// char is_appealing();


int main(){
    float a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;

    int amount_solution = solving_equation(a, b, c, &x1, &x2);

    printing_solutions(amount_solution, x1, x2);
}


int solving_equation(float a, float b, float c, float* x1, float* x2){
    printf("Привет, будем решать ax^2 + bx + c = 0! \nПрисылай коэффициенты через пробел ");

    scanf("%f %f %f", &a, &b, &c);

    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    // assert(a != NAN);
    // assert(b != NAN);
    // assert(c != NAN);

    int amount_solutions = solving_eq_deg2(a, b, c, x1, x2);

    return amount_solutions;
}


int solving_eq_deg2(float a, float b, float c, float* x1, float* x2){
    if (a == 0){
        solving_eq_deg1(b, c, x1);
    }

    float desc = funding_desc(a, b, c);

    if (desc < 0){
        return 0;

    } else if (desc == 0){
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


int solving_eq_deg1(float b, float c, float* x1){
    if (b == 0 && c == 0){
        return MAX_DEG + 1; /*при max степени уравнения n <= n корней*/

    } else if (b == 0 && c != 0){
        return 0;

    }else{
        *x1 = (-c / b);
        return 1;

    }
}


float funding_desc(float a, float b, float c){
    return (b * b) - (4 * a * c);

}

void printing_solutions(int amount_solution, float x1, float x2){
    switch(amount_solution){
            case (-1):
                printf("ПРОИЗОШЛА ОШИБКА/n");
                break;

            case (0):
                printf("У уравнения нет решений :(\n");
                break;

            case (1):
                printf("У уравнения 1 корень %.2f\n", x1);
                break;

            case (2):
                printf("У уравнения 2 корня %.2f и %.2f\n", x1, x2);
                break;

            case (MAX_DEG + 1):
                printf("У уравнения бесконечное количество решений\n");
                break;

            default:
                printf("ПРОИЗОШЛА ОШИБКА\n");
                break;
        }
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
