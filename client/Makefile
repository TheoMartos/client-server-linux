CC       = g++
CFLAGS   = -Wall #-std=c++14
LDFLAGS  = -lpthread
SRCS	 = $(wildcard *.cpp)
OBJFILES = $(SRCS:.cpp=.o)
TARGET   = client

all: $(TARGET)

$(TARGET): $(OBJFILES)
	${CC} ${CFLAGS} -o $(TARGET) $(OBJFILES) $(LDFLAGS)

%.o: %.cpp 
	${CC} ${CFLAGS} ${INCLUDES} -c $< 

clean:
	rm -f $(OBJFILES) Makefile.bak

mrproper: clean
	rm -f $(TARGET)

depend: 
	makedepend -I. $(SRCS)

exe: $(TARGET)
	./$(TARGET)