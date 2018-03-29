#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FTwoVectors& in )
  {
    a
    ( make_nvp( "v1", in.v1 )
    , make_nvp( "v2", in.v2 )
    );
  }
}