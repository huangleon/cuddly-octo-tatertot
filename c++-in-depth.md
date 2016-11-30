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
