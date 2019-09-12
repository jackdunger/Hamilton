%: Makefile

leap_frog_demo: leap_frog_demo.cpp LeapFrog.cpp LeapFrog.h
	g++ -std=c++11 -stdlib=libc++ -I/Users/Jack/hamilton/ leap_frog_demo.cpp LeapFrog.cpp -o $@

clean:
	rm -f leap_frog_demo
