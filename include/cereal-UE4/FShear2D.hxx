#pragma once
namespace cereal
{
  template < typename A >
  inline void CEREAL_SAVE_FUNCTION_NAME( A& a, const FShear2D& in )
  {
    const auto buffer = in.GetVector();
    a( cereal::make_nvp( "X", buffer.X ) );
    a( cereal::make_nvp( "Y", buffer.Y ) );
  }
  
  template < typename A >
  inline void CEREAL_LOAD_FUNCTION_NAME( A& a, FShear2D& out )
  {
    FVector2D buffer;
    a( cereal::make_nvp( "X", buffer.X ) );
    a( cereal::make_nvp( "Y", buffer.Y ) );
    
    out = FShear2D( buffer );
  }
}