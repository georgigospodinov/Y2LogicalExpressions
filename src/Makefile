# Binaries
stack.o: stack.c stack.h
	gcc stack.c -c -o stack.o

main.o: main.c stack.h
	gcc main.c -c -o main.o

ttable: main.o stack.o
	gcc main.o stack.o -o ttable

# Example formula
example: ttable
	clear
	echo "The exmple from the practical specification"
	./ttable 3 'ac#1&-a-0|b=->'

# Laws
demorgan: ttable
	clear
	echo "DE MORGAN LAWS:"
	echo "-(a|b) = (-a&-b)"
	./ttable 2 'ab|- a-b-& ='
	echo "-(a&b) = (-a|-b)"
	./ttable 2 'ab&- a-b-| ='

distributive: ttable
	clear
	echo "DISTRIBUTIVE LAWS:"
	echo "a|(b&c) = (a|b)&(a|c)"
	./ttable 3 'abc&| ab|ac|& ='
	echo "a&(b|c) = (a&b)|(a&c)"
	./ttable 3 'abc|& ab&ac&| ='

# Logical Puzzles
puzzleA: ttable
	clear
	echo "Puzzle A - Coin Flip"
	echo "Conditions: a|-a"
	./ttable 2 'aa-|'

puzzleB: ttable
	clear
	echo "Puzzle B - Ages"
	echo "Who is the oldest?"
	echo "Conditions: -(a&b&c)&(a#b#c), -a, c#b, a|-c"
	./ttable 3 'abc&&-abc##& a- cb# ac-| &&&'
	echo "Who is the yongest?"
	echo "Conditions: -(a&b&c)&(a#b#c), -c#-b, -a|c"
	./ttable 3 'abc&&-abc##& c-b-# a-c| &&'

puzzleC: ttable
	clear
	echo "Puzzle C - Dinner Attendence"
	echo "Conditions: d|c, b#e, b=a|b, e=d, (a&d)=c|(a&d)"
	./ttable 5 'dc| be# ab|b= ed= ad&ad&c|= &&&&'

# Clean
clean:
	rm -f *.o
	rm -f ttable
	
