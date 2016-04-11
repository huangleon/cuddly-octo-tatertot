#ifndef __GRAPH_H__
#define __GRAPH_H__

// vertex container
#include <map>
// adjacent vertex list
#include <set>
#include <string>

namespace Algorithms {
    typedef std::set<int> TVertexSet;
    typedef std::map<int, TVertexSet*> TVertex;

    // definition of graph
    class Graph {
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

            // dump graph
            void dump();
    };
    class DepthFirstSearch {
        // build the search tree
    };
    class BreadthFirstSearch {
        // build the search tree
    };

} // end namespace Algorithms
#endif // end of __GRAPH_H__

