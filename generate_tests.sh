#!/bin/bash

echo "#include \"stdlib.h\""
echo "testType tests_to_run[] = {"
objdump -t test_suites.o | grep "F .text" | awk '{print "{ &"$6",\""$6"\"},"}'
echo "{NULL,NULL}"
echo "};"

echo "unsigned int num_tests_to_run = \
 sizeof(tests_to_run)/sizeof(testType) -1;"
