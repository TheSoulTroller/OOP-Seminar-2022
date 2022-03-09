#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

const int MAX_SIZE = 10;
const int BUFFER = 64;

enum Game
{
    dummy = 0,
    CSGO,
    LOL,
    Dota,
    Valorant,
    Overwatch
};

struct Player
{
    char name [64];
    char team [32];
    Game game;
    int wins;
    int losses;
    double ratioWL;

    void createPlayer()
    {
        cout << "Enter name: ";
        cin.getline(name,32);
        cout << "Enter team: ";
        cin.getline(team,32);
        int userInput;
        cout << "Choose Game:" << "\n1.CS:GO" << "\n2.LOL" << "\n3.Dota" << "\n4.Valorant" << "\n5.Overwatch" << endl;
        cin >> userInput;
        game = (Game)(userInput);
        cout << "Wins: ";
        cin >> wins;
        while(wins < 0)
        {
            cout << "Wins must be a non-negative!" << "/nWins: ";
            cin >> wins;
        }
        cout << "Losses: ";
        cin >> losses;
        while(losses < 0)
        {
            cout << "Losses must be a non-negative!" << "/nLosses: ";
            cin >> losses;
        }
        cout << "Win to Loss ration is calculated automatically!" << endl;
        ratioWL = (double)wins/(double)losses;
        cin.ignore();
    }

    void printPlayer()
    {
        cout << "Player name: " << name << endl;
        cout << "Player team: " << team << endl;
        cout << "Player game: " << game << endl;
        cout << "Wins: " << wins << endl;
        cout << "Losses: " << losses << endl;
        cout << "W/L ratio: " << ratioWL << endl;
    }

};

void createClassPlayer(Player player[], int size)
{
    for(int i = 0; i < size; i++)
    {
        player[i].createPlayer();
    }
}

void printClassPlayer(Player player[], int size)
{
    for(int i = 0; i < size; i++)
    {
        player[i].printPlayer();
        cout << endl;
    }
}

const char* enumToStr(int game)
{
    switch (game)
    {
    case 1: return "CSGO";
    case 2: return "LOL";
    case 3: return "Dota";
    case 4: return "Valorant";
    case 5: return "Overwatch";
    default: return "Invalid value!";
    }
}

void writePlayer(Player player, std::ofstream& out)
{
    out << "Player name: " << player.name << '\n';
    out << "Player team: " << player.team << '\n';
    out << "Player game: " << player.game << '\n';
    out << "Wins: " << player.wins << '\n';
    out << "Losses: " << player.losses << '\n';
    out << "W/L ratio: " << player.ratioWL << '\n';
    out << "______________________________________" << '\n';
}

void writeClassPlayer(Player player[], int size)
{
    std::fstream out;
    out.open("player.txt", std::ios::out);
    if(!out.is_open()) return;

    out << "\t\tPlayer List" << '\n';

    for (int i = 0; i < size; i++)
    {
        out << '\n' << "Player name: " << player[i].name << '\n';
        out << "Player team: " << player[i].team << '\n';
        out << "Player game: " << enumToStr(player[i].game) << '\n';
        out << "Wins: " << player[i].wins << '\n';
        out << "Losses: " << player[i].losses << '\n';
        out << "W/L ratio: " << player[i].ratioWL << '\n';
        out << "_______________________________";
    }

    out.close();
}

int strToEnum(const char* game)
{
    if(strcmp(game,"CSGO") == 0) return 1;
    if(strcmp(game,"LOL") == 0) return 2;
    if(strcmp(game,"Dota") == 0) return 3;
    if(strcmp(game,"Overwatch") == 0) return 4;
    if(strcmp(game,"Valorant") == 0) return 5;
    return 0;
}

char* getData(char* line, char* result)
{
    for(int i = 0;line[i] != '\0';i++)
    {
        if(line[i] == ':')
        {
            i=i+2;
            int j = 0;
            for(;line[i] != '\0';j++, i++)
            {
                result[j] = line[i];
            }
            result[j] = '\0';
            return result;
        }
    }
}

void readClassPlayer(Player player[], int &size)
{
    std::fstream in;
    in.open("player.txt", std::ios::in);
    if(!in.is_open()) return;

    char line[BUFFER];
    char getInfo[16];

    // Skip row 1 and 2 from txt
    in.getline(line, BUFFER);
    in.getline(line, BUFFER);

    for(int i = 0; i < MAX_SIZE && !in.eof(); i++)
    {
        // Get name
        in.getline(line, BUFFER);
        getData(line, player[i].name);

        // Get team
        in.getline(line, BUFFER);
        getData(line, player[i].team);

        // Get game
        in.getline(line, BUFFER);
        getData(line, getInfo);
        player[i].game = (Game)(strToEnum(getInfo));

        // Get wins
        in.getline(line, BUFFER);
        getData(line, getInfo);
        player[i].wins = atoi(getInfo);

        // Get loss
        in.getline(line, BUFFER);
        getData(line, getInfo);
        player[i].losses = atoi(getInfo);

        // Skip W/L ratio
        in.getline(line, BUFFER);
        player[i].ratioWL = (double)player[i].wins / (double)player[i].losses;

        // Skip the __________
        in.getline(line, BUFFER);

        // Increase size of array
        size++;
    }

    in.close();
}

int main()
{
    Player players[MAX_SIZE];
    int size;
    cout << "How many players would you like to add(MAX 10): ";
    cin >> size;
    cin.ignore();

    createClassPlayer(players, size);

    writeClassPlayer(players, size);

    Player player[MAX_SIZE];
    size = 0;

    readClassPlayer(player, size);

    printClassPlayer(player, size);

    return 0;
}