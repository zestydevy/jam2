#pragma once

#include <ultra64.h>

#include "heap.hpp"
#include "array.hpp"

// -------------------------------------------------------------------------- //

template<typename TKey>
u32 hash(TKey const & key); // not implemented

template<>
u32 hash<char const *>(char const * const & key);

template <class TKey, class TValue>
class THashMap
{
public:

    THashMap(int size = 16) : mCurrentSize(0) 
    {
        mArray.setHeap(THeap::getCurrentHeap());
        mArray.resize(size);
    }

    ~THashMap() {}

    void set(const TKey& key, const TValue& val);

    TValue get(const TKey& key) const
    {
        int pos = hash(key) % mArray.size();

        if(mArray[pos].k == key)
        {
            return mArray[pos].v;
        }
        else
        {
            return TValue();
        }
    }

    TValue operator[](const TKey * key) {
        return get(key);
    }

private:
    struct TDataEntry
    {
        TKey k;
        TValue v;
        
        TDataEntry(const TKey& key = TKey(), const TValue& val = TValue()) : 
                  k(key), v(val) {}
    };

    TArray<TDataEntry> mArray{};
    int mCurrentSize;
};

// -------------------------------------------------------------------------- //