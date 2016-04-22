#include "graph.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

namespace Algorithms {
    //////////////////////////////////////////////////
    // implementation of graph
    UndirectedGraph::UndirectedGraph(const std::string& fname)
    {
        importFromFile(fname);
    }
    UndirectedGraph::~UndirectedGraph()
    {
    }
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
    // implementation of weighted edge
    Edge::Edge(int v, int w, float weight)
        : mV(v),
        mW(w),
        mWeight(weight)
    {
    }
    //////////////////////////////////////////////////
    // implementation of DirectedGraph
    DirectedGraph::DirectedGraph()
    {
    }
    DirectedGraph::DirectedGraph(const std::string& fname)
    {
        importFromFile(fname);
    }
    DirectedGraph::~DirectedGraph()
    {
    }
    void DirectedGraph::importFromFile(const std::string& fname)
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

    void DirectedGraph::add_edge(int v, int w)
    {
        mVertex[v].insert(w);
    }
    void DirectedGraph::addEdge(int v, int w)
    {
        add_edge(v, w);
    }
    void DirectedGraph::dump()
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
    void DirectedGraph::dump_adj(TAdjacentList::const_reference celem)
    {
        std::cout << celem << ", ";
    }
    DirectedGraph DirectedGraph::reverse() const
    {
        DirectedGraph res;
        res.mVertex.assign(mVertex.size(), TAdjacentList());
        for (TVertex::size_type i = 0; i < mVertex.size(); ++i)
        {
            TAdjacentList::const_iterator citr;
            for (citr = mVertex[i].begin(); citr != mVertex[i].end(); ++citr)
            {
                res.addEdge(*citr, i);
            }
        }
        return res;
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
        mMarked[v] = true;
        mCount ++;
        mEdgeTo[v] = v;
        mQueue.push_back(v);

        while ( !mQueue.empty() )
        {
            int w = mQueue.front();
            mQueue.pop_front();

            TAdjacentList::const_iterator citr;
            const TAdjacentList& adj = g.getAdjs(w);
            for (citr = adj.begin(); citr != adj.end(); ++citr)
            {
                if ( !mMarked[*citr] )
                {
                    mMarked[*citr] = true;
                    mCount ++;
                    mEdgeTo[*citr] = w;

                    mQueue.push_back(*citr);
                }
            }
        }
    }
    //////////////////////////////////////////////////
    // implementation of depth first order
    DepthFirstOrder::DepthFirstOrder(const Graph& g)
        : Search(g, 0)
    {
        mMarked.assign(g.getVertexCount(), false);
        for (int i = 0; i < g.getVertexCount(); i++)
            if ( !mMarked[i] )
            {
                mPre.push_back(i);
                dfs(g, i);
                mPost.push_back(i);
                mReversePost.push_back(i);
            }
    }
    DepthFirstOrder::~DepthFirstOrder()
    {
    }
    void DepthFirstOrder::dfs(const Graph& g, int v)
    {
        mMarked[v] = true;
        // mCount ++;
        TAdjacentList::const_iterator citr;
        const TAdjacentList& adj = g.getAdjs(v);
        for (citr = adj.begin(); citr != adj.end(); ++citr)
        {
            if ( !mMarked[*citr] )
            {
                mPre.push_back(*citr);

                dfs(g, *citr);
                // mEdgeTo[*citr] = v;

                mPost.push_back(*citr);
                mReversePost.push_back(*citr);
            }
        }
    }
    TArray DepthFirstOrder::reversePost() const
    {
        TArray result;
        TStack tmp = mReversePost;
        while ( !tmp.empty() )
        {
            result.push_back(tmp.back());
            tmp.pop_back();
        }
        return result;
    }
    void DepthFirstOrder::dump_vertex(TArray::const_reference elem)
    {
        std::cout << elem << ", ";
    }
    void DepthFirstOrder::dump_pre()
    {
        std::cout << "pre order: " << std::endl;
        TArray dumped = pre();
        std::for_each(dumped.begin(), dumped.end(), dump_vertex);
        std::cout << std::endl;
    }
    void DepthFirstOrder::dump_post()
    {
        std::cout << "post order: " << std::endl;
        TArray dumped = post();
        std::for_each(dumped.begin(), dumped.end(), dump_vertex);
        std::cout << std::endl;
    }
    void DepthFirstOrder::dump_reversePost()
    {
        std::cout << "reversePost order: " << std::endl;
        TArray dumped = reversePost();
        std::for_each(dumped.begin(), dumped.end(), dump_vertex);
        std::cout << std::endl;
    }
    //////////////////////////////////////////////////
    // implementation of CC
    CC::CC(const UndirectedGraph& g)
        : mCount(0)
    {
        mMarked.assign(g.getVertexCount(), false);
        mId.assign(g.getVertexCount(), 0);

        for (int v = 0; v < g.getVertexCount(); v++) {
            if ( !mMarked[v] ) {
                dfs(g, v);
                // bfs(g, v);
                mCount ++;
            }
        }
    }
    void CC::dfs(const UndirectedGraph& g, int v)
    {
        mId[v] = mCount;
        mMarked[v] = true;
        const TAdjacentList& adjs = g.getAdjs(v);
        TAdjacentList::const_iterator citr;
        for (citr = adjs.begin(); citr != adjs.end(); ++citr) {
            if ( !mMarked[v] ) {
                dfs(g, v);
            }
        }
    }
    void CC::bfs(const UndirectedGraph& g, int v)
    {
        mId[v] = mCount;
        mMarked[v] = true;
        TQueue vq;
        vq.push_back(v);

        while ( !vq.empty() ) {
            int v = vq.front();
            vq.pop_front();

            const TAdjacentList& adjs = g.getAdjs(v);
            TAdjacentList::const_iterator citr;
            for (citr = adjs.begin(); citr != adjs.end(); ++citr) {
                if ( !mMarked[*citr] ) {
                    mId[*citr] = mCount;
                    mMarked[*citr] = true;
                    vq.push_back(*citr);
                }
            } // end for
        } // end while
    }
    //////////////////////////////////////////////////
    // implementation of Kosaraju algorithm
    KosarajuSCC::KosarajuSCC(const DirectedGraph& g)
    {
        // get the post reverse order of g's reverse
        // that is topological order of g's reverse
        // then dfs(g) with the order of this order to get 
        // strongly connected component
        DirectedGraph rg = g.reverse();
        DepthFirstOrder order(rg);

        TArray toporder = order.reversePost();
        TArray::const_iterator citr;
        for (citr = toporder.begin(); citr != toporder.end(); ++citr)
        {
            if ( !mMarked[*citr] ) {
                dfs(g, *citr);
                mCount++;
            }
        }
    }
    void KosarajuSCC::dfs(const DirectedGraph& g, int v)
    {
        mId[v] = mCount;
        mMarked[v] = true;
        const TAdjacentList& adjs = g.getAdjs(v);
        TAdjacentList::const_iterator citr;
        for (citr = adjs.begin(); citr != adjs.end(); ++citr) {
            if ( !mMarked[v] ) {
                dfs(g, v);
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
    Algorithms::DirectedGraph dg("ordergraph.txt");
    Algorithms::DepthFirstSearch dfs(g, s);
    Algorithms::BreadthFirstSearch bfs(g, s);
    Algorithms::DepthFirstOrder order(dg);
    dfs.dump();
    bfs.dump();

    order.dump_pre();
    order.dump_post();
    order.dump_reversePost();
}
