CXX=g++

CFLAGS  = 

BINDIR = ./bin
LIBDIR = ./lib


TARGET= ShinMasuzawa
OBJS=   ShinMasuzawa.o  

.PHONY: all
all:$(TARGET)



$(LIBDIR)/%.o : %.cc
	$(CXX) -c -o $@ $<

$(TARGET): $(patsubst %,$(LIBDIR)/%,$(OBJS))
	$(CXX) -o $(BINDIR)/$@ $^

.PHONY: clean
clean:
	rm -f $(LIBDIR)/*.o $(LIBDIR)/*.d core $(BINDIR)/*

