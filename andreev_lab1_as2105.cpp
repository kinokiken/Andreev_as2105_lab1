#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
int PipeIndx = 0;
int CsIndx = 0;

using namespace std;

class Pipes
{
public:
    int PipeIndx = 0;
    string pname = "";
    float length = 0;
    float diameter = 0;
    bool repair = 0;
};

class CStation 
{
public:
    int CsIndx = 0;
    string name = "";
    int WorkshopsNum = 0;
    int WorkingNum = 0;
    float efficiency = 0;
};

int Menu();

bool choice();

int PipeIdCheck(unordered_map <int, Pipes>& pm);

void PipeGet (Pipes& pipe);

void CsGet (CStation& CS);

void PipeEdit (unordered_map <int, Pipes>& pm);

void CsEdit (unordered_map <int, CStation>& csm);

void PipeCsParameters (unordered_map <int, Pipes>& p_g, unordered_map <int, CStation>& cs_g);

void SaveParameters (unordered_map <int, Pipes>& p_g, unordered_map <int, CStation>& cs_g);

void LoadParameters (Pipes& pipe, CStation& CS);

int main()
{
    setlocale(LC_ALL, "rus"); 

    unordered_map<int, Pipes> pipes_map;
    unordered_map<int, CStation> cs_map;

    while (true)
    {
        switch(Menu())
        {
        case 1:{
            Pipes P;
            PipeGet (P);
            pipes_map.insert({P.PipeIndx, P});
            break;}
        case  2:{
            CStation CS;
            CsGet (CS);
            cs_map.insert({CS.CsIndx, CS});
            break;}
        case 3:{
            PipeCsParameters (pipes_map, cs_map);
            break;}
        case 4:
            PipeEdit(pipes_map);
            break;
        case 5:
            CsEdit(cs_map);
            break;
        // case 6:
        //     SaveParameters (pipes_map, cs_map);
        //     break;
        // case 7:
        
        //     LoadParameters (pipe.length, pipe.diameter, pipe.repair, cs.name, cs.WorkshopsNum, cs.WorkingNum, cs.efficiency);
        //     break;
        
        case 0:{
        
            return 0;
            break;}

        default:

            cout << "Выберите опцию из предложенных" << endl;
            break;
        }
    }
}

