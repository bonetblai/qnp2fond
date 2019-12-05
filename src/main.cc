#include <iostream>
#include <fstream>
#include <string>

#include "translation.h"

using namespace std;

bool direct_translation(const Reductions::QNP &qnp) {
    return !qnp.meta_info_increments();
}

int main(int argc, const char **argv) {
    if( argc < 5 ) {
        cout << "usage: " << *argv << " <qnp-file> <num-bits-per-counter> <max-stack-depth> <prefix>" << endl;
        exit(0);
    }
    string qnp_fname = argv[1];
    int num_bits_per_counter = atoi(argv[2]);
    int max_stack_depth = atoi(argv[3]);
    string prefix = argv[4];

    // QNP
    ifstream ifs(qnp_fname);
    Reductions::QNP *qnp = Reductions::QNP::read(ifs);
    ifs.close();
    cout << "qnp: #features=" << qnp->num_features()
         << ", #numeric=" << qnp->num_numeric_features()
         << ", #boolean=" << qnp->num_boolean_features()
         << ", #actions=" << qnp->num_actions()
         << endl;
    //cout << *qnp;

    // set values for translation parameters
    int n = qnp->num_features();
    if( num_bits_per_counter <= 0 ) {
        cout << "info: <num-bits-per-counter> set to " << 1 + n << endl;
        num_bits_per_counter = 1 + n;
    }
    if( max_stack_depth <= 0 ) {
        cout << "info: <max-stack-depth> set to " << 1 + n << endl;
        max_stack_depth = 1 + n;
    }

    // translation
    Reductions::Translations::Translation *tr = nullptr;
    if( direct_translation(*qnp) ) {
        cout << "using direct translation..." << endl;
        tr = new Reductions::Translations::Direct();
    } else {
        cout << "using full translation..." << endl;
        tr = new Reductions::Translations::Full(num_bits_per_counter, max_stack_depth);
    }

    // translate
    Reductions::FOND *fond = tr->translate(*qnp);
    Reductions::Translations::Statistics stats = tr->stats();
    cout << "translation: time=" << stats.time_in_seconds_ << endl;
    cout << "fond: #features=" << fond->num_features() << ", #actions=" << fond->num_actions() << endl;
    //cout << *fond;

    // PDDL domain
    ofstream ofs_d(prefix + "_d.pddl");
    fond->PDDL_dump_domain(ofs_d, num_bits_per_counter, max_stack_depth);
    ofs_d.close();

    // PDDL problem
    ofstream ofs_p(prefix + "_p.pddl");
    fond->PDDL_dump_problem(ofs_p);
    ofs_p.close();

    delete fond;
    delete qnp;
    return 0;
}

