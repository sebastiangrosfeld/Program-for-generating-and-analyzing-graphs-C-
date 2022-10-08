grapher: main.c bfs.c dijkstra.c generate.c graph.c handle_files.c random.c validate_input.c help.c
	$(CC) -o grapher $^



grapher_debug: main.c bfs.c dijkstra.c generate.c graph.c handle_files.c random.c validate_input.c help.c
	$(CC) -o grapher $^ -DDEBUG



.PHONY: test

test: test_file test_bfs test_dijkstra test_graph test_arguments



.PHONY: test_file

test_file: prepare_test_file
	@ ./test_file test_files/wf_graph.txt test_files/t_graph.txt

prepare_test_file: test_handle_files.c handle_files.c graph.c
	@ $(CC) -o test_file $^



.PHONY: test_bfs

test_bfs: prepare_test_bfs
	@ ./test_bfs test_files/cos_graph.txt test_files/incos_graph.txt

prepare_test_bfs: test_bfs.c bfs.c handle_files.c graph.c
	@ $(CC) -o test_bfs $^



.PHONY: test_dijkstra

test_dijkstra: prepare_test_dijkstra
	@ ./test_dijkstra test_files/t_graph.txt test_files/dijkstra_test_expected.txt 0 > test_dijkstra_results.txt
	@ ./test_dijkstra test_files/t_graph.txt test_files/dijkstra_test_expected.txt 1
	@ rm test_dijkstra_results.txt

prepare_test_dijkstra: test_dijkstra.c dijkstra.c handle_files.c graph.c
	@ $(CC) -o test_dijkstra $^



.PHONY: test_graph

test_graph: prepare_test_graph
	@ ./test_graph

prepare_test_graph: test_graph.c generate.c handle_files.c graph.c random.c bfs.c
	@ $(CC) -o test_graph $^ -DDEBUG



.PHONY: test_arguments

test_arguments: prepare_test_arguments
	@ echo "It should print invalid mode error"
	@ ./test_arguments mistake graf.txt 2 3 1 2
	@ echo "It should print invalid arguments errors"
	@ ./test_arguments generate_wages graf.txt 0 -1 -1 -2
	@ echo "It should print invalid number of arguments error"
	@ ./test_arguments analyze graf.txt 16 8 11

prepare_test_arguments: test_validate_input.c validate_input.c
	@ $(CC) -o test_arguments $^



.PHONY: clean

clean:
	@ rm -f test_file test_bfs test_dijkstra test_graph test_arguments test_graph_output.txt grapher grapher_debug
