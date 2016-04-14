#include "uf.h"

#include <iostream>
#include <fstream>

#include <sys/time.h>

namespace Algorithms {
    //////////////////////////////////////////////////
    Timer::Timer()
        : mCounter(0)
    {
        reset();
    }
    void Timer::reset()
    {
        struct timeval tv = {0};
        gettimeofday(&tv, 0);
        mCounter = tv.tv_sec * 1000000 + tv.tv_usec;
    }
    TU64 Timer::elapsed() const
    {
        TU64 cur = 0;
        struct timeval tv = {0};
        gettimeofday(&tv, 0);
        cur = tv.tv_sec * 1000000 + tv.tv_usec;
        return cur - mCounter;
    }

    //////////////////////////////////////////////////
    UF::UF(int N)
        : mCount(N)
    {
        for (int i = 0; i < N; i++)
            mId.push_back(i);
    }
    void UF::add_union(int p, int q)
    {
        // union 2 nodes into 1 component
        int pID = find(p);
        int qID = find(q);
        if ( pID == qID )
            return;

        TArray::iterator itr;
        for (itr = mId.begin(); itr != mId.end(); ++itr)
            if ( *itr == qID )
                *itr = pID;
        mCount --;
    }
    int UF::find(int p) const
    {
        return mId[p];
    }
    void UF::dump()
    {
        std::cout << "dump of UF:" << std::endl;
        std::cout << "component count: " << mCount << std::endl;
        for (TArray::size_type i = 0; i < mId.size(); ++i)
            std::cout << i << ": " << mId[i] << std::endl;
    }
    //////////////////////////////////////////////////
    QuickUF::QuickUF(int N)
        : mCount(N)
    {
        for (int i = 0; i < N; i++)
            mId.push_back(i);
    }
    int QuickUF::find(int p) const
    {
        while ( mId[p] != p )
            p = mId[p];
        return p;
    }
    void QuickUF::add_union(int p, int q)
    {
        // union 2 nodes into 1 component
        int pID = find(p);
        int qID = find(q);
        if ( pID == qID )
            return;
        mId[qID] = pID;
        mCount --;
    }
    void QuickUF::dump()
    {
        std::cout << "dump of UF:" << std::endl;
        std::cout << "component count: " << mCount << std::endl;
        for (TArray::size_type i = 0; i < mId.size(); ++i)
            std::cout << i << ": " << mId[i] << std::endl;
    }
    //////////////////////////////////////////////////
    WeightedQUF::WeightedQUF(int N)
        : mCount(N)
    {
        mSize.assign(N, 1);
        for (int i = 0; i < N; i++)
            mId.push_back(i);
    }
    int WeightedQUF::find(int p) const
    {
        while ( mId[p] != p )
            p = mId[p];
        return p;
    }
    void WeightedQUF::add_union(int p, int q)
    {
        // union 2 nodes into 1 component
        int pID = find(p);
        int qID = find(q);
        if ( pID == qID )
            return;

        if ( mSize[pID] < mSize[qID] )
        {
            mId[pID] = qID;
            mSize[qID] += mSize[pID];
        }
        else
        {
            mId[qID] = pID;
            mSize[pID] += mSize[qID];
        }
        mCount --;
    }
    void WeightedQUF::dump()
    {
        std::cout << "dump of UF:" << std::endl;
        std::cout << "component count: " << mCount << std::endl;
        for (TArray::size_type i = 0; i < mId.size(); ++i)
            std::cout << i << ": " << mId[i] << std::endl;
    }
} // end namespace Algorithms

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "usage: uf fname.txt" << std::endl;
        return 0;
    }

    std::ifstream ifs;
    ifs.open(argv[1]);
    int count;
    ifs >> count;

    Algorithms::Timer timer;
//    Algorithms::UF uf(count);
    Algorithms::QuickUF uf(count);
//    Algorithms::WeightedQUF uf(count);

    while ( !ifs.eof() )
    {
        timer.reset();
        int p, q;
        ifs >> p >> q;
        if ( uf.connected(p, q) )
            continue;
        uf.add_union(p, q);
        std::cout << "single union time:" << timer.elapsed() / 1000000.f << " secs" << std::endl;
//        std::cout << p << " " << q << std::endl;
    }
//    std::cout << uf.count() << " components." << std::endl;

//    uf.dump();
    std::cout << "elapsed time: " << timer.elapsed() / 1000 << " mili-seconds" << std::endl;
    return 0;
}
