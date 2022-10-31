#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Pipes
{
public:
    int PipeIndx = 0;
    string pname = "";
    float length = 0;
    float diameter = 0;
    bool repair = 0;

    friend istream& operator >> (istream& is, Pipes& pipe);
    friend ostream& operator << (ostream& os, Pipes& pipe);
    friend ofstream& operator << (ofstream& file, Pipes& pipe);
    friend ifstream& operator >> (ifstream& file, Pipes& pipe);
};

class CStation 
{
public:
    int CsIndx = 0;
    string name = "";
    int WorkshopsNum = 0;
    int WorkingNum = 0;
    int efficiency = 0;

    friend istream& operator >> (istream& is, CStation& cs);
    friend ostream& operator << (ostream& os, CStation& cs);
    friend ofstream& operator << (ofstream& file, CStation& cs);
    friend ifstream& operator >> (ifstream& file, CStation& cs);
};

int Pplus = 0;
int Cplus = 0;

int Menu();

string RepairMsg(bool repair);

void ShowParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

void PipeEdit (unordered_map <int, Pipes>& pm);

void CsEdit (unordered_map <int, CStation>& csm);

void SaveParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

void LoadParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm);

unordered_set <int> PipeFilter (unordered_map <int, Pipes>& pm);

unordered_set <int> CsFilter (unordered_map <int, CStation>& csm);

void PBatchEdit (unordered_map <int, Pipes>& pm);

void CsBatchEdit (unordered_map <int, CStation>& csm);

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
            ShowParameters (pipes_map, cs_map);
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
        case 10:{
            PBatchEdit(pipes_map);
            break;}
        case 11:{
            CsBatchEdit(cs_map);
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
    cout << " 6. Сохранить\n 7. Загрузить\n 8. Фильтр труб\n 9. Фильтр КС\n 10. Пакетное редактирование труб\n 11. Пакетное редактирование КС\n 0. Выход\n"<<endl;
    while (((cin >> MenuChoice).fail()) || (cin.peek() != '\n'))
    {
        cout << "\n Введите цифру для начала работы\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return MenuChoice;
}

string RepairMsg(bool repair)
{
    if (repair == 0)
    {
        return ("Труба находится в ремонте");
    }
    else
    {
        return ("Труба находится в работе");
    }
}

void CinClear()
{
    cout << "Задайте корректное значение:" << endl;
    cin.clear(); //https://overcoder.net/q/37792/%D0%BF%D0%BE%D1%87%D0%B5%D0%BC%D1%83-%D0%BC%D1%8B-%D0%B1%D1%83%D0%B4%D0%B5%D0%BC-%D0%B2%D1%8B%D0%B7%D1%8B%D0%B2%D0%B0%D1%82%D1%8C-cinclear-%D0%B8-cinignore-%D0%BF%D0%BE%D1%81%D0%BB%D0%B5-%D1%87%D1%82%D0%B5%D0%BD%D0%B8%D1%8F-%D0%B2%D0%B2%D0%BE%D0%B4%D0%B0
    cin.ignore(INT_MAX,'\n');    
}

template <typename T>
int IdCheck(unordered_map<int, T> umap)
{
    int id;
    while (((cin >> id).fail()) || (cin.peek() != '\n') || (id <= 0) || (!umap.contains(id)))
    {
        cout << "Такого объекта нет, введите другой индекс" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return id;
}

template <typename T>
void GetValue(T& a)
{
    while (((cin >> a).fail()) || (cin.peek() != '\n') || (a <=0))
        {
            CinClear();
        }    
}

template <typename T>
T GetLimValue(T min, T max) 
{
	T value;
	while (((cin >> value).fail()) || (cin.peek() != '\n') || (value < min) || (value > max))
    {
	    CinClear();
	}
    return value;
}

istream& operator >> (istream& is, Pipes& pipe)
{
    pipe.PipeIndx = ++Pplus;
    cout << "\nЗадайте название данной трубы:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, pipe.pname);
    cout << "Задайте длину трубы:" << endl;
    GetValue(pipe.length);
    cout << "Задайте диаметр трубы:" << endl;
    GetValue(pipe.diameter);
    cout << "Находится ли эта труба в ремонте? 0-да, 1-нет" << endl;
    pipe.repair = GetLimValue(0,1);
    cout << "\n Вы успешно задали параметры трубы, возвращаем Вас в меню" << endl << endl;
    return is;
}

ostream& operator << (ostream& os, Pipes& pipe)
{
    os << endl << pipe.PipeIndx << ") Параметры трубы с названием " << pipe.pname << ":" << "\n   Длина трубы: " << pipe.length 
    << "\n   Диаметр трубы: " << pipe.diameter << endl << "   " << RepairMsg(pipe.repair) << endl;
    return os;
}

istream& operator >> (istream& is, CStation& cs)
{
    cs.CsIndx = ++Cplus;
    cout << "\nЗадайте название компрессорной станции:" << endl;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "Задайте количество цехов компрессорной станции:" << endl;
    GetValue(cs.WorkshopsNum);
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
    cs.efficiency = GetLimValue(0,100);
    return is;
}

ostream& operator << (ostream& os, CStation& cs)
{
    os << endl << cs.CsIndx << ") Название компрессорной станции: " << cs.name
    << "\n   Количество цехов компрессорной станции: " << cs.WorkshopsNum
    << "\n   Количество работающих цехов компрессорной станции: " << cs.WorkingNum
    << "\n   Эффективность компрессорной станции (от 1 до 100): " <<  cs.efficiency << endl << endl;
    return os;
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
        cout << "\nКакую операцию вы хотите совершить? \n1) Удаление трубы \n2) Редактирование состояния трубы\n" << endl;
        if (GetLimValue(1,2)==1)
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

void EditWorkshops(int id, unordered_map <int, CStation>& csm)
{
    int AddRemoveWorkshop;
    cout << "\nКС: " << id << " | Всего цехов: " << csm.at(id).WorkshopsNum << " | Цехов в работе: " << csm.at(id).WorkingNum << endl;
    cout << "\n 1. Запустить цехи \n 2. Остановить цехи\n" << endl;
    if (GetLimValue(1,2) == 1)
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

void CsEdit (unordered_map <int, CStation>& csm)
{
    int id;
    if (csm.size()==0)
    {
        cout << "\n Для редактирования цехов сначала введите параметры компрессорной станции\n" << endl;
    }
    else
    {
        cout << "\nКакую операцию вы хотите совершить? \n1) Удаление КС \n2) Редактирование КС\n" << endl;
        if (GetLimValue(1,2) == 1)
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
            EditWorkshops(id, csm);
        } 
    }
}

void ShowParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm)
{
    if (pm.size() !=0) 
    {
        cout << "\n Параметры труб:" << endl;
        for (auto pipe: pm) 
        {
            cout << pipe.second;
        } 
    }
    else
    {
        cout << "\n Нет ни одной трубы" << endl;
    }    
    if (csm.size() !=0)
    {
        cout << "\n Параметры компрессорных станций:" << endl;
        for (auto cs: csm)
            {
                cout << cs.second;
            }
    }
    else
    {
        cout << "\n Нет ни одной КС" << endl;
    } 
}

ofstream& operator << (ofstream& file, Pipes& pipe)
{
    file << pipe.PipeIndx << endl << pipe.pname << endl << pipe.length << endl << pipe.diameter << endl << pipe.repair << endl;
    return file;
}

ofstream& operator << (ofstream& file, CStation& cs)
{
    file << cs.CsIndx << endl << cs.name << endl << cs.WorkshopsNum << endl << cs.WorkingNum << endl << cs.efficiency << endl;    
    return file;
}

ifstream& operator >> (ifstream& file, Pipes& pipe)
{
    file >> pipe.PipeIndx;
    file.ignore();
    getline(file, pipe.pname);
    file >> pipe.length >> pipe.diameter >> pipe.repair;
    return file;
}

ifstream& operator >> (ifstream& file, CStation& cs)
{
    file >> cs.CsIndx;
    file.ignore();
    getline(file, cs.name);
    file >> cs.WorkshopsNum >> cs.WorkingNum >> cs.efficiency;  
    return file; 
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
            file << pipe.second;
        }
        for (auto cs: csm)
        {
            file << cs.second;
        }
    }
    file.close();
}

void LoadParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm)
{
    int i;
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
        file >> Pplus;
        file >> Cplus;
        for (i = 0; i < Pplus; ++i)
        {
            file >> p;
            pm.insert({p.PipeIndx, p});
        }
        for (i = 0; i < Cplus; ++i)
        {
            file >> cs;  
            csm.insert({cs.CsIndx, cs});            
        }
    }
    file.close();
    cout << "\nДанные успешно извлечены!" << endl;          
}

unordered_set <int> PipeFilter (unordered_map <int, Pipes>& pm)
{
    unordered_set <int> PIndx;
    int choice;
    cout << "\nПо какому признаку отфильтровать трубы?" <<endl;
    cout << "1) По названию" <<endl;
    cout << "2) Вывести рабочие трубы" <<endl;
    cout << "3) Вывести трубы, находящиеся в ремонте\n" <<endl;
    choice = GetLimValue(1,3);
    if (choice == 1)
     {
        string name;
        cout << "\nПо какому названию отфильтровать трубы?\n" << endl;
        cin >> name;
		for (auto& pipe : pm) 
        {
			if (pipe.second.pname.find(name) != string::npos) 
            {
				PIndx.insert(pipe.first);
			}
		}
    }
    if (choice == 2)
    {
		for (auto& pipe : pm) 
        {
			if (pipe.second.repair == true) 
            {
				PIndx.insert(pipe.first);
			}
		}        
    }
    if (choice == 3)
    {
		for (auto& pipe : pm) 
        {
			if (pipe.second.repair == false) 
            {
				PIndx.insert(pipe.first);
			}
		}       
    }
    if (PIndx.size() != 0)
    {
        for (auto id: PIndx)
        {
            cout << pm[id];
        }
    }
    else
    {
        cout << "Не найдено ни одной трубы по данному фильтру" << endl;
    }
    return PIndx;
}

