# matrix-toolkit

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
