struct vec4 {
    float data[4];

    vec4 operator * (vec4 v) {
        vec4 result;

        spmd[4] {
            result.data[program_index] = data[program_index] * v.data[program_index];
        }

        return result;
    }
};


int f() {
    vec4 a, b, c;
    a = b * c;

    spmd[2, 4] {
        vec4 a, b, c; // vec4 varying[2, 4] ==>  xyzw xyzw 
        a = b * c;    // 2 x 4 mode
    }
}
