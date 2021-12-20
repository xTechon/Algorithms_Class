#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

// define data type for the queue, this is defining how the link is structured
struct entry {
  int data;
  STAILQ_ENTRY(entry) entries;
};

STAILQ_HEAD(slisthead, entry);

int main() {
  struct slisthead head; // Defines the head
  STAILQ_INIT(&head);    // Initalizes the queue at the head

  struct entry *n1;
  n1 = malloc(sizeof(struct entry));
  n1->data = 10;
  STAILQ_INSERT_HEAD(&head, n1, entries); // insert at head

  n1 = malloc(sizeof(struct entry));
  n1->data = 15;
  STAILQ_INSERT_TAIL(&head, n1, entries); // insert at TIAL

  STAILQ_FOREACH(n1, &head, entries)
  printf("\n%d", n1->data);

  return 0;
}
