#if 0
int main() {
  bool __attribute__((sierra_vector(4))) a = {true, true, false, true};
  bool __attribute__((sierra_vector(4))) b = {false, false, false, true};
  bool __attribute__((sierra_vector(4))) c = {true, false, true, true};
  if (a)
    bool __attribute__((sierra_vector(4))) x = a ? b : c;
  return 42;
}
#endif

__attribute__((sierra_spmd(4)))
void f(bool __attribute__((sierra_vector(4))) a, bool __attribute__((sierra_vector(4))) b, bool __attribute__((sierra_vector(4))) c) {
    bool __attribute__((sierra_vector(4))) x = a ? b : c;
}
