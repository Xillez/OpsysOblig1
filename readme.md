# IMT2282 Operativsystemer - Oblig 1
### Johannes G. Aas(473183) & Kent W. Holt(473209)


The tools used to ensure code quality were found at the following repository:  
https://github.com/NTNUcourses/opsys/blob/master/ in 'README-C-code-quality.txt'.


* **gcc file -Wall**  
Compiles using gcc with all warnings.

Install:
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Inherent on Ubuntu and OSX.


* **cppcheck --enable=all ./file**  
From http://cppcheck.sourceforge.net/:  
"Cppcheck is a static analysis tool for C/C++ code. It provides unique code analysis to detect bugs and focuses on detecting undefined behaviour and dangerous coding constructs. The goal is to detect only real errors in the code (i.e. have very few false positives)."

Install:  
&nbsp;&nbsp;&nbsp;&nbsp;cppcheck


* **clang-tidy-5.0 -checks='\*' file -- -std=c11**  
From https://clang.llvm.org/extra/clang-tidy/:  
"Clang-tidy is a clang-based C++ “linter” tool. Its purpose is to provide an extensible framework for diagnosing and fixing typical programming errors, like style violations, interface misuse, or bugs that can be deduced via static analysis. clang-tidy is modular and provides a convenient interface for writing new checks."

Install:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;clang compiler with version 5.0+  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;clang-tidy-5.0


* **valgrind:**  
From http://valgrind.org/:  
"Valgrind is an instrumentation framework for building dynamic analysis tools. There areValgrind tools that can automatically detect many memory management and threading bugs, andprofile your programs in detail. You can also use Valgrind to build new tools."

Install:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;valgrind

* **valgrind --leak-check=yes ./file**  

Monitors the memory usage of the program and checks for memory leaks.


* **valgrind --tool=helgrind ./file**  

Tests for various errors including bad use of API, synchronization mistakes and improperprotection of critical sector.  

Comment:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Gives false warnings caused by race-condition in downing the 'mutex' semaphore.
