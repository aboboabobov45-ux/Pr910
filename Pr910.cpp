/*Практика 9:
Определить структурный тип, описывающий компьютерные игры (название игры,
студия разработчик, стоимость подписки, объем аудитории игроков,
поддерживаемые платформы: PC, mobile, gamepad; тип: RPG, стратегия, гонки,
авиасимулятор и др.). Заполнить структурный массив 20-ю записями. Переписать из
исходного массива в другой массив, информацию только об авиасимуляторах с
аудиторией от 1 миллиона пользователей. Затем новый массив отсортировать по
поддерживаемым платформам. Вывести все данные по конкретной игре. Вывести 3
самых дорогих игр. Реализовать функцию изменения игры. В отдельный массив
поместить все стратегии для PC. Реализовать вывод отфильтрованных данных в виде
оберточной функции.

Практика 10:
1. Считать из текстового файла данные числового поля для вашей.
2. Сделать чтение / запись своей структуры в бинарный файл. Оформить в виде подпрограмм*/


#include <iostream>
using namespace std;
#include "math.h"
#include <fstream>
#include <string>

enum Platform {
    pc,
    mobile,
    gamepad,
    all
};

enum Genre {
    rpg,
    strategy,
    racinng,
    flight_sim,
    stealth,
    card,
    shooter,
    action
};

char genre_name[8][30] = { "RPG", "STRATEGY", "RACING", "FLIGHT_SIM", "STEALTH", "CARD", "SHOOTER", "ACTION" };
char platform_name[4][20] = { "PC", "MOBILE", "GAMEPAD", "ALL" };

struct nsdstrct {
    int release;
    float rating;
};

struct game {
    char name[50];
    char studio[50];
    float price;
    float audience;
    Platform platform;
    Genre genre;
    nsdstrct info;
};

const int SIZE = 20;

game* init() {
    game* games = new game[SIZE];
    games[0] = { "The witcher", "CD Project RED", 999.99, 10, all, rpg, {2015, 9.5} };
    games[1] = { "Assassin's creed", "Ubisoft", 1999.99, 8, all, stealth, {2017, 8.7} };
    games[2] = { "Skyrim", "Bethesda", 899.99, 12, all, rpg, {2011, 9.8} };
    games[3] = { "Tomb raider", "Core Design", 1999.99, 3, all, rpg, {2013, 8.9} };
    games[4] = { "Solitaire", "Narodnoe", 1.99, 10, all, card, {1990, 7.5} };
    games[5] = { "Microsoft flight simulator", "Asobo", 1000.0, 5, all, flight_sim, {2020, 9.7} };
    games[6] = { "TMP flight1", "Kontora1", 1111, 4, pc, flight_sim, {2021, 8.0} };
    games[7] = { "TMP flight2", "Kontora1", 1111, 4, mobile, flight_sim, {2021, 7.8} };
    games[8] = { "TMP flight3", "Kontora1", 1111, 4, pc, flight_sim, {2022, 8.2} };
    games[9] = { "TMP flight4", "Kontora1", 1111, 4, gamepad, flight_sim, {2022, 7.9} };
    games[10] = { "StarCraft II", "Blizzard", 0, 15, pc, strategy, {2010, 9.3} };
    games[11] = { "Civilization VI", "Firaxis", 1499.99, 20, all, strategy, {2016, 8.8} };
    games[12] = { "Need for speed", "EA Games", 2499.99, 18, all, racinng, {2019, 7.5} };
    games[13] = { "Forza horizon 5", "Playground Games", 2999.99, 25, pc, racinng, {2021, 9.4} };
    games[14] = { "Battlefield 1", "EA", 1234, 35, pc, shooter, {2016, 9.1} };
    games[15] = { "Star wars: battlefront II", "EA", 3999.99, 30, all, shooter, {2017, 7.2} };
    games[16] = { "Ready or not", "VOID Interactive", 999.99, 28, all, shooter, {2021, 8.6} };
    games[17] = { "Devil may cry", "Capcom", 10, 60, all, action, {2021, 9.2} };
    games[18] = { "Metal gear solid V", "Konami", 1499.99, 12, all, action, {2015, 9.0} };
    games[19] = { "Hitman 3", "IO Interactive", 1999.99, 10, all, stealth, {2021, 8.9} };
    return games;
}

//информация об авиасимуляторах с аудиторией больше миллиона
int flightsimmln(game* gms, int gmssize, game* ssave) {
    int cnt = 0;
    for (int i = 0; i < gmssize; i++) {
        if (gms[i].genre == flight_sim && gms[i].audience >= 1) {
            ssave[cnt] = gms[i];
            cnt++;
        }
    }
    return cnt;
}

//вывести все данные по конкретной игре
void gamename(game* games, int size, const char* srchgame) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (strcmp(games[i].name, srchgame) == 0) {
            found = true;
            cout << "Данные по игре: " << endl;
            cout << "Название: " << games[i].name << endl;
            cout << "Контора: " << games[i].studio << endl;
            cout << "Цена: " << games[i].price << " руб" << endl;
            cout << "Аудитория: " << games[i].audience << " млн" << endl;
            cout << "Платформа: " << platform_name[games[i].platform] << endl;
            cout << "Жанр: " << genre_name[games[i].genre] << endl;
            cout << "Год выпуска: " << games[i].info.release << endl;
            cout << "Рейтинг: " << games[i].info.rating << "/10" << endl;
            cout << " " << endl;
            break;
        }
    }
    if (!found) {
        cout << "Игра " << srchgame << " не найдена" << endl;
    }
}

