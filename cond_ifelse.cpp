//#include <iostream>

int main() {

  int __attribute__((sierra_vector(4))) a = {true, false, false, true};
  int __attribute__((sierra_vector(4))) b = {true, false, true, false};
  int __attribute__((sierra_vector(4))) c = false;

  if ( a ? b : true ) // {1, 1, 1, 0}
  {
    c = a;  // {1, 0, 0, 0}
  }

  //std::cout << "a: <" << ((int*) &a)[0] << ", " << ((int*) &a)[1] << ", "
    //<< ((int*) &a)[2] << ", " << ((int*) &a)[3] << ">" << std::endl;

  //std::cout << "b: <" << ((int*) &b)[0] << ", " << ((int*) &b)[1] << ", "
    //<< ((int*) &b)[2] << ", " << ((int*) &b)[3] << ">" << std::endl;

  //std::cout << "c: <" << ((int*) &c)[0] << ", " << ((int*) &c)[1] << ", "
    //<< ((int*) &c)[2] << ", " << ((int*) &c)[3] << ">" << std::endl;

  return 0;
}
