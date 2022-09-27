#include <iostream>
#include <fstream>
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

void Incorrect();

int Menu();

void PipeGet (float &length, float &diameter, bool &repair);

void CsGet (string &name, int &workshops,  int &working, float &efficiency);

bool PipeEdit (bool repair, float diameter);

int CsEdit (int workshops, int working);

void PipeCsParameters (float diameter, bool repair,float length, int workshops, string name, int working, float efficiency);

void SaveParameters (float length, float diameter, bool repair, string name, int workshops,  int working, float efficiency);

void LoadParameters (float &length, float &diameter, bool &repair, string &name, int &workshops,  int &working, float &efficiency);

int main()
{
    setlocale(LC_ALL, "rus"); 

    tubes pipe =  {}; //https://purecodecpp.com/archives/1439
    CStation cs = {};

    while (true)
    {
        switch(Menu())
        {
        case 1:
        
            PipeGet (pipe.length, pipe.diameter, pipe.repair);
            break;

        case  2:

            CsGet (cs.name, cs.WorkshopsNum, cs.WorkingNum, cs.efficiency);
            break;

        case 3:
       
            PipeCsParameters (pipe.diameter, pipe.repair, pipe.length, cs.WorkshopsNum, cs.name, cs.WorkingNum, cs.efficiency);
            break;

        case 4:

            pipe.repair = PipeEdit(pipe.repair, pipe.diameter);
            break;

        case 5:
    
            cs.WorkingNum = CsEdit(cs.WorkshopsNum, cs.WorkingNum);
            break;

        case 6:
        
            SaveParameters (pipe.length, pipe.diameter, pipe.repair, cs.name ,cs.WorkshopsNum, cs.WorkingNum, cs.efficiency);
            break;

        case 7:
        
            LoadParameters (pipe.length, pipe.diameter, pipe.repair, cs.name, cs.WorkshopsNum, cs.WorkingNum, cs.efficiency);
            break;

        case 9:
        
            return 0;
            break;

        default:

            cout << "Выберите опцию из предложенных" << endl;
            break;
        }
    }
}

