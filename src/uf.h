#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <vector>

namespace Algorithms {
    typedef std::vector<int> TArray;
    typedef unsigned long long TU64;
    //////////////////////////////////////////////////
    class Timer {
        private:
            // counter in micro-seconds
            TU64 mCounter;
        public:
            Timer();

            void reset();

            // elapsed time in micro-seconds
            TU64 elapsed() const;
    };
    //////////////////////////////////////////////////
    // union-find class
    // use array to store component id
    class UF {
        private:
            // for each node, store the union id
            TArray mId;
            int mCount;

            // return the component id of node p
            int find(int p) const;
        public:
            // initialize N sites with integer names (0 to N-1)
            UF(int N);
        public:
            void add_union(int p, int q);
            bool connected(int p, int q) const {
                return find(p) == find(q);
            }
            int count() const { return mCount; }

            void dump();
    };

    //////////////////////////////////////////////////
    // quick union-find class
    // use parent-link array to store component id
    class QuickUF {
        private:
            // for each node, store the union id
            TArray mId;
            int mCount;

            // return the component id of node p
            int find(int p) const;
        public:
            // initialize N sites with integer names (0 to N-1)
            QuickUF(int N);
        public:
            void add_union(int p, int q);
            bool connected(int p, int q) const {
                return find(p) == find(q);
            }
            int count() const { return mCount; }

            void dump();
    };

    //////////////////////////////////////////////////
    // weighted quick union-find class
    // use component size to optimize merge operation of union
    // make the tree height shorter
    class WeightedQUF {
        private:
            // for each node, store the union id
            TArray mId;
            TArray mSize;
            int mCount;

            // return the component id of node p
            int find(int p) const;
        public:
            // initialize N sites with integer names (0 to N-1)
            WeightedQUF(int N);
        public:
            void add_union(int p, int q);
            bool connected(int p, int q) const {
                return find(p) == find(q);
            }
            int count() const { return mCount; }

            void dump();
    };
} // end namespace Algorithms
#endif // end of  __UNION_FIND_H__
