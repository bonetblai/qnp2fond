# Translator from QNPs to FOND: Qualitative Numeric Planning to Fully Observable Non-Deterministic Planning


# QNP Format

QNP problems are stored in files with .qnp extension in QNP format.
The file begins with a line containing the name of the QNP. The
following line contains the features used: an initial integer
counts the number of features, followed by a list of pairs
where the first component is the name of the feature and the
second indicates whether the feature is numeric or boolean.

For example, the file ```examples/blocks04.qnp``` begins with



