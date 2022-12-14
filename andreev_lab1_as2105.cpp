#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Utils.h"
#include "process.h"
#include "cs.h"
#include "pipe.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus"); 

    Graph G;

    while (true)
    {
        switch(G.Menu())
        {
        case 1:{
            cin >> G.P;
            G.pm.insert({G.P.GetPid(), G.P});
            break;}
        case  2:{
            cin >> G.CS;
            G.csm.insert({G.CS.GetCid(), G.CS});
            break;}
        case 3:{
            G.ShowPipeParameters (G.pm);
            G.ShowCsParameters (G.csm);
            break;}
        case 4:
            G.PipeEdit(G.pm, G.graph);
            break;
        case 5:
            G.CsEdit(G.csm, G.graph);
            break;
        case 6:
            G.SaveParameters (G.pm, G.csm);
            break;
        case 7:
            G.LoadParameters (G.pm, G.csm, G.graph);
            G.P.Pplus = G.pm.size();
            G.CS.Cplus = G.csm.size();
            G.S.max_ids = G.graph.size()+1;
            break;
        case 8:
            G.PipeFilter(G.pm);
            break;
        case 9:
            G.CsFilter(G.csm);
            break;
        case 10:
            G.PBatchEdit(G.pm);
            break;
        case 11:
            G.CsBatchEdit(G.csm);
            break;
        case 12: {
            G.create_graph();
            break;
        }
        case 0:
            return 0;
            break;
        default:
            cout << "Выберите опцию из предложенных" << endl;
            break;
        }
    }
}

