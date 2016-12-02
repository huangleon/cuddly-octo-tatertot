#Reading notes about "C++ In-Depth Series"

###Simplified Overload Resolution:
* Perfect Match
* Match with minor adjustments
* Match with promotion
* Match with standard conversions only
* Match with user-defined conversions
* Match with ellipsis

Overload resolution occurs **after** template argument deduction.

###Refining the Perfect Match
* `T` and `T const&` both match equally well for an **rvalue** of type T.
* `T` and `T&` both match equally well for a **lvalue** of type T.

###Surrogate functions in C++
[Reference](http://stackoverflow.com/questions/11354737/how-does-surrogate-call-function-work)
```
template <typename Fcn1, typename Fcn2>
class Surrogate {
public:
    Surrogate(Fcn1 *f1, Fcn2 *f2) : f1_(f1), f2_(f2) {}

    // Overloaded operators.
    // But what does this do? What kind of operators are they?
    operator Fcn1*() { return f1_; }
    operator Fcn2*() { return f2_; }

private:
    Fcn1 *f1_;
    Fcn2 *f2_;
};

void foo (int i)
{
    std::cout << "foo: " << i << std::endl;
}

void bar (double i)
{
    std::cout << "bar: " << i << std::endl;
}

int main ()
{
    Surrogate<void(int), void(double)> callable(foo, bar);

    callable(10);       // calls foo, implicit conversion to Fcn1*, then call f1_
    callable(10.1);     // calls bar, implicit conversion to Fcn2*, then call f2_

    return 0;
}
```
