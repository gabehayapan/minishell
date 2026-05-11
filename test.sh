#!/usr/bin/bash

FAIL=0

run_test() {
	INPUT="$1"

	echo "$INPUT" | bash > expected.txt 2>&1
	echo "$INPUT" | ./minishell > output.txt 2>&1

	if ! diff -u expected.txt output.txt > diff.txt; then
		echo "FAIL: $INPUT"
		cat diff.txt
		FAIL=1
	else
		echo "PASS: $INPUT"
	fi
}

run_test "echo hello"
run_test "ls"

exit $FAIL
