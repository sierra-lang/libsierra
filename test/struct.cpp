#define varying(n) __attribute__((sierra_vector(n)))

struct vec3 {
    float x, y, z;
};

void foo(vec3 varying(4)) {}

int main() {
    vec3 varying(4) v;
    foo(v);
    vec3 varying(4) w;
    v.x = w.x;
    //float varying(4) fv = v.y;
}