int Menu()
{
    int MenuChoice;
    cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Редактировать трубу\n 5. Редактировать КС\n 6. Сохранить\n 7. Загрузить\n 9. Выход\n"<<endl;
    cin >> MenuChoice;
    while (!MenuChoice)
    {
        cout << "\n Введите цифру\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> MenuChoice;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    return MenuChoice;
}

void PipeGet (float &length, float &diameter, bool &repair)
{
    cout << "\nЗадайте длину трубы:" << endl;
    cin >> length;
    while ((!length) || (length <=0))
        {
            cout << "Задайте корректную длину трубы:" << endl;
            cin.clear(); //https://overcoder.net/q/37792/%D0%BF%D0%BE%D1%87%D0%B5%D0%BC%D1%83-%D0%BC%D1%8B-%D0%B1%D1%83%D0%B4%D0%B5%D0%BC-%D0%B2%D1%8B%D0%B7%D1%8B%D0%B2%D0%B0%D1%82%D1%8C-cinclear-%D0%B8-cinignore-%D0%BF%D0%BE%D1%81%D0%BB%D0%B5-%D1%87%D1%82%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D0%B2%D0%BE%D0%B4%D0%B0
            cin.ignore(INT_MAX,'\n');
            cin >> length;
        }
    cin.clear();
    cin.ignore(INT_MAX,'\n'); 

    cout << "Задайте диаметр трубы:" << endl;
    cin >> diameter;
    while ((!diameter) || (diameter<0))
        {
            cout << "Задайте корректный диаметр трубы:" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cin >> diameter;
        }
    cin.clear();
    cin.ignore(INT_MAX,'\n');

    cout << "Находится ли эта труба в ремонте? 0-да, 1-нет" << endl;
    while (!(cin>>repair))
    {
        cout << "Введите 0, если труба находится в ремонте; 1, если труба исправна" << endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    cout << "\n Вы успешно задали параметры трубы, возвращаем Вас в меню" << endl << endl;
}

void CsGet (string &name, int &workshops,  int &working, float &efficiency)
{
    string word;
    cout << "\nЗадайте название компрессорной станции:" << endl;
    cin >> word;
    getline(cin, name);
    name = word + name;

    cout << "Задайте количество цехов компрессорной станции:" << endl;
    cin >> workshops;
    while ((!workshops) || (workshops <= 0))
    {
        cout << "Задайте корректное количество цехов компрессорной станции:" << endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        cin >> workshops;
    }
    cin.clear();
    cin.ignore(INT_MAX,'\n');

    cout << "Какое количество цехов находится в работе?" << endl;
    cin >> working;
    while ((!working) || (working > workshops) || (working <0))
    {
        if (working > workshops)
        {
            cout << "Количество работающих цехов не может быть больше, чем общее количество цехов" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cin >> working;
        }
        else
        {
            cout << "Введите корректное количество работающих цехов" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            cin >> working;
        }
    }
    cin.clear();
    cin.ignore(INT_MAX,'\n');

    if (workshops == 0)
    {
        efficiency = 0;
    }
    else
    {
        efficiency = 100*working/workshops;
    }
}

bool PipeEdit(bool repair,float diameter)
{
    if ((!repair) && (!diameter))
    {
        cout << "\n Для редактирования состояния трубы сначала введите параметры трубы \n" << endl;
    }
    else if (repair == true)
    {
        repair = false;
        cout << "\n Труба отправлена в ремонт \n" << endl;
    }
    else
    {
        repair = true;
        cout << "\n Труба поставлена на работу \n" << endl;
    }
    return repair;
}

int CsEdit (int workshops, int working)
{
    int NewOption;
    int AddRemoveWorkshop;
    if (!workshops)
    {
        cout << "\n Для редактирования цехов сначала введите параметры компрессорной станции\n" << endl;
    }
    else
    {
        cout << "\n 1. Запустить цехи \n 2. Остановить цехи\n" << endl;
        cin >> NewOption;
        while (((NewOption !=1) && (NewOption !=2)) || (!NewOption))
        {
            cout << "Введите 1, чтобы запустить цехи или 2, чтобы остановить" << endl;
            cin >> NewOption;
        }
        if (NewOption == 1)
        {
            cout << "\nСколько еще цехов привести в работу?\n" <<endl;
            cin >> AddRemoveWorkshop;
            while ((!AddRemoveWorkshop) || (AddRemoveWorkshop <= 0) || ((AddRemoveWorkshop+working) > workshops))
            {
                if ((!AddRemoveWorkshop) || (AddRemoveWorkshop <= 0))
                {
                    cout << "\nВведите корректное число цехов, которые нужно подключить к работе\n" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cin >> AddRemoveWorkshop;
                }
                else
                {
                    cout << "\nКоличество работающих цехов не может превышать общее количество цехов\n" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cin >> AddRemoveWorkshop;
                }
            }
            working+=AddRemoveWorkshop;
        }
        else
        {
            cout << "\nСколько цехов нужно остановить?" <<endl;
            cin >> AddRemoveWorkshop;
            while ((!AddRemoveWorkshop) || (AddRemoveWorkshop <= 0) || ((working - AddRemoveWorkshop) < 0))
            {
                if ((!AddRemoveWorkshop) || (AddRemoveWorkshop <= 0))
                {
                    cout << "\nВведите корректное число цехов, которые нужно отключить от работы" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cin >> AddRemoveWorkshop;
                }
                else
                {
                    cout << "\nКоличество работающих цехов не может быть меньше нуля" << endl;
                    cin.clear();
                    cin.ignore(INT_MAX,'\n');
                    cin >> AddRemoveWorkshop;
                }
            }    
            working-=AddRemoveWorkshop;
        }
    } 
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    return working;
}

void PipeCsParameters (float diameter, bool repair,float length, int workshops, string name, int working, float efficiency)
{
    if (!diameter)
    {
        cout << "\n Параметры трубы не добавлены\n";
    }
    else
    {
        if (repair == false)
            {
                cout << "\n Параметры трубы:\n" << "\n Длина трубы: " << length << "\n Диаметр трубы: " << diameter;
                cout << "\n Труба находится в ремонте" << endl;
            }
        else
            {
                cout << "\n Параметры трубы:\n" << "\n Длина трубы: " << length << "\n Диаметр трубы: " << diameter;
                cout << "\n Труба находится в работе" << endl;
            }
    }

    if (!workshops)
        {
            cout << "\n Параметры компрессорной станции не добавлены\n" << endl;
        }
    else
        {
            cout << "\n Параметры компрессорной станции:\n" << "\n Название компрессорной станции: " << name;
            cout << "\n Количество цехов компрессорной станции: " << workshops;
            cout << "\n Количество работающих цехов компрессорной станции: " << working;
            if (workshops == 0)
            {
                efficiency = 0;
            }
            else
            {
                efficiency = 100*working/workshops;
            }
            cout << "\n Эффективность компрессорной станции (от 1 до 100): " <<  efficiency << endl << endl;
        }
}

void SaveParameters (float length, float diameter, bool repair, string name,int workshops, int working, float efficiency)
{
    ofstream file;
    file.open("parameters.txt");
    if (!file.is_open())
    {
        cout << "Ошибка! Не удалось открыть файл" << endl;
    }
    else
    {
        file << length << endl << diameter << endl << repair << endl;
        file << name << endl << workshops << endl << working << endl << efficiency;
    }
    file.close();
}

//использование ссылочных параметров https://www.techiedelight.com/ru/return-multiple-values-functions-cpp/

void LoadParameters (float &length, float &diameter, bool &repair, string &name, int &workshops,  int &working, float &efficiency)
{
            ifstream file;
            string variable;
            file.open("parameters.txt");
            if (!file.is_open())
            {
                cout << "Ошибка! Не удалось открыть файл" << endl;
            }
            else
            {
                while(!file.eof())
                {
                    getline(file, variable);
                    length = stof(variable);
                    getline(file, variable);
                    diameter = stof(variable);
                    getline(file, variable);
                    repair = stoi(variable);
                    getline(file, name);
                    getline(file, variable);
                    workshops = stoi(variable);
                    getline(file, variable);
                    working = stof(variable);
                    getline(file, variable);
                    efficiency = stof(variable);
                }
            }
            file.close();           
}