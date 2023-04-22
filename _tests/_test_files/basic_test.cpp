#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//------------------------------------------------------------------------------------------
//Files we are testing:



//------------------------------------------------------------------------------------------

using namespace std;

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running basic_test.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}


/*
build git:(master) ✗  😊 $> tree ../includes/table
../includes/table
├── table.cpp
├── table.h
└── typedefs.h

0 directories, 3 files
build git:(master) ✗  😊 $> ./bin/basic_test       
*/


/*


----------running basic_test.cpp---------


[==========] Running 5 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 1 test from TABLE_BASIC
[ RUN      ] TABLE_BASIC.TableBasic
Here is table t: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


Here are all the Yaos:

Table name: _select_table_1, records: 2
                   record                    fname                    lname                      age

                        0                      Flo                      Yao                       29
                        1                     Jack                      Yao                       19



here is the student table: 
Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15



20 year-olds:

Table name: _select_table_4, records: 3
                   record                      age                    fname                    lname

                        0                       20                      Joe                    Gomez
                        1                       20                      Flo                  Jackson
                        2                       20                      Flo                    Gomez

record numbers from original table: 0 4 5 


older than 20 years old:

Table name: _select_table_6, records: 2
                   record                      age                    fname                    lname

                        0                       21                    Karen                   Orozco
                        1                       29                      Flo                      Yao

record numbers from original table: 1 2 


younger than 20 years old:

Table name: _select_table_8, records: 2
                   record                      age                    fname                    lname

                        0                       15                    Karen                  Jackson
                        1                       19                     Jack                      Yao

record numbers from original table: 6 3 


20 or younger:

Table name: _select_table_10, records: 5
                   record                      age                    fname                    lname

                        0                       15                    Karen                  Jackson
                        1                       19                     Jack                      Yao
                        2                       20                      Joe                    Gomez
                        3                       20                      Flo                  Jackson
                        4                       20                      Flo                    Gomez

record numbers from original table: 6 3 0 4 5 


20 or older:

Table name: _select_table_12, records: 5
                   record                      age                    fname                    lname

                        0                       20                      Joe                    Gomez
                        1                       20                      Flo                  Jackson
                        2                       20                      Flo                    Gomez
                        3                       21                    Karen                   Orozco
                        4                       29                      Flo                      Yao

record numbers from original table: 0 4 5 1 2 

----- END TEST --------
[       OK ] TABLE_BASIC.TableBasic (23 ms)
[----------] 1 test from TABLE_BASIC (23 ms total)

[----------] 2 tests from TABLE_INTERMEDIATE
[ RUN      ] TABLE_INTERMEDIATE.TableRelational
recnos from all the Yaos query: 2 3 
all the Yaos: 

Table name: _select_table_15, records: 2
                   record                    lname                      age

                        0                      Yao                       29
                        1                      Yao                       19


[       OK ] TABLE_INTERMEDIATE.TableRelational (7 ms)
[ RUN      ] TABLE_INTERMEDIATE.TableLogical
here is the table: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


recnos from all the 17 to 20 year olds: 0 3 4 5 
all the 17 to 20 year olds : 

Table name: _select_table_18, records: 4
                   record                    lname                      age

                        0                    Gomez                       20
                        1                      Yao                       19
                        2                  Jackson                       20
                        3                    Gomez                       20


[       OK ] TABLE_INTERMEDIATE.TableLogical (5 ms)
[----------] 2 tests from TABLE_INTERMEDIATE (12 ms total)

[----------] 2 tests from TABLE_ADVANCED
[ RUN      ] TABLE_ADVANCED.TableFullCondition
here is the table: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


recnos from all all the 17 to 20 year olds (non inclusive) along with all the Gomezes: 0 3 5 


Table name: _select_table_21, records: 3
                   record                    lname                      age

                        0                    Gomez                       20
                        1                      Yao                       19
                        2                    Gomez                       20


[       OK ] TABLE_ADVANCED.TableFullCondition (7 ms)
[ RUN      ] TABLE_ADVANCED.TableStringCondition
here is the table: 

Table name: student, records: 7
                   record                    fname                    lname                      age

                        0                      Joe                    Gomez                       20
                        1                    Karen                   Orozco                       21
                        2                      Flo                      Yao                       29
                        3                     Jack                      Yao                       19
                        4                      Flo                  Jackson                       20
                        5                      Flo                    Gomez                       20
                        6                    Karen                  Jackson                       15


recnos from all all younger than 17, all older than 20, who are Jacksons: 6 


Table name: _select_table_24, records: 1
                   record                    lname                      age

                        0                  Jackson                       15


[       OK ] TABLE_ADVANCED.TableStringCondition (5 ms)
[----------] 2 tests from TABLE_ADVANCED (12 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 3 test cases ran. (47 ms total)
[  PASSED  ] 5 tests.
build git:(master) ✗  😊 $> 


 */


