Input:
	-Expressions should be entered in a (<Lval><operator><Rval>) format where parenthesis are optional.
		-Note: Negative values not currently supported.
	-Floats are the default type and operator truncation occurs on the 4th decimal value.
	-Valid Operators:
		^ - Power
		* - Multiplication
		/ - Division
		+ - Addition
		-  - Subtraction

Calling Conventions:
	./Calc.exe
		-Runs idle window that will take in lines of expressions and process them appropriately.
		-Enter q or Q to quit
	./Calc.exe <file>
		-Processes each line of <file> until eof is reached
		-Once eof is reached, converts to standard input mode
		-Input.txt is included with the project and the solution
