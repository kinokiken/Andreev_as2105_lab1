#include "process.h"
#include "pipe.h"
#include "cs.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int Graph::check_exist(int x) {
    while (csm.find(x) == csm.end()) {
        cout << "Нет такой КС, введите другой индекс" << endl;
        x = GetLimValue(0, INT_MAX);
    }
    return x;
}

ifstream& operator >> (ifstream& fcin, Graph::System& tr) 
{
    fcin >> tr.id >> tr.id_ent  >> tr.id_ex >> tr.id_pip;
    return fcin;
}

int Graph::check_p(int x) {
    int j = 0;
    if (graph.size() != 0) {
        for (auto& i : graph) {
            if ((i.second.id_ent == x) or (i.second.id_ex == x))
                j++;
        }
    }
    return j;
}

int Graph::System::max_ids = 0;

int Graph::check_graph(int x) {
    while (check_p(x) >= csm[x].GetPshops()) {
        cout << "Выберите другую КС" << endl;
        x = GetLimValue(0, INT_MAX);

    }
    return x;
}

bool Graph::check_used(int x, int y) 
{
    int k = 0;
    for (auto& i : graph) 
    {
        if ((i.second.id_ent == x and i.second.id_ex == y) or (i.second.id_ent == y and i.second.id_ex == x)) 
        {
            k++;
            cout << "Такая связь существует" << endl;
        }
    }
        if (k == 0)
            return true;
        else
            return false;
}

bool Graph::check_i(int x) {
    int n = 0;
    for (auto& i : graph)
    {
        if (i.second.id_pip == x)
        {
            n++;
        } 
    }
    if (n == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Graph::edge(float x) {
    int k = -1;
    for (auto& i : pm) 
    {
        if (i.second.GetDiam() == x) 
        {
            if (check_i(i.first)) 
            {
                k = i.first;
            }
        }
    }
    return k;
}

void Graph::topologicalSortUtil(int V, unordered_map<int, int>& visited, stack<int>& SortedV) 
{
    visited[V] = 1;
    list<System>::iterator i;
    for (i = Graph_l[V].begin(); i != Graph_l[V].end(); ++i)
    {
        try {
            if (visited[i->id_ex] == 0)
                topologicalSortUtil((*i).id_ex, visited, SortedV);
            else if (visited[i->id_ex] == 1)
                throw string("Найден цикл. Сортировать можно только ациклические графы");
            }
            catch (...) {
                throw;
            }
    }
    visited[V] = 2;
    SortedV.push(V);
    while (SortedV.empty() != false)
        cout << SortedV.top()<<endl;
}

void Graph::topologicalSort()
{
    stack <int> SortedV;
    unordered_map <int, int> visited;
    for (auto& v : Graph_l)
        visited.insert({ v.first, 0 });
    for (auto& v : Graph_l)
    {
        try
        {
            if (!visited[v.first])
                topologicalSortUtil(v.first, visited, SortedV);
        }
        catch (string cycle) 
        {
            cout << cycle <<endl;
            return;
        }
    }
    while (SortedV.empty() == false) 
    {
        cout << SortedV.top() << " ";
        SortedV.pop();
    }
}

void Graph::sort() 
{
    Graph A;
    A.fill_graphl(graph);
    topologicalSort();
}

int Graph::Menu()
{
    int MenuChoice;
    cout << "\n 1. Добавить трубу\n 2. Добавить КС\n 3. Просмотр всех объектов\n 4. Редактировать трубу\n 5. Редактировать КС " << endl;
    cout << " 6. Сохранить\n 7. Загрузить\n 8. Фильтр труб\n 9. Фильтр КС\n 10. Пакетное редактирование труб " << endl; 
    cout << " 11. Пакетное редактирование КС\n 12. Редактировать связи\n 0. Выход\n"<<endl;
    while (((cin >> MenuChoice).fail()) || (cin.peek() != '\n'))
    {
        cout << "\n Введите цифру для начала работы\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return MenuChoice;
}

void Graph::SaveParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm)
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
        file << pm.size() << endl << csm.size() << endl << graph.size() << endl;
        for (auto pipe: pm)
        {
            file << pipe.second;
        }
        for (auto cs: csm)
        {
            file << cs.second;
        }
        for (auto gr: graph)
        {
            file << gr.first << "\n" << gr.second.id_ent << "\n" << gr.second.id_ex << "\n" << gr.second.id_pip << endl;;
        }
    }
    file.close();
}

void Graph::LoadParameters (unordered_map <int, Pipes>& pm, unordered_map <int, CStation>& csm,  unordered_map<int, System>& gr)
{
    int i, a , b, c;
    ifstream file;
    string filename;
    pm.clear();
    csm.clear();
    Pipes p;
    CStation cs;
    Graph::System sys;
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
        file >> c;
        p.SetPid(a);
        cs.SetCsid(b);
        sys.id = c+1;
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
        for (i = 0; i < c; ++i)
        {
            file >> sys;
            gr.insert({ sys.id, sys });
        }
        cout << "\nДанные успешно извлечены!" << endl; 
    }
    file.close();         
}

void Graph::ShowCsParameters (unordered_map <int, CStation>& csm)
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

