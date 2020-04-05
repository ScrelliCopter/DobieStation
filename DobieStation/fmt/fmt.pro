# Staticlib configuration for qmake builds
# For some reason qmake 3.1 fails to identify source dependencies and excludes format.cc and printf.cc
# from compilation so it _MUST_ be called as qmake -nodepend
# A workaround is implemented below: a custom compiler is defined which does not track dependencies

TEMPLATE = lib

TARGET = fmt

QMAKE_EXT_CPP = .cc

CONFIG = staticlib warn_on c++11

# Can't use INCLUDEPATH because custom compiler workaround, unfortunately
FMT_INCLUDEPATH = ../../ext/fmt/include
FMT_FLAGS = -I$$FMT_INCLUDEPATH
#INCLUDEPATH += $$FMT_INCLUDEPATH

FMT_SOURCES = \
    ../../ext/fmt/src/format.cc \
    ../../ext/fmt/src/posix.cc

fmt.name = libfmt
fmt.input = FMT_SOURCES
fmt.output = ${QMAKE_FILE_BASE}$$QMAKE_EXT_OBJ
fmt.clean = ${QMAKE_FILE_BASE}$$QMAKE_EXT_OBJ
fmt.depends = ${QMAKE_FILE_IN}
# QMAKE_RUN_CXX will not be expanded
fmt.commands = $$QMAKE_CXX -c $$QMAKE_CXXFLAGS $$QMAKE_CXXFLAGS_WARN_ON $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO $$QMAKE_CXXFLAGS_CXX11 $$FMT_FLAGS ${QMAKE_FILE_IN}
fmt.variable_out = OBJECTS
fmt.CONFIG = no_dependencies no_link
QMAKE_EXTRA_COMPILERS += fmt