Algorithms, 3 features:
    1. Finite.
    2. Deterministic.
    3. Effective

Recursion:
    1. Has base case
    2. Address subproblems *smaller*.
    3. Address subproblems not overlapped.

Definition of division and remainder:
a / b, a % b
Quotient a / b rounds toward 0;
Remainder a % b defined such that (a / b) * b + a % b is always equal to a.
(Watch out for negative integer):
-14 % 3 is -2
14 % -3 is 2

Hallmark of object-oriented programming: Encapsulation, encapsulate everything(data types/method) within implementation.

Autoboxing, Autounboxing:
Java provides mechanism of conversion between reference and its corresponding primitive types:
Integer/int, Long/long...

Scientific Method
1. Observe
2. Hypothesize a model
3. Predict events using the hypothesis
4. Verify predictions by making further observation
5. Validate by repeating until the hypothesis and observations agree.

Useful approximations for the analysis of algorithms

<!-- H_{N}=1+\frac{1}{2}+\frac{1}{3}+\frac{1}{4}+\cdots +\frac{1}{N}\sim \ln N -->
<!-- 1+2+3+4+\cdots +N\sim \frac{N^{2}}{2} -->
<!-- 1+2+4+8+\cdots +N=2N-1\sim 2N \; when N=2^{n} -->
<!-- \lg N!=\lg 1+ \lg 2+ \lg 3 + \lg 4 + \cdots + \lg N \sim N\lg N -->
<!-- \binom{N}{k} \sim \frac{N^{k}}{k!} \; when\; k\; is\; a\; small\; constant -->
<!-- \left(1-\frac{1}{x} \right )^{x}\sim \frac{1}{\mathrm{e}} -->
description|approximation
----|----
harmonic sum|![harmonic sum](http://latex.codecogs.com/svg.latex?H_%7BN%7D=1+%5Cfrac%7B1%7D%7B2%7D+%5Cfrac%7B1%7D%7B3%7D+%5Cfrac%7B1%7D%7B4%7D+%5Ccdots%20+%5Cfrac%7B1%7D%7BN%7D%5Csim%20%5Cln%20N)
triangular sum|![triangular sum](http://latex.codecogs.com/svg.latex?1+2+3+4+%5Ccdots%20+N%5Csim%20%5Cfrac%7BN%5E%7B2%7D%7D%7B2%7D)
geometric sum|![geometric sum](http://latex.codecogs.com/svg.latex?1+2+4+8+%5Ccdots%20+N=2N-1%5Csim%202N%20%5C;%20when%20N=2%5E%7Bn%7D)
Stirling's approximation|![Stirling's approximation](http://latex.codecogs.com/svg.latex?%5Clg%20N!=%5Clg%201+%20%5Clg%202+%20%5Clg%203%20+%20%5Clg%204%20+%20%5Ccdots%20+%20%5Clg%20N%20%5Csim%20N%5Clg%20N)
binomial coefficients|![binomial coefficients](http://latex.codecogs.com/svg.latex?%5Cbinom%7BN%7D%7Bk%7D%20%5Csim%20%5Cfrac%7BN%5E%7Bk%7D%7D%7Bk!%7D%20%5C;%20when%5C;%20k%5C;%20is%5C;%20a%5C;%20small%5C;%20constant)
exponential|![exponential](http://latex.codecogs.com/svg.latex?%5Cleft(1-%5Cfrac%7B1%7D%7Bx%7D%20%5Cright%20)%5E%7Bx%7D%5Csim%20%5Cfrac%7B1%7D%7B%5Cmathrm%7Be%7D%7D)






