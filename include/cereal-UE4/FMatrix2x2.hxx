#pragma once
namespace cereal
{
  template < typename A >
  inline void CEREAL_SAVE_FUNCTION_NAME( A& a, const FMatrix2x2& in )
  {
    float m00 = 0, m01 = 0, m10 = 0, m11 = 0;
    in.GetMatrix( m00, m01, m10, m11 );
    a( cereal::make_nvp( "m00", m00 ) );
    a( cereal::make_nvp( "m01", m01 ) );
    a( cereal::make_nvp( "m10", m10 ) );
    a( cereal::make_nvp( "m11", m11 ) );
  }
  
  template < typename A >
  inline void CEREAL_LOAD_FUNCTION_NAME( A& a, FMatrix2x2& out )
  {
    float m00 = 0, m01 = 0, m10 = 0, m11 = 0;
    a( cereal::make_nvp( "m00", m00 ) );
    a( cereal::make_nvp( "m01", m01 ) );
    a( cereal::make_nvp( "m10", m10 ) );
    a( cereal::make_nvp( "m11", m11 ) );
    
    out = FMatrix2x2( m00, m01, m10, m11 );
  }
}