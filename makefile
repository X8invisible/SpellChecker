all: compile sentences single delete
compile: spell.c dictionary_search.c
	cl spell.c dictionary_search.c
sentences:
	spell -i sentences_test.txt
	spell -i sentences_test.txt -c
single:
	spell -i single_words_test.txt
	spell -i single_words_test.txt -c
delete:
	del *.obj *.exe