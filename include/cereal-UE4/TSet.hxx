#pragma once
namespace cereal
{
  template < typename A, typename E, typename K, typename L >
  inline void CEREAL_SAVE_FUNCTION_NAME( A& a, const TSet< E, K, L >& in )
  {
    a( make_size_tag( static_cast< size_type >( in.Num() ) ) );
    
    for( const auto& e : in )
      a( e );
  }
  
  template < typename A, typename E, typename K, typename L >
  inline void CEREAL_LOAD_FUNCTION_NAME( A& a, TSet< E, K, L >& out )
  {
    size_type size;
    a( make_size_tag( size ) );
    
    out.Empty();
    out.Reserve( size );
    
    for( size_type i = 0; i < size; ++i )
    {
      E e;
      
      a( e );
      out.Emplace( MoveTemp( e ) );
    }
  }
}