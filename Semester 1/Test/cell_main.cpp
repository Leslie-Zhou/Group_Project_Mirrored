#include <iostream>
#include <Cell.h>
#include <vector>
#include <vectorClass.h>

using namespace std;

int main()
{
    vectorClass vctr[8];
    vectorClass gravCentre;
    float volume;
    vctr[0].setVector(0,0,0,0);
    vctr[1].setVector(1,1,0,0);
    vctr[2].setVector(2,1,1,0);
    vctr[3].setVector(3,0,1,0);
    vctr[4].setVector(4,0,0,1);
    vctr[5].setVector(5,1,0,1);
    vctr[6].setVector(6,1,1,1);
    vctr[7].setVector(7,0,1,1);

    Cell cell_1('p');
    cell_1.setVector(vctr);
    cell_1.setVolume();
    cell_1.setGravityCentre();
    gravCentre = cell_1.getGravityCentre();
    volume = cell_1.getVolume();

    cout << gravCentre.getX() << " " << gravCentre.getY() << " " << gravCentre.getZ() << endl;
    cout << volume << endl;
    cout << cell_1.getVectorNum();


    return 0;
}
