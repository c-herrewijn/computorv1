A CODAM project in C++ to create a solver for 2nd order polynomial equations.

### bulid
```
make
```

### example
```sh
./computor "2*X^2 + 2*X = 12"
```

output:
```
Standard reduced form:
-12 * X^0 + 2 * X^1 + 2 * X^2 = 0

Polynomial degree: 2
Solving ...

step 1:
Standard simplified form:
2 * X^2 + 2*X - 12 = 0

step 2: determine A, B and C using ABC-formula:
A*X^2 + B*X + C = 0
A = 2
B = 2
C = -12

step 3: calculate 'Discriminant'
Discriminant = B^2 - 4 * A * C
Discriminant = 2^2 - 4 * 2 * -12
Discriminant = 4 - -96
Discriminant = 100

step 4: general solution formula for discriminant > 0:
two solutions:
  X = (-1 * B + sqrt(discriminant)) / (2 * A)
or:
  X = (-1 * B - sqrt(discriminant)) / (2 * A)
substituting A and B:
solution 1:
  X = (-1 * 2 + sqrt(100)) / (2 * 2)
  X = (-2 + 10) / 4
  X = 8 / 4
  X = 2
solution 2:
  X = (-1 * 2 - sqrt(100)) / (2 * 2)
  X = (-2 - 10) / 4
  X = -12 / 4
  X = -3
```
