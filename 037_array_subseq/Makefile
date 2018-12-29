FLAGS=-std=gnu99 -Wall 
maxSeq: test-subseq.o maxSeq.o
	gcc -o maxSeq test-subseq.o maxSeq.o
test-subseq.o: test-subseq.c
	gcc $(FLAGS) -c test-subseq.c
maxSeq.o: maxSeq.c
	gcc $(FLAGS) -c maxSeq.c
