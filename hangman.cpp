#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

string secret_word;
map<char, bool> has_guessed;
vector<char> wrong_guesses;

bool char_in_string(char guess)
{
    for (char letter : secret_word)
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
    for (char letter : secret_word)
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
    for (char letter : secret_word)
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

void toupper_str(string &word)
{
    transform(word.begin(), word.end(), word.begin(), ::toupper);
}

void save_db_file(vector<string> words)
{
    ofstream db;
    db.open("words.txt");
    if (db.is_open())
    {
        db << words.size() << endl;
        for (string word : words)
        {
            db << word << endl;
        }

        db.close();
    }
    else
    {
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

vector<string> read_file()
{
    ifstream my_file;
    vector<string> words;
    my_file.open("words.txt");

    if (my_file.is_open())
    {
        int word_quantity;
        my_file >> word_quantity;
        for (int i = 0; i < word_quantity; i++)
        {
            string current_word;
            my_file >> current_word;
            words.push_back(current_word);
        }

        my_file.close();
        return words;
    }
    else
    {
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void add_word_to_db()
{
    cout << "Digite a nova palavra: " << endl;
    string new_word;
    cin >> new_word;
    toupper_str(new_word);

    vector<string> words;
    words = read_file();
    words.push_back(new_word);
    save_db_file(words);
}

void handle_endgame()
{
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era " << secret_word << endl;

    if (!got_all_letters())
    {
        cout << "Você perdeu! Tente novamente" << endl;
    }
    else
    {
        cout << "Parabéns! Você acertou a palavra secreta" << endl;
        cout << "Você deseja adicionar uma nova palavra ao jogo? (S/N)" << endl;
        char answer;
        cin >> answer;
        if (toupper(answer) == 'S')
        {
            add_word_to_db();
        }
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

void choose_secret_word()
{
    int index;
    vector<string> words;
    words = read_file();

    srand(time(NULL));
    index = rand() % words.size();
    secret_word = words[index];
}

int main()
{

    greetings();
    choose_secret_word();

    while (has_tries_left() && !got_all_letters())
    {

        print_wrong_guesses(wrong_guesses);

        print_hangman_letters(has_guessed);

        char guess = get_user_guess();
        has_guessed[guess] = true;

        handle_guess(guess);
    }

    handle_endgame();
}