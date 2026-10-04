# Pure x86-64 Assembly C Compiler for Windows

A self-contained C compiler written entirely in **100% pure x86-64 assembly** for Windows. It compiles modern subset C source code directly into x86-64 assembly (`default rel`, Windows x64 ABI) that assembles and links with `gcc` (MinGW-w64).

---

## Features

- **Language Features**:
  - **Data Types**: `int` (64-bit integer), `char` (8-bit), `void`, pointers (`int*`, `char*`, multi-level `**`), arrays (`int arr[N]`), structs (`struct Tag { ... };`).
  - **Operators & Precedence**:
    - Arithmetic: `+`, `-`, `*`, `/`, `%`
    - Bitwise: `&`, `|`, `^`, `~`, `<<`, `>>`
    - Unary: prefix `++`, `--`, address-of `&`, dereference `*`, negation `-`, bitwise not `~`, logical not `!`
    - Postfix: `x++`, `x--`, array subscripting `arr[i]`, struct member access `s.m`, pointer member access `p->m`
    - Relational & Equality: `==`, `!=`, `<`, `<=`, `>`, `>=`
    - Short-Circuit Logical: `&&`, `||`
    - Conditional Operator: Ternary `condition ? true_expr : false_expr`
    - Assignments: Simple (`=`) and compound (`+=`, `-=`, `*=`, `/=`, `%=`, `&=`, `|=`, `^=`, `<<=`, `>>=`)
  - **Control Flow**:
    - `if` and `if-else` (both compound braced blocks and single statements)
    - `while` loops
    - `for` loops (with optional init, condition, and step expressions)
    - `do-while` loops
    - `switch`, `case <constant>:`, `default:`, with `break;` and intentional fallthrough
    - `break` and `continue` across nested loops and switches
    - `return` statements with optional expressions
  - **Structures**:
    - `struct` definitions with arbitrarily many typed members
    - Direct member access (`rect.width = 30;`)
    - Pointer member access (`ptr->width = 30;`)
    - Correct alignment and struct sizing
  - **Functions & ABI**:
    - Parameter passing adhering strictly to the **Windows x64 ABI** (`RCX`, `RDX`, `R8`, `R9`, shadow space, and stack spilling)
    - Stack alignment (16-byte aligned frames)
    - Recursive functions (e.g. recursive Factorial and Fibonacci)
    - Calling external C runtime functions (e.g., `printf`) via `extern`
  - **Literals**:
    - Integer constants (decimal, negative)
    - Character literals (`'a'`, `'\n'`)
    - String literals (`"Hello, World!\n"`) stored in the `.data` section

---

## Repository Structure

```
├── bin/
│   └── c_compiler.exe           # Prebuilt standalone compiler executable
├── src/
│   ├── defs.inc                 # Token types, limits, and structure constants
│   ├── main.asm                 # Entry point, CLI argument parsing, file I/O & data emission
│   ├── lexer.asm                # Full lexical analyzer (tokens, keywords, numbers, strings)
│   ├── parser.asm               # Recursive descent parser & statement/expression generator
│   ├── codegen.asm              # Low-level x86-64 instruction emitter
│   ├── symtab.asm               # Scoped symbol tables (globals, locals, strings, externs)
│   ├── types.asm                # Type system, struct table, member layout & size calculations
│   └── utils.asm                # String operations and memory utilities
├── tests/
│   ├── test01_return42.c        # Exit code 42
│   ├── test02_vars.c            # Arithmetic and local variable bindings
│   ├── test03_recursion.c       # Recursive factorial (5! = 120) with ABI parameter spilling
│   ├── test04_loops.c           # while, for, do-while, break, continue
│   ├── test05_switch.c          # switch, case, default, break, fallthrough
│   ├── test06_pointers.c        # Address-of, dereference, pointer mutation & aliasing
│   ├── test07_arrays.c          # Local array indexing, reads, writes, and compound updates
│   ├── test08_globals.c         # Initialized global variables and global arrays
│   ├── test09_structs.c         # Struct definitions, s.m, p->m, and struct mutation
│   ├── test10_strings_printf.c  # String literals, indexing, and external printf C-runtime linkage
│   ├── test11_bitwise_ternary.c # Bitwise ops, short-circuit && and ||, ternary ?:
│   ├── test12_sorting.c         # Bubble sort on 8 integers and binary search algorithm
│   ├── test13_fibonacci.c       # Recursive Fibonacci calculation
│   ├── test_if.c                # if statement block
│   ├── test_if1.c               # if (1) constant condition
│   └── test_if2.c               # if single statement without braces
├── run_tests.py                 # Automated Python test runner and verifier
├── build.bat                    # Windows batch script to rebuild compiler
├── build.ps1                    # PowerShell build script
└── README.md
```

---

## Building the Compiler

### Prerequisites
- **x86-64 Assembler** (added to PATH)
- **MinGW-w64 GCC** (added to PATH)
- **Python 3.8+** (for running the automated test suite)

### Build Command
Run either:
```cmd
build.bat
```
or in PowerShell:
```powershell
.\build.ps1
```

Or manually:
```cmd
nasm -f win64 -I ./ src\main.asm -o bin\c_compiler.obj
gcc bin\c_compiler.obj -o bin\c_compiler.exe
```

---

## Running the Automated Test Suite

Run the Python test runner to compile, assemble, link, and execute all tests:
```powershell
python run_tests.py
```

Expected output:
```text
======================================================================
  PURE x86-64 ASSEMBLY C COMPILER - AUTOMATED TEST SUITE
======================================================================
 [PASS] test01_return42.c            -> OK (exit code 42)
 [PASS] test02_vars.c                -> OK (exit code 50)
 [PASS] test03_recursion.c           -> OK (exit code 120)
 [PASS] test04_loops.c               -> OK (exit code 0)
 [PASS] test05_switch.c              -> OK (exit code 0)
 [PASS] test06_pointers.c            -> OK (exit code 0)
 [PASS] test07_arrays.c              -> OK (exit code 0)
 [PASS] test08_globals.c             -> OK (exit code 0)
 [PASS] test09_structs.c             -> OK (exit code 0)
 [PASS] test10_strings_printf.c      -> OK (exit code 0)
 [PASS] test11_bitwise_ternary.c     -> OK (exit code 0)
 [PASS] test12_sorting.c             -> OK (exit code 0)
 [PASS] test13_fibonacci.c           -> OK (exit code 0)
 [PASS] test_if.c                    -> OK (exit code 1)
 [PASS] test_if1.c                   -> OK (exit code 1)
 [PASS] test_if2.c                   -> OK (exit code 1)
======================================================================
  SUMMARY: 16 PASSED, 0 FAILED across 16 tests
======================================================================
```

---

## Compiling Your Own C Programs

1. **Write C code** (`my_prog.c`):
   ```c
   extern int printf(char *fmt, int val);

   int main() {
       int sum = 0;
       int i;
       for (i = 1; i <= 10; i = i + 1) {
           sum += i;
       }
       printf("Sum of 1..10 = %d\n", sum);
       return 0;
   }
   ```

2. **Compile to assembly**:
   ```cmd
   .\bin\c_compiler.exe my_prog.c my_prog.asm
   ```

3. **Assemble and link**:
   ```cmd
   nasm -f win64 my_prog.asm -o my_prog.obj
   gcc my_prog.obj -o my_prog.exe
   ```

4. **Run**:
   ```cmd
   .\my_prog.exe
   ```

---

## License
MIT License
