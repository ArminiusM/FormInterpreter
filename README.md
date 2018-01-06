# FormInterpreter

FormInterpreter is a c\+\+ class to interpret formulas stored in a text string.

FormInterpreter is compiled using GNU compiler g\+\+ version 4.4.3 using the \-std=c\+\+0x
option. If your compiler does not support C\+\+11 it will not compile the code.
To create the library, go to the directory containing the code and type

> make libFormInterpreter.a

After creating the library, create the test program by typing

> make test

and start it by typing

> ./test

The output should end with the line

```
---------------------
| All tests passed! |
---------------------
```
