int main()
{
    bool __attribute__((sierra_vector(4))) a = {true, true, false, true};
    bool __attribute__((sierra_vector(4))) b = {false, false, false, true};

    int __attribute__((sierra_vector(4))) x = 0;

    if ( a || b )
        x++;

    return ((int*) &x)[0];
}