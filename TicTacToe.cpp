#include <conio.h>
#include <iostream>
#include <locale.h>

using namespace std;

int const N = 3;
int Win;
char const P1S = 'X', P2S = '0', NPS = '-';

void NewGame(char a[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a[i][j] = NPS;
        }
    }
}
bool PlayerTurn(bool a)
{
    if (a)
    {
        return false;
    }
    else
        return true;
}
bool Mistake(int b[2], char a[N][N])
{
    if ((a[b[0] - 1][b[1] - 1] == P1S) || (a[b[0] - 1][b[1] - 1] == P2S))
    {
        return true;
    }
    else return false;
}
void TextInput(bool a, bool b)
{
    if (a && !b)
    {
        cout << "\nИгрок 1, введите координаты \'" << P1S << "\': ";
    }
    else if (!a && !b)
    {
        cout << "\nИгрок 2, введите координаты \'" << P2S << "\': ";
    }
    if (a && b)
    {
        cout << "\nИгрок 1, вы ошиблись, повторите ввод \'" << P1S << "\': ";
    }
    else if (!a && b)
    {
        cout << "\nИгрок 2, вы ошиблись, повторите ввод \'" << P2S << "\': ";
    }
}
int Input()
{
    int a;
    while (!(cin >> a) || a <= 0 || a > 3)
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Ошибка!!! Повторите ввод: ";
    }
    return a;
}
void GameMap(char a[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (a[i][j] != P1S && a[i][j] != P2S)
            {
                a[i][j] = NPS;
            }
        }
    }
    cout << "   1  2  3\n";
    for (int i = 0; i < N; i++)
    {
        cout << i + 1 << " ";
        for (int j = 0; j < N; j++)
        {
            cout << "[" << a[i][j] << "]";
        }
        cout << endl;
    }
}
bool InGame(char a[N][N], bool b)
{
    char simbol;
    if (b) simbol = P1S;
    else simbol = P2S;
    bool GameOwer = false;
    Win = 0;
    for (int i = 0; i < N; i++)
    {
        Win = 0;
        if (!GameOwer)
        {
            for (int j = 0; j < N; j++)
            {
                if (a[i][j] == simbol) Win++;
            }
            if (Win == 3) GameOwer = true;
            else if (Win < 3) Win = 0;
        }
        if (!GameOwer)
        {
            for (int j = 0; j < N; j++)
            {
                if (a[j][i] == simbol) Win++;
            }
            if (Win == 3) GameOwer = true;
            else if (Win < 3) Win = 0;
        }
    }
    if (!GameOwer)
    {
        for (int i = 0; i < N; i++)
        {
            if (a[i][i] == simbol) Win++;
        }
        if (Win == 3) GameOwer = true;
        else if (Win < 3) Win = 0;
    }
    if (!GameOwer)
    {
        for (int i = 0, j = N - 1; j > 0; i++, j--)
        {
            if (a[i][j] == simbol) Win++;
        }
        if (Win == 3) GameOwer = true;
        else if (Win < 3) Win = 0;
    }
    if (!GameOwer)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (a[i][j] == P1S || a[i][j] == P2S) Win++;
            }
        }
        if (Win == 9) GameOwer = true;
        else if (Win < 9) Win = 0;
    }
    if (!GameOwer) return true;
    else return false;
}
void Outpoot(char a[N][N])
{
    bool Player1 = true;
    bool GameRuning = InGame(a, Player1);
    while (GameRuning)
    {
        bool OutputMistake = false;
        bool Turn = true;
        int Coordinates[2];
        while (Player1 && Turn)
        {
            Turn = true;
            GameMap(a);
            TextInput(Player1, OutputMistake);
            Coordinates[0] = Input();
            Coordinates[1] = Input();
            if (!Mistake(Coordinates, a))
            {
                a[Coordinates[0] - 1][Coordinates[1] - 1] = P1S;
                GameRuning = InGame(a, Player1);
                if (GameRuning)
                {
                    Player1 = PlayerTurn(Player1);
                    system("cls");
                    Turn = false;
                }
                else if (!GameRuning) Turn = false;
            }
            else if (Mistake(Coordinates, a))
            {
                OutputMistake = true;
                system("cls");
            }
        }
        while (!Player1 && Turn)
        {
            Turn = true;
            GameMap(a);
            TextInput(Player1, OutputMistake);
            Coordinates[0] = Input();
            Coordinates[1] = Input();
            if (!Mistake(Coordinates, a))
            {
                a[Coordinates[0] - 1][Coordinates[1] - 1] = P2S;
                GameRuning = InGame(a, Player1);
                if (GameRuning)
                {
                    Player1 = PlayerTurn(Player1);
                    system("cls");
                    Turn = false;
                }
                else if (!GameRuning) Turn = false;
            }
            else if (Mistake(Coordinates, a))
            {
                OutputMistake = true;
                system("cls");
            }
        }
        if (!GameRuning && Win != 9)
        {
            switch (Player1)
            {
            case 1:
            {
                system("cls");
                GameMap(a);
                cout << "\nПоздравляем! Победил игрок 1.\n";
            }
            break;
            case 0:
            {
                system("cls");
                GameMap(a);
                cout << "\nПоздравляем! Победил игрок 2.\n";
            }
            break;
            }
        }
        else if (Win == 9)
        {
            system("cls");
            GameMap(a);
            cout << "\nХо-хо-хо, ничья!!!\n";
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    bool Retry = true;
    char a;
    while (Retry)
    {
        char Game[N][N];
        Outpoot(Game);
        cout << "\nЖелаете повторить? (y/s): ";
        while (!(cin >> a) || a != 'y' && a != 'n')
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Ошибка! Повторите! (y/n): ";
        }
        switch (a)
        {
        case 'y':
        {
            NewGame(Game);
            Retry = true;
            system("cls");
        }
        break;
        case 'n': Retry = false; break;
        }
    }
    return 0;
}
