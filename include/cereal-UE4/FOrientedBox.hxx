#pragma once
namespace cereal
{
  template < typename A >
  inline void serialize( A& a, FOrientedBox& in )
  {
    a
    ( make_nvp( "AxisX", in.AxisX )
    , make_nvp( "AxisY", in.AxisY )
    , make_nvp( "AxisZ", in.AxisZ )
    , make_nvp( "Center", in.Center )
    , make_nvp( "ExtentX", in.ExtentX )
    , make_nvp( "ExtentY", in.ExtentY )
    , make_nvp( "ExtentZ", in.ExtentZ )
    );
  }
}