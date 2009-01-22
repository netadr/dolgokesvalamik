#ifndef _sceneloader_h_
#define _sceneloader_h_

#include "scripting/lua.h"

	struct node_t;

	static node_t* load_scene(const char* i_scenename);
	static void save_scene(const char* i_scenename,node_t* i_scene);
#endif//_sceneloader_h_
