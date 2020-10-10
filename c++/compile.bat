::Coded by Davoleo::
mkdir ./build/theory
mkdir ./build/exercises

:: Compile the averager source file
g++ ./theory/media.cpp -o ./build/theory/media

:: Compile the statement theory file
g++ ./theory/statements.cpp -o ./build/theory/statements