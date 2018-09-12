# Translator from QNPs to FOND: Qualitative Numeric Planning to Fully Observable Non-Deterministic Planning

The translator is invoked using

```
qnp2fond <qnp-file> <counter-capacity> <loop-nesting> <prefix>
```

where the first argument is the name of a .qnp file (see below), 
the two additional arguments are non-negative integers, typicall
small ones such as 0, 1 or 2, and the last argument is the prefix
for the generated files (domain and problem files).


## QNP Format

QNP problems are stored in files with .qnp extension in QNP format.
The file begins with a line containing the name of the QNP. The
following line contains the list of used features: an initial integer
counts the number of features, followed by a list of pairs
where the first component is the name of the feature and the
second indicates whether the feature is numeric or boolean.

For example, the file ```examples/blocks04.qnp``` begins with

```
blocks-clear-x
5 nabove(A) 1 nother(A) 1 hold(A) 0 hold-other(A) 0 some-below(A) 0
```

indicating that the QNP consists of 5 features: two numerical
features ```nabove(A)``` and ```nother(A)```, and three boolean
features ```hold(A)```, ```hold-other(A)```, and ```some-below(A)```.

The following two lines contain the description of the initial and
goal situations respectively. Both are described in a similar way.

A first integer tells the number of conditions. Each condition
corresponds to a pair of items: the first is the name of the
feature and the second denotes the condition on the feature:
0 for the feature being equal to zero or false for numerical
or boolean features respectively, and 1 for the feature being
bigger than zero or true for numerical or boolean features
respectively.

The initial and goal situation in the example are

```
4 nabove(A) 1 hold(A) 0 hold-other(A) 0 some-below(A) 1
3 nabove(A) 0 hold(A) 0 hold-other(A) 0
```

Thus, in the initial situation the numeric variables ``nabove(a)`` 
and ``nother(A)`` have values bigger than zero and zero respectively,
the boolean fluents ``hold(A)`` and ``hold-other(A)`` are both
false, and the boolean fluent ``some-below(A)`` is true.
Likewise, in the goal situation, the numeric variable ``nabove(A)``
is zero, and the boolean fluents ``hold(A)`` and ``hold-other(A)``
are both false.

The rest of the file contains the description of the actions.

A first integer indicates the number of actions in the file.
Each action is described with three lines: the first is the
name of the action, the second gives the preconditions of the
action, and the third line gives the effects of the action.

The first item in the precondition is the number of conditions.
Each condition then corresponds to a pair of items, the first
the name of the feature and the second the condition on such
a feature: 0 for the feature being equal to zero or false
for numerical or boolean features respectively, and 1 for
the feature being bigger than zero or true for numerical
or boolean features respectively.

The effects are described in a similar way. The first item
tells the number of effects. Then, for each effect, the
name of the affected feature is given together with the
effect on the feature: 0 if the feature is decremented
or set to false for numerical or boolean features respectively,
and 1 if the feature is incremented or set to true for
numerical or boolean features respectively.

For example, the file ```examples/blocks04.qnp``` contains:

```
Pick-x-some-below
4 nabove(A) 0 hold(A) 0 hold-other(A) 0 some-below(A) 1
3 nother(A) 1 hold(A) 1 some-below(A) 0
```



