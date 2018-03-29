#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FBox& in )
  {
    a
    ( make_nvp( "IsValid", in.Max )
    , make_nvp( "Min", in.Min )
    , make_nvp( "Max", in.Max )
    );
  }
}