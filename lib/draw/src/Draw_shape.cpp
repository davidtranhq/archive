#include "Draw_shape.hpp"

namespace draw
{

shape::shape(unsigned int w, bool aa) noexcept
	: _weight {w},
	  _anti_aliased {aa}
{
}
	
} // namespace draw

