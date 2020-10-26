::Coded by Davoleo::
mkdir build

:: Compile the averager source file
g++ ./theory/media.cpp -o ./build/media

:: Compile the statement theory file
g++ ./theory/statements.cpp -o ./build/statements

::Compile date validator Excercise
:: g++ ./exercises/1_date_validator.cpp -o ./build/1_date_validator

::Compile Equation Resolver Excercise
:: g++ ./exercises/2_eq2_resolver.cpp -o ./build/2_eq2_resolver

::Compile Weighted Average Excercise
:: g++ ./exercises/3_weighted_average.cpp -o ./build/3_weighted_average

::Compile Inches <-> cms Excercise
g++ ./exercises/4_inches_cm_converter.cpp -o ./build/4_inches_cm_converter

:: Tryangle builder
g++ ./exercises/5_tryangle.cpp -o ./build/5_tryangle

:: Int Operations menu
g++ ./exercises/6_operations.cpp -o ./build/6_operations