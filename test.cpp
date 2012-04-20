// _sierra_vec<Type, Length>
template<class T, int L> 
struct internal_vec       
{ 
    typedef T __attribute__((sierra_vector (L))) type; 
    //typedef T __attribute__((ext_vector_type (L))) type; 
};

// uniform specialization
template<class T>        
struct internal_vec<T, 1> 
{ 
    typedef T type; 
};

// alias for convenience
template<class T, int L> 
using vec = typename internal_vec<T, L>::type;


vec<float, 4> fmad(vec<float, 4> a, vec<float, 4> b) {
    return a * b;
}

//void test1() {
    //vec<int, 4> i;
    //vec<bool, 4> b = i;
//}

void test() {
    //vec<float, 4> a, b;
    //vec<float, 8> c, d;
    vec<int, 4> a;
    vec<int, 8> b;
    //if (a < 0) {}

    if (a) {
        if (b) {
        }
    }
}
