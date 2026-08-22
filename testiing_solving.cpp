#include <stdio.h>
#include <assert.h>
#include <math.h>


int running_tests();
bool run_test(float coef_2, float coef_1, float coef_0, AmountSolutions amount_solutions, float solution_1, float solution_2);
void printing_error(float coef_2, float coef_1, float coef_0, AmountSolutions ref_amount_solutions, float ref_solution_1, float ref_solution_2, AmountSolutions e_amount_solutions, float e_solution_1, float e_solution_2);
void creating_equation_by_solutions(AmountSolutions amount_solutions, float* coef_2, float* coef_1, float* coef_0, float solution_1, float solution_2);


int running_tests(){
    float coef_2 = 1, coef_1 = -5, coef_0 = 6;
    AmountSolutions ref_amount_solutions =  TWO_SOLUTIONS;
    float ref_solution_1 = 2, ref_solution_2 = 3;

    bool is_correct = run_test(coef_2, coef_1, coef_0, ref_amount_solutions, ref_solution_1, ref_solution_2);

    return 0;
}

bool run_test(float coef_2, float coef_1, float coef_0, AmountSolutions ref_amount_solutions, float ref_solution_1, float ref_solution_2){
    float e_solution_1 = NAN, e_solution_2 = NAN;
    AmountSolutions e_amount_solutions = solving_equation(coef_2, coef_1, coef_0, &e_solution_1, &e_solution_2);

    if (e_amount_solutions != ref_amount_solutions){
        printing_error(coef_2, coef_1, coef_0, ref_amount_solutions, ref_solution_1, ref_solution_2, e_amount_solutions, e_solution_1, e_solution_2);
        return false;
    } else {
        int is_equal_solution_1 = is_equal(ref_solution_1, e_solution_1);
        int is_equal_solution_2 = is_equal(ref_solution_2, e_solution_2);

        if ((is_equal_solution_1 + is_equal_solution_2) == ref_amount_solutions){
            return true;
        } else {
            printing_error(coef_2, coef_1, coef_0, ref_amount_solutions, ref_solution_1, ref_solution_2, e_amount_solutions, e_solution_1, e_solution_2);
            return false;
        }
    }
}


void printing_error(float coef_2, float coef_1, float coef_0, AmountSolutions ref_amount_solutions, float ref_solution_1, float ref_solution_2, AmountSolutions e_amount_solutions, float e_solution_1, float e_solution_2){
    printf("ОШИБКА в решении уравнения: %.2lfx^2 + %.2lfx + %.2lf = 0 \n"
           "Ожидалось  %d решений: первое %5.2lf, второе %5.2lf\n"
           "Получилось %d решений: первое %5.2lf, второе %5.2lf\n",
           coef_2, coef_1, coef_0,
           ref_amount_solutions, ref_solution_1, ref_solution_2,
           e_amount_solutions, e_solution_1, e_solution_2);
}


void creating_equation_by_solutions(AmountSolutions amount_solutions, float* coef_2, float* coef_1, float* coef_0, float solution_1, float solution_2){
    switch (amount_solutions){
        case(TWO_SOLUTIONS):
            *coef_2 = 1;
            *coef_1 = -(solution_1 + solution_2);
            *coef_0 = solution_1 * solution_2;

        case(ONE_SOLUTION):
            *coef_2 = 0;
            *coef_1 = - solution_1;
    }
}
