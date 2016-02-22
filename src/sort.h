#ifndef __SORT_H__
#define __SORT_H__

namespace Algorithms {
    // Definition of base class.
    class Sort {
        private:
            const int COUNT;
            int* mNumbers;
        public:
            Sort(int count);
            virtual ~Sort();

            int count() const { return COUNT; }
            int compare(int i, int j) const
            {
                if (mNumbers[i] < mNumbers[j])
                    return -1;
                else if (mNumbers[i] == mNumbers[j])
                    return 0;
                else return 1;
            }
            void exch(int i, int j);
            void dump();
    };
    // Definition of InsertionSort
    class InsertionSort {
        // sort arrays using insertion sort.
        private:
            Sort mData;
        public:
            InsertionSort(int count);

            void sort();
            void dump();
    };
    class SelectionSort {
        // sort arrays using selection sort.
        private:
            Sort mData;
        public:
            SelectionSort(int count);

            void sort();
            void dump();
    };
    class ShellSort {
        // sort arrays using selection sort.
        private:
            Sort mData;
        public:
            ShellSort(int count);

            void sort();
            void dump();
    };
}
#endif // end of __SORT_H__
