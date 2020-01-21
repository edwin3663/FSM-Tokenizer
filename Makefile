APPS = tokenize

OBJECTS = parserClasses.o tokenizer.o
HEADERS = parserClasses.h

#Debug flag
CXXFLAGS += -g -Wall -std=c++11

all: $(APPS)

$(OBJECTS): $(HEADERS)
$(APPS): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) *.o $(APPS)


