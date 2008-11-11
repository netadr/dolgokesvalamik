#ifndef _aabox_h_
#define _aabox_h_

#include "vec3.h"
#include "mtx4x3.h"

	struct aabb
	{
		vec3 min;
		vec3 max;

		vec3 get_center() const
		{
			return 0.5f*(this->min+this->max);
		}

		vec3 get_extent() const
		{
			return 0.5f*(this->max-this->min);
		}
	};

	MLINLINE aabb transform(const mtx4x3& i_mtx, const aabb& i_src)
	{
		aabb dst;

		vec3 center=0.5f*(i_src.min+i_src.max);
		vec3 extent=0.5f*(i_src.max-i_src.min);

		vec3 newcenter;
		i_mtx.transform(newcenter,center);
		mtx3x3 absmtx;

		for (unsigned n=0; n<9;++n)
		{
			absmtx[n]=fabsf(i_mtx[n]);
		}
		vec3 newextent;
		absmtx.transform3x3(newextent,extent);

		dst.min=newcenter-newextent;
		dst.max=newcenter+newextent;

		return dst;
	}
#endif//_aabox_h_


