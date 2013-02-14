sdl-particles-custom-allocator

Author:

	Jurgen Schober
	
Date:
   
	January, 2013
	
Short:
  
	Particle engine (see sdl-particles) but modifed to use a custom memory pool and stl::allocator to handle 
	particle memory.

Description:

    This is based on sdl-particles but adds a new memory allocator to use memory pools to handle 
    a large amount of particles in one memory block as an example how to write custom allocators.
        
    All sdl-xx-examples are written in C++11 using MinGW gcc 4.6 and are Windows only. I'm using
    Eclipse Juno as Development IDE.

Libs used:

    boost_thread
    boost_system
    boost_filesystem
    boost_iostreams
    glew
    + OpenGL

License:

    Use as is. No license other then the ones included with third party libraries are required.

Compiler used:

    MinGW with Eclipse Juno (gcc4.6 with -std=c++0x). Windows only. Linux might just work, MacOS will 
    need some work due to the fact OSX needs to run the render loop in the main loop (compiles with 
    LVM compiler). This example runs a render thread decoupled from the main thread.

Have fun
Jurgen
