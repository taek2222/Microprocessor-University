#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked.h"


struct node {
	int		data;
	struct node	*link;
};

struct node *Head = NULL;

struct node *get_node() // �޸� �Ҵ�
{
	struct node *cp;

	cp = (struct node *)malloc(sizeof(struct node));
	return(cp);
}

void free_node(struct node *np)
{
	free(np);
}

void insert_node_head(struct node *np) // ���
{
	if(!Head) {
		Head = np;
		np -> link = NULL;
	}
	else {
		np -> link = Head;
		Head = np;
	}
}
// list h �Է� �� a, b, c, d, e, f �Է� ��
// f - e - d - c - b - a ���

void insert_node_tail(struct node *np) // ����
{
	struct node *cp;

	if(!Head)
		Head = np;
	else {
		for (cp = Head; cp->link != NULL; cp = cp->link);
		cp -> link = np;
	}
	np -> link = NULL;
}
// list t �Է� �� a, b, c, d, e, f �Է� ��
// a - b - c - d - e - f ���


void insert_node_ascn(struct node *np) // ���� ���� 
{
	struct node *cp, *pp;
	if(!Head) {
		Head = np;
		np -> link = NULL;
	}
	else {
		for (cp = Head, pp = NULL; cp != NULL && cp -> data < np->data;
		pp = cp, cp = cp->link);
		
		if(pp == NULL) {
			np -> link = Head;
			Head = np;
		} else {
			np -> link = pp -> link;
			pp -> link = np;
		}
	}
}
// list �Է� �� a, b, c, d, e, f �Է� ��
// a - b - c - d - e - f ���

void insert_node_desc(struct node *np) { // ���� ����
   struct node *cp, *pp;

   if(!Head) {
      Head = np;
      np->link = NULL;
   } else {
      for(cp = Head, pp = NULL; cp != NULL && cp->data > np->data; pp = cp, cp = cp->link);

      if(pp == NULL) {
         np->link = Head;
         Head = np;
      } else {
         np->link = pp->link;
         pp->link = np;
      }
   }
}
// list �Է� �� a, b, c, d, e, f �Է� ��
// f - e - d - c - b - a ���

void tour_list() { // list �迭 ���
	struct node *cp;
	printf("\n");
	
	for ( cp = Head; cp != NULL; cp = cp-> link)
		printf("-->%c ", cp-> data);
	printf("\n");
}

void free_list() // ��� �ݳ�
{
	struct node *cp;
	
	for(; Head != NULL; ) {
		cp = Head;
		Head = cp->link;
		free_node(cp);
	}
}	

void app_list(char *ap) // list ��ɾ� ����
{
	char buf[8], how = 'a' ;
	struct node *np;

	if (ap) how = *ap;
	while(1) {
		printf( " > ");
		if(fgets(buf, 8, stdin) == NULL)
			break;
		np = get_node();
		np -> data = buf[0];
		switch(how) {
			case 'h' : insert_node_head(np); break; // ���
			case 't' : insert_node_tail(np); break; // ����
			case 'd' : insert_node_desc(np); break; // ��������
			default : insert_node_ascn(np); // ��������
		}
	}
	tour_list(); // ����Ʈ ���
	free_list(); // �޸� �ݳ�
}

