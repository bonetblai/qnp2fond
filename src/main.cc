#include <iostream>
#include <fstream>
#include "qnp.h"

using namespace std;

int main(int argc, const char **argv) {
    string fname = argv[1];
    int d = atoi(argv[2]);
    ifstream ifs(fname);
    QNP *qnp = QNP::read(ifs);
    ifs.close();
    //cout << *qnp;
    QNP *fond = qnp->translate(d);
    //cout << *fond;
    fond->PDDL_dump(cout);
    return 0;
}