int Menu()
{
    int MenuChoice;
    cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Редактировать трубу\n 5. Редактировать КС\n 6. Сохранить\n 7. Загрузить\n 0. Выход\n"<<endl;
    while (((cin >> MenuChoice).fail()) || (cin.peek() != '\n'))
    {
        cout << "\n Введите цифру для начала работы\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return MenuChoice;
}

bool choice()
{
    bool choice;
    while (((cin >> choice).fail()) || (cin.peek() != '\n') || ((choice !=1) && (choice !=0)))
    {
        cout << "Введите 0 или 1" << endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }
    return choice;
}

int PipeIdCheck(unordered_map <int, Pipes>& pm)
{
    int id;
    while (((cin >> id).fail()) || (cin.peek() != '\n') || (id <= 0) || (!pm.contains(id)))
    {
        cout << "Такой трубы нет, введите другой индекс" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return id;
}

int CsIdCheck(unordered_map <int, CStation>& csm)
{
    int id;
    while (((cin >> id).fail()) || (cin.peek() != '\n') || (id <= 0) || (!csm.contains(id)))
    {
        cout << "Такой КС нет, введите другой индекс" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return id;
}

void PipeGet (Pipes& pipe)
{
    pipe.PipeIndx = ++PipeIndx;
    cout << "\nЗадайте название данной трубы:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, pipe.pname);
    cout << "Задайте длину трубы:" << endl;
    while (((cin >> pipe.length).fail()) || (cin.peek() != '\n') || (pipe.length <=0))
        {
            cout << "Задайте корректную длину трубы:" << endl;
            cin.clear(); //https://overcoder.net/q/37792/%D0%BF%D0%BE%D1%87%D0%B5%D0%BC%D1%83-%D0%BC%D1%8B-%D0%B1%D1%83%D0%B4%D0%B5%D0%BC-%D0%B2%D1%8B%D0%B7%D1%8B%D0%B2%D0%B0%D1%82%D1%8C-cinclear-%D0%B8-cinignore-%D0%BF%D0%BE%D1%81%D0%BB%D0%B5-%D1%87%D1%82%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D0%B2%D0%BE%D0%B4%D0%B0
            cin.ignore(INT_MAX,'\n');
        }

    cout << "Задайте диаметр трубы:" << endl;
    while (((cin >> pipe.diameter).fail()) || (cin.peek() != '\n') || (pipe.diameter<=0))
        {
            cout << "Задайте корректный диаметр трубы:" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }

    cout << "Находится ли эта труба в ремонте? 0-да, 1-нет" << endl;
    pipe.repair = choice();
    cout << "\n Вы успешно задали параметры трубы, возвращаем Вас в меню" << endl << endl;
}

void CsGet (CStation& cs)
{
    cs.CsIndx = ++CsIndx;
    cout << "\nЗадайте название компрессорной станции:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);

    cout << "Задайте количество цехов компрессорной станции:" << endl;
    while (((cin >> cs.WorkshopsNum).fail()) || (cin.peek() != '\n') || (cs.WorkshopsNum <= 0))
    {
        cout << "Задайте корректное количество цехов компрессорной станции:" << endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }

    cout << "Какое количество цехов находится в работе?" << endl;
    while (((cin >> cs.WorkingNum).fail()) || (cin.peek() != '\n') || (cs.WorkingNum > cs.WorkshopsNum) || (cs.WorkingNum <0))
    {
        if (cs.WorkingNum > cs.WorkshopsNum)
        {
            cout << "Количество работающих цехов не может быть больше, чем общее количество цехов" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
        else
        {
            cout << "Введите корректное количество работающих цехов" << endl;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
    }

    cout << "Какова эффективность данной КС по стобалльной шкале?" << endl;
    while (((cin >> cs.efficiency).fail()) || (cin.peek() != '\n') || (cs.efficiency > 100) || (cs.efficiency <= 0))
    {
        cout << "Задайте корректную эффективность КС:" << endl;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }
}

void PipeEdit(unordered_map <int, Pipes>& pm)
{
    int id;
    if (pm.size()==0) 
    {
        cout << "\n Для редактирования труб сначала введите параметры хотя бы одной трубы \n" << endl;
    }
    else
    {
        cout << "\nКакую операцию вы хотите совершить? \n0) Удаление трубы \n1) Редактирование состояния трубы\n" << endl;
        if (choice()==0)
        {
            cout << "\nКакую трубу удалить?" << endl;
            id = PipeIdCheck(pm);
            auto pipe = pm.find(id);
            pm.erase(pipe);
        }
        else
        {
            cout << "\nКакую трубу отправить в ремонт или вернуть на работу?" << endl;
            id = PipeIdCheck(pm);
            auto pipe = pm.find(id);
            if (pm.at(id).repair == true)
            {
                pm.at(id).repair = false;
                cout << "\n Труба отправлена в ремонт \n" << endl;
            }
            else
            {
                pm.at(id).repair = true;
                cout << "\n Труба поставлена на работу \n" << endl;
            }
        }
    }
}

void CsEdit (unordered_map <int, CStation>& csm)
{
    int AddRemoveWorkshop;
    int id;
    if (csm.size()==0)
    {
        cout << "\n Для редактирования цехов сначала введите параметры компрессорной станции\n" << endl;
    }
    else
    {
        cout << "\nКакую операцию вы хотите совершить? \n0) Удаление КС \n1) Редактирование КС\n" << endl;
        if (choice() == 0)
        {
            cout << "\nКакую КС удалить?" << endl;
            id = CsIdCheck(csm);
            auto cs = csm.find(id);
            csm.erase(cs);
        }
        else
        {
            cout << "\nКакую КС отредактировать?" << endl;
            id = CsIdCheck(csm);
            auto cs = csm.find(id);
            cout << "\n 0. Запустить цехи \n 1. Остановить цехи\n" << endl;
            if (choice() == 0)
            {
                cout << "\nСколько еще цехов привести в работу?\n" <<endl;
                while (((cin >> AddRemoveWorkshop).fail()) || (cin.peek() != '\n') || (AddRemoveWorkshop <= 0) || (AddRemoveWorkshop+csm.at(id).WorkingNum > csm.at(id).WorkshopsNum))
                {
                    if ((AddRemoveWorkshop+csm.at(id).WorkingNum) > csm.at(id).WorkshopsNum)
                    {
                        cout << "\nКоличество работающих цехов не может превышать общее количество цехов, введите корректное значение\n" << endl;
                        cin.clear(); 
                        cin.ignore(INT_MAX,'\n');
                    }
                    else
                    {
                        cout << "\nВведите корректное число цехов, которые нужно подключить к работе\n" << endl;
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                    }
                }
                csm.at(id).WorkingNum+=AddRemoveWorkshop;
            }
            else
            {
                cout << "\nСколько цехов нужно остановить?" <<endl;
                while (((cin >> AddRemoveWorkshop).fail()) || (cin.peek() != '\n') || (AddRemoveWorkshop <= 0) || ((csm.at(id).WorkingNum - AddRemoveWorkshop) < 0))
                {
                    if ((csm.at(id).WorkingNum - AddRemoveWorkshop) < 0)
                    {
                        cout << "\nКоличество работающих цехов не может быть меньше нуля, введите корректное значение" << endl;
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                    }
                    else
                    {
                        cout << "\nВведите корректное количество цехов, которые нужно остановить" << endl;
                        cin.clear();
                        cin.ignore(INT_MAX,'\n');
                    }
                }    
                csm.at(id).WorkingNum-=AddRemoveWorkshop;
            }
        } 
    }
}

void PipeCsParameters (unordered_map <int, Pipes>& p_g, unordered_map <int, CStation>& cs_g)
{
    if (p_g.size() !=0) 
    {
        cout << "\n Параметры труб:" << endl;
        for (auto pipe: p_g) 
        {
            if (pipe.second.repair == false)
            {
                    cout << endl << pipe.first << ") Параметры трубы с названием " << pipe.second.pname << ":" << "\n   Длина трубы: " << pipe.second.length 
                    << "\n   Диаметр трубы: " << pipe.second.diameter;
                    cout << "\n   Труба находится в ремонте" << endl;
            }
            else
            {
                    cout << endl<< pipe.first << ") Параметры трубы с названием " << pipe.second.pname << ":" << "\n   Длина трубы: " << pipe.second.length
                    << "\n   Диаметр трубы: " << pipe.second.diameter;
                    cout << "\n   Труба находится в работе" << endl;
            }
        }
    }
    else
    {
        cout << "\n Не добавлено ни одной трубы" << endl;
    }

    if (cs_g.size() !=0)
    {
        cout << "\n Параметры компрессорных станций:" << endl;
        for (auto cs: cs_g)
            {
                cout << endl << cs.first << ") Название компрессорной станции: " << cs.second.name;
                cout << "\n   Количество цехов компрессорной станции: " << cs.second.WorkshopsNum;
                cout << "\n   Количество работающих цехов компрессорной станции: " << cs.second.WorkingNum;
                cout << "\n   Эффективность компрессорной станции (от 1 до 100): " <<  cs.second.efficiency << endl << endl;
            }
    }
    else
    {
        cout << "\n Не добавлено ни одной КС" << endl;
    }
}

void SaveParameters (unordered_map <int, Pipes>& p_g, unordered_map <int, CStation>& cs_g)
{
    ofstream file;
    file.open("parameters.txt");
    if (!file.is_open())
    {
        cout << "Ошибка! Не удалось открыть файл" << endl;
    }
    else
    {
        if (CS.WorkshopsNum == 0)
        {
            CS.efficiency = 0;
        }   
        else
        {
            CS.efficiency = 100*CS.WorkingNum/CS.WorkshopsNum;
        }
        file << pipe.length << endl << pipe.diameter << endl << pipe.repair << endl;
        file << CS.name << endl << CS.WorkshopsNum << endl << CS.WorkingNum << endl << CS.efficiency;
    }
    file.close();
}

//использование ссылочных параметров https://www.techiedelight.com/ru/return-multiple-values-functions-cpp/

void LoadParameters (Pipes& pipe, CStation& CS)
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
                    pipe.length = stof(variable);
                    getline(file, variable);
                    pipe.diameter = stof(variable);
                    getline(file, variable);
                    pipe.repair = stoi(variable);
                    getline(file, CS.name);
                    getline(file, variable);
                    CS.WorkshopsNum = stoi(variable);
                    getline(file, variable);
                    CS.WorkingNum = stof(variable);
                    getline(file, variable);
                    CS.efficiency = stof(variable);
                }
            }
            file.close();           
}