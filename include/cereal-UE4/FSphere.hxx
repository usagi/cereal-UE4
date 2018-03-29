#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FSphere& in )
  {
    a
    ( make_nvp( "Center", in.Center )
    , make_nvp( "W", in.W )
    );
  }
}