//************************************************************************
// File: emitter.cpp
// Date: Jan 17, 2013
// Author: Jurgen
//************************************************************************

#include "emitter.h"
#include "entitypool.h"
#include "renderer.h"
#include "brush.h"

#include <GL/glew.h>

#include <SDL/SDL.h>

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

extern struct Brush sParticleTexture;

const std::size_t NUM_PARTICLES = 100000;
const static std::size_t NUM_COLORS = 12;
static Vector sColors[NUM_COLORS] = // Rainbow Of Colors
{
    {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
    {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
    {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

struct PoolDeleter
{
    void operator()(void const *p) const
    {
        EntityPool::DestroyPool( (MemoryPool*)p );
    }
};
boost::shared_ptr<MemoryPool> particlePool(EntityPool::CreatePool<Particle>( NUM_PARTICLES ), PoolDeleter() );

template< class T >
struct EntityPoolDeleter
{
    MemoryPool * m_MemoryPool;
    int          m_Num;

    EntityPoolDeleter( MemoryPool* pool, int num = 1 )
        : m_MemoryPool( pool )
        , m_Num(num)
    {
    }

    void operator()(void const *p) const
    {
//        EntityPool::Delete<T>( m_MemoryPool, (T*)p, m_Num );
//        T* e = (T*)p;
//        e->~T();
//        EntityPool::Free( m_MemoryPool, e );
    }
};

Emitter::Emitter(Renderer* renderer) throw()
    : m_Texture( new Texture() )
    , m_Renderer( renderer )
    , m_MemoryPool( EntityPool::CreatePool<Particle>( NUM_PARTICLES ), PoolDeleter() )
    , m_Particles( m_MemoryPool )
{
    // TODO: Register frame call back to renderer
    ASSERT( renderer, "Error! Renderer is invalid!" );

    renderer->RegisterUpdateFunction( boost::bind( &Emitter::OnUpdate, this, _1 ) );

    m_Particles.resize( NUM_PARTICLES );
    {
//        Allocator<Particle> allocator( m_MemoryPool );
//        std::vector< Particle, Allocator<Particle> > pl( allocator );
//        pl.resize( NUM_PARTICLES );

//        m_Particles = &pl[0];

//        m_Particles = EntityPool::Construct<Particle>(m_MemoryPool, NUM_PARTICLES );
//        pl.assign( &m_Particles[0], &m_Particles[NUM_PARTICLES-1] );
//        pl.push_back( Particle(sColors[4*NUM_COLORS/NUM_PARTICLES]) );
    }
//    MemoryPool* pool = particlePool.get();
//    try {
//        Particle* _particle = EntityPool::Construct<Particle>(particlePool.get(), NUM_PARTICLES );
//        boost::shared_ptr< Particle > _p( _particle, EntityPoolDeleter<Particle>(pool, NUM_PARTICLES ) );
//        _particle->~Particle();
//        EntityPool::Free( *particlePool, _particle );
//    }
//    catch ( ... ) {
//        throw ;
//    }

    int i(0);
    for ( auto& particle : m_Particles ) {
        particle.SetFlag(Entity::F_ENABLE);
        particle.SetColor(sColors[i*NUM_COLORS/NUM_PARTICLES]); ++i;
    }
//    m_Particles = EntityPool::Construct<Particle>(m_MemoryPool, NUM_PARTICLES );
//    for ( std::size_t i = 0; i < NUM_PARTICLES; ++i ) {
//        Particle* particle = &m_Particles[i];// ( &_particle[i], EntityPoolDeleter<Particle>(pool) ); // new Particle( sColors[i*NUM_COLORS/NUM_PARTICLES] ) );
//        particle->SetFlag(Entity::F_ENABLE);
//        particle->SetColor(sColors[i*NUM_COLORS/NUM_PARTICLES]);
//        m_Particles.push_back( particle );
//    }
}

Emitter::~Emitter()
{
//    EntityPool::Delete<Particle>( m_MemoryPool, m_Particles, NUM_PARTICLES );
    m_Particles.clear();
//    EntityPool::DestroyPool( m_MemoryPool );
}

bool Emitter::HandleEvent( const SDL_Event& event )
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            break;
        default:
            break;
        }
        break;
    }

    return false;
}

bool Emitter::OnUpdate( float ticks )
{
    ASSERT( m_Renderer, "Invalid Renderer!" );

    return false; // true removes updater
}

bool Emitter::Initialize( Renderer* renderer )
{
    m_Texture->Allocate( sParticleTexture.m_Width, sParticleTexture.m_Height, GL_RGBA );
    m_Texture->Load( sParticleTexture.m_Pixels, sParticleTexture.m_Width, sParticleTexture.m_Height, GL_RGBA );

//    for ( auto particle : m_Particles ) {
    for ( std::size_t i = 0; i < NUM_PARTICLES; ++i ) {
        Particle* particle = &m_Particles[i];
        particle->Initialize( renderer );
    }
    return true;
}

void Emitter::Render( float ticks )
{
    glPushMatrix();

    int gl_blend_src, gl_blend_dst;
    glGetIntegerv(GL_BLEND_SRC, &gl_blend_src);
    glGetIntegerv(GL_BLEND_DST, &gl_blend_dst);

    int blend_enabled;
    glGetIntegerv(GL_BLEND, &blend_enabled);
    if (!blend_enabled) glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_ALPHA_TEST );

    ASSERT( m_Texture, "Missing texture! Bailing out!" );
    m_Texture->Enable();

//    for ( std::size_t i = 0; i < NUM_PARTICLES; ++i ) {
//        Particle* particle = &m_Particles[i];
//        particle->Render( ticks );
//    }
    for ( auto& particle : m_Particles ) {
        particle.Render( ticks );
    }

    if ( !blend_enabled ) {
        glDisable(GL_ALPHA_TEST);
    }
    glBlendFunc( gl_blend_src, gl_blend_dst);
    m_Texture->Disable();

    glPushMatrix();
}

void Emitter::PostRender( )
{

}
