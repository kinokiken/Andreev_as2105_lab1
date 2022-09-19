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
    int WorkshopsNum;
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
            while ((!pipe.length) || (pipe.length <=0))
            {
                cout << "Задайте корректную длину трубы:" << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin >> pipe.length;
            }

            cout << "Задайте диаметр трубы:" << endl;
            cin >> pipe.diameter;
            while ((!pipe.diameter) || (pipe.diameter <=0))
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

        else if (MenuChoice == 2)
        {
            cout << "Задайте название компрессорной станции:" << endl;
            cin >> cs.name;
            while (cs.name == "")
            {
                cout << "Задайте корректное название компрессорной станции:" << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin >> cs.name;
            }

            cout << "Задайте количество цехов компрессорной станции:" << endl;
            cin >> cs.WorkshopsNum;
            while ((!cs.WorkshopsNum) || (cs.WorkshopsNum <= 0))
            {
                cout << "Задайте корректное количество цехов компрессорной станции:" << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin >> cs.WorkshopsNum;
            }

            cout << "Какое количество цехов находится в работе?" << endl;
            cin >> cs.WorkingNum;
            if (cs.WorkingNum !=0)
            {
                while ((!cs.WorkingNum) || (cs.WorkingNum > cs.WorkshopsNum) || (cs.WorkingNum <0))
                    {
                        if (cs.WorkingNum > cs.WorkshopsNum)
                        {
                            cout << "Количество работающих цехов не может быть больше, чем общее количество цехов" << endl;
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');
                            cin >> cs.WorkingNum;
                        }
                        else
                        {
                            cout << "Введите корректное количество работающих цехов" << endl;
                            cin.clear();
                            cin.ignore(INT_MAX,'\n');
                            cin >> cs.WorkingNum;
                        }
                    }
            }

            cout << "Задайте эффективность компрессорной станции:" << endl;
            cin >> cs.efficiency;
            while ((!cs.efficiency) || (cs.efficiency <= 0))
            {
                cout << "Задайте корректное значение эффективности компрессорной станции:" << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin >> cs.efficiency;
            }

            cout << "\n Вы успешно задали параметры компрессорной станции, возвращаем Вас в меню" << endl << endl;
        }
    }

    return 0;
}