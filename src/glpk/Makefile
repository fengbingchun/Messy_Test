NAME = `pwd | awk -f getlastfragment.awk`
all:
clean:
dist: distclean
	tar -C .. -cf ../$(NAME).tar $(NAME)
	gzip -f ../$(NAME).tar;md5sum ../$(NAME).tar.gz > ../$(NAME).tar.gz.md5
distclean:
	rm -f *~
	-find . -name .svn -exec rm {} -r -f \;
install:
check:
