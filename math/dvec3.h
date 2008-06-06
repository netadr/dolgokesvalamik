#ifndef _dvec3_h_
#define _dvec3_h_

#define myinline

namespace math
{
	class dvec3
	{
	public:
		dvec3();
		dvec3(double i_xcoord, double i_ycoord, double i_zcoord);
		dvec3(const double* i_src);

		double&	operator[](int i_index);
		const double& operator[](int i_index) const;

		void	clear();
		void	set(double i_xcoord, double i_ycoord, double i_zcoord);

		void	cross(const dvec3& i_src1, const dvec3& i_src2);
		friend 
		dvec3 cross(const dvec3& i_src1, const dvec3& i_src2);
		dvec3 cross(const dvec3& i_other) const;
		
		double	dot(const dvec3& i_other) const;
		friend
		double	dot(const dvec3& i_v1, const dvec3& i_v2);

		double	squarelength() const;
		double	length() const;
		void	normalize();
		void	normalizesafe();

		void rotate(const dvec3& i_src, const dvec3& i_axis, double i_angle);

		void	abs(const dvec3& i_src);

		dvec3	operator+(const dvec3& i_other) const;
		dvec3	operator-(const dvec3& i_other) const;
		void	operator+=(const dvec3& i_other);
		void	operator-=(const dvec3& i_other);

		dvec3	operator*(double i_scalar) const;
		dvec3	operator/(double i_scalar) const;

		friend
		dvec3 operator*(double i_scalar, const dvec3& i_vector);

		void	operator*=(double i_scalar);
		void	operator/=(double i_scalar);

		dvec3	operator-() const;

		void max(const dvec3& i_v1, const dvec3& i_v2);
		void max(const dvec3& i_other);
		void min(const dvec3& i_v1, const dvec3& i_v2);
		void min(const dvec3& i_other);

		double maxelem() const;

		void interpolate(const dvec3& i_src1, const dvec3& i_src2, double i_time);


		double x,y,z;
	};//dvec3

	myinline dvec3::dvec3()
	{
	}

	myinline dvec3::dvec3(double i_xcoord, double i_ycoord, double i_zcoord)
	{
		x=i_xcoord;
		y=i_ycoord;
		z=i_zcoord;
	}

	myinline dvec3::dvec3(const double* i_src)
	{
		x=i_src[0];
		y=i_src[1];
		z=i_src[2];
	}


	myinline double& dvec3::operator[](int i_index)
	{
		return *(((double*)this)+i_index);
	}

	myinline const double& dvec3::operator[](int i_index) const
	{
		return *(((double*)this)+i_index);
	}

	myinline void dvec3::clear()
	{
		x=y=z=0.0f;
	}

	myinline void dvec3::set(double i_xcoord, double i_ycoord, double i_zcoord)
	{
		x=i_xcoord;
		y=i_ycoord;
		z=i_zcoord;
	}


	myinline void	dvec3::cross(const dvec3& i_src1, const dvec3& i_src2)
	{
		x=i_src1.y*i_src2.z-i_src1.z*i_src2.y;
		y=i_src1.z*i_src2.x-i_src1.x*i_src2.z;
		z=i_src1.x*i_src2.y-i_src1.y*i_src2.x;
	}

	myinline dvec3 cross(const dvec3& i_src1, const dvec3& i_src2)
	{
		return dvec3(
			i_src1.y*i_src2.z-i_src1.z*i_src2.y,
			i_src1.z*i_src2.x-i_src1.x*i_src2.z,
			i_src1.x*i_src2.y-i_src1.y*i_src2.x
			);
	}

	myinline dvec3 dvec3::cross(const dvec3& i_other) const
	{
		return dyn::cross(*this,i_other);
	}

	myinline double	dvec3::dot(const dvec3& i_other) const
	{
		return x*i_other.x+y*i_other.y+z*i_other.z;
	}

	myinline double dot(const dvec3& i_v1, const dvec3& i_v2)
	{
		return i_v1.x*i_v2.x+i_v1.y*i_v2.y+i_v1.z*i_v2.z;
	}

	myinline double	dvec3::squarelength() const
	{
		return x*x+y*y+z*z;
	}

	myinline double	dvec3::length() const
	{
		return sqrt(squarelength());
	}

	myinline void	dvec3::normalize()
	{
		double length=length();

		x/=length;
		y/=length;
		z/=length;
	}

	myinline void	dvec3::normalizesafe()
	{
		double squarelength=squarelength();

		if (squarelength>0.000001f)
		{
			double length=sqrt(squarelength);

			x/=length;
			y/=length;
			z/=length;
		}
		else
		{
			x=y=z=0;
		}
	}

	myinline dvec3	dvec3::operator+(const dvec3& i_other) const
	{
		return dvec3(x+i_other.x,y+i_other.y,z+i_other.z);
	}

