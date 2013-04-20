#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <Utilities/Memory/SmartPtr/SharedPtr.h>

namespace utils
{

template<typename KeyType, typename ObjectType>
class Factory {
private:

    class Allocator {
    public:
        virtual ObjectType* allocate()=0;
        virtual ~Allocator() {}
    };

    template<typename T>
    class Functor : public Allocator {
    public:
        Functor( T functor ):m_functor( functor ) {}
        ObjectType* allocate()
        {
            return m_functor();
        }

    private:
        T m_functor;
    };

public:
    template<typename AllocatorType>
    void registerAllocator( KeyType key, AllocatorType allocator ) {
        m_allocators[key]=SharedPtr<Allocator>(new Functor<AllocatorType>(allocator) );
    }

    template<ObjectType defValue>
    ObjectType* create( KeyType key )
    {
        ObjectType* result = defValue;
        if( m_allocators.find(key) != m_allocators.end() )
        {
            result = m_allocators[key]->allocate();
        }

        return result;
    }

private:
    std::map< KeyType, SharedPtr< Allocator > > m_allocators;
};

}

#endif // FACTORY_H
