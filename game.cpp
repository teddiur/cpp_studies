#include <cstdlib>
#include <iostream>
#include <ctime> 
using namespace std;

string check_guess(int guess, int right_number){
    if (guess > right_number){
        return "Muito alto";
    } 
    else {
        return "Muito baixo";
    }
    
}

int main() {
    srand(time(NULL));
    int our_number = rand() % 20 + 1;
    int user_guess = 0;

    while (true) {
        cout << "Escolha um número entre 1 e 20" << endl;
        cin >> user_guess;

        if(!user_guess) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Digite um número, cabeçudo" << endl;
            continue;
        }

        if (user_guess == our_number) {
            cout << "VOCÊ É GÊNIO!!!" << endl;
            break;
        }

        cout << check_guess(user_guess, our_number) << endl;

    }

    return 0;
}