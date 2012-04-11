int main() 
{
    int x = /*...*/;
    int vector[2] v = /*...*/;

    // scalar pointer to scalar data
    {
        int* p;

        int a = p[x]; // normal C
        p[x] = a;     // normal C

        // gather
        // [ a[[0]] = *(p + v[[0]]), 
        //   a[[1]] = *(p + v[[1]]) ]
        int vector[[2]] a = p[v];

        // broadcast + scatter
        // [ *(p + v[[0]]) = a, 
        //   *(p + v[[1]]) = a ]
        p[v] = a;
    }

    // vectorial pointer to scalar data
    {
        int* vector[2] p;

        // gather
        // [ a[[0]] = *(p[[0]] + x), 
        //   a[[1]] = *(p[[0]] + x) ]
        int vector[2] a = p[x];

        // vec-scatter
        // [ *(p[[0]] + v[[0]]) = a],
        //   *(p[[1]] + v[[1]]) = a] ],
        p[v] = a;
    }


    // scalar pointer to vectorial data
    {
        int vector[2]* p;

        int vector[2] a = p[x]; // almost normal C
        p[x] = a;               // almost normal C

        // gather + assemble
        // [ a[[0]] =  (  *(p + v[[0]])  )[[0]],
        //   a[[1]] =  (  *(p + v[[1]])  )[[1]] ]
        int vector[2] a = p[v]; // gather + assemble

        // scatter + assemble
        // [ (  *(p + v[[0]])  )[[0]] = a[[0]],
        //   (  *(p + v[[1]])  )[[1]] = a[[1]] ]
        p[v] = a;               // disassemble + scatter
    }

    // vectorial pointer to vectorial data
    {
        int vector[2]* vector[2] p;

        // [ a[[0]] = (  *(p[[0]] + x) ))[0], 
        //   a[[1]] = (  *(p[[1]] + x) ))[1] ]
        int vector[2] a = p[x];

        // [ (  *(p[[0]] + x) ))[0] = a[[0]],
        //   (  *(p[[1]] + x) ))[1] = a[[1]] ]
        p[x] = a;               // 

        // [ a[[0]] = (  *(p[[0]] + v[[0]]) ))[0], 
        //   a[[1]] = (  *(p[[1]] + v[[1]]) ))[1] ]
        int vector[2] a = p[v]; // vec-gather + assemble

        // [ a[[0]] = (  *(p[[0]] + v[[0]]) ))[0], 
        //   a[[1]] = (  *(p[[1]] + v[[1]]) ))[1] ]
        p[v] = a;               // disassemble + vec-scatter
    }
}
