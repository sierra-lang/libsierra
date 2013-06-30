int main()
{
  bool __attribute__((sierra_vector(4))) a = {true, true, false, true};
  bool __attribute__((sierra_vector(4))) b = {false, false, false, true};
  bool __attribute__((sierra_vector(4))) c = {true, false, true, true};
  bool __attribute__((sierra_vector(4))) d = {true, false, false, true};

  int x = 0;

  if ( ( a || b ) && ( c && d ) )
    x++;
  else
    x--;

  return x;
}
