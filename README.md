# clean-ranges

A batteries-included functional C++ library for collections and ranges.


## Generalized function object

Many operations on ranges support a _generalized_ notion of function that can be passed.
For example, `cr::sum(my_range, f)` supports the following for `f`:

* free functions (e.g. `int f(int x) { return x + 1; }`), calls `f(e)` per element
* lambdas (e.g. `auto f = [](int x) { return x + 1; }`), calls `f(e)` per element
* function objects (e.g. `foo f` with `int foo::operator()(int x) { return x + 1; }`), calls `f(e)` per element
* pointer-to-member (e.g. `auto f = &foo::x` with `struct foo { int x; };`), evaluates `e.*f` per element
* pointer-to-member-function (e.g. `auto f = &foo::bar` with `struct foo { int bar() { return x + 1;} };`), calls `(e.*f)()` per element

NOTE: pointer-to-members (and -functions) do not only work on values or references:

* for values and references, uses `e.*f`
* for pointers, uses `e->*f`
* for smart pointers, uses `(*e).*f`

(implementation detail: actually just uses `e.*f` or `(*e).*f` depending on which one would compile)


## TODO

Algorithms:

* n_th / n_th_last (how?)
* drop_first / _last / drop_while
* at / at_or / at_opt
* mean / average
* median
* mode
* percentile
* map (with index support)
* indexed
* find / find_or / find_opt
* flatten
* where (index support)
* ordered_by / sort (inplace)
* zip / unzip
* windowed / chunked / pairwise
* reverse
* collect / to / into
* apply / transform / each (with index support)
* unique / distinct
* group_by
* join_to / join_to_string
* partition (pred -> left and right result)
* shuffled
* associate (creates a map)
* comparisons

Built-in ranges:

* from-to
* infinite ranges
* iterator pairs
* from function

Optimizations:

* random access / reverse its for faster reverse
* _last versions can be faster with random access / reverse its
* O(1) size

QoL:

* support indices in call
* xyz vs xyz'ed versions (e.g. sort vs sorted, reverse vs reversed)

Extensibility:

* CRTP range + inheritance
