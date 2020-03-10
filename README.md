# clean-ranges

A batteries-included functional C++ library for collections and ranges.


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
* index_of / index_of_first / index_of_last
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

Built-in ranges:

* from-to
* infinite ranges
* iterator pairs
* from function

Optimizations:

* random access / reverse its for faster reverse
* O(1) size

QoL:

* support indices in call
* call support pointer-to-member(-fun) for smart pointers

Extensibility:

* CRTP range + inheritance
