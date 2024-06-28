//
// Created by holer on 28.06.2024.
//

#ifndef PROJECT_SUDOKUGENERATOR_HPP
#define PROJECT_SUDOKUGENERATOR_HPP

#include "Operator.hpp"

int candidates[9][9][9];
int iteration_count = 0;

void initCandidate(int i, int j) {
    for (int k = 0; k < 9; k++) {
        candidates[i][j][k] = 1 + k;
    }
    std::random_shuffle(&candidates[i][j][0], &candidates[i][j][9]);
}

void initCandidates(int **sudoku) {
    srand(time(nullptr));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            initCandidate(i, j);
        }
    }
}

int getCandidate(int i, int j, int **sudoku) {
    for (int k  =  0; k  <  9; k++)  {
        if (candidates[i][j][k]  !=  0){
            int candidate_value = candidates[i][j][k];
            candidates[i][j][k]  =  0;
            return candidate_value;
        }
    }
    return 0;
}

bool testCandidate(int i, int j, int  **sudoku)  {
    int current_candidate = sudoku[i][j];
    iteration_count ++;
    for (int p = 0; p < 9; p++){
        if (p == j) continue;
        if (sudoku[i][p]  ==  current_candidate)
            return false;
    }

    for (int p = 0; p < 9; p++){
        if (p == i) continue;
        if  (sudoku[p][j] == current_candidate)
            return false;
    }

    int square_start_i = (int) i / 3 * 3;
    int square_start_j  =  (int) j / 3 * 3;
    int square_end_i = square_start_i + 3;
    int square_end_j = square_start_j + 3;
    for (int p = square_start_i; p < square_end_i; p++){
        for (int m = square_start_j; m < square_end_j; m++){
            if (p == i && m == j) continue;
            if (sudoku[p][m]  ==  current_candidate)
                return false;
        }
    }
    return true;
}

int generate(int **sudoku) {
    initCandidates(sudoku);
    int candidate_value;
    int i = 0;
    int j = 0;
    bool test_result = false;
    do{
        do{
            candidate_value = getCandidate(i, j, sudoku);
            sudoku[i][j] = candidate_value;
            if (candidate_value == 0){
                initCandidate(i, j);
                if (j == 0){
                    j = 8;
                    i--;
                }
                else
                    j--;
                sudoku[i][j] = 0;
                break;
            }
            test_result  =  testCandidate(i, j, sudoku);
        }while(!test_result);

        if (test_result){
            if (j == 8){
                j = 0;
                i++;
            }
            else
                j++;
        }
    }while(sudoku[8][8] == 0);

    std::cout << std::endl << "Iteration count to generate: " << iteration_count << std::endl << std::endl;
    return 0;
}

#endif //PROJECT_SUDOKUGENERATOR_HPP
