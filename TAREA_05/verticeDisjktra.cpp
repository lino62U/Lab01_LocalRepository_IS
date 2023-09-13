
#include <list>
#include <stack>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

#include <list>
#include <algorithm>
#include <string>
#include <iostream>

#define INF 99999

using namespace std;

template <class V, class A>
class Edge;

template <class V, class A>
class Vertex
{
public:
    V m_Dato;
    int m_Costo;
    bool m_Visit;
    list<Edge<V, A>> m_list_Edge;

    Vertex(V vertice)
    {
        m_Dato = vertice;
        m_Costo = INF;
        m_Visit = false;
    }

    bool operator==(const Vertex<V, A> &Ve)
    {
        return m_Dato == Ve.m_Dato;
    }
};

template <class V, class A>
class Edge
{
public:
    A m_Dato;
    Vertex<V, A> *m_pVertex;

    Edge(A a, Vertex<V, A> *q = 0)
    {
        m_Dato = a;
        m_pVertex = q;
    }

    bool operator==(const Edge<V, A> &Ar)
    {
        return m_Dato == Ar.m_Dato;
    }
};

template <class V, class A>
class Graph
{
    typedef typename list<Vertex<V, A>>::iterator Iterator_Vertex;
    typedef typename list<Edge<V, A>>::iterator Iterator_Edge;

private:
    list<Vertex<V, A>> m_Graph;

public:
    Graph(){};

    void Insert(V Vertice)
    {
        m_Graph.push_back(Vertex<V, A>(Vertice));
    };
    void Insert_Edge(V v1, V v2, A a)
    {
        Iterator_Vertex p = find_Vertex(v1);
        Iterator_Vertex q = find_Vertex(v2);
        if (p != m_Graph.end() && q != m_Graph.end())
        {
            // ¿Qué ocurre si la arista y existe?
            Vertex<V, A> *pDestino = &(*q);
            p->m_list_Edge.push_back(Edge<V, A>(a, pDestino));
        }
    };

    void Reset_Graph()
    {
        Iterator_Vertex it = m_Graph.begin();
        for (; it != m_Graph.end(); it++)
        {
            it->m_Visit = false;
        }
    }

    Iterator_Vertex find_Vertex(V v)
    {
        return std::find(m_Graph.begin(), m_Graph.end(), Vertex<V, A>(v));
    }

    bool find_edge(V v, A a)
    {
        Iterator_Vertex p = find_Vertex(v);
        Iterator_Edge q = std::find(p->m_list_Edge.begin(), p->m_list_Edge.end(), Edge<V, A>(a));
        if (q != p->m_list_Edge.end())
            return true;
    }
    void Print()
    {
        typedef typename list<Vertex<V, A>>::iterator Iterator_Vertex;
        Iterator_Vertex it = m_Graph.begin();
        for (; it != m_Graph.end(); it++)
        {
            Iterator_Edge it_e = it->m_list_Edge.begin();
            for (; it_e != it->m_list_Edge.end(); ++it_e)
            {
                cout << it->m_Dato << " ---> " << it_e->m_Dato << "---->" << it_e->m_pVertex->m_Dato << endl;
            }
        }
    }


    void heuristicaVecinoMasCercano(V Or, vector<Vertex<V,A> *> &solucion)
    {
        

        Vertex<V,A> * nodoActual = &(*find_Vertex(Or));
        
        solucion.push_back( &(*nodoActual));
        nodoActual->m_Visit = true;
        
        Vertex<V,A> * nodoSiguiente = nodoActual->m_list_Edge.begin()->m_pVertex ;
         int min_d;
        while (solucion.size() < m_Graph.size())
        {
            //&(*it)
            

            min_d = INF;
            // Buscar el nodo no vistado mas cercano al actual
            //min_element(nodoActual->m_list_Edge.begin(), nodoActual->m_list_Edge.end(), [](const Iterator_Edge & a, Iterator_Edge & b) { return (*a)->m_Dato })
            for (Iterator_Edge it = nodoActual->m_list_Edge.begin();  it != nodoActual->m_list_Edge.end(); it++)
            {
                if(!it->m_pVertex->m_Visit &&  it->m_Dato < min_d)
                {
                    nodoSiguiente = it->m_pVertex;
                    min_d=it->m_Dato;
                }
            }

            // Si se encontró un nodo no visitado, agregarlo al recorrido y marcarlo como visitado
            if (nodoSiguiente) {
                
                
                solucion.push_back(nodoSiguiente); 
                nodoSiguiente->m_Visit = true;
                nodoSiguiente->m_Costo = min_d;
                nodoActual = nodoSiguiente;
            }
            
            
        }
        
        for (Iterator_Edge it = nodoSiguiente->m_list_Edge.begin();  it != nodoSiguiente->m_list_Edge.end(); it++)
        {
            if(it->m_pVertex->m_Dato == solucion[0]->m_Dato)
            {
                solucion[0]->m_Costo = it->m_Dato;
                break;
            }
        }
        

    }

    
};
template <class V, class A>
void printSolution(vector<Vertex<V,A> *>& solucion )
{
    A costoTotal = 0;
    cout<<"\nNodo inicial: "<<solucion[0]->m_Dato<<endl;
    for(auto k: solucion)
    {
        cout<<k->m_Dato<<" -> ";
        costoTotal+=  k->m_Costo;
    }
    cout<<solucion[0]->m_Dato<<endl;
    
    bool band = false;
    for(auto k: solucion)
    {
        if(band)
        {
            cout<<"  "<<k->m_Costo<<" ";
            
        }
        band=true;
        
    }
    cout<<"  "<<solucion[0]->m_Costo<<endl;
    
    cout<<"\nCosto Total: "<<costoTotal<<endl<<endl;
}
void test1()
{
    Graph<string, int> G;
    std::vector<Vertex<string,int> *> solucion;
    
    
    G.Insert("1");
    G.Insert("2");
    G.Insert("3");
    G.Insert("4");
    G.Insert("5");

    G.Insert_Edge("5","1", 45);
    G.Insert_Edge("5","2", 40);
    G.Insert_Edge("5","3", 30);
    G.Insert_Edge("5","4", 50);

    G.Insert_Edge("1","2", 10);
    G.Insert_Edge("1","3", 55);
    G.Insert_Edge("1","4", 25);
    G.Insert_Edge("1","5", 45);
    
    G.Insert_Edge("2","1", 10);
    G.Insert_Edge("2","3", 20);
    G.Insert_Edge("2","4", 25);
    G.Insert_Edge("2","5", 40);

    G.Insert_Edge("3","1", 55);
    G.Insert_Edge("3","2", 20);
    G.Insert_Edge("3","4", 15);
    G.Insert_Edge("3","5", 30);
    
    G.Insert_Edge("4","1", 25);
    G.Insert_Edge("4","2", 25);
    G.Insert_Edge("4","3", 15);
    G.Insert_Edge("4","5", 50);
    
    
    // G.Print();
    
    cout<<"El ultimo nodo implica el bucle: es decir apunta al nodo inicial"<<endl;
    
    
    // G.heuristicaVecinoMasCercano("1",solucion);
    // printSolution(solucion);
    
    cout<<"En caso de pesos iguales se esta tomanto el nodo mas cercano segun el orden que se ingreso a la lista de vertices"<<endl;
    G.heuristicaVecinoMasCercano("5",solucion);
    printSolution(solucion);
    
}

int main()
{
    test1();
    return 1;
}