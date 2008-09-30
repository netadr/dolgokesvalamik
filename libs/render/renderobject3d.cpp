#include "renderobject3d.h"
#include "rendersystem.h"
#include "objectmanager.h"
//#include "scene/nodefactory.h"

namespace render
{
	DEFINE_OBJECT(object3d,scene::node);
	BIND_PROPERTY(object3d,m_modelname,"modelname",string);

	object3d::object3d()
	{
	}

	object3d::object3d(const char* i_name):
	scene::node(i_name)
	{
	}
	
	object3d::~object3d()
	{
	}

	void object3d::render()
	{
		object3d* ptr=this;

		while (ptr)
		{
			for (unsigned n=0; n<ptr->m_mesh.size(); ++n)
				system::instance()->add_mesh(ptr->m_mesh[n].get(),ptr->get_worldposition());

			ptr=(object3d*)ptr->get_next();
		}
	}

	void object3d::on_load()
	{
		if (m_modelname!="")
		{
			object3d* obj=objectmanager::instance()->get_object(m_modelname.c_str());
			if (obj)
				add_child(obj);
		}
	}
	
	
	
}