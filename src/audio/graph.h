#ifndef _GRAPH
#define _GRAPH

#include "../config.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeData {
} NodeData;

typedef void (*t_perform)(void *node, nframes_t nframes);
struct Graph {
  char *name;
  struct Graph *next;
  struct Graph *prev;
  struct Graph *_graph;
  NodeData *data;
  sample_t *out;
  int schedule;
  int should_free;
  t_perform perform;
};
typedef struct Graph Graph;

Graph *graph_perform(Graph *graph, nframes_t nframes);
Graph *add_before(Graph *graph_node, Graph *new_node);
Graph *add_after(Graph *graph_node, Graph *new_node);

Graph *remove_from_graph(Graph *node);

void debug_graph(Graph *graph);
void debug_node(Graph *node, char *text);

#endif