#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <functional>

namespace utils
{

template<typename KeyType, typename ObjectType>
class Factory {
public:
    void registerAllocator( KeyType key, std::function<ObjectType* ()> allocator ) {
        m_allocators[key]=allocator;
    }

    ObjectType* create( KeyType key )
    {
        ObjectType* result = nullptr;
        if( m_allocators.find(key) != m_allocators.end() ){
            result = m_allocators[key]();
        }

        return result;
    }

private:
    std::map< KeyType, std::function<ObjectType* ()> > m_allocators;
};

}

#endif // FACTORY_H
