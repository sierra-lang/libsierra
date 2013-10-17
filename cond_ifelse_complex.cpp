int main() {

    bool __attribute__((sierra_vector(4))) a = {false, false, false, true};
    bool __attribute__((sierra_vector(4))) b = {true, false, true, false};
    int __attribute__((sierra_vector(4))) c = {0, 0, 0, 0};

    if ( a ? b : true ) // {1, 1, 1, 0}
        c = c - 1; // {-1, -1, -1, 0}
    else
        c = c + 1; // {0, 0, 0, 1}
    
    return 0;
}
