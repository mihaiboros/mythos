#ifndef __HERA_BLEND_H__
#define __HERA_BLEND_H__

namespace hera
{

struct Blend
{
  // blend factors
  enum Factor
  {
    One = 0,
    Src_alpha,
    One_minus_src_alpha,
    Dst_alpha,
    One_minus_dst_alpha
  };

  // source factor
  Factor src{Factor::One};
  // destination factor
  Factor dst{Factor::One};
};

} // namespace hera

#endif //__HERA_BLEND_H__
