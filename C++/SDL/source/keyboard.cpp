#include <SDL.h>
#include <vector>

enum class KeyPressSurfaces
{
	up, down, left, right, total
};

int main(int argc, char *argv[])
{
	const std::string res_path {"C:\Users\david\Documents\Programming\C++\SDL\res\lesson04\\"}
	sdl::init(SDL_INIT_VIDEO);
	
	sdl::window w {"Key Presses"};
	
	std::vector<sdl::surface> imgs {res_path + "press.bmp",
		res_path + "up.bmp", res_path + "down.bmp", res_path + "left.bmp"
		res_path + "right.bmp"}
		
	
}