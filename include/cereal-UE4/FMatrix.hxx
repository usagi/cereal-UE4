#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FMatrix& in )
  {
    a( cereal::make_nvp( "m00", in.M[0][0] ) );
    a( cereal::make_nvp( "m01", in.M[0][1] ) );
    a( cereal::make_nvp( "m02", in.M[0][2] ) );
    a( cereal::make_nvp( "m03", in.M[0][3] ) );
    
    a( cereal::make_nvp( "m10", in.M[1][0] ) );
    a( cereal::make_nvp( "m11", in.M[1][1] ) );
    a( cereal::make_nvp( "m12", in.M[1][2] ) );
    a( cereal::make_nvp( "m13", in.M[1][3] ) );
    
    a( cereal::make_nvp( "m20", in.M[2][0] ) );
    a( cereal::make_nvp( "m21", in.M[2][1] ) );
    a( cereal::make_nvp( "m22", in.M[2][2] ) );
    a( cereal::make_nvp( "m23", in.M[2][3] ) );
    
    a( cereal::make_nvp( "m30", in.M[3][0] ) );
    a( cereal::make_nvp( "m31", in.M[3][1] ) );
    a( cereal::make_nvp( "m32", in.M[3][2] ) );
    a( cereal::make_nvp( "m33", in.M[3][3] ) );
  }
}