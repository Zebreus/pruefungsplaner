#!/bin/sh

DESTDIR=../built-frontend
qmake pruefungsplaner.pro QMAKE_CXXFLAGS_RELEASE="'"-O${optimization_level}"'" QMAKE_LFLAGS_RELEASE="'"-O${optimization_level}"'" DESTDIR=${DESTDIR}
make -j ${make_threads}
cp -r concourse/web/. ${DESTDIR}
