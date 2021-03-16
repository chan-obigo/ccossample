all:
	./CommonAPI/cgen/commonapi-generator/commonapi-generator-linux-x86_64 -d ./CommonAPI/src-gen -sk ./CommonAPI/fidl/sample_ipc.fidl
	./CommonAPI/cgen/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86_64 -d ./CommonAPI/src-gen ./CommonAPI/fidl/sample_ipc.fidl
	mkdir -p obigo_parent/obigoparent_source/build
	qmake obigo_parent/obigoparent_source/obigoparent.pro -o obigo_parent/obigoparent_source/build
	make -C obigo_parent/obigoparent_source/build
	make -C obigo_child

install:
	mkdir -p output/lib/systemd/system
	mkdir -p output/ccos/apps/hmi/obigo_parent
	mkdir -p output/ccos/apps/hmi/obigo_child
	cp obigo_parent/obigoparent_recipe/obigoparent/obigo_parent.service output/lib/systemd/system
	cp obigo_parent/obigoparent_source/appinfo.json output/ccos/apps/hmi/obigo_parent
	cp obigo_parent/obigoparent_source/build/obigo_parent output/ccos/apps/hmi/obigo_parent
	cp obigo_child/obigo_child output/ccos/apps/hmi/obigo_child

clean:
	rm -rf output
	rm -rf CommonAPI/src-gen
	make -C obigo_parent/obigoparent_source/build clean
	make -C obigo_child	clean
