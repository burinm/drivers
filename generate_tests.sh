#!/bin/bash

echo "#include \"stdlib.h\""
echo "testType tests_to_run[] = {"
for i in suite*.o; do
objdump -t $i | grep "F .text" | awk '{print "{ &"$6",\""$6"\"},"}';
done
echo "{NULL,NULL}"
echo "};"

echo "unsigned int num_tests_to_run = \
 sizeof(tests_to_run)/sizeof(testType) -1;"
