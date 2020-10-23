::Coded by Davoleo::
mkdir build

:: Compile the averager source file
g++ ./theory/media.cpp -o ./build/media

:: Compile the statement theory file
g++ ./theory/statements.cpp -o ./build/statements

::Compile date validator Excercise
:: g++ ./exercises/date_validator.cpp -o ./build/date_validator

::Compile Equation Resolver Excercise
:: g++ ./exercises/eq2_resolver.cpp -o ./build/eq2_resolver

::Compile Weighted Average Excercise
:: g++ ./exercises/weighted_average.cpp -o ./build/weighted_average

::Compile Inches <-> cms Excercise
 g++ ./exercises/inches_cm_converter.cpp -o ./build/inches_cm_converter