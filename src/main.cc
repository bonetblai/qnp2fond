#include <iostream>
#include <fstream>
#include <string>
#include "problem.h"

using namespace std;

int main(int argc, const char **argv) {
    if( argc < 5 ) {
        cout << "usage: " << *argv << " <qnp-file> <num-bits-per-counter> <loop-nesting> <prefix>" << endl;
        exit(0);
    }
    string qnp_fname = argv[1];
    int num_bits_per_counter = atoi(argv[2]);
    int loop_nesting = atoi(argv[3]);
    string prefix = argv[4];

    ifstream ifs(qnp_fname);
    QNP::Problem *qnp = QNP::Problem::read(ifs);
    ifs.close();
    //cout << *qnp;
    //
    QNP::Problem *fond = qnp->translate(num_bits_per_counter, loop_nesting);
    //cout << *fond;

    ofstream ofs_d(prefix + "_d.pddl");
    fond->PDDL_dump_domain(ofs_d);
    ofs_d.close();

    ofstream ofs_p(prefix + "_p.pddl");
    fond->PDDL_dump_problem(ofs_p);
    ofs_p.close();

    delete fond;
    delete qnp;
    return 0;
}

