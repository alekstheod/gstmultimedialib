#ifndef LRUCACHE_H
#define LRUCACHE_H
#include <map>
#include <list>

namespace utils
{

/**
 * Implementation of the Least Recently used cache algorithm.
 */
template<typename KeyType, typename ValueType>
class LRUCache
{
private:
    typedef typename std::list< KeyType >::iterator LruIterator;

    /**
     * List of the least recently used keys.
     */
    std::list< KeyType > m_lruList;

    /**
     * A mapping of the keys and the cached data.
     */
    std::map< KeyType, std::pair< ValueType, Iterator> > m_cache;

    /**
     * A maximum size of the cache.
     */
    const unsigned int m_size;

    /**
     * Default destoryer function.
     */
    void destroy( ValueType value ){}
    
public:
    explicit LRUCache(const unsigned int size): m_size( size != 0? size: 1)
    {
    }

        /**
     * Algorithm implementation.
     * @param key key needed for the algorithm.
     * @param creator value creator.
     * @return cached or the new created value.
     */
    template<typename CreatorType>
    ValueType Read( KeyType key,  CreatorType creator)
    {
      return Read(key, creator, std::bind( &LRUCache::destroy, this, std::placeholders::_1) );
    }
    
    /**
     * Algorithm implementation.
     * @param key key needed for the algorithm.
     * @param creator value creator.
     * @param destroyer the deallocator for the object.
     * @return cached or the new created value.
     */
    template<typename CreatorType, typename Destroyer>
    ValueType Read( KeyType key,  CreatorType creator, Destroyer destroyer)
    {
        ValueType result;
        typename std::map< KeyType, std::pair< ValueType, Iterator> >::iterator i = m_cache.find(key);
        if( i == m_cache.end() )
        {
            if( m_lruList.size() >= m_size )
            {
	        i = m_cache.find( m_lruList.back() );
	        destroyer(  i->second.first );
                m_cache.erase( i );
                m_lruList.pop_back();
            }

            ValueType value = creator(key);
            m_lruList.push_front( key );
            m_cache.insert( std::make_pair(key, std::make_pair( value, m_lruList.begin()  ) )  );
            result = value;
        }
        else
        {
            std::pair<ValueType, Iterator> value = i->second;
            if ( value.second != m_lruList.begin() ) {
                m_lruList.splice( m_lruList.begin(), m_lruList, value.second );
            }

            result = value.first;
        }

        return result;
    }

    void clear()
    {
        m_cache.clear();
        m_lruList.clear();
    }

    unsigned int size()
    {
        return m_lruList.size();
    }

    ~LRUCache() {}
};

}

#endif // LRUCACHE_H
