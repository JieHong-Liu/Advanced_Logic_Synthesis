# State Assignment

Implement a state assignment algorithm for Finite State Machine.
+ Minimum power dissipation 

## How to compile

In `HW3/`, enter the following command:

```
$make

```
An executable file sa will be generated in `HW3/bin/`.

If you want to remove it, please enter the following command:

```
$ make clean
```

## How to Run
Usage:
```
$ ./bin/sa  <input kiss file> <output blif file>
```

E.g.,
```
$ ./bin/sa ./resource/benchmarks/bbara_opt.kiss ./outputBLIF/bbara_opt.blif
```

## How to Test
In `HW3/`, enter the following command:

```
$ make test $name
```

It will build an executable file and test on testcase $name with k=$k.

E.g., test on s27_opt

```
$ make test s27_opt
```

It will build an executable file and test on testcase (here is s27_opt.kiss), and it will print the result of my optimization result and SIS optimization result.

