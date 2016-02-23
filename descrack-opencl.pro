TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

LIBS += -lpthread -l:libOpenCL.so.1 -lcrypto

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/desutils.cpp \
    src/keybatchdistributor.cpp \
    src/devicecrackingcontext.cpp \
    src/descracker.cpp \
    src/gpu/processingunit.cpp \
    src/gpu/devicecontext.cpp \
    src/gpu/globalcontext.cpp \
    src/gpu/kernelloader.cpp \
    src/gpu/devicelistcontext.cpp \
    src/gpu/uintprogramtraits.cpp \
    src/gpu/programcontext.cpp \
    src/tests/tests.cpp

HEADERS += \
    src/keydata.h \
    src/keybatchdistributor.h \
    src/descracker.h \
    src/devicecrackingcontext.h \
    src/desutils.h \
    src/alignment.h \
    src/gpu/opencl.h \
    src/gpu/cl.hpp \
    src/gpu/processingunit.h \
    src/gpu/devicecontext.h \
    src/gpu/globalcontext.h \
    src/gpu/kernelloader.h \
    src/gpu/programcontext.h \
    src/gpu/devicelistcontext.h \
    src/gpu/uintprogramtraits.h \
    src/gpu/kernelconfig.h \
    src/tests/tests.h

OTHER_FILES += \
    data/opencl/kernels/des_sboxes_openwall.h \
    data/opencl/kernels/des_sboxes_openwall_bitsel.h \
    data/opencl/kernels/des_vector_uint.h \
    data/opencl/kernels/des_tables.h \
    data/opencl/kernels/des_sboxes_mkwan.h \
    data/opencl/kernels/des.cl \
    data/opencl/kernels/c_compat.h
