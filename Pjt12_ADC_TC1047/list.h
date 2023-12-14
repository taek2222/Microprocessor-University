#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>

struct node{
	int	data;
	struct node *link;
};

extern struct node *Head;

struct node *get_node();
void free_node(struct node *np);

void insert_node_head(struct node *np), insert_node_tail(struct node *np), insert_node_ascn(struct node *np);

void tour_list(), free_list();
