# new_RTD
It's time for a new regime of power.

###To compile plPlot wx examples
In the PLplot Makefile, under the recipe for wxPLplotDemo.cpp, you must include `wx-config --cxxflags` as part of the linker flags and as part of the cpp flags. The resulting line looks like this:
/usr/bin/x86_64-linux-gnu-g++ wxPLplotDemo.cpp -o wxPLplotDemo  `PKG_CONFIG_PATH="/usr/lib/pkgconfig" pkg-config  --cflags --libs plplotd-wxwidgets` -c -Wall `wx-config --cxxflags`
See dat?
