#include "graph.h"

#include <iostream>
#include <algorithm>
#include <fstream>

namespace Algorithms {
    Graph::Graph()
    {
    }
    Graph::~Graph()
    {
        std::for_each(mVertex.begin(), mVertex.end()
                , release_vertex_adj);
        mVertex.clear();
    }
    void Graph::release_vertex_adj(TVertex::reference elem)
    {
        if (elem.second)
            delete elem.second;
        elem.second = NULL;
    }
    void Graph::importFromFile(const std::string& filename)
    {
        std::ifstream ifs;
        ifs.open(filename.c_str());

        while ( !ifs.eof() )
        {
            int v, w;
            ifs >> v >> w;
            addEdge(v, w);
        }

        ifs.close();
    }
    void Graph::add_edge(int v, int w)
    {
        TVertex::iterator itr = mVertex.find(v);
        if ( mVertex.end() == itr )
        {
            TVertexSet * p = new TVertexSet;
            p->insert(w);
            mVertex.insert( TVertex::value_type(v, p) );
        }
        else
        {
            itr->second->insert(w);
        }
    }
    void Graph::addEdge(int v, int w)
    {
        // for undirected graph
        add_edge(v, w);
        add_edge(w, v);
    }
    void Graph::dump()
    {
        TVertex::const_iterator citr;
        std::for_each(mVertex.begin(), mVertex.end()
                , dump_vertex);
    }
    void Graph::dump_vertex(TVertex::const_reference celem)
    {
        std::cout << "vertex[" << celem.first << "]: ";
        if (celem.second)
        std::for_each(celem.second->begin(), celem.second->end()
                , dump_adj);
        std::cout << std::endl;
    }
    void Graph::dump_adj(TVertexSet::const_reference celem)
    {
        std::cout << celem << ", ";
    }
} // end namespace Algorithms

int main()
{
    Algorithms::Graph g;
    g.importFromFile("testgraph.txt");
    g.dump();
}
