#!/bin/bash
function quick()
{
	find ./src ./include | entr -sc 'make -j$(nproc) run_quick_tests'
}

function full()
{
	find ./src ./include | entr -sc 'make -j$(nproc) run_tests'
}

case $1 in
	quick) quick ;;
	full) full ;;
esac
