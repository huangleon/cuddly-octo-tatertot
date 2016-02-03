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

description|approximation
----|----
test|![](http://latex.codecogs.com/svg.latex?H_{N}=1+\frac{1}{2}+\frac{1}{3}+\frac{1}{4}+\cdots +\frac{1}{N}\sim \ln N)
harmonic sum|<img src="http://latex.codecogs.com/svg.latex?H_{N}=1+\frac{1}{2}+\frac{1}{3}+\frac{1}{4}+\cdots +\frac{1}{N}\sim \ln N" border="0"/>
triangular sum|<img src="http://latex.codecogs.com/svg.latex?1+2+3+4+\cdots +N\sim \frac{N^{2}}{2}" border="0"/>
geometric sum|<img src="http://latex.codecogs.com/svg.latex?1+2+4+8+\cdots +N=2N-1\sim 2N \; when N=2^{n}" border="0"/>
Stirling's approximation|<img src="http://latex.codecogs.com/svg.latex?\lg N!=\lg 1+ \lg 2+ \lg 3 + \lg 4 + \cdots + \lg N \sim N\lg N" border="0"/>
binomial coefficients|<img src="http://latex.codecogs.com/svg.latex?\binom{N}{k} \sim \frac{N^{k}}{k!} \; when\; k\; is\; a\; small\; constant" border="0"/>
exponential|<img src="http://latex.codecogs.com/svg.latex?\left(1-\frac{1}{x} \right )^{x}\sim \frac{1}{\mathrm{e}}" border="0"/>






