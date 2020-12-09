all: 
	g++ -o driver driver.cpp BTree.cpp -g

run:
	./driver input.txt
