CXXFLAGS = -pedantic -std=c++11 -Wall -Werror -Isrc/

TEST_SOURCES = $(wildcard tests/test_*.cpp)
TEST_BIN = $(patsubst %.cpp,%,$(TEST_SOURCES))
TEST_OUT = $(patsubst %.cpp,%.out,$(TEST_SOURCES))
TEST_DIFF = $(patsubst %.cpp,%.diff,$(TEST_SOURCES))

tests/test_%: tests/test_%.o
	$(CXX) $(CXXFLAGS) $< -o $@

tests/test_%.out: tests/test_%
	./$< > $@

tests/test_%.diff: tests/test_%.out tests/test_%.correct
	diff $? > $@

report: $(TEST_DIFF)
	-@rm $@
	for out in $(TEST_DIFF); do du $$out > $@; done

tests: report
	cat $<

clean:
	-@rm -v $(TEST_DIFF) $(TEST_OUT) $(TEST_BIN)
