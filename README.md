# Translator from QNPs to FOND: Qualitative Numeric Planning to Fully Observable Non-Deterministic Planning


## QNP Format

QNP problems are stored in files with .qnp extension in QNP format.
The file begins with a line containing the name of the QNP. The
following line contains the features used: an initial integer
counts the number of features, followed by a list of pairs
where the first component is the name of the feature and the
second indicates whether the feature is numeric or boolean.

For example, the file ```examples/blocks04.qnp``` begins with

``
blocks-clear-x
5 nabove(A) 1 nother(A) 1 hold(A) 0 hold-other(A) 0 some-below(A) 0
``

indicating that the QNP consists of 5 features: two numerical
features ```nabove(A)``` and ```nother(A)```, and three boolean
features ```hold(A)```, ```hold-other(A)```, and ```some-below(A)```.

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



