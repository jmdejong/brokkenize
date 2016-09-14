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

### Compile using `-Wall`

- This ensures that you see all warnings. Submitted code should never emit any warnings.

### Use dromedarisCase for identifiers

- so `int someValue = 10;` and `int fooBarBaz()`. 

### Use CamelCase for (self-declared) types.

BAD:

```C++
enum class states {OK, FAIL}
```

GOOD:

```C++
enum class States {OK, FAIL}
```


### Use CAPITALS for symbolic enum constants.

BAD:

```C++
enum class States {ok, fail}
```

GOOD:

```C++
enum class States {OK, FAIL}
```

### Use enum class-types over integer-mapped constants whenever possible.

BAD:

```C++
enum States {OK, FAIL}
int foo = OK; //note that the word OK now always (implicitly!) refers to the States value.
```

GOOD: 

```C++
enum class States {OK, FAIL}
int foo = States::OK; //note that the word OK now is nested in a namespace.
```

The only exception to this rule is when you actually need to do arithmetic with the integer values of your enums.
This itself should only happen really rarely (in practice, only when using bit flags).

### Put `const` immediatly _after_ the thing (type, pointer) that should become constant

BAD:

```C++
const int *fooBar;
```

GOOD: (makes it impossible to change contents of `baz` through this pointer; allows changing what `fooBar` points to)

```C++
int const *fooBar = baz;
```

GOOD: (makes it impossible to change what `fooBar` points to; allows changing contents of `baz`)

```C++
int *const fooBar = baz;
```

_(See C++ annotations cf. 3.1 for more info)_


### Don't write too long lines

- Brokken is not very clear what is 'too long', but a rule-of-thumb might be 80 characters.

Don't auto-wrap lines; these won't compile when entered as-is in a compiler. 
Instead, split your line into shorter lines, or use `\` to continue a long string on the next line.

_Tip: Make your monospace font pointsize smaller, so more source code fits on a line._


### BABO: Blanks around Binary Operators

BAD: `1+2`, `x+=3`

GOOD: `1 + 2`, `x += 3`

(With the binary operator `.`, no spaces should be used, e.g. `foo.bar`.)

### No spaces in `static_cast<type>` et al.

BAD:

```C++
static_cast<size_t> (x)
static_cast <size_t>(x)
static_cast <size_t> (x)
```

GOOD:

```C++
static_cast<size_t>(x)
```

### NMN: No Magic Numbers

- Create a `const` for a number if that number has some meaning. (e.g. `const alphabetSize = 26`)
- Create an Enum if there are multiple possible numbers. The actual number values should _not_ be hard-coded, because it looks to a user of your code like a number might be substituted for any other number:
  - BAD: 
  ```C++
  processString(string, 0);
  processString(string, 1);

  processString(string, 80);  // Huh?
  ```
  - GOOD:
  ```C++
  processString(string, StringProcessing::NORMAL);
  processString(string, StringProcessing::CASE_INSENSITIVE);
  ```

### PP: Prefer Prefix Increment/Decrement

- Use `++x` instead of `x++` whenever possible. (The same for `--x` vs `x--`).

This is because this instruction is significantly quicker to execute, because no extra intermediate assignment is necessary.

### GOTO: NEVER use `goto`

- If you ever use `goto`, you will be hunt and killed.

### Macros: Don't use them

- Most things that in C is done with macros can be done with templates in C++. Use those instead, whenever possible.
- Don't use `#define`, etc.

One exception is `#include <header_file>`, which is of high importance to writing segmented programs. 

The second exception are _include guards_, which make sure that an `#include` statement is only executed once, even if your file is (indirectly) included multiple times in another file. Example:

```C++
#ifndef YOUR_FILE_NAME
#define YOUR_FILE_NAME
class A { int a; };
#endif
```  

### PO: Premature Optimization

- Premature Optimization is the root of all evil:
  - Do not try to think for the compiler.
  -Try to write _readable_ code instead.

## Comments

- In-line comments should not be verbose.
- Describe in in-line comments _why_ it happens, (not _what_ happens, as the code statement already shows this.)
- When having multiple in-line comments, align them vertically, so at the right side of your functions you can see what happens in a pseudo-description.

## Keywords & Control

### Add a space between keywords and following condition
BAD:

```C++
if(x == 10)
{
  //...
}
```

GOOD:

```C++
if (z == 10)
{
  // ...
}
```

### No {} around single statement bodies of `if`, `else`, `for`, `while`, etc.
BAD:

```C++
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

```C++
if(x)
  return ++x;
else
  return x;
```


### Align Break and Case
BAD:

```C++
  case statement:
    // ...
    break;
  case anotherstatement:
    // ...
    break;
```

GOOD:

```C++
  case statement:
    // ...
  break;
  case anotherstatement:
    // ...
  break;
```

The same holds if the case-statement ends with `return`, `exit` or `throw`. (In those cases, align thát keyword with `case`)

### Separate groups of lines performing distinct parts of a function's purpose with a newline.

BAD:

```C++
    int main(int argc, char *argv[])
    {
        .....       // inspecting the arguments
        .....
        .....       // processing arguments
        .....
        .....
        .....       // doing something with the processed arguments
        .....
    }
```


GOOD: 

```C++
    int main(int argc, char *argv[])
    {
        .....       // inspecting the arguments
        .....

        .....       // processing arguments
        .....
        .....

        .....       // doing something with the processed arguments
        .....
    }
