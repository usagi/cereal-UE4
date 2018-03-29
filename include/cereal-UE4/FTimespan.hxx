#pragma once
namespace cereal
{
  template < typename A >
  inline std::string save_minimal( A& a, const FTimespan& in )
  {
    return std::string( TCHAR_TO_UTF8( *in.ToString() ) );
  }
  
  template < typename A >
  inline void load_minimal( A& a, FTimespan& out, const std::string& v )
  {
    FTimespan::Parse( UTF8_TO_TCHAR( v.data() ), out );
  }
}