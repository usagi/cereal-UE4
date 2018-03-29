#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FIntPoint& in )
  {
    a
    ( make_nvp( "X", in.X )
    , make_nvp( "Y", in.Y )
    );
  }
}