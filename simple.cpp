template<class T, int L> 
struct internal_vec       
{ 
    typedef T __attribute__((sierra_vector (L))) type; 
    //typedef T __attribute__((ext_vector_type (L))) type; 
};

template<class T>        
struct internal_vec<T, 1> 
{ 
    typedef T type; 
};

// alias for convenience
template<class T, int L> 
using vec = typename internal_vec<T, L>::type;


//vec<float, 4> fmad(vec<float, 4> a, vec<float, 4> b, vec<float, 4> c) {
    //return a * b + c;
//}

vec<bool, 4> test(vec<float, 4> a, vec<float, 4> b) {
    vec<bool, 4> res = a < b;
    return res;
}
