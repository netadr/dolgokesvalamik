#include "stdafx.h"

#include <MMSystem.h>

#include "render/rendersystem.h"
#include "file/filesystem.h"
#include "threading/taskmanager.h"
#include "render/shadermanager.h"
#include "render/texturemanager.h"
#include "render/rendermaterial.h"
#include "math/mtx4x4.h"
#include "math/vec2.h"

struct game
{
	render::mesh* m_mesh;
	math::mtx4x3 m_mtx;
} g_game;

threading::taskmanager* g_taskmanager=NULL;

RECT g_rect;
unsigned g_time;
HWND g_hwnd;

void init_app(HWND i_hwnd)
{
	file::system::create();
	file::system::instance()->register_path("shader","c:\\data\\shader\\");
	file::system::instance()->register_path("texture","c:\\data\\texture\\");

	g_taskmanager=new threading::taskmanager(4);

	render::shadermanagerdesc shaderdesc("shader");
	render::shadermanager::create(&shaderdesc);

	render::texturemanagerdesc textdesc("texture");
	render::texturemanager::create(&textdesc);

	render::systemdesc renderdesc;
	renderdesc.m_backbuffercount=2;
	RECT rect;
	GetClientRect(i_hwnd,&rect);
	renderdesc.m_screenwidth=abs(rect.right-rect.left);
	renderdesc.m_screenheight=abs(rect.bottom-rect.top);
	renderdesc.m_window=i_hwnd;
	renderdesc.m_windowed=true;

	render::system::create(&renderdesc);

	::GetWindowRect(i_hwnd,&g_rect);
	g_time=timeGetTime();
	g_hwnd=i_hwnd;

	math::mtx4x4 mtx; mtx.set_projectionmatrix(tan(math::degreetorad(45)),4.0f/3,1,10000);

	render::mesh* mesh=new render::mesh;

	ctr::vector<render::vertexelements> ve;

	ve.push_back(render::element_pos3);
	ve.push_back(render::element_uv);

	mesh->m_vb=render::system::instance()->create_vertexbuffer(4,ve);
	mesh->m_ib=render::system::instance()->create_indexbuffer(6);

	class vertex_t
	{
	public:
		math::vec3 pos;
		math::vec2 uv;
	};

	vertex_t* vb=(vertex_t*)mesh->m_vb->lock();

	vb[0].pos.set(-1.0f, 1.0f, 0.0f); vb[0].uv.set(0.0f,0.0f);
	vb[1].pos.set(1.0f, 1.0f, 0.0f); vb[1].uv.set(1.0f,0.0f );
	vb[2].pos.set(-1.0f,-1.0f, 0.0f); vb[2].uv.set(0.0f,1.0f );
	vb[3].pos.set(1.0f,-1.0f, 0.0f); vb[3].uv.set( 1.0f,1.0f );

	mesh->m_vb->unlock();

	unsigned short* ib=mesh->m_ib->lock();

	const unsigned short buf[]={0,1,2,1,3,2};

	memcpy(ib,buf,6*sizeof(short));

	mesh->m_ib->unlock();


	mesh->m_trisetbuf.resize(1);
	render::triset& ts=mesh->m_trisetbuf.back();
	ts.m_firstindex=0;
	ts.m_numindices=6;
	ts.m_firstvertex=0;
	ts.m_numvertices=4;
	ts.m_material=new render::material;

	ts.m_material->set_shader(render::shadermanager::instance()->get_shader("dx9_hlsl_fx_simple.fx"));

//	render::texture* txt=render::texturemanager::instance()->get_texture("test.bmp");
//	ts.m_material->m_texturebuf.push_back(txt);

	g_game.m_mtx.identity();
	g_game.m_mtx.trans().z=4;
	g_game.m_mesh=mesh;

}

void update_app()
{
	unsigned acttime=::timeGetTime();
	unsigned deltatime=acttime-g_time;

	if (deltatime<33)
		return;

	g_time=acttime;

	
	unsigned width=abs(g_rect.left-g_rect.right);
	unsigned heigth=abs(g_rect.bottom-g_rect.top);

	::MoveWindow(g_hwnd,g_rect.left+(unsigned)(100*sin(acttime/1000.0)),g_rect.top,width,heigth,TRUE);
//	::GetWindowRect()
//		::SetWindowPos()
//		::setwin
//	::MoveWindow()

	math::mtx4x3 cammtx=math::mtx4x3::identitymtx();
//	cammtx.t.z=-10;

	math::mtx4x3 viewmtx; viewmtx.linearinvert(cammtx);

	render::system::instance()->set_projection_params(math::degreetorad(90),1,0.1f,100,(math::mtx4x4)cammtx);

	render::system::instance()->add_mesh(g_game.m_mesh,g_game.m_mtx);
	render::system::instance()->render();
}

void exit_app()
{
	file::system::release();
	delete g_taskmanager; g_taskmanager=NULL;
	render::shadermanager::release();
	render::texturemanager::release();
	render::system::release();
}