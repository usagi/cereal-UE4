#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FCapsuleShape& in )
  {
    a
    ( make_nvp( "Center", in.Center )
    , make_nvp( "Radius", in.Radius )
    , make_nvp( "Orientation", in.Orientation )
    , make_nvp( "Length", in.Length )
    );
  }
}