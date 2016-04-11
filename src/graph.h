#ifndef __GRAPH_H__
#define __GRAPH_H__

// vertex container
#include <map>
// adjacent vertex list
#include <set>
#include <string>
#include <vector>

namespace Algorithms {
    //////////////////////////////////////////////////
    // definition of graph
    typedef std::set<int> TVertexSet;
    typedef std::map<int, TVertexSet*> TVertex;

    class Graph {
        friend class DepthFirstSearch;
        private:
            // graph contains Edges and Vertexes.
            // adjacent vertex list
            TVertex mVertex;

            // internal utility function for adding edge.
            // it adds directed edge.
            void add_edge(int v, int w);
            static
            void release_vertex_adj(TVertex::reference elem);
            static
            void dump_vertex(TVertex::const_reference celem);
            static
            void dump_adj(TVertexSet::const_reference celem);
        public:
            Graph();
            virtual ~Graph();

        public:
            void importFromFile(const std::string& filename);
            // add edge for undirected graph
            void addEdge(int v, int w);
            // add edge for directed graph, edge v->w
            void addDirectedEdge(int v, int w);

            TVertex::size_type getVertexCount() const { return mVertex.size(); }
            void getVertexes(std::map<int, int>& vertex);

            // dump graph
            void dump();
    };

    //////////////////////////////////////////////////
    // definition of DFS
    class DepthFirstSearch {
        typedef std::vector<int> TArray;
        typedef std::map<int, int> TSymbolTable;
        // build the search tree
        private:
            Graph mGraph;
            // symbol table, vertex to index mapping
            TSymbolTable mST;
            // store the parent node for each tree node
            TArray mEdgeTo;
            TArray mMarked;
        public:
            DepthFirstSearch(const std::string& filename);
            virtual ~DepthFirstSearch();

        public:
            // dump the search tree
            void dump();

            // dfs the whole graph
            void dfs();
            // dfs from the single source vertex
            void dfs(int vertex);
    };
    class BreadthFirstSearch {
        // build the search tree
    };

} // end namespace Algorithms
#endif // end of __GRAPH_H__

