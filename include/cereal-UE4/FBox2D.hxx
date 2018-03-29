#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FBox2D& in )
  {
    a
    ( make_nvp( "bIsValid", in.Max )
    , make_nvp( "Min", in.Min )
    , make_nvp( "Max", in.Max )
    );
  }
}