#include <bits/stdc++.h>
#include <cstdlib>
#include <time.h>
#include <stdio.h>


#define INF 0x3f3f3f3f
using namespace std;

class Graph{
private:
        int V;
        //lista de aristas, con formato <peso,origen,destino>
        vector<pair<int,pair<int,int> > > edges;
        bool hasNegativeCycle = false;
public:
    Graph(int V);
    void addEdge(int u,int v,int w);
    void bellmanFord(int src);
    //void printDistances();
};
Graph::Graph(int V){
    this->V = V;
}
void Graph::addEdge(int u,int v,int w){
     //edges.push_back(make_pair(w,make_pair(u,v)));
    edges.push_back({w,{u,v}});
}
void Graph::bellmanFord(int src){
    //arreglo de distancias seteado inicialmente como infinito
    vector<int> dist(this->V,INF);
    //la distancia a si mismo debe ser 0
    dist[src] = 0;
    vector<pair<int,pair<int,int> > >::iterator it;

    for(int i=1;i<this->V;i++){
        for(it = edges.begin();it!=edges.end();++it){
            int u = it->second.first;
            int v = it->second.second;
            int w = it->first;
             //Relajacion de las aristas
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
            }
        }
    }
        //¿Quedó alguna arista sin relajardespués de las V*E relajaciones?  
        // Quiere decir que el grafo tiene ciclos internos de peso negativo, el algoritmo Bellman Ford no funcionará correctamente. 
    for(it = edges.begin();it!=edges.end();++it){
        int u = it->second.first;
        int v = it->second.second;
        int w = it->first;
        if(dist[u] + w < dist[v]){
            this->hasNegativeCycle = true;
            //return false
        }
    }
        //Imprime todas las distancias desde el origen hasta todos los vertices. 
    if(!hasNegativeCycle){
        for(int i=0;i<V;i++){
            cout << i << " - " << dist[i] << endl;
        }
    }
}
int main(){

    clock_t t_ini, t_fin;
    double secs;

    t_ini = clock();
    int V = 600;
    //int E; cuantas aristas
    Graph g(V);
 
    int valor = 0;
    for (int x = 0 ; x<600; x++){
        for (int i = 0 ; i<600; i++){   
                //valor = rand()%i;
            g.addEdge(x , i, rand()%50000);
           /*for (int j = 0 ; j<50; j++){
               
           }*/
        }
    }


    g.bellmanFord(2);

    t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
    cout<< secs * 1000.0 <<" milisegundos"<<endl;

    return 0;
}

/* g.addEdge(0,1,7);
    g.addEdge(0,4,6);
    g.addEdge(1,2,9);
    g.addEdge(1,3,-3);
    g.addEdge(2,0,2);
    g.addEdge(2,3,7);
    g.addEdge(3,4,-2);
    g.addEdge(4,1,8);
    g.addEdge(4,2,-4);
    g.addEdge(4,3,5);*/