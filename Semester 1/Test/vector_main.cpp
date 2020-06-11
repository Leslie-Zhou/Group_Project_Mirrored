#include <iostream>
#include "vectorClass.h"

using namespace std;

int main()
{
    float x, y, z;
    vectorClass v1, v2, v3, v5;

    vectorClass v4(1,3,4,5);
    v1.setVector(1,5,7,9);
    v2.setVector(2,4,6,8);
    v3.setVector(3,2,1,1.1);

    v1.getVector(1,&x,&y,&z);
    v2.getVector(2,&x,&y,&z);

    v5 = v1.vectorProduct(v1,v2);
    v5.getVector(5,&x,&y,&z);

}
