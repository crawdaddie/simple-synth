#include "graph.h"

Graph *graph_perform(Graph *graph, nframes_t nframes) {
  if (!graph) {
    return NULL;
  };

  graph->perform(graph, nframes);

  if (graph->_graph) {
    graph->perform(graph->_graph, nframes);
  };
  Graph *next = graph->next;
  if (next) {
    return graph_perform(next, nframes); // keep going until you return tail
  };
  return graph;
}

void debug_node(Graph *node, char *text) {
  if (text)
    printf("%s\n", text);
  printf("\tnode &: %#08x\n", node);
  printf("\tnode name: %s\n", node->name);
  printf("\tnode perform: %#08x\n", node->perform);
  printf("\tnode next: %#08x\n", node->next);
  printf("\tnode prev: %#08x\n", node->next);
  printf("\tnode size: %d\n", sizeof(*node));
  printf("\tnode schedule: %d\n", node->schedule);
  /* printf("node add: %#08x\n", node->add); */
}

void debug_graph(Graph *graph) {
  debug_node(graph, NULL);

  if (graph->next) {
    printf("↓\n");
    return debug_graph(graph->next);
  };
  printf("----------\n");
}
Graph *remove_from_graph(Graph *node) {
  Graph *prev = node->prev;
  Graph *next = node->next;
  prev->next = next;
  next->prev = prev;
  free(node);
}

Graph *add_before(Graph *graph_node, Graph *new_node) {
  if (!graph_node) {
    graph_node = new_node;
    return new_node;
  }

  Graph *prev = graph_node->prev;
  if (prev) {
    prev->next = new_node;
  };
  new_node->next = graph_node;
  graph_node->prev = new_node;
  return new_node;
}

Graph *add_after(Graph *graph_node, Graph *new_node) {
  if (!graph_node) {
    graph_node = new_node;
    return graph_node;
  };
  Graph *next = graph_node->next;
  if (next) {
    new_node->next = next;
  };
  new_node->prev = graph_node;
  graph_node->next = new_node;
  return new_node;
}