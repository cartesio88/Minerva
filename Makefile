OUTPUTDIR = bin/
OBJSDIR = obj/
BULLETDIR = bullet-2.78

#To build libs, please run a 'make libs' first!

all: credentials dirs libs
	cd source; $(MAKE)

libs: ARTK BULLET

credentials:
	@echo "Minerva's Makefile, by César Mora Castro."

dirs:
	mkdir -p $(OUTPUTDIR)
	mkdir -p $(OBJSDIR)

ARTK:
	cd lib/ARToolKit; $(MAKE)

BULLET:
	cd lib/$(BULLETDIR); rm -f CMakeCache.txt; cmake -DBUILD_EXTRAS=OFF -DBUILD_DEMOS=OFF . -G "Unix Makefiles"; $(MAKE)

clean:
	cd source; $(MAKE) clean

allclean: clean
	cd lib/ARToolKit; $(MAKE) clean
	cd lib/$(BULLETDIR); $(MAKE) clean
	rm -Rf bin

install:
	mkdir -p $(DESTDIR)/usr/bin
	mkdir -p $(DESTDIR)/usr/share/minerva/data
	cp bin/minerva $(DESTDIR)/usr/bin
	cp usr/share/minerva/data/camera_para.dat $(DESTDIR)/usr/share/minerva/data
