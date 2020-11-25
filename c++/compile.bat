::Coded by Davoleo::
mkdir build

:: Compile the averager source file
g++ ./theory/media.cpp -o ./build/media

:: Compile the statement theory file
g++ ./theory/statements.cpp -o ./build/statements

::Compile date validator Exercise
:: g++ ./exercises/1_date_validator.cpp -o ./build/1_date_validator

::Compile Equation Resolver Exercise
:: g++ ./exercises/2_eq2_resolver.cpp -o ./build/2_eq2_resolver

::Compile Weighted Average Exercise
:: g++ ./exercises/3_weighted_average.cpp -o ./build/3_weighted_average

::Compile Inches <-> cms Exercise
:: g++ ./exercises/4_inches_cm_converter.cpp -o ./build/4_inches_cm_converter

:: Tryangle builder
:: g++ ./exercises/5_tryangle.cpp -o ./build/5_tryangle

:: Int Operations menu
:: g++ ./exercises/6_operations.cpp -o ./build/6_operations

:: Array Subtractor
::g++ ./exercises/7_array_subtractor.cpp -o ./build/7_array_subtractor

:: Rotation Printer
::g++ ./exercises/8_rotation_printer.cpp -o ./build/8_rotation_printer

:: Trials
::g++ ./exercises/9_trials.cpp -o ./build/9_trials

:: Subzero temperatures
g++ ./exercises/10_subzero_temps.cpp -o ./build/10_subzero_temps

:: Word Comparator
g++ ./exercises/11_word_comparator.cpp -o ./build/11_word_comparator

:: Phone Numbers Table
g++ ./exercises/12_phone_numbers_table.cpp -o ./build/12_phone_numbers_table