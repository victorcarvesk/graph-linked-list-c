#include <stdio.h>


#include "../libs/graph.h"

void main(int argc, char *argv[])
{
  char *file;

  if (argc == 2) file = argv[1];

  Vertice *graph = load_graph(file);

  print_graph(graph);

}