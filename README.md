# A learning project in the C programming language. A console program for drawing a graph of a function based on the entered expression. The Linux platform.

## Building and running

Building
```
make build
```

Running
```
./build/graph
```

Run tests, it also checks for memory leaks
```
make tests
```

Code coverage
```
make gcov_report
```

## Description
After launching, the program prompts you to enter a mathematical expression. After entering the corresponding graph is displayed in the console.

### Graph Parameters

The size of the field for displaying graphs is a rectangle of 25 by 80 points.

Definition area - [0; 4 Pi]

Range of values - [-1; 1]

Orientation of the coordinate plane - the ordinate axis is directed downward, the abscissa axis is directed to the right.

The center of coordinates is middle of the left border (point {0, 13}).

Nothing but the graph is displayed

The field is displayed with a Star symbol for the chart line and "." for the rest of the screen space.

## Possible operations & functions
> "+" \
> "-" (unary and binary) \
> "*" \
> "/" \
> "()" \
> sin(x) \
> cos(x) \
> tan(x) \
> ctg(x) \
> sqrt(x) \
> ln(x)
