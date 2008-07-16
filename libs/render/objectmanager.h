#ifndef _objectmanager_h_
#define _objectmanager_h_

#include "renderobject3d.h"
#include "utils/singleton.h"
#include "containers/stringmap.h"

namespace render
{
	struct objectmanagerdesc
	{
		objectmanagerdesc(const char* i_group):m_objectgroup(i_group){}
		ctr::string m_objectgroup;
	};
	struct objectmanager
	{
		DECLARE_SINGLETON_DESC(objectmanager,objectmanagerdesc);
	public:
		objectmanager(const objectmanagerdesc* i_desc);
		~objectmanager();

		object3d* get_object(const char* i_name);


	private:
		ctr::string m_objectgroup;
		ctr::stringmap<object3d> m_map;

		object3d* load_mmod_file(const char* i_name);
	};
}
#endif//_objectmanager_h_