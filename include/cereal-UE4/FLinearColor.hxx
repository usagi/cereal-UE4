#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FLinearColor& in )
  {
    a
    ( make_nvp( "R", in.R )
    , make_nvp( "G", in.G )
    , make_nvp( "B", in.B )
    , make_nvp( "A", in.A )
    );
  }
}