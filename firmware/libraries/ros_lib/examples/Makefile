IFLAGS    = -I ../ros_lib -I ../ros_lib/vortex86/utilities
OBJFILES  = HelloROS.o 86DuinoHardware.o time.o duration.o io.o irq.o err.o vortex86.o
OBJFILES += 
EXEFILES  = HelloROS.exe
LIBFILES  = -lrt
OPTIONS   = 
# GNU Make will set CXX to correct C++ compiler if it is not set.
# You can use other compiler from command line of make, ex:
# make CXX=gcc
#CXX       = gcc

.PHONY : everything all clean

everything : $(OBJFILES) $(EXEFILES)

all : clean everything

clean :
	-rm -f $(EXEFILES) $(OBJFILES)

%.o: %.cpp
	$(CXX) -c $< $(IFLAGS) $(OPTIONS)

%.o: ../ros_lib/%.cpp
	$(CXX) -c $< $(IFLAGS) $(OPTIONS)

%.o: ../ros_lib/vortex86/utilities/%.cpp
	$(CXX) -c $< $(IFLAGS) $(OPTIONS)

HelloROS.exe : $(OBJFILES)
	$(CXX) -o $@ $(OBJFILES) $(LIBFILES) $(OPTIONS)
