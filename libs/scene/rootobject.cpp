#include "rootobject.h"
#include "nodefactory.h"


namespace scene
{

	class rootobject_metaobject:public metaobject
	{
	public:
		rootobject_metaobject():metaobject("rootobject",NULL){}
		rootobject* create() const{return new rootobject;}
	};//class

	rootobject_metaobject g_rootobject_metaobject;




	int rootobject::get_typeid() const
	{
		return g_rootobject_metaobject.get_typeid();
	}

	metaobject* rootobject::get_metaobject() const
	{
		return &g_rootobject_metaobject;
	}

	metaobject* rootobject::get_class_metaobject()
	{
		return &g_rootobject_metaobject;
	}


//	DEFINE_OBJECT(rootobject,NULL);

	const ctr::string& rootobject::get_name() const
	{
		return m_name;
	}

	void rootobject::set_name(const char* i_name)
	{
		m_name=i_name;
	}

}//namespace