int main() {

  int __attribute__((sierra_vector(4))) a = {true, false, false, true};
  int __attribute__((sierra_vector(4))) b = {true, false, true, false};
  int __attribute__((sierra_vector(4))) c = false;

  for ( int __attribute__((sierra_vector(4))) i = 0; i < a; ++i )
  {
    if ( a < b )
    {
      while ( b < c )
      {
        ++b;
      }
    }
    else
    {
      for ( ; b < c ; ++c );
    }
    do
    {
      ++c;
    }
    while ( c < a );
  }

  return 0;
}
