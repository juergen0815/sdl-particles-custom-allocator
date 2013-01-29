
#include "app.h"
#include "err.h"

#include <exception>
#include <iostream>

static void HandleUnexpected()
{
    ShowError( "Application failed with unexpected Exception!", "Unexpected Exception" );
}

extern "C" int SDL_main( int argc, char* argv[] )
{
    std::set_unexpected( HandleUnexpected );
	try {
		App app;
		app.Init( argc, argv );
		return app.Run();
	}
    catch ( std::bad_alloc &ex ) {
        ShowError( ex.what(), "Application failed with Memory Exception!" );
    }
	catch ( std::exception &ex ) {
		ShowError( ex.what(), "Application failed with Exception!" );
	}
	catch ( ... ) {
        ShowError( "Unknown Error!", "Application failed with Memory Error!" );
	}
	return -1;
}
