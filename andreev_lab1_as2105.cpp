#include <iostream>
#include <string>

using namespace std;

struct tubes
{
    float length;
    float diameter;
    bool repair;
};

struct CStation 
{
    string name;
    int workshops;
    int WorkingNum;
    float efficiency;
};

int main()
{
    setlocale(LC_ALL, "rus");

    tubes pipe =  {};
    CStation cs = {};
    int MenuChoice = -1;

    while (MenuChoice)
    {
    cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 0. Выход"<<endl;
    cin >> MenuChoice;

    if (MenuChoice == 1)
    {
        cout << "Задайте длину трубы:" << endl;
        cin >> pipe.length;
        while (!pipe.length)
        {
            cout << "Задайте корректную длину трубы:" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cin >> pipe.length;
        }

        cout << "Задайте диаметр трубы:" << endl;
        cin >> pipe.diameter;
        while (!pipe.diameter)
        {
            cout << "Задайте корректный диаметр трубы:" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cin >> pipe.diameter;
        }

        cout << "Находится ли эта труба в ремонте? 0-да, 1-нет" << endl;
        while (!(cin>>pipe.repair))
        {
            cout << "Введите 0, если труба находится в ремонте; 1, если труба исправна" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }

    cout << "\n Вы успешно задали параметры трубы, возвращаем Вас в меню" << endl << endl;

    }
    else
    {
        break;
    }
    }

    return 0;
}