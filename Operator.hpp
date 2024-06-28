//
// Created by holer on 28.06.2024.
//

#ifndef PROJECT_OPERATOR_HPP
#define PROJECT_OPERATOR_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <limits>

#include "GameFeatures.hpp"
#include "sudokuGenerator.hpp"
using namespace std;
const int N = 9;

void gameStart(){
    int x, y, number, lives = 3;
    srand(time(nullptr));
    auto **sudoku = new int*[N];
    for (int i = 0; i < N; ++i){
        sudoku[i] = new int[N];
    }
    auto **play_field = new int *[N];
    for (int i = 0; i < N; ++i){
        play_field[i] = new int[N];
    }
    generate(sudoku);
    equate(sudoku, play_field);
    mask(play_field);

    while(true){
        if (lives == 0){
            cout << "You have no more lives left." << endl << endl << "Goog luck next time!" << endl;
            cout << "The solution was:" << endl << endl;
            print_sudoku(sudoku);
            getchar();
            exit(0);
        }
        if (check_win(play_field, N)){
            break;
        }
        print_sudoku(play_field);
        cout << "Print where to put the number:";
        cout << endl << "Row - "; cin >> y;
        while (cin.fail() || y >= 10 || y <= 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, print the int number from 1 to 9" << endl;
            cout << "Row - "; cin >> y;
        }
        cout << endl << "Column - "; cin >> x;
        while (cin.fail() || x >= 10 || x <= 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, print the int number from 1 to 9" << endl;
            cout << "Column - "; cin >> x;
        }
        cout << "Now print the number to put: "; cin >> number;
        while (cin.fail() || number >= 10 || number <= 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please, print the int number from 1 to 9" << endl;
            cout << "Now print the number to put: "; cin >> number;
        }

        if (!check_line(x, y, number, play_field, N)){
            --lives;
            cout << endl << "=== MISTAKE! ===" << endl << "There's already such a number in this row!" << endl << "Lives left: " << lives << endl << endl;
        }
        else if (!check_column(x, y, number, play_field, N)){
            --lives;
            cout << endl << "=== MISTAKE! ===" << endl << "There's already such a number in this column!" << endl << "Lives left: " << lives << endl << endl;
        }
        else if (!check_quadrant(x, y, play_field, number, identify_quadrant(x, y))){
            --lives;
            cout << endl << "=== MISTAKE! ===" << endl << "There's already such a number in this quadrant!" << endl << "Lives left: " << lives << endl << endl;
        }
        else {
            play_field[y-1][x-1] = number;
            cout << "Successfully added!" << endl << endl;
        }
    }
    print_sudoku(play_field);
    cout << endl << endl << "Congratulations! You've won the game!" << endl << "Lives left: " << lives << "/" << 3 << endl;
    getchar();
}





#endif //PROJECT_OPERATOR_HPP
