int main()
{
  bool __attribute__((sierra_vector(4))) a = {true, true, false, false};
  int __attribute__((sierra_vector(4))) x = {0, 10, 20, 30};

  if (!a)
    ++x;

  return ((int*) &x)[0] + ((int*) &x)[2]; // expecting 21
}

