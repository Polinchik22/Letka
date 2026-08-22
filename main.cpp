#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "square_equation.cpp"
#include "testiing_solving.cpp"


int main() {
    float coef_2 = NAN, coef_1 = NAN, coef_0 = NAN;
    float solution_1 = NAN, solution_2 = NAN;

    entering_coefs(&coef_2, &coef_1, &coef_0);

    AmountSolutions amount_solution = solving_equation(coef_2, coef_1, coef_0, &solution_1, &solution_2);

    printing_solutions(amount_solution, coef_2, coef_1, coef_0, solution_1, solution_2);


}