void Graph::CsEdit (unordered_map <int, CStation>& csm, unordered_map<int, System>& gr)
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
            for (int i = 0; i <= gr.size()+1; ++i)
            {
                auto a = gr.cbegin();
                while (a != gr.cend()) 
                {
                    if (((*a).second.id_ent == id) || ((*a).second.id_ex == id))
                    {
                        gr.erase(a);
                        break;
                    }
                    ++a;
                }
            }
        }
        else
        {
            cout << "\nКакую КС отредактировать?" << endl;
            id = IdCheck(csm);
            EditWorkshops(id, csm);
        } 
    }
}

void Graph::EditWorkshops(int id, unordered_map <int, CStation>& csm)
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

unordered_set <int> Graph::CsFilter (unordered_map <int, CStation>& csm)
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

void Graph::CsBatchEdit (unordered_map <int, CStation>& csm)
{
    int choice;
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

void Graph::PipeEdit(unordered_map <int, Pipes>& pm, unordered_map<int, System>& gr)
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
            auto a = gr.cbegin();
            while (a != gr.cend()) 
            {
                if ((*a).second.id_pip == id) 
                {
                    gr.erase(a);
                    break;
                }
                a++;
            }
        }
        else
        {
            cout << "\nКакую трубу отправить в ремонт или вернуть на работу?" << endl;
            id = IdCheck(pm);
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

void Graph::ShowPipeParameters (unordered_map <int, Pipes>& pm)
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

unordered_set <int> Graph::PipeFilter (unordered_map <int, Pipes>& pm)
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

void Graph::PBatchEdit (unordered_map <int, Pipes>& pm)
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

ostream& operator<<(ostream& out, unordered_set<int> s) {
    cout << "Объекты: ";
    for (auto& i : s)
        cout << i << " ";
    cout << endl;
    return out;
}

istream& operator >>(istream& in, Graph& gts) 
{
    Graph::System sys;
    cout << gts.csm;
    cout << "Выберите номер КС на входе: " << endl;
    sys.id_ent = GetLimValue(0, INT_MAX);
    sys.id_ent = gts.check_exist(sys.id_ent);
    sys.id_ent = gts.check_graph(sys.id_ent);
    cout << gts.csm;
    cout << "Выберите номер КС на выходе" << endl;
    sys.id_ex = GetLimValue(0, INT_MAX);
    while (sys.id_ex == sys.id_ent) 
    {
        cout << "Выберите другой номер КС" << endl;
        sys.id_ex = GetLimValue(0, INT_MAX);
    }
    sys.id_ex = gts.check_exist(sys.id_ex);
    sys.id_ex = gts.check_graph(sys.id_ex);
    if (gts.check_used(sys.id_ent, sys.id_ex)) 
    {
        cout << "Выберите диаметр трубы: 500, 700 или 1400" << endl;
        double dia_pipe = GetLimValue(500.0, 1400.0);
        int k = gts.edge(dia_pipe);
        while (gts.pm.find(k) == gts.pm.end()) {
            cout << "А такой трубы нет, 1.Выбрать другую  2.Создать" << endl;
            int choice = GetLimValue(1, 2);
            if (choice == 2) 
            {
                Pipes p;
                cin >> p;
                gts.pm.insert({ p.GetPid(), p });
            }
            cout << "Введите диаметр: 500, 700 или 1400" << endl;
            dia_pipe = GetLimValue(0.0, 10000000.0);
            k = gts.edge(dia_pipe);
            cout << k<< endl;
        }
        sys.id_pip = k;

        gts.graph.insert({ sys.id, sys });
    }
    else 
    {
        return in;
    }
    return in;
}

void Graph::fill_graphl(unordered_map<int, Graph::System>& sys) 
{
    Graph_l.clear();
    for (auto& e : sys)
    {
        Graph_l[e.second.id_ent].push_back(e.second);
    }
}

void Graph::create_graph() 
{
    Graph c;
    if (graph.size() != 0) 
    {
        cout << "Связи: " << endl;
        for (auto& [i, j] : graph)
            cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;
    }
    cout << "\nЧто сделать: 1. Присоединить 2. Отсоединить 3. Топологическая сортировка\n" << endl;
    int chose = GetLimValue(1, 3);
    if (chose == 1) 
    {
        if ((csm.size() < 2) or (pm.size() < 1))
            cout << "Недостаточно объектов для создания сети\n" << endl;
        else
            cin >> c;
    }
    else if (chose == 3)
    {
        fill_graphl(graph);
        sort();
    }
    else
    {
        if (graph.size() != 0) {
            cout << "Введите номер КС на входе: " << endl;
            int ent = GetLimValue(0, CStation::Cplus);
            cout << "Введите номер КС на выходе: " << endl;
            int ext = GetLimValue(0, CStation::Cplus);
            if (ent == ext) 
            {
                cout << "Выберите другую КС!: ";
                ext = GetLimValue(0, CStation::Cplus);
            }
            auto a = graph.cbegin();
            while (a != graph.cend()) {
                if (((*a).second.id_ent == ent) and ((*a).second.id_ex == ext)) {
                    graph.erase(a);
                    break;
                }
                a++;
            }
        }
    }
    cout << endl;
    for (auto& [i, j] : graph)
        cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;
}