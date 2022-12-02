# s2p_file_converter
Example of some C code

s2p_file_converter opens a Sunlord Microwave test data file (see test.csv as an example) and creates a new 
file in the industry standard Touchstone s2p format (as per Touchstone File Format Specification 2.0). See example
of the output file, DVRF00242.s2p.


C FILES:

fileinfo.h defines 2 structs, FileInfo for the general file information, and FreqPoint for the actual test data.

s2p_get_data.c opens the target file and pulls all the data.

s2p_create_file.c pushs the data to the new file, part_number.s2p.

test_s2p_creator.c tests the above using test.csv as the test case. 


C++ FILES:

form1 is the code to create the Windows form and call the C functions above.


