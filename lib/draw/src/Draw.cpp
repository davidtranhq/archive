#include "Draw.hpp"

#include <SDLpp.hpp>
#include <stdexcept>

namespace draw
{
	
void init()
{
	try
	{
		sdl::init();
	}
	catch (const std::runtime_error &e)
	{
		throw e;
	}
}

}