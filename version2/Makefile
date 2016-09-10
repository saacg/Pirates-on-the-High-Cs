# in EC327, we use the ${GCC} compiler
# therefore, we define the GCC variable
GCC = g++
CXXFLAGS = -g -Wall -Wextra
OBJECTS = CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o View.o Merchant.o Pirate.o Kraken.o pa4.o


HighCs: $(OBJECTS)
	${GCC} $(CXXFLAGS) $(OBJECTS) -o HighCs

%.o: %.c
	${GCC} $(CXXFLAGS) -c $<

clean:
	rm CartPoint.o CartVector.o GameObject.o Port.o Dock.o Sailor.o Model.o GameCommand.o View.o Merchant.o Pirate.o Kraken.o pa4.o HighCs


