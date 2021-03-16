TARGET=obigo_child

INCLUDE=-I../CommonAPI/src-gen -I$(SDKTARGETSYSROOT)/usr/include/CommonAPI-3.1/ -I$(SDKTARGETSYSROOT)/usr/include/dbus-1.0 -I$(SDKTARGETSYSROOT)/usr/lib/dbus-1.0/include/
LIBRARY=-lwayland-client -livi-application -lwayland-egl -lEGL -lGLESv2 -lCommonAPI -lCommonAPI-DBus -ldbus-1
SRC=main.cpp SubSurface.cpp SubSurfaceManager.cpp ObigoProxy.cpp EGLClient.cpp
SRC+=../CommonAPI/src-gen/v1/commonapi/examples/ObigoTestDBusProxy.cpp ../CommonAPI/src-gen/v1/commonapi/examples/ObigoTestDBusDeployment.cpp
CXXFLAGS+=-fpermissive -Wno-write-strings

all:
	$(CXX) -o $(TARGET) $(SRC) $(CXXFLAGS) $(INCLUDE) $(LIBRARY)

clean:
	rm  $(TARGET)
