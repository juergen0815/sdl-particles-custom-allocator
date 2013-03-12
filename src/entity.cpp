/*
 * entity.cpp
 *
 *  Created on: 2013-01-21
 *      Author: jurgens
 */

#include "entity.h"
#include "entitypool.h"

void Entity::CheckDestroy()
{
    delete this;
}

//void* Entity::operator new( std::size_t size ) throw( std::bad_alloc )
//{
//    void *p = malloc( size );
//    ASSERT( p, "Failed to allocate %d bytes of memory", size );
//    return p;
////    void *p = static_cast<void*>(EntityPool::Allocate( size ));
////    return p;
//}
//
//void Entity::operator delete( void *p ) throw ()
//{
//    ASSERT( p, "Tried to free nullptr!" );
//    free(p);
////    EntityPool::Delete( static_cast<Entity*>(p) );
//}
//