```

## Loops

### Use `for` for known numbers of iterations

- such as when looping over a list or other collection.

### Use `while` if you don't know the number of iterations.

### Use the canonical for-variants whenever possible:

#### Basic Incrementing for-loop:

```C++
for (size_t idx = 0; idx != end; ++idx)
{
    ...
}
```


#### Basic Decrementing for-loop:

```C++
for (size_t idx = end; idx--; )
{
    ...
}
```

### Use the canonical stream-processing `while` whenever possible:

```C++
while (true)
    {
    // optionally perform tasks before reading information

    // read information

    if (/* the reading fails (e.g., end of file was reached) */)
        break;

    // process the obtained information.
}
```

- When reading a whole stream or file, one of the following contractions is often possible:

```C++

while (getline(cin, string))
    // process the read information.
```

```C++
while (cin >> variable)
    // process the read information.
```

### Avoid statement repetition around `while`-loops:

BAD:

```C++
prompting();
while (obtainData())
{
    processData();
    prompting();            // statement repetition
}

```

GOOD:

```C++
while (true)
{
    prompting();
    if (not obtainData())
        break;
    processData();
}
```

### Use failure-first or shorter-first conditional structures:

BAD:

```C++
if (foo == 1)
{
    // ... a
    // ... lot
    // ... of
    // ... code
    // ... with
    // ... the
    // ... result
}
else
{
    // ... less code, or a failure where the function/loop is exited early.
}
```

You can [see here](https://gist.github.com/Qqwy/d0a276e1ac95bbcf329460d66e6f639d) what happens to the code readability, indentation and size when this nesting is done improperly multiple levels deep.

BOOD:

```C++
if (foo != 1)
{
    // ... less code, or a failure where the function/loop is exited early.
}

// ... a
// ... lot
// ... of
// ... code
// ... with
// ... the
// ... result

```

Notice that the failure stays together with its condition, and that there is no indentation necessary if multiple checks were to be added.

### Write in an if/else ladder, the `else if` on a single line

GOOD:

```C++
if (cond-1)
    statement-1;
else if (cond-2)
    statement-2;
else if (cond-3)
    statement-3
else
    statement-4

```

## Variables & Identifiers

### Use readable names

- SLV: Never use Single Letter Variables
  - BAD: `i` **even for `for`-loop iterators!**
  - GOOD: `index`.
- VI: Avoid Verbose Identifiers
  - BAD: `aLongStringWhichContainsOnlyLetters`. 
  - GOOD: `letters`.

### Pointers before _names_.
BAD: `char** argv;`

GOOD: `char **argv;`

### Limit scope of variables as much as possible

- Define variables only when you need them (not before).

### Define every variable on its own line

BAD:

```C++
int foo, bar, baz = 10;
```

GOOD:

```C++
int foo = 10;
int bar = 10;
int baz = 10;
```

This is to make it easy to remove a variable.

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

## Types

### Use `size_t` over `unsigned int` for positive integer values.

## Classes

### Prefix data member names with `d_`

BAD:

```C++
class Animal
{
    int width;
    int height;
    std::string name;
}
```

GOOD:

```C++
class Animal
{
    int d_width;
    int d_height;
    std::string d_name;
}
```

### Prefix manipulators ('setters') with `set`
BAD:

```C++
class Animal
{
    int Location(int x, int y)
}
```

ALSO BAD:

```C++
class Animal
{
    int goToLocation(int x, int y)
}
```

GOOD:

```C++
class Animal
{
    int setLocation(int x, int y)
}
```

### No prefix for accessors ('getters') (although prefixing with `get` is allowed)

BAD:

```C++
class Animal
{
    std::string whatIsTheName()
}
```

ACCEPTABLE:

```C++
class Animal
{
    std::string getName()
}
```

GOOD:

```C++
class Animal
{
    std::string name()
}
```


### ICI: Don't write in-class implementations
???

## Interfaces

### IBI: Define inline members below interfaces

???

## Input/Output

### Use _streams_ for Input/Output

- `std::cin >> yourVariable` for input. 
  - Note that this automatically casts values to the format of `yourVariable`, which is nice.
  - also note that this strips any whitespace (spaces, tabs, newlines) from the front of `std::cin` before putting something into `yourVariable`.
- `std::cout << yourVariable << "some other text"` for output.
  - Use syntax for a single char when only adding a single char:
    BAD: `std::cout << "\n";`
    GOOD: `std::cout << '\n'`. 
      - Using `"\n"` is slower, as this results in a null-terminated string being created first.
- avoid nontrivial computations inside `std::cout`, because these reduce readability.

### Avoid using `std::endl`

It also flushes the stream, and thefore is slow.
Usually, this is not needed. Use `'\n'` instead.

### Don't read a whole file at once:

Instead, read sections (lines, words, whatever makes sense for the task at hand), then process this section, and then read the next one.
This has far lower memory usage (i.e. constant, instead of depending on the file size).

## Strings

### use `std::string` over Null-Terminated Byte Strings (NTB strings, NTBS) whenever possible.

The reason is that `std::string` can handle strings that contain null-characters, while NTB strings cannot.

The same is true for functions. For instance, use `cppString.length()` over `strlen(cString)`.

### Use `int` over `char` whenever possible.
  
This is because `char` is an unsigned data type that will overflow on e.g. EOF.
Only use `char` (or `char *`) when working with true C Null-Terminated Byte Strings (NTBS), such as `argv` that is passed to `main(int argc, char* argv[])`.

### Use the index `[]` operator for strings when you know you will not go out of bounds.

In other words, only use `someString.at(int index)` when you expect that going out of bounds is highly possible.

