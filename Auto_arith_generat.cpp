#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int generateNumber(int grade) {
    if (grade == 1) {
        return rand() % 20 + 1;
    }
    else if (grade == 2) {
        return rand() % 50 + 1;
    }
    else if (grade == 3) {
        return rand() % 1000 + 1;
    }
    else {
        return rand() % 100 + 1;
    }
}

char generateOperator(int grade) {
    if (grade == 1) {
        return (rand() % 2 == 0) ? '+' : '-';
    }
    else if (grade == 2) {
        return (rand() % 2 == 0) ? '+' : '-';
    }
    else if (grade == 3) {
        int op = rand() % 3;
        if (op == 0) return '+';
        else if (op == 1) return '-';
        else return '*';
    }
    else {
        int op = rand() % 4;
        if (op == 0) return '+';
        else if (op == 1) return '-';
        else if (op == 2) return '*';
        else return '/';
    }
}

int main() 
{
    string m;
    while (1) {
        srand(time(0));

        int grade, numQuestions;
        cout << "Enter grade level (1-6): ";
        cin >> grade;
        while(grade > 6 || grade < 0)
        {
            cout << "The number is not appropriate please resume inputing a new number: ";
            cin >> grade;
        }
        cout << "Enter number of questions: ";
        cin >> numQuestions;

        for (int i = 0; i < numQuestions; i++) {
            int num1 = generateNumber(grade);
            int num2 = generateNumber(grade);
            char op = generateOperator(grade);

            if (op == '/' && num2 == 0) {
                num2 = 1;  // Avoid division by zero
            }

            cout << num1 << " " << op << " " << num2 << " = " << endl;
        }
       
        cout << "Do you want to continue to generate more questions? :  ";
        cin >> m;
        if (m == "no")
        {
            return 0;
        }
    
    }
    return 0;
}