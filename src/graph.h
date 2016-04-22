#ifndef __GRAPH_H__
#define __GRAPH_H__

// vertex container
#include <map>
// adjacent vertex list
#include <set>
#include <string>
#include <vector>
//#include <deque>
#include <queue>

namespace Algorithms {
    //////////////////////////////////////////////////
    // definition of graph
    typedef std::set<int> TAdjacentList;
    typedef std::vector<TAdjacentList> TVertex;
    // symbol table from vertex id to array index
    typedef std::map<int, int> TSymbolTable;
    typedef std::vector<bool> TMarked;
    typedef std::vector<int> TArray;
    typedef std::queue<int> TQueue;
    typedef std::queue<int> TStack;

    class Graph {
        public:
            virtual ~Graph() {};
        public:
            virtual void addEdge(int v, int w) = 0;
            virtual int getVertexCount() const = 0;
            virtual const TAdjacentList& getAdjs(int v) const = 0;
    };
    //////////////////////////////////////////////////
    // definition of UndirectedGraph
    class UndirectedGraph : public Graph {
        private:
            // graph contains Edges and Vertexes.
            // adjacent vertex list
            TVertex mVertex;

            // internal utility function for adding edge.
            // it adds directed edge.
            void add_edge(int v, int w);
            // import from file
            void importFromFile(const std::string& fname);
            static
                void dump_adj(TAdjacentList::const_reference celem);
        public:
            explicit UndirectedGraph(const std::string& fname);
            virtual ~UndirectedGraph();

        public:
            // add edge for undirected graph
            virtual void addEdge(int v, int w);

            virtual int getVertexCount() const {
                return mVertex.size();
            }
            virtual const TAdjacentList& getAdjs(int v) const {
                return mVertex[v];
            }

            // dump graph
            void dump();
    };
    //////////////////////////////////////////////////
    // Edge
    class Edge {
        friend class EdgeComp;
        private:
            // edge vertex, from v to w
            int mV, mW;
            float mWeight;
        public:
            explicit Edge(int v, int w, float weight);
            int either() { return mV; }
            int from(int v) {
                if ( v == mV )
                    return mW;
                else if ( v == mW )
                    return mV;
                else
                    return -1;
            }
    };
    class EdgeComp {
        public:
            EdgeComp() {}
            bool operator () (const Edge& lhs, const Edge& rhs) const {
                return lhs.mWeight < rhs.mWeight;
            }
    };
    typedef std::priority_queue<Edge,
            std::vector<Edge>,
            EdgeComp> TEdgeHeap;
    typedef std::set<Edge, EdgeComp> TEdgeAdjList;
    typedef std::vector<TEdgeAdjList> TVertics;

    //////////////////////////////////////////////////
    // edge-weighted graph, undirected graph
    class EdgeWeightedGraph {
        private:
            TVertics mVertics;
        public:
            EdgeWeightedGraph();
            explicit EdgeWeightedGraph(const std::string& fname);
            virtual ~EdgeWeightedGraph();

        public:
            void addEdge(int v, int w, float weight);
            int getVertexCount() const;
            const TEdgeAdjList& getAdjs() const;

    };
    //////////////////////////////////////////////////
    // edge-weighted digraph

    class EdgeWeightedDigraph {
    };
    //////////////////////////////////////////////////
    // definition of DirectedGraph
    class DirectedGraph : public Graph {
        private:
            // graph contains Edges and Vertexes.
            // adjacent vertex list
            TVertex mVertex;

            // internal utility function for adding edge.
            // it adds directed edge.
            void add_edge(int v, int w);
            // import from file
            void importFromFile(const std::string& fname);

            static
                void dump_adj(TAdjacentList::const_reference celem);
        public:
            DirectedGraph();
            explicit DirectedGraph(const std::string& fname);
            virtual ~DirectedGraph();

        public:
            // add edge for undirected graph
            virtual void addEdge(int v, int w);

            virtual int getVertexCount() const {
                return mVertex.size();
            }
            virtual const TAdjacentList& getAdjs(int v) const {
                return mVertex[v];
            }

