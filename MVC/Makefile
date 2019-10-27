CC = g++
GTKMM= `pkg-config gtkmm-3.0 --cflags --libs`
CFLAGS =$(GTKMM) -Wall
LDFLAGS = $(GTKMM)
SRC = main.cpp VueGraphique.cpp token_list.cpp
PROG = projrobo
OBJS = $(SRC:.cpp=.o)
.SUFFIXES: .cpp .o

all: $(PROG)

$(PROG): $(OBJS)
		$(CC) -o $@ $^ $(LDFLAGS)
token_list.o: token.hpp token_list.hpp Modele.hpp
main.o: Vue.hpp VueGraphique.hpp Modele.hpp ModeleEnv2D.hpp Controleur.hpp
VueGraphique.o: VueGraphique.hpp Controleur.hpp Info.hpp

%.o:%.cpp
		$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
		rm -f *.o *- core a.out $(PROG)
