#ifndef RES_PATH_H
#define RES_PATH_H

#include <SDL.h>
#include <string>
#include <iostream>

std::string get_res_path(const std::string &sub_dir = "")
{
	// windows uses \ as a path seperator, others use /
	#ifdef _WIN32
		const char path_sep = '\\';
	#else
		const char path_sep = '/';
	#endif
	static std::string res_path;
	if (res_path.empty())
	{
		char *path = SDL_GetBasePath();
		if (path)
			res_path = path;
		else
		{
			std::cerr << "Error getting resource path! SDL_Error: "
				<< SDL_GetError();
			return res_path; // empty string return indicates error
		}
		// find and replace 'bin' with 'res'
		size_t bin = res_path.rfind("bin");
		res_path = res_path.substr(0, bin) + "res" + path_sep;
		return sub_dir.empty() ? res_path : res_path + sub_dir + path_sep;
	}
}

#endif