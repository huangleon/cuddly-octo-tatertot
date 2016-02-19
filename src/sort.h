#ifndef __SORT_H__
#define __SORT_H__

namespace Algorithms {
    class Sort {
        public:

    };
    class InsertionSort {
        // sort arrays using insertion sort.
        private:
            const int COUNT;
            int* mNumbers;
        public:
            InsertionSort(int count);
            virtual ~InsertionSort();

            void sort();
            void dump();
        private:
            void exch(int i, int j);
    };
}
#endif // end of __SORT_H__
