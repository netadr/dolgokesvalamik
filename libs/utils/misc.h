#ifndef _misc_h_
#define _misc_h_
#endif//_misc_h_

namespace utils
{
	#define MLINLINE __forceinline
	#define  NULL 0

	#define SAFE_DELETE(_PTR_) {if (_PTR_){delete _PTR_; _PTR_=NULL;}}

#define member(_T_,_V_) private: _T_ m_##_V_ ; public: const _T_ &get_##_V_ () const{return m_##_V_ ;} void set_##_V_ (const _T_ &i_##_V_ ){m_##_V_ =i_##_V_ ;}
}