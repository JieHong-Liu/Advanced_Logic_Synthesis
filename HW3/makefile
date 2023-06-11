# LIBROOT=/users/student/mr111/jhliu22/ALS/HW3/lib
# LEDAROOT=/users/student/mr111/jhliu22/LEDA_lib/LEDA

# CPP = g++
# CPPFLAGS= -std=c++11 -O3 -c -g -I$(LEDAROOT)/incl -I$(LIBROOT)
# LIBS = -L$(LEDAROOT) -lG -lL -lm 

# SRCS = test-graph.cpp
# OBJS = ${SRCS:%.cpp=%.o}
# EXE = test

# $(EXE):	$(OBJS)
# 	$(CPP)	-o $(EXE) $(OBJS) $(LIBS);
# # $(OBJS): $(SRCS)
# # 	 $(CPP)	$(CPPFLAGS) -c -o $(OBJS) $(SRCS);

# $(OBJS): $(SRCS)
# 	$(CPP) $(CPPFLAGS) -c -o $@ $(@:%.o=%.cpp)

# clean:
# 	rm -f $(OBJS); rm -f $(EXE);


LIBROOT=/users/student/mr111/jhliu22/ALS/HW3/lib
LEDAROOT=/users/student/mr111/jhliu22/LEDA_lib/LEDA
GLPKROOT=/users/student/mr111/jhliu22/ALS/HW3/glpk-4.47/src/
CPP = g++
CPPFLAGS = -std=c++11 -O3 -g -I$(LEDAROOT)/incl -I$(LIBROOT) -I$(GLPKROOT)
LIBS = -L$(LEDAROOT) -L$(GLPKROOT) -lG -lL -lm -lglpk

SRCS = src/main.cpp src/state_assigner.cpp
OBJS = $(SRCS:.cpp=.o)
EXE = ./bin/sa

all: $(EXE)

$(EXE): $(OBJS)
	$(CPP) -o $(EXE) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)
