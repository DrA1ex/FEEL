Fast Expression Evaluator Library (c++, .net)
====

With this library you can evaluate math expressions fast and easily.
See Demo project for examples.

Features:
---

1. Easy extensible (you can add more operations if you want)
2. Fast (expression **compiling** into **native code**)
3. Powerful (you can use variables and change it without side effects)


At this point Expression Evaluator supports only Windows platform. 

Compile isn't perfect now, but more faster, than generic solution.

Some benchmarks:
---

```
Expression:     "(cos(x)^0.5*cos(200*x)+abs(x)^0.5-0.7)*(4-x^2)^0.01"
Start value:    -1.6
End value:      1.6
Steps:          10000000 (10m)

.NET Benchmark results:
Library name            Avg. time
FEEL (this library):    3255ms
Ciloci.Flee:            3818ms (~20% slower)
NCalc:                  27402ms (~741% slower)

C# compiled code:       3336ms (~2$ slower)

C++ Benchmark results:
Library name            Avg. time
FEEL (this library):    1943ms
ExprEval:               3253ms (~67% slower)

C++ compiled code:      1120ms (~40% faster)
```
