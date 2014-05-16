#include "sierra/defines.h"
#include "sierra/math.h"

bool varying(8) xmin(float varying(8) a, float varying(8) b) {
    return sierra::fmin(a, b);
}
