#!/bin/bash
RESULT=$(make run_quick_tests_valgrind &>/dev/stdout | awk '/ERROR SUMMARY/ { print $4 }')

function _success()
{
	echo "Valgrind check didn't return any errors!"
	exit 0
}

function _fail()
{
	echo "Valgrind exited with errors!"
	exit 1
}

[ "$RESULT" == "0" ] && _success || _fail
