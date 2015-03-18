
Rapidnet
========

6) Using the data-structures
----------------------------

`-I`: indicates the location of the header files

`-l`: indicates we want to use the CVC4 libraries

`-L`: where the implementation of the header files can be found

    Run g++ -I<path-to-rapidnet>/src/rapidnet-compiler -<path-to-rapidnet>/lkloh/rapidnet/src/rapidnet-compiler <file-using-data-structures>.cc -o <file-using-data-structures> -lcvc4

Example: I clone this folder to my home directory, with path `/home/lkloh`. To run the file `hellpeworld.cpp` which sources the data structure files from rapidnet, I cd into the location where `helloworld.cpp` may be found, and type:

    g++ -I/home/lkloh/rapidnet/src/rapidnet-compiler -L/home/lkloh/rapidnet/src/rapidnet-compiler helloworld.cpp -o helloworld -lcvc4

7) Remove DS_Store before pushing.
----------------------------------

At the top level of the repository, type

    find . -name .DS_Store -print0 | xargs -0 git rm -f --ignore-unmatch
    
As suggested [here](http://stackoverflow.com/questions/107701/how-can-i-remove-ds-store-files-from-a-git-repository).

8) [Installing on MacOS](https://github.com/lkloh/rapidnet/wiki/Installing-On-MacOS)
------------------------------------------------------------------------------------

9) How to run a NDLog program from outside the folder
-----------------------------------------------------

In the command line, cd into the rapidnet folder. Get the entire path the the NDLog file you want to run `<path-to-file>/<My-NDLog-Program>.olg`. Run 

    ./rapidnet/dpcompiler/dpcompile <path-to-file>/<My-NDLog-Program>.olg
    
In NDLog Programs, all string constants must be assigned a value larger than 1000 using 

    #define <STR-CONSTANT-NAME> value
    
where value > 1000,  so we know it is a string constant. (March 12, 2015)

10) SMT-LIB
-----------
* [SMT-LIB Official Website](http://smtlib.cs.uiowa.edu/)
* [String Declaration](http://cvc4.cs.nyu.edu/wiki/Strings)
* [Installin Z3 on MacOS](http://z3.codeplex.com/wikipage?title=Building%20the%20unstable%20%28working-in-progress%29%20branch&referringTitle=Documentation)

11) Running examples
--------------------
* `./rapidnet/compiler/compile /Users/lkloh/rapidnet/src/applications/firewall/firewall.olg`
* [Upenn Tutorial](http://netdb.cis.upenn.edu/rapidnet/doxygen/html/rapidnet-ndlog-application.html)
