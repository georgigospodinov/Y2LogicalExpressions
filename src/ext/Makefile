# Binaries
estack.o: estack.c estack.h
	gcc estack.c -c -o estack.o

logic.o: logic.c estack.h
	gcc logic.c -c -o logic.o

ttable2: logic.o estack.o
	gcc logic.o estack.o -o ttable2

# Laws
demorgan: ttable2
	clear
	echo "DE MORGAN LAWS:"
	echo "-(a|b) = (-a&-b)"
	./ttable2 2 'ab|-' 'a-b-&'
	echo "-(a&b) = (-a|-b)"
	./ttable2 2 'ab&-' 'a-b-|'

distributive: ttable2
	clear
	echo "DISTRIBUTIVE LAWS:"
	echo "a|(b&c) = (a|b)&(a|c)"
	./ttable2 3 'abc&|' 'ab|ac|&'
	echo "a&(b|c) = (a&b)|(a&c)"
	./ttable2 3 'abc|&' 'ab&ac&|'

another: ttable2
	clear
	echo "another law"
	echo "-(a#b) = (a=b)"
	./ttable2 2 'ab#-' 'ab='

# Logical Puzzles
puzzleA: ttable2
	clear
	echo "Puzzle A - Coin Flip"
	echo "Conditions: a|-a"
	./ttable2 1 'aa-|'

puzzleB: ttable2
	clear
	echo "Puzzle B - Ages"
	echo "Who is the oldest?"
	echo "Conditions: -(a&b&c)&(a#b#c), -a, c#b, a|-c"
	./ttable2 3 'abc&&-abc##& a- cb# ac-| &&&'
	echo "Who is the yongest?"
	echo "Conditions: -(a&b&c)&(a#b#c), -c#-b, -a|c"
	./ttable2 3 'abc&&-abc##& c-b-# a-c| &&'

puzzleC: ttable2
	clear
	echo "Puzzle C - Dinner Attendence"
	echo "Conditions: d|c, b#e, b=a|b, e=d, (a&d)=c|(a&d)"
	./ttable2 5 'dc| be# ab|b= ed= ad&ad&c|= &&&&'

puzzleX: ttable2
	clear
	echo "Puzzle X - Boxes, Cards, and a Prize"
	echo "Too many conditions to show, see report"
	./ttable2 9 'abc&&-abc##& def&&-def##& ghi&&-ghi##& &&  adg&&-adg##& beh&&-beh##& cfi&&-cfi##& &&  ac-f||ac-f#=& ac-f&&-ac-f##& |  ec-=  &&&'

# Clean
clean:
	rm -f *.o
	rm -f ttable2
	
