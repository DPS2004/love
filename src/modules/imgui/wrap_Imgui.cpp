/**
 * Copyright (c) 2006-2026 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#include "common/config.h"

 // LOVE
#include "wrap_Imgui.h"

namespace love
{
namespace imgui
{

#define instance() (Module::getInstance<Imgui>(Module::M_IMGUI))


int w_getCaptureMouse(lua_State *L)
{
	lua_pushboolean(L, instance()->getCaptureMouse());
	return 1;
}
int w_getCaptureKeyboard(lua_State *L)
{
	lua_pushboolean(L, instance()->getCaptureKeyboard());
	return 1;
}

static const luaL_Reg functions[] =
{
	{ "getCaptureMouse", w_getCaptureMouse },
	{ "getCaptureKeyboard", w_getCaptureKeyboard },
	{ 0, 0 }
};

extern "C" int luaopen_love_imgui(lua_State *L)
{
	Imgui *instance = instance();
	if (instance == nullptr)
	{
		luax_catchexcept(L, [&]() { instance = new love::imgui::Imgui(); });
	}
	else
		instance->retain();

	WrappedModule w;
	w.module = instance;
	w.name = "imgui";
	w.type = &Module::type;
	w.functions = functions;
	w.types = 0;

	return luax_register_module(L, w);
}

} // imgui
} // love
