#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

const string SECRET_WORD = "MELANCIA";
map<char, bool> has_guessed;
vector<char> wrong_guesses;

bool char_in_string(char guess)
{
    for (char letter : SECRET_WORD)
    {
        if (guess == letter)
        {
            return true;
        }
    }
    return false;
}

void greetings()
{
    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl
         << endl;
    cout << "Vamos jogar o jogo da forca!" << endl;
}

void print_wrong_guesses(vector<char> wrong_guesses)
{
    cout << "Chutes errados: ";
    for (char letter : wrong_guesses)
    {
        cout << letter << " ";
    }
    cout << endl;
}

void print_hangman_letters(map<char, bool> has_guessed)
{
    for (char letter : SECRET_WORD)
    {
        if (has_guessed[letter])
        {
            cout << letter << " ";
        }
        else
        {
            cout << "_ ";
        }
    }
    cout << endl;
}

char get_user_guess()
{
    char guess;
    cout << "Chute uma letra:";
    cin >> guess;
    return toupper(guess);
}

bool got_all_letters()
{
    for (char letter : SECRET_WORD)
    {
        if (!has_guessed[letter])
        {
            return false;
        }
    }
    return true;
}

bool has_tries_left()
{
    return wrong_guesses.size() < 5;
}

void print_endgame_messages()
{
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era " << SECRET_WORD << endl;

    if (!got_all_letters())
    {
        cout << "Você perdeu! Tente novamente" << endl;
    }
    else
    {
        cout << "Parabéns! Você acertou a palavra secreta" << endl;
    }
}

void handle_guess(char guess)
{
    if (char_in_string(guess))
    {
        cout << "Você acertou, o seu chute está na palavra!" << endl;
    }
    else
    {
        cout << "Você errou, o seu chute não está na palavra!" << endl;
        wrong_guesses.push_back(guess);
    }
    cout << endl;
}

int main()
{
    greetings();
    while (has_tries_left() && !got_all_letters())
    {

        print_wrong_guesses(wrong_guesses);

        print_hangman_letters(has_guessed);

        char guess = get_user_guess();
        has_guessed[guess] = true;

        handle_guess(guess);
    }

    print_endgame_messages();
}