//сравнение по платформам
bool sortplat(game g1, game g2) {
    return g1.platform > g2.platform;
}
//сравнение по цене
bool sortprice(game g1, game g2) {
    return g1.price < g2.price;
}
//сортировка
game* sorted(game arr[], int n, bool(*ykaz)(game, game)) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ykaz(arr[j], arr[j + 1])) {
                game tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    return arr;
}

//вывести 3 самых дорогих игры
void top3(game* games, int size) {
    game tmp[20];
    for (int i = 0; i < size; i++) {
        tmp[i] = games[i];
    }
    sorted(tmp, size, sortprice);

    cout << "Три самых дорогих игры: " << endl;
    for (int i = 0; i < 3 && i < size; i++) {
        cout << tmp[i].name << " - " << tmp[i].price << " руб" << endl;
        cout << "Студия: " << tmp[i].studio << endl;
        cout << "Аудитория: " << tmp[i].audience << " млн" << endl;
        cout << "Год выпуска: " << tmp[i].info.release << endl;
        cout << "Рейтинг: " << tmp[i].info.rating << "/10" << endl;
        cout << endl;
    }
    cout << " " << endl;
}

//реализовать функцию изменения игры
void modgame(game& gm, const char* newname, const char* newsudio, float newprice) {
    strcpy_s(gm.name, newname);
    strcpy_s(gm.studio, newsudio);
    gm.price = newprice;
    cout << "Игра изменена" << endl;
}

//в отдельный массив поместить все стратегии для PC
int pcstrat(game* source, int sourceSize, game* destination) {
    int count = 0;
    for (int i = 0; i < sourceSize; i++) {
        if (source[i].genre == strategy && source[i].platform == pc) {
            destination[count] = source[i];
            count++;
        }
    }
    return count;
}

//реализовать вывод отфильтрованных данных в виде оберточной функции
void display(game arr[], int n, const char* title) {
    cout << title << endl;
    if (n == 0) {
        cout << "Нет игр для вывода" << endl;
    }
    else {
        for (int i = 0; i < n; i++) {
            cout << arr[i].name << ", "
                << genre_name[arr[i].genre] << ", "
                << platform_name[arr[i].platform] << ", "
                << "цена: " << arr[i].price << " руб, "
                << "аудитория: " << arr[i].audience << " млн, "
                << "год: " << arr[i].info.release << ", "
                << "рейтинг: " << arr[i].info.rating << "/10" << endl;
        }
    }
    cout << endl;
}

//практика 10, задание 1 (считать из текстового файла данные числового поля для вашей)
void chprices(game* games, int size) {
    ifstream fin;
    fin.open("myfile.txt");

    if (fin.is_open()) {
        int i = 0;
        while (!fin.eof() && i < size) {
            fin >> games[i].price;
            cout << games[i].name << " " << games[i].price << endl;
            i++;
        }
        fin.close();
        cout << "Данные из файла считаны\n" << endl;
    }
    else {
        cout << "Не удалось открыть файл" << endl;
    }
}

//практика 10, задание 2.1 (сделать чтение своей структуры в бинарный файл. Оформить в виде подпрограмм)
void readbingame(game* games, int size, const char* filename) {
    ifstream in(filename, ios::binary | ios::in);

    if (!in.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return;
    }
    in.read((char*)games, sizeof(game) * size);
    in.close();

    cout << "Массив из " << size << " игр считан из " << filename << endl;
}

//практика 10, задание 2.2 (сделать запись своей структуры в бинарный файл. Оформить в виде подпрограмм)
void writebingame(game* games, int size, const char* filename) {
    ofstream out(filename, ios::binary | ios::out);

    if (!out.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return;
    }
    out.write((char*)games, sizeof(game) * size);
    out.close();

    cout << "Массив из " << size << " игр записан в " << filename << endl;
}

void main() {
    setlocale(LC_ALL, "Ru");
    game* games = init();

    //информация об авиасимуляторах с аудиторией больше миллиона
    game flightsim[20];
    int flightcnt = flightsimmln(games, SIZE, flightsim);
    display(flightsim, flightcnt, "Авиасимуляторы с аудиторией от 1 млн: ");

    //новый массив отсортировать по поддерживаемым платформам
    sorted(flightsim, flightcnt, sortplat);
    display(flightsim, flightcnt, "Авиасимуляторы (по платформам): ");

    //вывести все данные по конкретной игре
    gamename(games, SIZE, "Skyrim");

    //вывести 3 самых дорогих игры
    top3(games, SIZE);

    //реализовать функцию изменения игры
    cout << "Изменение игры: " << endl;
    cout << "До изменения:" << endl;
    cout << "Название: " << games[2].name << ", Цена: " << games[2].price << " руб" << endl;
    modgame(games[2], "Skyrim SE", "Bethesda", 1299.99);
    cout << "После изменения:" << endl;
    cout << "Название: " << games[2].name << ", Цена: " << games[2].price << " руб" << endl;

    //в отдельный массив поместить все стратегии для PC
    game pcstrateg[20];
    int strcnt = pcstrat(games, SIZE, pcstrateg);
    display(pcstrateg, strcnt, "Стратегии для PC");

    //практика 10, задание 1
    cout << "Чтение цен из файла:" << endl;
    chprices(games, SIZE);

    //практика 10, задание 2.2 (сделать запись своей структуры в бинарный файл.Оформить в виде подпрограмм)
    cout << "Запись в бинарный файл: " << endl;
    writebingame(games, SIZE, "games.txt");

    //практика 10, задание 2.1 (сделать чтение своей структуры в бинарный файл.Оформить в виде подпрограмм)
    cout << "Чтение из бинарного файла: " << endl;
    game* loadedGames = new game[SIZE];
    readbingame(loadedGames, SIZE, "games.txt");

    delete[] games;
}