#include <iostream>
#include <fstream>
#include <string>

#include "translation.h"

using namespace std;

bool use_direct_translation(const Reductions::QNP &qnp) {
    return qnp.incremented_features().empty();
}

void usage(ostream &os, const string &name) {
    os << "usage: " << name << " [--force-direct] [--disable-optimizations] <qnp-file> <num-bits-per-counter> <max-stack-depth> <prefix>" << endl;
}

void insufficient_arguments(ostream &os, const string &name) {
    os << Utils::error() << "insufficient arguments" << endl;
    usage(os, name);
    exit(0);
}

int main(int argc, const char **argv) {
    // print call
    const string call_str(Utils::cmdline(argc, argv));
    cout << "call: " << call_str << endl;

    // read executable name
    string executable_name(*argv);

    // read options
    bool opt_force_direct = false;
    bool opt_disable_optimizations = false;
    for( ++argv, --argc; (argc > 0) && (**argv == '-'); ++argv, --argc ) {
        if( string(*argv) == "--force-direct" ) {
            opt_force_direct = true;
        } else if( string(*argv) == "--disable-optimizations" ) {
            opt_disable_optimizations = true;
        }
    }

    // read arguments
    if( argc == 0 ) insufficient_arguments(cout, executable_name);
    string qnp_fname = *argv++;
    --argc;

    if( argc == 0 ) insufficient_arguments(cout, executable_name);
    int num_bits_per_counter = atoi(*argv++);
    --argc;

    if( argc == 0 ) insufficient_arguments(cout, executable_name);
    int max_stack_depth = atoi(*argv++);
    --argc;

    if( argc == 0 ) insufficient_arguments(cout, executable_name);
    string prefix = *argv++;
    --argc;

    // read QNP
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

    // select translation type
    Reductions::Translations::Translation *tr = nullptr;
    if( opt_force_direct || (!opt_disable_optimizations && use_direct_translation(*qnp)) ) {
        cout << "using direct translation..." << endl;
        tr = new Reductions::Translations::Direct();
    } else {
        cout << "using full translation..." << endl;
        tr = new Reductions::Translations::Complete(num_bits_per_counter, max_stack_depth, opt_disable_optimizations);
    }

    // do translation
    Reductions::FOND *fond = tr->translate(*qnp);
    Reductions::Translations::Statistics stats = tr->stats();
    cout << "translation: time=" << stats.time_in_seconds_ << endl;
    cout << "translation: stats.extra=[";
    for( size_t i = 0; i < stats.extra_.size(); ++i )
        cout << " " << stats.extra_.at(i);
    cout << " ]" << endl;
    cout << "fond: #features=" << fond->num_features() << ", #actions=" << fond->num_actions() << endl;
    //cout << *fond;

    // dump PDDL domain
    ofstream ofs_d(prefix + "_d.pddl");
    fond->PDDL_dump_domain(ofs_d);
    ofs_d.close();

    // dump PDDL problem
    ofstream ofs_p(prefix + "_p.pddl");
    fond->PDDL_dump_problem(ofs_p);
    ofs_p.close();

    delete fond;
    delete tr;
    delete qnp;
    return 0;
}

