EXTRA_DIST = \
glpk-cli.tex \
index.sty \
mybib.bib \
glpk-cli.pdf

all:

clean-local:
	rm -f *.aux
	rm -f *.bbl
	rm -f *.blg
	rm -f *.gz
	rm -f *.idx
	rm -f *.ilg
	rm -f *.ind
	rm -f *.log
	rm -f *.out
	rm -f *.toc
	rm -f *~

documentation:
	pdflatex glpk-cli.tex
	bibtex glpk-cli
	pdflatex glpk-cli.tex
	makeindex glpk-cli.idx
	pdflatex glpk-cli.tex

install:
	mkdir -p -m 755 $(DESTDIR)${docdir};true
	install -m 644 glpk-cli.pdf $(DESTDIR)${docdir}/glpk-cli.pdf

check:
