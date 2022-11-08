#include "Utils.h"

using namespace std;

int Menu()
{
    int MenuChoice;
    cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Редактировать трубу\n 5. Редактировать КС " << endl;
    cout << " 6. Сохранить\n 7. Загрузить\n 8. Фильтр труб\n 9. Фильтр КС\n 10. Пакетное редактирование труб " << endl; 
    cout << " 11. Пакетное редактирование КС\n 0. Выход\n"<<endl;
    while (((cin >> MenuChoice).fail()) || (cin.peek() != '\n'))
    {
        cout << "\n Введите цифру для начала работы\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return MenuChoice;
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
    int i, a , b;
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
        file >> a;
        file >> b;
        p.SetPid(a);
        cs.SetCsid(b);
        for (i = 0; i < a; ++i)
        {
            file >> p;
            pm.insert({p.GetPid(), p});
        }
        for (i = 0; i < b; ++i)
        {
            file >> cs;  
            csm.insert({cs.GetCid(), cs});            
        }
    }
    file.close();
    cout << "\nДанные успешно извлечены!" << endl;          
}

void ShowCsParameters (unordered_map <int, CStation>& csm)
{   
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

void EditWorkshops(int id, unordered_map <int, CStation>& csm)
{
    int AddRemoveWorkshop;
    int a;
    cout << "\nКС: " << id << " | Всего цехов: " << csm.at(id).GetPshops() << " | Цехов в работе: " << csm.at(id).GetWorks() << endl;
    cout << "\n 1. Запустить цехи \n 2. Остановить цехи \n" << endl;
    if (GetLimValue(1,2) == 1)
    {
        cout << "\nСколько еще цехов привести в работу?\n" <<endl;
        while (((cin >> AddRemoveWorkshop).fail()) || (cin.peek() != '\n') || (AddRemoveWorkshop <= 0) || 
        (AddRemoveWorkshop+csm.at(id).GetWorks() > csm.at(id).GetPshops()))
        {
            if ((AddRemoveWorkshop+csm.at(id).GetWorks()) > csm.at(id).GetPshops())
            {
                cout << "\nКоличество работающих цехов не может превышать общее количество цехов, введите корректное значение\n" << endl;
                cin.clear(); 
                cin.ignore(INT_MAX,'\n');
            }
            else
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
            }
        }
        a = csm.at(id).GetWorks() + AddRemoveWorkshop;
        csm.at(id).SetWorks(a);
    }
    else
    {
        cout << "\nСколько цехов нужно остановить?" <<endl;
        while (((cin >> AddRemoveWorkshop).fail()) || (cin.peek() != '\n') || (AddRemoveWorkshop <= 0) || 
        ((csm.at(id).GetWorks() - AddRemoveWorkshop) < 0))
        {
            if ((csm.at(id).GetWorks() - AddRemoveWorkshop) < 0)
            {
                cout << "\nКоличество работающих цехов не может быть меньше нуля, введите корректное значение" << endl;
                cin.clear();
                cin.ignore(INT_MAX,'\n');
            }
            else
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
            }
        }    
        a = csm.at(id).GetWorks() - AddRemoveWorkshop;
        csm.at(id).SetWorks(a);
    }
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
			if (cs.second.GetCname().find(findname) != string::npos) 
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
                if (((cs.second.GetPshops()-cs.second.GetWorks())*100/cs.second.GetPshops()) == percent) 
                {
                    CIndx.insert(cs.first);
                }
            } 
        }
        if (NewChoice == 2)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.GetPshops()-cs.second.GetWorks())*100/cs.second.GetPshops()) > percent) 
                {
                    CIndx.insert(cs.first);
                }
            } 
        }
        if (NewChoice == 3)
        {
            for (auto& cs : csm) 
            {
                if (((cs.second.GetPshops()-cs.second.GetWorks())*100/cs.second.GetPshops()) < percent) 
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

void CsBatchEdit (unordered_map <int, CStation>& csm)
{
    int choice;
    bool rep;
    unordered_set <int> set;
    cout << "\nКакие КС нужно отредактировать/удалить?" << endl;
    cout << "1) Выбрать по фильтру" << endl;
    cout << "2) Выбрать вручную\n" << endl;
    choice = GetLimValue(1,2);
    if (choice == 1)
    {
        set = CsFilter(csm);
        cout << "\n 1) Отредактировать\n 2) Удалить\n" << endl;
        choice = GetLimValue(1,2);
        if (choice == 1)
        {
            for (auto& i: set)
            {
                EditWorkshops(i, csm);
            }
        }
        else 
        {
            for (auto& i: set)
            {
                csm.erase(i);
            }   
        }
    }
    else
    {
        cout << "\nСколько КС в сумме вы хотите отредактировать/удалить\n" << endl;
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
            cout << "\n КС выбраны, переходим к редактированию/удалению\n" << endl;
            cout << "\n 1) Отредактировать\n 2) Удалить\n" << endl;
            choice = GetLimValue(1,2);
            if (choice == 1)
            {
                for (auto& i: set)
                {
                    EditWorkshops(i, csm);
                }
            }   
            else 
            {
                for (auto& i: set)
                {
                    csm.erase(i);
                }   
            }
        }
        else
        {
            cout << "Передумали? Возвращаем в меню" << endl;
        }
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
            if (pm.at(id).GetRepair() == true)
            {
                pm.at(id).SetRepair(false);
                cout << "\n Труба отправлена в ремонт \n" << endl;
            }
            else
            {
                pm.at(id).SetRepair(true);
                cout << "\n Труба поставлена на работу \n" << endl;
            }
        }
    }
}

void ShowPipeParameters (unordered_map <int, Pipes>& pm)
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
			if (pipe.second.GetPname().find(name) != string::npos) 
            {
				PIndx.insert(pipe.first);
			}
		}
    }
    if (choice == 2)
    {
		for (auto& pipe : pm) 
        {
			if (pipe.second.GetRepair() == true) 
            {
				PIndx.insert(pipe.first);
			}
		}        
    }
    if (choice == 3)
    {
		for (auto& pipe : pm) 
        {
			if (pipe.second.GetRepair() == false) 
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

void PBatchEdit (unordered_map <int, Pipes>& pm)
{
    int choice;
    int rep;
    unordered_set <int> set;
    cout << "\nКакие трубы нужно отредактировать?" << endl;
    cout << "1) Выбрать по фильтру" << endl;
    cout << "2) Выбрать вручную\n" << endl;
    choice = GetLimValue(1,2);
    if (choice == 1)
    {
        set = PipeFilter(pm);
        cout << "\n 1) Поставить все на работу\n 0) Отправить все на ремонт\n 2) Удалить\n" << endl;
        rep = (GetLimValue(0,2));
        if (rep == 2)
        {
            for (auto& i: set)
            {
                pm.erase(i);
            }
        }
        else
        {
            for (auto& i: set)
            {
                pm[i].SetRepair(rep);
            }
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
            cout << "\n 1) Поставить все на работу\n 0) Отправить все на ремонт\n 2) Удалить\n" << endl;
            rep = (GetLimValue(0,2));
            if (rep == 2)
            {
                for (auto& i: set)
                {
                    pm.erase(i);
                }
            }
            else
            {
                for (auto& i: set)
                {
                    pm[i].SetRepair(rep);
                }
            }
        }
        else
        {
            cout << "Передумали? Возвращаем в меню" << endl;
        }
    }
}
