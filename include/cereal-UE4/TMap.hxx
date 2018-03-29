#pragma once
namespace cereal
{
  template < typename A, typename K, typename V, typename L, typename F >
  inline void CEREAL_SAVE_FUNCTION_NAME( A& a, const TMap< K, V, L, F >& in )
  {
    a( make_size_tag( static_cast< size_type >( in.Num() ) ) );
    
    for( const auto& p : in )
      a( make_map_item( p.Key, p.Value ) );
  }
  
  template < typename A, typename K, typename V, typename L, typename F >
  inline void CEREAL_LOAD_FUNCTION_NAME( A& a, TMap< K, V, L, F >& out )
  {
    size_type size;
    a( make_size_tag( size ) );
    
    out.Empty();
    out.Reserve( size );
    
    for( size_type i = 0; i < size; ++i )
    {
      K key;
      V value;
      
      a( make_map_item( key, value ) );
      out.Emplace( MoveTemp( key ), MoveTemp( value ) );
    }
  }
}