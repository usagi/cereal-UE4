#pragma once
namespace cereal
{
  template < typename A, typename E >
  inline void serialize( A& a, TInterval< E >& in )
  {
    a
    ( make_nvp( "Min", in.Min )
    , make_nvp( "Max", in.Max )
    );
  }
}