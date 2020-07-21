# Translator from QNPs to FOND: Qualitative Numeric Planning to Fully Observable Non-Deterministic Planning

The translator is invoked using

```
qnp2fond <qnp-file> <prefix>
```

where the first argument is the name of a .qnp file (see below)
and the second argument is the prefix for the generated files 
(PDDL domain and problem files). A number of options is supported 
that can be inspected with ``qnp2fond --help``.

The source code of ``qnp2fond`` is in the folder ``src`` together with a makefile for building it.
The program is simple and there should be no issues when compiling it. Some examples can be
found in ``examples``, the examples used in the paper about QNPs are in ``examples/qnp-paper``.
Other examples are included in ``examples/other``.

Feel free to use the translator and let us know of any bug or comment.
We are interested in applications for QNPs.

To reference the translator and QNPs, you can use:

- Blai Bonet and Hector Geffner. *Qualitative Numeric Planning: Reductions and Complexity*. Journal of Artificial Intelligence Research (JAIR). Forthcoming. 2020.


## QNP Format

QNP problems are stored in files with .qnp extension in QNP format.
The file begins with a line that has the name of the QNP. The
following line has the list of used features: an initial integer
counts the number of features, followed by a list of pairs
where the first component in the pair is the name of the feature and the
second component is 0 or 1 to indicate whether the feature is numeric or boolean.

For example, the file ```examples/qnp-paper/blocks_clear/blocks_clear.qnp``` begins with

```
blocks-clear
2 n 1 holding 0
```

indicating that the QNP consists of 2 features: a numerical
feature ```n``` and one boolean feature ```holding```.

The following two lines contain the description of the initial and
goal situations respectively. Both are described in a similar way,
yet the second component in a pair indicates whether the boolean
valuation of the feature is true or false. That is, for boolean
features the second component, 0 or 1, tells whether the feature
is true, and for numerical features, the second component tells
whether the feature is equal to 0 or greater than 0 using 0 or 1
respectively.

This notation is also used to specify preconditions of actions,
and also to specify effects. In the latter case, a pair (f,0)
indicates that the feature f becomes false or decrements whether
f is boolean or numerical respectively. Likewise, a pair (f,1)
indicates that the feature becomes true or increments.

The initial and goal situation in the example are

```
2 n 1 holding 0
1 n 0
```

Thus, in the initial situation the numeric variables ``n`` is bigger
than zero, and the boolean ``holding`` is false. The goal, on the
other hand, is just to reach a state where ``n`` is zero.

The rest of the file contains the description of the actions.

A first integer indicates the number of actions in the file.
Each action is described with three lines: the first is the
name of the action, the second gives the preconditions of the
action, and the third line gives the effects of the action.

The first item in the precondition is the number of conditions.
Each condition then corresponds to a pair of items as described above.

The effects are described in a similar way. The first item
tells the number of effects, followed by a list of pairs.

For example, the file ```examples/qnp-paper/blocks_clear/blocks_clear.qnp``` contains:

```
Pick-above-x
2 n 1 holding 0
2 n 0 holding 1
```

which is an abstraction of any action that picks a block above block x.
Indeed, the precondition for such an action is that no block is being held and
there are some blocks above x, and the effect is to set ``holding`` to true
and decrement the number of blocks above x, i.e., the feature ``n``.




