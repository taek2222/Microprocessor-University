#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked.h"


struct node {
	int		data;
	struct node	*link;
};

struct node *Head = NULL;

struct node *get_node() // 메모리 할당
{
	struct node *cp;

	cp = (struct node *)malloc(sizeof(struct node));
	return(cp);
}

void free_node(struct node *np)
{
	free(np);
}

void insert_node_head(struct node *np) // 헤더
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
// list h 입력 후 a, b, c, d, e, f 입력 시
// f - e - d - c - b - a 출력

void insert_node_tail(struct node *np) // 꼬리
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
// list t 입력 후 a, b, c, d, e, f 입력 시
// a - b - c - d - e - f 출력


void insert_node_ascn(struct node *np) // 오름 차순 
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
// list 입력 후 a, b, c, d, e, f 입력 시
// a - b - c - d - e - f 출력

void insert_node_desc(struct node *np) { // 내림 차순
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
// list 입력 후 a, b, c, d, e, f 입력 시
// f - e - d - c - b - a 출력

void tour_list() { // list 배열 출력
	struct node *cp;
	printf("\n");
	
	for ( cp = Head; cp != NULL; cp = cp-> link)
		printf("-->%c ", cp-> data);
	printf("\n");
}

void free_list() // 노드 반납
{
	struct node *cp;
	
	for(; Head != NULL; ) {
		cp = Head;
		Head = cp->link;
		free_node(cp);
	}
}	

void app_list(char *ap) // list 명령어 실행
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
			case 'h' : insert_node_head(np); break; // 헤더
			case 't' : insert_node_tail(np); break; // 꼬리
			case 'd' : insert_node_desc(np); break; // 내림차순
			default : insert_node_ascn(np); // 오름차순
		}
	}
	tour_list(); // 리스트 출력
	free_list(); // 메모리 반납
}

