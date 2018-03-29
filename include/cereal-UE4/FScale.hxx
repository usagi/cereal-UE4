#pragma once
#include "Runtime/Core/Public/Math/TransformCalculus3D.h"
namespace cereal
{
  template < typename A >
  inline void CEREAL_SAVE_FUNCTION_NAME( A& a, const FScale& in )
  {
    const auto buffer = in.GetVector();
    a( cereal::make_nvp( "X", buffer.X ) );
    a( cereal::make_nvp( "Y", buffer.Y ) );
    a( cereal::make_nvp( "Z", buffer.Z ) );
  }
  
  template < typename A >
  inline void CEREAL_LOAD_FUNCTION_NAME( A& a, FScale& out )
  {
    FVector buffer;
    a( cereal::make_nvp( "X", buffer.X ) );
    a( cereal::make_nvp( "Y", buffer.Y ) );
    a( cereal::make_nvp( "Z", buffer.Z ) );
    
    out = FScale( buffer );
  }
}