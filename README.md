# matrix-toolkit
## Installation & Start-up
To install, you can download all source files by `git clone https://github.com/Sibelius-6/matrix-toolkit/` then create an excutable by `make`.

`Makefile` has created an excutable called `matrix`. Run this executable by `./matrix`, then type command `help` to see the following usage.

For the full usage and examples, please consult [here](https://sibelius-6.github.io/projects/matrix-toolkit/).

## Prerequisites
If you have taken first (math 136) and second (math 235) linear algebra courses, you should be fine.
### left & right inverse
* A right inverse of a non-square matrix A exists, provided A has full row rank.
* A left inverse of a non-square matrix A exists, provided A has full column rank.

[full rank defn](https://www.cds.caltech.edu/~murray/amwiki/index.php/FAQ:_What_does_it_mean_for_a_non-square_matrix_to_be_full_rank%3F)

## Other Sources

### Eigen
For eigenvalues and eigenvectors calculation, it's hard to apply the technique we learned in linear algebra (charateristic polynomial). There are some good algorithms to use, like [Jacobi_eigenvalue_algorithm](https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm), which could be implemented. For simplicity, I adopted one C++ library. 

The descriptions can be found [here](http://eigen.tuxfamily.org/index.php?title=Main_Page). To install it, 
`
hg clone https://bitbucket.org/eigen/eigen/
` . In order to succuessfuly compile (make), please be at the same directory as the whole source files. 

The documentation and tutorial can be found [here](http://eigen.tuxfamily.org/dox/index.html). 

### RREF
I have adopted the algorithms from [here](http://rosettacode.org/wiki/Reduced_row_echelon_form#C.2B.2B)

### determinant
[Algorithms](https://www.tutorialspoint.com/cplusplus-program-to-compute-determinant-of-a-matrix)
