main: main.o book_management.o User_management.o User.o librarian.o utility.o search.o borrow_management.o
	gcc -o $@ $^
main.o: main.c book_management.h User_management.h librarian.h User.h utility.h
	gcc -c $<
book_management.o: book_management.c book_management.h utility.h
	gcc -c $<
User_management.o: User_management.c User_management.h utility.h
	gcc -c $<
User.o: User.c utility.h book_management.h User_management.h borrow_management.h search.h User.h
	gcc -c $<
librarian.o: librarian.c utility.h book_management.h User_management.h search.h librarian.h
	gcc -c $<
utility.o: utility.c User_management.h book_management.h
	gcc -c $<
search.o: search.c utility.h book_management.h search.h librarian.h
	gcc -c $<
borrow_management.o: borrow_management.c utility.h book_management.h User_management.h User.h borrow_management.h
	gcc -c $<
clean:
	rm -rf *.o main
