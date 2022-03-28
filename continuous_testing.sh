#!/bin/bash
function quick()
{
	find ./src ./include | entr -sc 'make -j$(nproc) run_quick_tests'
}

function quick_valgrind()
{
	find ./src ./include | entr -sc 'make -j$(nproc) run_quick_tests_valgrind'
}

function full()
{
	find ./src ./include | entr -sc 'make -j$(nproc) run_tests'
}

function full_valgrind()
{
	find ./src ./include | entr -sc 'make -j$(nproc) run_tests_valgrind'
}

case $1 in
	quick) quick ;;
	quick_valgrind) quick_valgrind ;;
	full_valgrind) full_valgrind ;;
	*) echo "Run this script with either argument 'quick' or 'full'" ;;
esac
