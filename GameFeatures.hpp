//
// Created by holer on 28.06.2024.
//

#ifndef PROJECT_GAMEFEATURES_HPP
#define PROJECT_GAMEFEATURES_HPP

#include "Operator.hpp"

void mask(int **play_field) {
    srand(time(nullptr));
    for (int i = 0; i < 9; i++) {
        for (int k = 0; k < 9; k++) {
            int x = rand() % 3;
            if (x != 0) {
                play_field[i][k] = -1;
            }
        }
    }
}

void print_sudoku(int **sudoku){
    int i, j;
    for (i = 0; i < 9; i++){
        if (i%3 == 0){
            std::cout << "========================\n";
        }
        std::cout << "| ";

        for (j = 0; j < 9; j++){
            if (sudoku [i][j] <= 0 || sudoku  [i][j]  >= 10){
                std::cout << "  ";
            }
            else std::cout << sudoku[i][j] << " ";

            if ((j+1)%3 == 0) std::cout << "| ";
        }
        std::cout << std::endl;
    }
    std::cout << "========================\n";
}

bool check_line(int x, int y, int number, int **sudoku, int size_array){
    if (sudoku[y-1][x-1] == number){
        return true;
    }
    for (int i = 0; i < size_array; i++){
        if (sudoku[y-1][i] == number) return false;
    }
    return true;
}

bool check_column(int x, int y, int number, int **sudoku, int size_array){
    if (sudoku[y-1][x-1] == number){
        return true;
    }
    for (int i; i < size_array; i++){
        if (sudoku[i][x-1] == number)return false;
    }
    return true;
}

int identify_quadrant(int x, int y){
    for (int i = 3; i <= 9; i += 3){
        if (x <= i){
            if (y <= 3){
                return i/3;
            }
            else if (y <= 6){
                return i/3+3;
            }
            else if (y <= 9){
                return i/3+6;
            }
        }
    }
    return 0;
}

bool check_quadrant(int x, int y, int **sudoku, int number, int quadrant){
    if (sudoku[y-1][y-1] == number){
        return true;
    }
    for (int z = 0; z <= 6; z+=3){
        if (quadrant <= z+3){
            for (int i = z; i < z+3; i++){
                for (int k = (quadrant - z - 1) * 3; k < (quadrant - z) * 3; k++){
                    if (sudoku[i][k] == number){
                        return false;
                    }
                }
            }
            break;
        }
    }
    return true;
}

bool check_win(int **sudoku, int size_array) {
    for (int i = 0; i < size_array; i++){
        for (int k = 0; k < size_array; k++){
            if (sudoku[i][k] <= 0 || sudoku[i][k] >= 10){
                return false;
            }
        }
    }
    return true;
}

void equate(int **giver, int **gainer){
    for (int i = 0; i < 9; i++){
        for (int k = 0; k < 9; k++){
            gainer[i][k] = giver[i][k];
        }
    }
}

#endif //PROJECT_GAMEFEATURES_HPP
