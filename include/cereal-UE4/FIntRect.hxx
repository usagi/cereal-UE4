#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FIntRect& in )
  {
    a
    ( make_nvp( "Min", in.Min )
    , make_nvp( "Max", in.Max )
    );
  }
}