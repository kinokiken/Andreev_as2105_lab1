#include <iostream>
#include <string>
#include <cmath>

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
        cout << " 1. Добавить трубу \n 2. Добавить КС \n 3. Просмотр всех объектов \n 4. Редактировать трубу \n 5. Редактировать КС \n 6. Сохранить \n 7. Загрузить \n 0. Выход \n"<<endl;
        cin >> MenuChoice;  

        if (MenuChoice == 1)
        {
            cout << "\nЗадайте длину трубы:" << endl;
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
            cout << "\nЗадайте название компрессорной станции:" << endl;
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

            cout << "Задайте коэффициент эффективности цеха компрессорной станции:" << endl;
            cin >> cs.efficiency;
            while ((!cs.efficiency) || (cs.efficiency <= 0))
            {
                cout << "Задайте корректное значение эффективности цеха компрессорной станции:" << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                cin >> cs.efficiency;
            }
            cs.efficiency*=(pow(1.5,cs.WorkingNum));

            cout << "\n Вы успешно задали параметры компрессорной станции, возвращаем Вас в меню" << endl << endl;
        }


        else if (MenuChoice == 3)
        {
            if (!pipe.diameter)
            {
                cout << "\n Параметры трубы не добавлены\n";
            }
            else
            {
                if (pipe.repair == false)
                {
                    cout << "\n Параметры трубы:\n" << "\n Длина трубы: " << pipe.length << "\n Диаметр трубы: " << pipe.diameter;
                    cout << "\n Труба находится в ремонте" << endl;
                }
                else
                {
                    cout << "\n Параметры трубы:\n" << "\n Длина трубы: " << pipe.length << "\n Диаметр трубы: " << pipe.diameter;
                    cout << "\n Труба находится в работе" << endl;
                }
            }

            if (!cs.WorkshopsNum)
            {
                cout << "\n Параметры компрессорной станции не добавлены\n" << endl;
            }
            else
            {
                cout << "\n Параметры компрессорной станции:\n" << "\n Название компрессорной станции: " << cs.name;
                cout << "\n Количество цехов компрессорной станции: " << cs.WorkshopsNum;
                cout << "\n Количество работающих цехов компрессорной станции: " << cs.WorkingNum;
                cout << "\n Эффективность компрессорной станции: " <<  cs.efficiency << endl << endl;
            }
        }

        else if (MenuChoice == 4)
        {
            if ((!pipe.repair) && (!pipe.diameter))
            {
                cout << "\n Для редактирования состояния трубы сначала введите параметры трубы \n" << endl;
            }
            else if (pipe.repair == true)
            {
                pipe.repair = false;
                cout << "\n Труба отправлена в ремонт \n" << endl;
            }
            else
            {
                pipe.repair = true;
                cout << "\n Труба поставлена на работу \n" << endl;
            }
        }

        else if (MenuChoice == 5)
        {
            if (!cs.WorkshopsNum)
            {
                cout << "\n Для редактирования цехов сначала введите параметры компрессорной станции\n" << endl;
            }
            
        }
    }

    return 0;
}