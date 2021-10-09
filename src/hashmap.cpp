#include "hashmap.hpp"
#include "array.hpp"

// -------------------------------------------------------------------------- //
template<typename TKey>
u32 hash(TKey const & key)
{
    u32 value = 16777619;    
    const char* strc = reinterpret_cast<const char*>(&key);

    for(size_t i = 0; i < sizeof(TKey); ++i) {
        value = ((value ^ key[i]) * 2166136261);
    }

    return value;
}

// -------------------------------------------------------------------------- //

template<>
u32 hash<char const *>(char const * const & key) {
    u32 value = 16777619;

    for (u32 i = 0; key[i] != '\0'; ++i) {
        value = ((value ^ key[i]) * 2166136261);
    }

    return value;
}

// -------------------------------------------------------------------------- //

template <>
void THashMap<char const *, u32>::set(char const * const & key, const u32& val)
{
    int pos = hash(key) % mArray.size();
    mArray[pos] = TDataEntry(key, val);
    ++mCurrentSize;  
}

// -------------------------------------------------------------------------- //