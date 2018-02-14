# IMT2282 Operativsystemer - Oblig 1
### Johannes G. Aas(473183) & Kent W. Holt(473209)


The following tools were used to insure code quality in this hand-in:
* **gcc file -Wall**
Compiles the program with all warnings using gcc. Inherent on Ubuntu and OSX.

* **cppcheck --enable=all ./file**
Static analysis tool that checks for semantic bugs, bad conventions and undefined behaviour.
Has to be installed with bash command 'sudo apt-get install cppcheck'.

* **clang-tidy-5.0 -checks='\*' file -- -std=c11**
Linter tool that points out misuse of interfaces, inconsistency in conventions / style violations.
Has to be installed by first installing the clang compiler of version 5.0 with 'sudo apt-get install clang-5.0',
then installing tidy with 'sudo apt-get install clang-tidy-5.0'.

* **valgrind --leak-check=yes ./file**
Dynamic analysis tool that monitors memory usage and give error in the case of memory leaks.
Has to be installed with 'sudo apt-get install valgrind'.

* **valgrind --tool=helgrind ./file**
Checks for multithreading errors such as synchronization errors, misuse of api's, unprotected entry to critical sector.
After testing the first two files in the hand-in, I ended up making the following bash function, to save time in future.
It doesn't compile all the answers for you in a list at the bottom. However, it still saves time.

```bash
cTest(){

		if [ -z "$1" ] || [[ $1 == -h ]]; then	#Test input parameters
    	printf 	"\nNo input file supplied.
		 		 \nUsage: cTest input-file.c optional-gcc-compile-parameter
		 		 \nExample: cTest main.c -pthread\n"
		return									#Exit function if bad input.
		fi


		printf "\n\n\e[32mgcc test:\n"
		tput sgr0								#Resets color to current profile default.
		gcc $1 -Wall $2

		printf "\n\n\e[32mcppcheck test:\n"
		tput sgr0								#Resets color to current profile default.
		cppcheck --enable=all ./$1

		printf "\n\n\e[32mclang-tidy test:\n"
		tput sgr0								#Resets color to current profile default.
		clang-tidy-5.0 -checks='*' $1 -- -std=c11

		printf "\n\n\e[32mmem-leak test:\n"
		tput sgr0								#Resets color to current profile default.
		valgrind --leak-check=yes ./$1

		printf "\n\n\e[32msynchronisation POSIX pthreads test:\n"
		tput sgr0								#Resets color to current profile default.
		valgrind --tool=helgrind ./$1
}
```