            // return reversed directed graph
            DirectedGraph reverse() const;

            // dump graph
            void dump();
    };
    //////////////////////////////////////////////////
    // definition of Search
    class Search {
        public:
            // search of graph g from single source s
            explicit Search (const Graph& g, int s) {}
            virtual ~Search() {}
        public:
            // is v connected to s
            virtual bool marked(int v) const = 0;
            // how many vertices are connected to s
            virtual int count() const  = 0;
    };

    //////////////////////////////////////////////////
    // definition of DFS
    class DepthFirstSearch : public Search {
        // build the search tree
        private:
            // symbol table, vertex to index mapping
            // store the parent node for each tree node
            TArray mEdgeTo;
            TMarked mMarked;
            int mCount;

            // dfs from the single source vertex
            void dfs(const Graph& g, int v);
        public:
            explicit DepthFirstSearch(const Graph& g, int s);
            virtual ~DepthFirstSearch();
        public:
            // dump the search tree
            void dump();
            virtual bool marked(int v) const {
                return mMarked[v];
            }
            virtual int count() const {
                return mCount;
            }
    };
    //////////////////////////////////////////////////
    // definition of BFS
    class BreadthFirstSearch : public Search {
        // build the search tree
        private:
            // symbol table, vertex to index mapping
            // store the parent node for each tree node
            TArray mEdgeTo;
            TMarked mMarked;
            TQueue mQueue;
            int mCount;

            // dfs from the single source vertex
            void bfs(const Graph& g, int v);
        public:
            explicit BreadthFirstSearch(const Graph& g, int s);
            virtual ~BreadthFirstSearch();
        public:
            // dump the search tree
            void dump();
            virtual bool marked(int v) const {
                return mMarked[v];
            }
            virtual int count() const {
                return mCount;
            }
    };
    //////////////////////////////////////////////////
    // definition of depth first order
    class DepthFirstOrder : public Search {
        private:
            TMarked mMarked;
            TQueue mPre, mPost;
            TStack mReversePost;

            // dfs
            void dfs(const Graph& g, int v);
            static void dump_vertex(TArray::const_reference elem);
        public:
            explicit DepthFirstOrder(const Graph& g);
            virtual ~DepthFirstOrder();
        public:
            virtual bool marked(int v) const {
                return mMarked[v];
            }
            virtual int count() const {
                return mPre.size();
            }
            // return the pre-order, post-order, reversePost-order
            TArray pre() const {
                return TArray(mPre.begin(), mPre.end());
            }
            TArray post() const {
                return TArray(mPost.begin(), mPost.end());
            }
            TArray reversePost() const;

            void dump_pre();
            void dump_post();
            void dump_reversePost();
    };
    //////////////////////////////////////////////////
    // definition of CC
    // connected component for graph
    class CC {
        private:
            TMarked mMarked;
            TArray mId;
            int mCount;
            void dfs(const UndirectedGraph& g, int v);
            void bfs(const UndirectedGraph& g, int v);
        public:
            CC(const UndirectedGraph& g);
            int id(int v) const { return mId[v]; }
            bool connected(int v, int w) const {
                return mId[v] == mId[w];
            }
    };
    //////////////////////////////////////////////////
    // definition of Kosaraju algorithm
    // for finding strong component for digraph
    class KosarajuSCC {
        private:
            TMarked mMarked;
            TArray mId;
            int mCount;

            void dfs(const DirectedGraph& g, int v);
        public:
            KosarajuSCC(const DirectedGraph& g);
        public:
            int id(int v) const { return mId[v]; }
            bool stronglyConnected(int v, int w) {
                return mId[v] == mId[w];
            }
    };
    //////////////////////////////////////////////////
    // MST minimum spanning tree (edge-weighted graph)
    // Prim-lazy/Prim-eager/Kruskal algorithm
    // SP single source shortest path (edge-weighted graph)
} // end namespace Algorithms
#endif // end of __GRAPH_H__