	myinline dvec3	dvec3::operator-(const dvec3& i_other) const
	{
		return dvec3(x-i_other.x,y-i_other.y,z-i_other.z);
	}

	myinline void	dvec3::operator+=(const dvec3& i_other)
	{
		x+=i_other.x;
		y+=i_other.y;
		z+=i_other.z;
	}

	myinline void	dvec3::operator-=(const dvec3& i_other)
	{
		x-=i_other.x;
		y-=i_other.y;
		z-=i_other.z;
	}

	myinline dvec3	dvec3::operator*(double i_scalar) const
	{
		return dvec3(x*i_scalar,y*i_scalar,z*i_scalar);
	}

	myinline dvec3	dvec3::operator/(double i_scalar) const
	{
		return dvec3(x/i_scalar,y/i_scalar,z/i_scalar);
	}

	myinline dvec3 operator*(double i_scalar, const dvec3& i_vector)
	{
		return i_vector*i_scalar;
	}

	myinline void	dvec3::operator*=(double i_scalar)
	{
		x*=i_scalar;
		y*=i_scalar;
		z*=i_scalar;
	}

	myinline void	dvec3::operator/=(double i_scalar)
	{
		x/=i_scalar;
		y/=i_scalar;
		z/=i_scalar;
	}

	myinline dvec3	dvec3::operator-() const
	{
		return dvec3(-x,-y,-z);
	}

	myinline void dvec3::abs(const dvec3& i_src)
	{
		x=fabsf(i_src.x);
		y=fabsf(i_src.y);
		z=fabsf(i_src.z);
	}

	myinline void dvec3::max(const dvec3& i_v1, const dvec3& i_v2)
	{
		x=i_v1.x > i_v2.x ? i_v1.x : i_v2.x;
		y=i_v1.y > i_v2.y ? i_v1.y : i_v2.y;
		z=i_v1.z > i_v2.z ? i_v1.z : i_v2.z;
	}

	myinline void dvec3::max(const dvec3& i_other)
	{
		if (i_other.x>x)
			x=i_other.x;
		if (i_other.y>y)
			y=i_other.y;
		if (i_other.z>z)
			z=i_other.z;
	}

	myinline double dvec3::maxelem() const
	{
		double r=x;
		if (y>r) r=y;
		if (z>r) r=z;

		return r;
	}

	myinline void dvec3::min(const dvec3& i_v1, const dvec3& i_v2)
	{
		x=i_v1.x < i_v2.x ? i_v1.x : i_v2.x;
		y=i_v1.y < i_v2.y ? i_v1.y : i_v2.y;
		z=i_v1.z < i_v2.z ? i_v1.z : i_v2.z;
	}

	myinline void dvec3::min(const dvec3& i_other)
	{
		if (i_other.x<x)
			x=i_other.x;
		if (i_other.y<y)
			y=i_other.y;
		if (i_other.z<z)
			z=i_other.z;
	}

	myinline void dvec3::rotate(const dvec3& i_src, const dvec3& i_axis, double i_angle)
	{
		dvec3 a=i_src.dot(i_axis)*i_axis;
		dvec3 b=i_src-a;
		dvec3 c; c.cross(i_axis,b);
		*this=b*cosf(i_angle)+c*sinf(i_angle)+a;
	}

	myinline void getorthogonalaxes(dvec3& o_axis1, dvec3& o_axis2, const dvec3& i_axissrc)
	{
		if ((i_axissrc.z) > 0.707f || i_axissrc.z<-0.707f)
		{
			// y-z plane
			double  a = i_axissrc.y*i_axissrc.y + i_axissrc.z*i_axissrc.z;
			double k = 1/sqrt(a);
			o_axis1.x = 0;
			o_axis1.y = -i_axissrc.z*k;
			o_axis1.z = i_axissrc.y*k;

			o_axis2.x = a*k;
			o_axis2.y = -i_axissrc.x*o_axis1.z;
			o_axis2.z = i_axissrc.x*o_axis1.y;
		}
		else
		{
			// x-y plane
			double a = i_axissrc.x*i_axissrc.x + i_axissrc.y*i_axissrc.y;
			double k = 1/sqrt(a);
			o_axis1.x = -i_axissrc.y*k;
			o_axis1.y = i_axissrc.x*k;
			o_axis1.z = 0;

			o_axis2.x = -i_axissrc.z*o_axis1.y;
			o_axis2.y = i_axissrc.z*o_axis1.x;
			o_axis2.z = a*k;
		}
	}

	myinline void dvec3::interpolate(const dvec3& i_src1, const dvec3& i_src2, double i_time)
	{
		x=i_src1.x+i_time*(i_src2.x-i_src1.x);
		y=i_src1.y+i_time*(i_src2.y-i_src1.y);
		z=i_src1.z+i_time*(i_src2.z-i_src1.z);
	}

}//namespace math
#endif//_dvec3_h_