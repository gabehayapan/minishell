#!/usr/bin/bash

FAIL=0

run_test() {
	INPUT="$1"

	OUTPUT=$(echo "$INPUT" | ./minishell | tail -n +2 | head -n -1)
	EXPECTED=$(echo "$INPUT" | bash)

	if [ "$OUTPUT" != "$EXPECTED" ]; then
		echo "Test FAILED"
		echo "Input: $INPUT"
		echo "Expected: $EXPECTED"
		echo "Got: $OUTPUT"
		FAIL=1
	else
		echo "Test PASSED: $INPUT"
	fi
}

run_test "echo hello"
run_test "pwd"

exit $FAIL
