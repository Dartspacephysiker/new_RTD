# examples/c++/Makefile.examples.in for PLplot
###
### Process this file with configure to produce Makefile.examples
###
# Copyright (C) 2002, 2004  Alan W. Irwin
# Copyright (C) 2004  Rafael Laboissiere
# Copyright (C) 2004  Andrew Ross
#
# This file is part of PLplot.
#
# PLplot is free software; you can redistribute it and/or modify
# it under the terms of the GNU Library General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# PLplot is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public License
# along with the file PLplot; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

CXX = /usr/bin/x86_64-linux-gnu-g++
EXEEXT = 

LIB_TAG = d
PKG_CONFIG_ENV = PKG_CONFIG_PATH="/usr/lib/pkgconfig"
RPATHCMD = 
QT_MOC_EXECUTABLE = /usr/lib/x86_64-linux-gnu/qt4/bin/moc
qt_RPATHCMD = 

PLPLOTWXWIDGETS_EXECUTABLES_list = \
	wxPLplotDemo$(EXEEXT)

qt_gui_EXECUTABLES_list = \
	qt_example$(EXEEXT)

EXECUTABLES_list = \
		 x01cc$(EXEEXT) \
		 x00$(EXEEXT) \
		 x01$(EXEEXT) \
		 x02$(EXEEXT) \
		 x03$(EXEEXT) \
		 x04$(EXEEXT) \
		 x05$(EXEEXT) \
		 x06$(EXEEXT) \
		 x07$(EXEEXT) \
		 x08$(EXEEXT) \
		 x09$(EXEEXT) \
		 x10$(EXEEXT) \
		 x11$(EXEEXT) \
		 x12$(EXEEXT) \
		 x13$(EXEEXT) \
		 x14$(EXEEXT) \
		 x15$(EXEEXT) \
		 x16$(EXEEXT) \
		 x17$(EXEEXT) \
		 x18$(EXEEXT) \
		 x19$(EXEEXT) \
		 x20$(EXEEXT) \
		 x21$(EXEEXT) \
		 x22$(EXEEXT) \
		 x23$(EXEEXT) \
		 x24$(EXEEXT) \
		 x25$(EXEEXT) \
		 x26$(EXEEXT) \
		 x27$(EXEEXT) \
		 x28$(EXEEXT) \
		 x29$(EXEEXT) \
		 x30$(EXEEXT) \
		 x31$(EXEEXT) \
		 x33$(EXEEXT) \
		 $(PLPLOTWXWIDGETS_EXECUTABLES_list) \
		 $(qt_gui_EXECUTABLES_list)


all: $(EXECUTABLES_list)

clean:
	rm -f $(EXECUTABLES_list)

wxPLplotDemo$(EXEEXT): wxPLplotDemo.cpp
	$(CXX) $< -o $@ $(RPATHCMD) `$(PKG_CONFIG_ENV) pkg-config  --cflags --libs plplot$(LIB_TAG)-wxwidgets` -Wall `wx-config --cxxflags`

# Note, must filter out -p options which confuse $(QT_MOC_EXECUTABLE).  Such
# options (e.g., -pthread) tend to appear in the static driver case.
moc_qt_PlotWindow.cpp: qt_PlotWindow.h
	$(QT_MOC_EXECUTABLE) `$(PKG_CONFIG_ENV) pkg-config  --cflags-only-I plplot$(LIB_TAG)-qt` $< -o $@

qt_example$(EXEEXT): qt_example.cpp qt_PlotWindow.cpp moc_qt_PlotWindow.cpp
	$(CXX) qt_example.cpp qt_PlotWindow.cpp moc_qt_PlotWindow.cpp -o $@ $(qt_RPATHCMD) `$(PKG_CONFIG_ENV) pkg-config  --cflags --libs plplot$(LIB_TAG)-qt` `$(PKG_CONFIG_ENV) pkg-config  --cflags --libs plplotd`

.cc$(EXEEXT):
	$(CXX) $< -o $@ $(RPATHCMD) `$(PKG_CONFIG_ENV) pkg-config  --cflags --libs plplot$(LIB_TAG)-c++` `wx-config --cxxflags`

.SUFFIXES: .cc $(EXEEXT)
