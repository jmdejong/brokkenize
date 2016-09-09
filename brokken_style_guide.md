# Disclaimer:


This styleguide is based on:

- Brokken's [list of Abbreviations you don't want to receive](https://www.icce.rug.nl/edu/1/abbreviations.shtml).
- Brokken's [General Hints, Tips and Tricks](https://www.icce.rug.nl/edu/1/hints.shtml).
- The slideshows of Brokken's C++ guide.
- the C++ Annotations book, version 10.5.1

Use this styleguide at your own risk. The information that this styleguide was created from is in constant flux. Furthermore, the original information might have been mis-interpreted. Also, Brokken is a complex person. His opinions may change over time. 

Please submit pull requests or open issues when you see something that is missing, unclear or wrong with the styleguide.

# Guide:

## General

### Don't write too long lines

- Brokken is not very clear what is 'too long', but a rule-of-thumb might be 80 characters.

### BABO: Blanks around Binary Operators

BAD: `1+2`, `x+=3`

GOOD: `1 + 2`, `x += 3`

(With the binary operator `.`, no spaces should be used, e.g. `foo.bar`.)

### NMN: No Magic Numbers

- Create a `const` for a number if that number has some meaning. (e.g. `const alphabetSize = 26`)
- Create an Enum if there are multiple possible numbers. The actual number values should _not_ be hard-coded, because it looks to a user of your code like a number might be substituted for any other number.

### PP: Prefer Prefix

- Use `++x` instead of `x++` whenever possible. (The same for `--x` vs `x--`).

This is because this instruction is quicker to execute.

### GODO: NEVER use `goto`

If you ever use `goto`, you will be hunt and killed.

### PO: Premature Optimization

Premature Optimization is the root of all evil:
Do not try to think for the compiler.

Try to write _readable_ code instead.

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

## Loops

### Use `for` for known numbers of iterations

- such as when looping over a list or other collection.

### Use `while` if you don't know the number of iterations.

### Use the canonical for-variants whenever possible:



## Variables & Identifiers

### Use readable names

- 
  - BAD: `i` **even for for-loop iterators!**
  - GOOD: `index`.
- VI: Avoid Verbose Identifiers
  - BAD: `aLongStringWhichContainsOnlyLetters`. 
  - GOOD: `letters`.

### Pointers before _names_.
BAD: `char** argv;`

GOOD: `char **argv;`

### Limit scope of variables as much as possible

- Define variables only when you need them (not before).


## Functions

### One space after a comma

BAD: `int foo(int bar,bool baz  , float qux)`

GOOD: `int foo(int bar, bool baz, float qux)`

### RBA: Return By Argument

- Put output-pointers before inputs in function heads:

BAD:
`void add_to_string(int number, char* output)`

GOOD:
`void add_to_string(char* output, int number)`

## Classes

### ICI: Don't write in-class implementations
???

## Interfaces

### IBI: Define inline members below interfaces

???
