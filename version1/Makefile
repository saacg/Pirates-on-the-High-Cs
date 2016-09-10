# in EC327, we use the ${GCC} compiler
# therefore, we define the GCC variable
GCC = g++ 


#checkpoint1: CartPoint.o CartVector.o testCheckpoint1.o 
#	${GCC} CartPoint.o CartVector.o testCheckpoint1.o -o checkpoint1

#checkpoint2: GameObject.o CartPoint.o CartVector.o Port.o testCheckpoint1and2.o
#	${GCC} GameObject.o testCheckpoint1and2.o CartPoint.o CartVector.o Port.o -o checkpoint2 

#checkpoint3: CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o TestCheckpoint3.o
#	${GCC} CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o TestCheckpoint3.o -o checkpoint3

#checkpoint4: CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o TestCheckpoint4.o
#	${GCC} CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o TestCheckpoint4.o -o checkpoint4

HighCs: CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o View.o pa3.o
	${GCC} CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o View.o pa3.o -o HighCs


CartPoint.o: CartPoint.cpp
	${GCC} -c CartPoint.cpp

CartVector.o: CartVector.cpp
	${GCC} -c CartVector.cpp

testCheckpoint1.o: testCheckpoint1.cpp
	${GCC} -c testCheckpoint1.cpp

GameObject.o: GameObject.cpp
	${GCC} -c GameObject.cpp

Port.o: Port.cpp
	${GCC} -c Port.cpp

testCheckpoint1and2.o: testCheckpoint1and2.cpp
	${GCC} -c testCheckpoint1and2.cpp

Dock.o: Dock.cpp
	${GCC} -c Dock.cpp

Sailor.o: Sailor.cpp
	${GCC} -c Sailor.cpp

Model.o: Model.cpp
	${GCC} -c Model.cpp

GameCommand.o: GameCommand.cpp
	${GCC} -c GameCommand.cpp

View.o: View.cpp
	${GCC} -c View.cpp

pa3.o: pa3.cpp
	${GCC} -c pa3.cpp

TestCheckpoint3.o: TestCheckpoint3.cpp
	${GCC} -c TestCheckpoint3.cpp

TestCheckpoint4.o: TestCheckpoint4.cpp
	${GCC} -c TestCheckpoint4.cpp

clean:
	rm CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o View.o pa3.o HighCs

#clean:
#	rm CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o TestCheckpoint4.o checkpoint4

#clean:
#	rm CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o TestCheckpoint3.o checkpoint3

#clean:
#	rm CartPoint.o CartVector.o testCheckpoint1.o checkpoint1  
