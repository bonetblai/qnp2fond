#include <iostream>
#include <fstream>
#include <string>
#include "problem.h"

using namespace std;

int main(int argc, const char **argv) {
    if( argc < 4 ) {
        cout << "usage: " << *argv << " <qnp-file> <num-bits-per-counter> <loop-nesting>" << endl;
        exit(0);
    }
    string fname = argv[1];
    int num_bits_per_counter = atoi(argv[2]);
    int loop_nesting = atoi(argv[3]);
    ifstream ifs(fname);
    QNP::Problem *qnp = QNP::Problem::read(ifs);
    ifs.close();
    //cout << *qnp;
    QNP::Problem *fond = qnp->translate(num_bits_per_counter, loop_nesting);
    //cout << *fond;
    fond->PDDL_dump(cout);
    delete fond;
    delete qnp;
    return 0;
}

