#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

string  rand(string word);
int     init_game(char mode);
int     new_game(char mode);
string  get_word(char mode);

string  rand(string word)
{
    string  rand_word;
    int     pos(0);
    int     size_word;
    int     i;

    size_word = word.size();
    i = 0;
    rand_word = word;
    while (i < size_word)
    {
        pos = rand() % word.size();
        rand_word[i] = word[pos];
        word.erase(pos, 1);
        i++;
    }
    return (rand_word);
}

int     init_game(char mode)
{
    string  rand_word;
    string  rep;
    int     cnt;
    string  word;

    cnt = 5;
    word = get_word(mode);
    rand_word = rand(word);
    do
    {
        cout << "Quel est ce mot ? " << endl;
        cout << rand_word << endl;
        cin >> rep;
        cin.ignore();
        if (word.compare(rep) == 0)
        {
            cout << "Bravo !" << endl << endl;
            new_game(mode);
            rep = "";
        }
        else
        {
            cout << "Ce n'est pas le mot !" << endl;
            cnt--;
            if (cnt <= 0)
            {
                cout << "Vous avez perdu" << endl;
                new_game(mode);
            }
            cout << "Il vous reste " << cnt << " tentatives" << endl;
        }
    }while (rep != word);

    return (1);
}

int     new_game(char mode)
{
    char    c;
    do
    {
        cout << "Voulez vous faire une nouvelle partie ? (o/N)" << endl;
        cin >> c;
        if (c == 'o' || c == 'O')
            init_game(mode);
        else if (c == 'n' || c == 'N')
        {
            cout << "Aurevoir !" << endl;
            exit (0);
        }
        else
            cout << "Vous devez répondre par o/N" << endl;
    }while (c != 'o' && c != 'O' && c != 'n' && c != 'N');
    return (0);
}

string  get_word(char mode)
{
    string  word;
    int     pos;
    int     file_size;

    if (mode == '1')
    {
        ifstream    file("./dico.txt");
        if (file)
        {
            file.seekg(0, ios::end);
            file_size = file.tellg();
            pos = rand() % file_size;
            file.seekg(pos, ios::beg);
            getline(file, word); 
            file >> word; 
        }
        else
            cout << "Erreur d'ouverture du fichier" << endl;
    }    
    else
    {
        cout << "Veuillez saisir un mot" << endl;
        cin >> word;
    }

    return (word);
}
int     main()
{   
    char     mode;

    srand(time(0));
    
    cout << "[Bienvenu sur le jeu du mot mystere]" << endl << endl;
    do
    {
        cout << "Veuillez choisir un mode de jeu :" << endl;
        cout << "Solo(1) / Deux joueurs(2)" << endl;
        cin >> mode;
        cin.ignore();
    }while (mode != '1' && mode != '2');

    init_game(mode);

    return 0;
}
