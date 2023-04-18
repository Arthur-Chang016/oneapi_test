

all:
	icpx -fsycl pipe.cpp
	
run:
	./a.out
	
clean:
	rm -f a.out
	
.SILENT: run
.PHONY: all
	