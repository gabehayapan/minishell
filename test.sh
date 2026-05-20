#!/usr/bin/bash

FAIL=0

run_test() {
	INPUT="$1"

	echo "$INPUT" | bash 2>expected_error.txt > expected.txt
	EXPECTED_EXIT_STATUS="$?"
	echo "$INPUT" | ./minishell 2>output_error.txt | tail -n +2 | head -n -1 > output.txt
	MINISHELL_EXIT_STATUS="$(echo 'echo $?' | ./minishell | tail -n +2 | head -n -1)"

	if ! diff -u expected.txt output.txt > diff.txt; then
		echo "FAIL: $INPUT"
		cat diff.txt
		FAIL=1
	else
		echo "PASS: $INPUT"
	fi

#	if [ "$EXPECTED_EXIT_STATUS" != "$MINISHELL_EXIT_STATUS" ]; then
#		echo "Wrong EXIT status"
#		echo "bash: $EXPECTED_EXIT_STATUS"
#		echo "minishell: $MINISHELL_EXIT_STATUS"
#		FAIL=1
#	fi
}

run_test "echo hello"
run_test "ls"
run_test "./include"

exit $FAIL
