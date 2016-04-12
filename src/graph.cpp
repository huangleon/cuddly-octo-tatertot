#include "graph.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace Algorithms {
    ////////////////////////////////////////////////////////////////////////////////
    // implementation of graph
    UndirectedGraph::UndirectedGraph(const std::string& fname)
    {
        importFromFile(fname);
    }
    UndirectedGraph::~UndirectedGraph()
    {
//        std::for_each(mVertex.begin(), mVertex.end()
//                , release_vertex_adj);
//        mVertex.clear();
    }
//    void UndirectedGraph::release_vertex_adj(TVertex::reference elem)
//    {
//        if (elem)
//            delete elem;
//        elem = NULL;
//    }
    void UndirectedGraph::importFromFile(const std::string& fname)
    {
        std::ifstream ifs;
        ifs.open(fname.c_str());
        // vertex count and edge count
        int vcount, ecount;
        ifs >> vcount >> ecount;
        mVertex.assign(vcount, TAdjacentList());
        while ( !ifs.eof() )
        {
            int v, w;
            ifs >> v >> w;
            addEdge(v, w);
        }

        ifs.close();
    }
    void UndirectedGraph::add_edge(int v, int w)
    {
        mVertex[v].insert(w);
    }
    void UndirectedGraph::addEdge(int v, int w)
    {
        // for undirected graph
        add_edge(v, w);
        add_edge(w, v);
    }
    void UndirectedGraph::dump()
    {
        for (TVertex::size_type i = 0; i < mVertex.size(); i++)
        {
            std::cout << "vertex[" << i << "]: ";
            std::for_each(mVertex[i].begin()
                    , mVertex[i].end()
                    , dump_adj);
        }
        std::cout << std::endl;
    }
    void UndirectedGraph::dump_adj(TAdjacentList::const_reference celem)
    {
        std::cout << celem << ", ";
    }

    //////////////////////////////////////////////////
    // implementation of DFS
    DepthFirstSearch::DepthFirstSearch(const Graph& g, int s)
        : Search(g, s)
          , mCount(0)
    {
        mEdgeTo.assign(g.getVertexCount(), 0);
        mMarked.assign(g.getVertexCount(), false);

        dfs(g, s);
        mEdgeTo[s] = s;
    }
    DepthFirstSearch::~DepthFirstSearch()
    {
    }
    void DepthFirstSearch::dump()
    {
        std::cout << "depth first search dump:" << std::endl;
        std::cout << "connected count: " << mCount << std::endl;
        for (TArray::size_type i = 0; i < mEdgeTo.size(); i++)
        {
            std::cout << "edge["
                << i
                << "]: "
                << mEdgeTo[i]
                << std::endl;
        }
    }
    void DepthFirstSearch::dfs(const Graph& g, int v)
    {
        mMarked[v] = true;
        mCount ++;
        TAdjacentList::const_iterator citr;
        const TAdjacentList& adj = g.getAdjs(v);
        for (citr = adj.begin(); citr != adj.end(); ++citr)
        {
            if ( !mMarked[*citr] )
            {
                dfs(g, *citr);
                mEdgeTo[*citr] = v;
            }
        }
    }
    //////////////////////////////////////////////////
    // implementation of BreadthFirstSearch
    BreadthFirstSearch::BreadthFirstSearch(const Graph& g, int s)
        : Search(g, s)
          , mCount(0)
    {
        mEdgeTo.assign(g.getVertexCount(), 0);
        mMarked.assign(g.getVertexCount(), false);

        bfs(g, s);
        mEdgeTo[s] = s;
    }
    BreadthFirstSearch::~BreadthFirstSearch()
    {
    }
    void BreadthFirstSearch::dump()
    {
        std::cout << "breadth first search dump:" << std::endl;
        std::cout << "connected count: " << mCount << std::endl;
        for (TArray::size_type i = 0; i < mEdgeTo.size(); i++)
        {
            std::cout << "edge["
                << i
                << "]: "
                << mEdgeTo[i]
                << std::endl;
        }
    }
    void BreadthFirstSearch::bfs(const Graph& g, int v)
    {
        mQueue.push_back(v);

        while ( !mQueue.empty() )
        {
            int w = mQueue.front();
            mQueue.pop_front();
            mMarked[w] = true;
            mCount ++;

            TAdjacentList::const_iterator citr;
            const TAdjacentList& adj = g.getAdjs(w);
            for (citr = adj.begin(); citr != adj.end(); ++citr)
            {
                if ( !mMarked[*citr] )
                {
                    mQueue.push_back(*citr);
                    mEdgeTo[*citr] = w;
                }
            }
        }
    }
} // end namespace Algorithms

int main(int argc, char* argv[])
{
    int s = 0;
    if ( argc > 1 )
    {
        std::stringstream ss;
        ss << argv[1];
        ss >> s;
    }
    Algorithms::UndirectedGraph g("testgraph.txt");
    Algorithms::DepthFirstSearch dfs(g, s);
    Algorithms::BreadthFirstSearch bfs(g, s);
    dfs.dump();
    bfs.dump();
}
