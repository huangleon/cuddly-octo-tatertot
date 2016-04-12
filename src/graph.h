#ifndef __GRAPH_H__
#define __GRAPH_H__

// vertex container
#include <map>
// adjacent vertex list
#include <set>
#include <string>
#include <vector>
#include <deque>

namespace Algorithms {
    //////////////////////////////////////////////////
    // definition of graph
    typedef std::set<int> TAdjacentList;
    typedef std::vector<TAdjacentList> TVertex;
    // typedef std::map<int, TAdjacentList*> TVertex;
    // symbol table from vertex id to array index
    typedef std::map<int, int> TSymbolTable;
    typedef std::vector<bool> TMarked;
    typedef std::vector<int> TArray;
    typedef std::deque<int> TQueue;

    class Graph {
        public:
            virtual ~Graph() {};
        public:
            virtual void addEdge(int v, int w) = 0;
            virtual int getVertexCount() const = 0;
            virtual const TAdjacentList& getAdjs(int v) const = 0;
    };
    class UndirectedGraph : public Graph {
        // friend class DepthFirstSearch;
        private:
            // graph contains Edges and Vertexes.
            // adjacent vertex list
            TVertex mVertex;

            // internal utility function for adding edge.
            // it adds directed edge.
            void add_edge(int v, int w);
            // import from file
            void importFromFile(const std::string& fname);

//            static
//                void release_vertex_adj(TVertex::reference elem);
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
} // end namespace Algorithms
#endif // end of __GRAPH_H__

