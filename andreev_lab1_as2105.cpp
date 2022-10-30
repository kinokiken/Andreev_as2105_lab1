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
    int efficiency = 0;
};

int Menu();

bool choice();

istream& operator >> (istream& is, Pipes& pipe);

istream& operator >> (istream& is, CStation& cs);

void PipeEdit (unordered_map <int, Pipes>& pm);

void CsEdit (unordered_map <int, CStation>& csm);

ostream& operator << (ostream& os, unordered_map <int, Pipes>& pm);

ostream& operator << (ostream& os, unordered_map <int, CStation>& csm);

void SaveParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

void LoadParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

void PipeFilter (unordered_map <int, Pipes>& pm);

void CsFilter (unordered_map <int, CStation>& csm);

void PBatchEdit (unordered_map <int, Pipes>& pm);

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
            cin >> P;
            pipes_map.insert({P.PipeIndx, P});
            break;}
        case  2:{
            CStation CS;
            cin >> CS;
            cs_map.insert({CS.CsIndx, CS});
            break;}
        case 3:{
            cout << pipes_map;
            cout << cs_map;
            break;}
        case 4:
            PipeEdit(pipes_map);
            break;
        case 5:
            CsEdit(cs_map);
            break;
        case 6:
            SaveParameters (pipes_map, cs_map);
            break;
        case 7:{
            LoadParameters (pipes_map, cs_map);
            break;}
        case 8:{
            PipeFilter(pipes_map);
            break;}
        case 9:{
            CsFilter(cs_map);
            break;}
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
    cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Редактировать трубу\n 5. Редактировать КС " << endl;
    cout << " 6. Сохранить\n 7. Загрузить\n 8. Фильтр труб\n 9. Фильтр КС\n 0. Выход\n"<<endl;
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

void CinClear()
{
    cout << "Задайте корректное значение:" << endl;
    cin.clear(); //https://overcoder.net/q/37792/%D0%BF%D0%BE%D1%87%D0%B5%D0%BC%D1%83-%D0%BC%D1%8B-%D0%B1%D1%83%D0%B4%D0%B5%D0%BC-%D0%B2%D1%8B%D0%B7%D1%8B%D0%B2%D0%B0%D1%82%D1%8C-cinclear-%D0%B8-cinignore-%D0%BF%D0%BE%D1%81%D0%BB%D0%B5-%D1%87%D1%82%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D0%B2%D0%BE%D0%B4%D0%B0
    cin.ignore(INT_MAX,'\n');    
}

int IdCheck(unordered_map <int, Pipes>& pm)
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

int IdCheck(unordered_map <int, CStation>& csm)
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

float GetValue()
{
    float value;
    while (((cin >> value).fail()) || (cin.peek() != '\n') || (value <=0))
        {
            CinClear();
        } 
    return value;   
}

istream& operator >> (istream& is, Pipes& pipe)
{
    pipe.PipeIndx = ++PipeIndx;
    cout << "\nЗадайте название данной трубы:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, pipe.pname);
    cout << "Задайте длину трубы:" << endl;
    pipe.length = GetValue();
    cout << "Задайте диаметр трубы:" << endl;
    pipe.diameter = GetValue();
    cout << "Находится ли эта труба в ремонте? 0-да, 1-нет" << endl;
    pipe.repair = choice();
    cout << "\n Вы успешно задали параметры трубы, возвращаем Вас в меню" << endl << endl;
    return is;
}

int GetEfficiency()
{
    int efficiency;
    while (((cin >> efficiency).fail()) || (cin.peek() != '\n') || (efficiency > 100) || (efficiency < 0))
    {
        CinClear();
    } 
    return efficiency;   
}

istream& operator >> (istream& is, CStation& cs)
{
    cs.CsIndx = ++CsIndx;
    cout << "\nЗадайте название компрессорной станции:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "Задайте количество цехов компрессорной станции:" << endl;
    while (((cin >> cs.WorkshopsNum).fail()) || (cin.peek() != '\n') || (cs.WorkshopsNum <=0))
        {
            CinClear();
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
            CinClear();;
        }
    }
    cout << "Какова эффективность данной КС по стобалльной шкале?" << endl;
    cs.efficiency = GetEfficiency();
    return is;
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
            id = IdCheck(pm);
            auto pipe = pm.find(id);
            pm.erase(pipe);
        }
        else
        {
            cout << "\nКакую трубу отправить в ремонт или вернуть на работу?" << endl;
            id = IdCheck(pm);
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
            id = IdCheck(csm);
            auto cs = csm.find(id);
            csm.erase(cs);
        }
        else
        {
            cout << "\nКакую КС отредактировать?" << endl;
            id = IdCheck(csm);
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
                        CinClear();
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
                        CinClear();
                    }
                }    
                csm.at(id).WorkingNum-=AddRemoveWorkshop;
            }
        } 
    }
}

ostream& operator << (ostream& os, unordered_map <int, Pipes>& pm)
{
    if (pm.size() !=0) 
    {
        cout << "\n Параметры труб:" << endl;
        for (auto pipe: pm) 
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
        cout << "\n Нет ни одной трубы" << endl;
    }    
    return os;
}

ostream& operator << (ostream& os, unordered_map <int, CStation>& csm)
{
    if (csm.size() !=0)
    {
        cout << "\n Параметры компрессорных станций:" << endl;
        for (auto cs: csm)
            {
                cout << endl << cs.first << ") Название компрессорной станции: " << cs.second.name;
                cout << "\n   Количество цехов компрессорной станции: " << cs.second.WorkshopsNum;
                cout << "\n   Количество работающих цехов компрессорной станции: " << cs.second.WorkingNum;
                cout << "\n   Эффективность компрессорной станции (от 1 до 100): " <<  cs.second.efficiency << endl << endl;
            }
    }
    else
    {
        cout << "\n Нет ни одной КС" << endl;
    }    
    return os;
}

void SaveParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm)
{
    string filename;
    ofstream file;
    cout << "Как вы хотите назвать файл сохранения?" << endl;
    cin >> filename;
    file.open(filename + ".txt");
    if (!file.is_open())
    {
        cout << "Ошибка! Не удалось открыть файл" << endl;
    }
    else
    {
        file << pm.size() << endl << csm.size() << endl;
        for (auto pipe: pm)
        {
        file << pipe.first << endl << pipe.second.pname << endl << pipe.second.length << endl << pipe.second.diameter << endl << pipe.second.repair << endl;
        }
        for (auto cs: csm)
        {
        file << cs.first << endl << cs.second.name << endl << cs.second.WorkshopsNum << endl << cs.second.WorkingNum << endl << cs.second.efficiency << endl;    
        }
    }
    file.close();
}

void LoadParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm)
{
    int i;
    int pipes_amount;
    int cs_amount;
    ifstream file;
    string filename;
    pm.clear();
    csm.clear();
    Pipes p;
    CStation cs;
    cout << "Из какого файла брать данные?" << endl;
    cin >> filename;
    file.open(filename + ".txt");
    if (!file.is_open())
    {
        cout << "Ошибка! Не удалось открыть файл" << endl;
    }
    else
    {
    file >> pipes_amount;
    file >> cs_amount;
    for (i = 0; i < pipes_amount; ++i)
    {
        file >> p.PipeIndx;
        file.ignore();
        getline(file, p.pname);
        file >> p.length >> p.diameter >> p.repair;
        pm.insert({p.PipeIndx, p});
    }
    for (i = 0; i < cs_amount; ++i)
    {
        file >> cs.CsIndx;
        file.ignore();
        getline(file, cs.name);
        file >> cs.WorkshopsNum >> cs.WorkingNum >> cs.efficiency;   
        csm.insert({cs.CsIndx, cs});            
    }
    }
    file.close();
    cout << "\nДанные успешно извлечены!" << endl;          
}

void PipeFilter (unordered_map <int, Pipes>& pm)
{
    int choice;
    unordered_map<int, Pipes> Chosen;
    cout << "\nПо какому признаку отфильтровать трубы?" <<endl;
    cout << "1) По названию" <<endl;
    cout << "2) Вывести рабочие трубы" <<endl;
    cout << "3) Вывести трубы, находящиеся в ремонте\n" <<endl;
    while (((cin >> choice).fail()) || (cin.peek() != '\n') || ((choice !=1) && (choice !=2) && (choice !=3)))
        {
            CinClear();
        }
    if (choice == 1)
    {
        string name;
        cout << "\nПо какому названию отфильтровать трубы?\n" << endl;
        cin >> name;
		for (auto& pipe : pm) 
        {
			if (pipe.second.pname.find(name) != string::npos) 
            {
				Chosen.insert(pipe);
			}
		}
    }
    if (choice == 2)
    {
		for (auto& pipe : pm) 
        {
			if (pipe.second.repair == true) 
            {
				Chosen.insert(pipe);
			}
		}        
    }
    if (choice == 3)
    {
		for (auto& pipe : pm) 
        {
			if (pipe.second.repair == false) 
            {
				Chosen.insert(pipe);
			}
		}       
    }
    cout << Chosen;
}

void CsFilter (unordered_map <int, CStation>& csm)
{
    int choice;
    int percent;
    unordered_map<int, CStation> Chosen;
    cout << "\nПо какому признаку отфильтровать компрессорные станции" <<endl;
    cout << "1) По названию" <<endl;
    cout << "2) По заданному проценту незадействованных цехов\n" <<endl;
    while (((cin >> choice).fail()) || (cin.peek() != '\n') || ((choice !=1) && (choice !=2)))
        {
            CinClear();
        }
    if (choice == 1)
    {
        string findname;
        cout << "\nПо какому названию отфильтровать трубы?\n" << endl;
        cin >> findname;
		for (auto& cs : csm) 
        {
			if (cs.second.name.find(findname) != string::npos) 
            {
				Chosen.insert(cs);
			}
		}
    }
    if (choice == 2)
    {
        int NewChoice;
        cout << "\nКакое условие для фильтра по проценту незадействованных цехов?" << endl;
        cout << "1) Процент незадействованных цехов равен данному проценту" <<endl;
        cout << "2) Процент незадействованных цехов больше заданного процента" <<endl;
        cout << "3) Процент незадействованных цехов меньше заданного процента\n" <<endl;
        while (((cin >> NewChoice).fail()) || (cin.peek() != '\n') || ((NewChoice !=1) && (NewChoice !=2) && (NewChoice != 3)))
        {
            CinClear();
        }
        cout << "\nВведите процент незадействованных цехов для фильра" << endl;
        percent = GetEfficiency();
        if (NewChoice == 1)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.WorkshopsNum-cs.second.WorkingNum)*100/cs.second.WorkshopsNum) == percent) 
                {
                    Chosen.insert(cs);
                }
            } 
        }
        if (NewChoice == 2)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.WorkshopsNum-cs.second.WorkingNum)*100/cs.second.WorkshopsNum) > percent) 
                {
                    Chosen.insert(cs);
                }
            } 
        }
        if (NewChoice == 3)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.WorkshopsNum-cs.second.WorkingNum)*100/cs.second.WorkshopsNum) < percent) 
                {
                    Chosen.insert(cs);
                }
            } 
        }     
    }
    cout << Chosen;
}
