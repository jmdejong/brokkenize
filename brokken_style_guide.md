## General

### Don't write too long lines

- Brokken is not very clear what is 'too long', but a rule-of-thumb might be 80 characters.

### BABO: Blanks around Binary Operators

BAD: `1+2`, `x+=3`
GOOD: `1 + 2`, `x += 3`

Not needed with the binary operator `.`.


## Comments

- In-line comments should not be verbose.
- Describe in in-line comments _why_ it happens, (not _what_ happens, as the code statement already shows this.)


## Keywords & Control

### Add a space between keywords and following condition
BAD:

```
if(x == 10)
{
  //...
}
```

GOOD:

```
if (z == 10)
{
  // ...
}
```

### No {} around single statement bodies of `if`, `else`, `for`, `while`, etc.
BAD:

```
if(x)
{
  return ++x;
}
else
{
  return x;
}
```

GOOD:

```
if(x)
  return ++x;
else
  return x;
```


### Align Break and Case
BAD:
```
  case statement:
    // ...
    break;
```
GOOD:
```
  case statement:
    // ...
  break;
```


## Variables & Identifiers

### Pointers before _names_.
BAD: `char** argv;`
GOOD: `char **argv;`

### No Single

## Functions

### One space after a comma

BAD: `int foo(int bar,bool baz  , float qux)`
GOOD: `int foo(int bar, bool baz, float qux)`

## Classes

### ICI: Don't write in-class implementations
???

## Interfaces

### IBI: Define inline members below interfaces

???
