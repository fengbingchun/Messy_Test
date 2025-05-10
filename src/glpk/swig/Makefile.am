EXTRA_DIST = *.i *.h *.java pom.xml src/site

# copy version-info from glpk package: src/Makefile.am
VERSION_INFO = 43:0:3

all:
	mkdir -p target/classes
	mkdir -p target/apidocs
	mkdir -p src/c
	mkdir -p src/main/java/org/gnu/glpk
	cp ${srcdir}/*.java src/main/java/org/gnu/glpk
	$(SWIG) $(SWIGFLAGS) -java -package org.gnu.glpk \
	  -o src/c/glpk_wrap.c -outdir src/main/java/org/gnu/glpk \
	  ${srcdir}/glpk.i
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) $(CPPFLAGS) -I. -c -fPIC \
	  src/c/glpk_wrap.c
	$(LIBTOOL) --mode=link \
	  $(CC) -version-info $(VERSION_INFO) -revision $(PACKAGE_VERSION) \
	  -g -O -o libglpk_java.la -rpath ${prefix}/lib/jni glpk_wrap.lo \
	  $(LDFLAGS) -lglpk 
	$(JAVADOC) -locale en_US \
	-encoding UTF-8 -charset UTF-8 -docencoding UTF-8 \
	-sourcepath ./src/main/java org.gnu.glpk -d ./target/apidocs
	$(JAR) cf glpk-java-javadoc.jar -C ./target/apidocs .
	$(JAR) cf glpk-java-sources.jar -C ./src/main/java .
	$(JAVAC) -source 1.8 -target 1.8 -classpath ./src/main/java \
	  -d ./target/classes *.java 
	$(JAR) cf glpk-java.jar -C ./target/classes .
if HAVEMVN
	$(MVN) clean package site
endif

clean-local:
	rm -f -r src/main src/c target .libs
	rm -f *.jar *.o *.la *.lo ../examples/java/*.class
	rm -rf target 
	rm -f *~ ../examples/java/*~ ../w32/*~ ../w64/*~

documentation:

install:
	mkdir -p -m 755 $(DESTDIR)${libdir}/jni;true
	$(LIBTOOL) --mode=install install -c libglpk_java.la \
	  $(DESTDIR)${libdir}/jni/libglpk_java.la
	$(LIBTOOL) --mode=finish $(DESTDIR)${libdir}/jni
	mkdir -p -m 755 $(DESTDIR)${datarootdir}/java;true
	install -m 644 glpk-java.jar \
	  $(DESTDIR)${datarootdir}/java/glpk-java-$(PACKAGE_VERSION).jar
	cd $(DESTDIR)${prefix}/share/java/; \
	  $(LN_S) -f glpk-java-$(PACKAGE_VERSION).jar glpk-java.jar
	mkdir -p -m 755 $(DESTDIR)${docdir};true
	install -m 644 glpk-java-javadoc.jar \
	  $(DESTDIR)${docdir}/glpk-java-javadoc-$(PACKAGE_VERSION).jar
	cd $(DESTDIR)${docdir}; \
	  $(LN_S) -f glpk-java-javadoc-$(PACKAGE_VERSION).jar \
	  glpk-java-javadoc.jar
	install -m 644 glpk-java-sources.jar \
	  $(DESTDIR)${docdir}/glpk-java-sources-$(PACKAGE_VERSION).jar
	cd $(DESTDIR)${docdir}; \
	  $(LN_S) -f glpk-java-sources-$(PACKAGE_VERSION).jar \
	  glpk-java-sources.jar

check:
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 \
	  -classpath ../../swig/glpk-java.jar Gmpl.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. Gmpl marbles.mod
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 -classpath \
	  ../../swig/glpk-java.jar Lp.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. Lp
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 -classpath \
	  ../../swig/glpk-java.jar Mip.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. Mip
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 \
	   -classpath ../../swig/glpk-java.jar OutOfMemory.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	   -classpath ../../swig/glpk-java.jar:. OutOfMemory
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 \
	   -classpath ../../swig/glpk-java.jar ErrorDemo.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	   -classpath ../../swig/glpk-java.jar:. ErrorDemo
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 \
	  -classpath ../../swig/glpk-java.jar LinOrd.java
	cd ../examples/java && rm -f tiw56r72.sol && \
	  java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. LinOrd tiw56r72.mat \
	  tiw56r72.sol && rm tiw56r72.sol
	cd ../examples/java; $(JAVAC) -source 1.8 -target 1.8 \
	  -classpath ../../swig/glpk-java.jar MinimumCostFlow.java
	cd ../examples/java; rm -f mincost.dimacs mincost.lp && \
	  java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. MinimumCostFlow && \
	  rm mincost.dimacs mincost.lp
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 \
	  -classpath ../../swig/glpk-java.jar Relax4.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. Relax4 sample.min

check-swing:
	cd ../examples/java;$(JAVAC) -source 1.8 -target 1.8 \
	  -classpath ../../swig/glpk-java.jar GmplSwing.java
	cd ../examples/java;java -Djava.library.path=../../swig/.libs \
	  -classpath ../../swig/glpk-java.jar:. GmplSwing marbles.mod


dist-hook:
	rm -rf `find $(distdir) -name '*~'`
	rm -rf `find $(distdir) -name .svn`
	rm -rf `find $(distdir) -name '*.bak'`
	rm -f ../examples/java/mincost.dimacs ../examples/java/mincost.lp
	rm -f ../examples/java/tiw56r72.sol

