#include <SDLpp.hpp>
#include <SDL_ttf.h>
#include <tuple>
#include <iostream>
#include <ctime>

class Player
{
	public:
		explicit Player(int x=0, int y=0)
			: rect_ {x, y, 10, 20}, speed_(0, 0)
			{
			}
		void update()
		{
			rect_.x += std::get<0>(speed_);
			rect_.y += std::get<1>(speed_);
			std::get<0>(speed_) *= fric_;
			
		}
		void walk(int direction)
		{
			if (direction > 0)
				std::get<0>(speed_) += std::get<0>(accel_);
			else if (direction < 0)
				std::get<0>(speed_) -= std::get<0>(accel_);
			
			if (std::get<0>(speed_) > maxspeed_)
				std::get<0>(speed_) = maxspeed_;
		}
		void fall()
		{
			std::get<1>(speed_) += std::get<1>(accel_);
		}
		void jump()
		{
		}
		
		const SDL_Rect *rect() { return &rect_; }
		
	private:
		SDL_Rect rect_;
		float fric_ {0.9};
		struct std::tuple<float, float> speed_;
		int maxspeed_ {10};
		struct std::tuple<int, int> accel_ {2, 2};
};

const int FPS_CAP = 60;
const int TPS = 1000 / FPS_CAP; //ticks per frame;
int main(int argc, char *argv[])
{
	sdl::init();
	sdl::window w("Move!");
	sdl::renderer r(w);
	sdl::texture 
		fps_display(r, "FPS: ", sdl::font("Geometric.ttf", 256), {255, 0, 0});
	sdl::texture fps_count(r, "XX", sdl::font("Geometric.ttf", 256), {255, 0, 0});
	sdl::timer fps_timer;
	int counted_frames = 0;
	const SDL_Rect box {0, 0, 40, 20};
	bool quit = false;
	SDL_Event e;
	Player p;
	while (!quit)
	{
		fps_timer.start();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{	
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_DOWN:
					p.fall();
					break;
					case SDLK_LEFT:
					p.walk(-1);
					break;
					case SDLK_RIGHT:
					p.walk(1);
					break;
					case SDLK_SPACE:
					p.jump();
					break;
				}
			}
		}
		p.update();
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(r);
		SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(r, p.rect());
		SDL_RenderCopy(r, , NULL, &box);
		SDL_RenderPresent(r);
	}
	return 0;
}