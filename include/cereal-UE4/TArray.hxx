#pragma once
namespace cereal
{
  template < typename A, typename E, typename L >
  inline void
  CEREAL_SAVE_FUNCTION_NAME( A& a, const TArray<E, L>& in )
  {
    a( make_size_tag( static_cast< size_type >( in.Num() ) ) );
    for( auto&& e : in )
      a( e );
  }
  
  template < typename A, typename E, typename L >
  inline void
  CEREAL_LOAD_FUNCTION_NAME( A& a, TArray< E, L >& out )
  {
    size_type size;
    a( make_size_tag( size ) );
    
    out.SetNum( static_cast< int32 >( size ) );
    for( auto&& e : out )
      a( e );
  }
}