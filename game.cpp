#include <cstdlib>
#include <iostream>
#include <ctime> 
using namespace std;

string check_guess(int guess, int right_number){
    if (guess > right_number){
        return "Muito alto! :c";
    } 
    else {
        return "Muito baixo! D:";
    }
    
}

int get_guess(int current_try) {
    int guess;
    cout << "Tentativa " << current_try << endl;
    cout << "Escolha um número entre 1 e 20" << endl;
    cin >> guess;
    return guess;
}

int get_max_tries(){
    char level;
    cout << "Escolha uma dificuldade de jogo" << endl;
    cout << "Fácil(F), Médio(M) ou Díficil(D)" << endl;
    cin >> level;

    if (level == 'F'){
        return 15;
    } else if (level == 'M') {
        return 10;
    } else {
        return 5;
    }

}

int main() {
    srand(time(NULL));
    const int our_number = rand() % 20 + 1;
    int user_guess = 0;
    int current_try = 1; 
    int max_tries;

    max_tries = get_max_tries();

    cout << "Você tem " << max_tries << " tentativas para descobrir o número" << endl;

    for (current_try; current_try <= max_tries; current_try++) {
        user_guess = get_guess(current_try);

        if(!user_guess) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Digite um número, cabeçudo" << endl;
            continue;
        }

        if (user_guess == our_number) {
            cout << "VOCÊ É GÊNIO!!!" << endl;
            cout << "Terminou em " << current_try << " tentativas" << endl;
            break;
        }

        cout << check_guess(user_guess, our_number) << endl;

    }

    return 0;
}