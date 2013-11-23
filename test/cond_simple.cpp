int main() {

    bool __attribute__((sierra_vector(4))) a = {false, false, false, true};
    bool __attribute__((sierra_vector(4))) b = {true, false, true, false};
    bool __attribute__((sierra_vector(4))) c = {false, false, true, true};
    bool __attribute__((sierra_vector(4))) d;

    d = a ? b : c;
    
    return 0;
}