unordered_set <int> CsFilter (unordered_map <int, CStation>& csm)
{
    int choice;
    int percent;
    unordered_set <int> CIndx;
    cout << "\nПо какому признаку отфильтровать компрессорные станции" <<endl;
    cout << "1) По названию" <<endl;
    cout << "2) По заданному проценту незадействованных цехов\n" <<endl;
    choice = GetLimValue(1,2);
    if (choice == 1)
    {
        string findname;
        cout << "\nПо какому названию отфильтровать КС?\n" << endl;
        cin >> findname;
		for (auto& cs : csm) 
        {
			if (cs.second.name.find(findname) != string::npos) 
            {
				CIndx.insert(cs.first);
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
        NewChoice = GetLimValue(1,3);
        cout << "\nВведите процент незадействованных цехов для фильра" << endl;
        percent = GetLimValue(0,100);
        if (NewChoice == 1)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.WorkshopsNum-cs.second.WorkingNum)*100/cs.second.WorkshopsNum) == percent) 
                {
                    CIndx.insert(cs.first);
                }
            } 
        }
        if (NewChoice == 2)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.WorkshopsNum-cs.second.WorkingNum)*100/cs.second.WorkshopsNum) > percent) 
                {
                    CIndx.insert(cs.first);
                }
            } 
        }
        if (NewChoice == 3)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.WorkshopsNum-cs.second.WorkingNum)*100/cs.second.WorkshopsNum) < percent) 
                {
                    CIndx.insert(cs.first);
                }
            } 
        }     
    }
    if (CIndx.size() != 0)
    {
        for (auto id: CIndx)
        {
            cout << csm[id];
        }
    }
    else
    {
        cout << "Не найдено ни одной КС по данному фильтру" << endl;
    }   
    return CIndx;
}

void PBatchEdit (unordered_map <int, Pipes>& pm)
{
    int choice;
    bool rep;
    unordered_set <int> set;
    cout << "\nКакие трубы нужно отредактировать?" << endl;
    cout << "1) Выбрать по фильтру" << endl;
    cout << "2) Выбрать вручную\n" << endl;
    choice = GetLimValue(1,2);
    if (choice == 1)
    {
        set = PipeFilter(pm);
        cout << "\n 1) Поставить все на работу\n 0) Отправить все на ремонт" << endl;
        rep = (GetLimValue(0,1));
        for (auto& i: set)
        {
            pm[i].repair = rep;
        }
    }
    else
    {
        cout << "\nСколько труб в сумме вы хотите отредактировать\n" << endl;
        int amount;
        amount = GetLimValue(0, (int)pm.size());
        if (amount != 0)
        {
            cout << "Поочередно вписывайте номера труб" << endl;
            int num;
            for (int i = 0; i < amount; i++)
            {
                num = IdCheck(pm);
                set.insert(num);
            }
            cout << "\n 1) Поставить все на работу\n 0) Отправить все на ремонт" << endl;
            rep = GetLimValue(0, 1);
            for (auto& i : set)
            {
                pm[i].repair = rep;
            }
        }
        else
        {
            cout << "Передумали? Возвращаем в меню" << endl;
        }
    }
}

void CsBatchEdit (unordered_map <int, CStation>& csm)
{
    int choice;
    bool rep;
    unordered_set <int> set;
    cout << "\nКакие КС нужно отредактировать?" << endl;
    cout << "1) Выбрать по фильтру" << endl;
    cout << "2) Выбрать вручную\n" << endl;
    choice = GetLimValue(1,2);
    if (choice == 1)
    {
        set = CsFilter(csm);
        for (auto& i: set)
        {
            EditWorkshops(i, csm);
        }
    }
    else
    {
        cout << "\nСколько КС в сумме вы хотите отредактировать\n" << endl;
        int amount;
        amount = GetLimValue(0, (int)csm.size());
        if (amount != 0)
            {
            cout << "Поочередно вписывайте номера КС" << endl;
            int num;
            for (int i = 0; i < amount; i++)
            {
                num = IdCheck(csm);
                set.insert(num);
            }
            cout << "\n КС выбраны, переходим к редактированию \n" << endl;
            for (auto& i : set)
            {
                EditWorkshops(i, csm);
            }
        }
        else
        {
            cout << "Передумали? Возвращаем в меню" << endl;
        }
    }  
}