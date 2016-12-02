all: bison flex gcc
	@echo "Feito."

bison: Parser.y
	bison Parser.y

flex: Scanner.l
	flex Scanner.l

gcc: Scanner.c Parser.c Arvore.c
	gcc -Wall -o trab4 Scanner.c Parser.c Arvore.c Tabelas.c -ly

clean:
	@rm -f *.o Scanner.c Parser.h Parser.c trab4
