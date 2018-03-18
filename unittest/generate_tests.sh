#!/bin/bash

CALLING_DIR=$1
SUITES_TO_RUN=`grep  --color=never  "^suite*" TESTS | xargs`

echo "#include \"stdlib.h\""
echo "testType tests_to_run[] = {"
for i in $SUITES_TO_RUN; do
objdump -t $CALLING_DIR/$i | grep "F .text" | awk '{print "{ &"$6",\""$6"\"},"}';
done
echo "{NULL,NULL}"
echo "};"

echo "unsigned int num_tests_to_run = \
 sizeof(tests_to_run)/sizeof(testType) -1;"
