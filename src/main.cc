#include <iostream>
#include <fstream>
#include <string>

#include "translation.h"

using namespace std;

bool use_direct_translation(const Reductions::QNP &qnp) {
    return qnp.incremented_features().empty();
}

void usage(ostream &os, const string &name) {
    os << "usage: " << name << " [--bits-per-counter <n>] [--disable-optimizations] [--force-direct] [--help] [--stack-depth <m>] <qnp-file> <prefix>" << endl
       << endl
       << "where <qnp-file> is path to file containing qnp to be translated and <prefix> is used" << endl
       << "to form the names of generated files. The default value for number of bits per counter" <<endl
       << "is the number of variables in the problem, and for the stack depth is the number of" << endl
       << "numerical variables in the problem. For the options:" << endl
       << endl
       << "    --bits-per-counter <n>     to override with <n> the default value for number of bits per counter" << endl
       << "    --disable-optimizations    to disable all optimizations and use the full translation" << endl
       << "    --force-direct             to do a direct translation (most probably incorrect)" << endl
       << "    --help                     to print this help and exit" << endl
       << "    --stack-depth <m>          to override with <m> the default value for stack depth" << endl
       << endl;
}

void insufficient_arguments(ostream &os, const string &name) {
    os << Utils::error() << "insufficient arguments" << endl << endl;
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
    int stack_depth = -1;
    int num_bits_per_counter = -1;
    bool opt_force_direct = false;
    bool opt_disable_optimizations = false;
    for( ++argv, --argc; (argc > 0) && (**argv == '-'); ++argv, --argc ) {
        if( string(*argv) == "--bits-per-counter" ) {
            ++argv;
            --argc;
            if( argc == 0 ) insufficient_arguments(cout, executable_name);
            num_bits_per_counter = atoi(*argv);
        } else if( string(*argv) == "--disable-optimizations" ) {
            opt_disable_optimizations = true;
        } else if( string(*argv) == "--force-direct" ) {
            opt_force_direct = true;
        } else if( string(*argv) == "--help" ) {
            usage(cout, executable_name);
            exit(0);
        } else if( string(*argv) == "--stack-depth" ) {
            ++argv;
            --argc;
            if( argc == 0 ) insufficient_arguments(cout, executable_name);
            stack_depth = atoi(*argv);
        } else {
            cout << Utils::error() << "unreconized option '" << *argv << "'" << endl;
            exit(-1);
        }
    }

    // read arguments
    if( argc == 0 ) insufficient_arguments(cout, executable_name);
    string qnp_fname = *argv++;
    --argc;

    if( argc == 0 ) insufficient_arguments(cout, executable_name);
    string prefix = *argv++;
    --argc;

    // read QNP
    ifstream ifs(qnp_fname);
    if( ifs.fail() ) {
        cout << "error: cannot open " << qnp_fname << endl;
        exit(0);
    }
    Reductions::QNP *qnp = Reductions::QNP::read(ifs);
    ifs.close();

    if( !qnp->check(cout) ) exit(0);
    cout << "qnp: #features=" << qnp->num_features()
         << ", #numeric=" << qnp->num_numeric_features()
         << ", #boolean=" << qnp->num_boolean_features()
         << ", #actions=" << qnp->num_actions()
         << endl;
    //cout << *qnp;

    // set values for translation parameters
    if( num_bits_per_counter < 0 ) {
        num_bits_per_counter = 1 + qnp->num_features();
        cout << "info: num-bits-per-counter set to " << num_bits_per_counter << endl;
    }
    if( stack_depth <= 0 ) {
        stack_depth = 1 + qnp->num_numeric_features();
        cout << "info: stack-depth set to " << stack_depth << endl;
    }

    // select translation type
    Reductions::Translations::Translation *tr = nullptr;
    if( opt_force_direct || (!opt_disable_optimizations && use_direct_translation(*qnp)) ) {
        cout << "using direct translation..." << endl;
        tr = new Reductions::Translations::Direct();
    } else {
        cout << "using full translation..." << endl;
        tr = new Reductions::Translations::Complete(num_bits_per_counter, stack_depth, opt_disable_optimizations);
    }

    // do translation
    Reductions::FOND *fond = tr->translate(*qnp);
    Reductions::Translations::Statistics stats = tr->stats();
    cout << "translation: time=" << stats.time_in_seconds_ << endl;
    cout << "translation: stats.extra(#stack-features,#counter-features,#push-actions,#pop-actions,#move-actions)=[";
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

