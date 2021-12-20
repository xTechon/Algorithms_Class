#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

struct node {
  int value;
  int cost;
  int pX;
  int pY;
  int X;
  int Y;
};

typedef struct node NODE;

struct entry {
  NODE *data;
  STAILQ_ENTRY(entry) next;
};

STAILQ_HEAD(listHead, entry);
// sets all values on map to int value
void setMap(int sizeX, int sizeY, NODE map[sizeX][sizeY], int value) {
  int i, j;
  for (i = 0; i < sizeY; i++) {
    for (j = 0; j < sizeX; j++) {
      map[i][j].value = value;
    }
  }
  return;
}
// sets all cost values on map to int cost
void setCostUni(int sizeX, int sizeY, NODE map[sizeX][sizeY], int cost) {
  int i, j;
  for (i = 0; i < sizeY; i++) {
    for (j = 0; j < sizeX; j++) {
      map[i][j].cost = cost;
    }
  }
  return;
}
// resets the parents of all nodes on the map
void resetPar(int sizeX, int sizeY, NODE map[sizeX][sizeY]) {
  int i, j;
  for (i = 0; i < sizeY; i++) {
    for (j = 0; j < sizeX; j++) {
      map[i][j].pX = -1;
      map[i][j].pY = -1;
    }
  }
  return;
}
// colors for map
void resetColor() { printf("\033[0m"); }

void red() { printf("\033[1;31m"); }

void yellow() { printf("\033[1;33m"); }

void blue() { printf("\033[0;34m"); }

// prints out the entire map
void printMap(int sizeX, int sizeY, NODE map[sizeX][sizeY]) {
  int i, j;
  resetColor();
  printf("    ");
  for (i = 0; i < sizeX; i++) {
    printf("|%3d ", i);
  }
  printf("\n---");
  for (j = 0; j < sizeX; j++)
    printf("-----");
  printf("\n");
  for (i = 0; i < sizeY; i++) {
    resetColor();
    printf("%3d ", i);
    for (j = 0; j < sizeX; j++) {
      blue();
      if (map[j][i].value >= 0) {
        yellow();
      }
      printf("|%3d ", map[j][i].value);
    }
    printf("\n---");
    for (j = 0; j < sizeX; j++)
      printf("-----");
    printf("\n");
  }
  resetColor();
  return;
}

void getHead(struct listHead *head, struct entry *item) {
  item = STAILQ_FIRST(head);
  return;
}

// prints out the entire map and highlights the head of the queue in red
void printMapQueue(int sizeX, int sizeY, NODE map[sizeX][sizeY],
                   struct listHead *head) {
  int i, j;
  struct entry *item = malloc(sizeof(struct entry));
  memset(item, 0, sizeof(struct entry));
  item = STAILQ_FIRST(head);
  resetColor();
  printf("    ");
  for (i = 0; i < sizeX; i++) {
    printf("|%3d ", i);
  }
  printf("\n---");
  for (j = 0; j < sizeX; j++)
    printf("-----");
  printf("\n");
  for (i = 0; i < sizeY; i++) {
    resetColor();
    printf("%3d ", i);
    for (j = 0; j < sizeX; j++) {
      blue();
      if (map[j][i].value >= 0) {
        yellow();
      }
      // color red if it's the head of the queue
      if ((j == (*item->data).X) && (i == (*item->data).Y)) {
        red();
      }
      printf("|%3d ", map[j][i].value);
    }
    printf("\n---");
    for (j = 0; j < sizeX; j++)
      printf("-----");
    printf("\n");
  }
  resetColor();
  item = NULL;
  free(item);
  return;
}
// Breadth First search generation of field of movement given limit
void BFS(int sizeX, int sizeY, NODE map[sizeX][sizeY], int x, int y,
         int limit) {
  int i, j, c = limit;
  map[x][y].value = limit;
  map[x][y].pX = -2;
  map[x][y].pY = -2;
  map[x][y].X = x;
  map[x][y].Y = y;

  struct listHead head; // Define the head of the queue
  STAILQ_INIT(&head);   // initalize the head
  struct entry *item;   // create queue object
  struct entry *nItem;  // new item for later
  // Fill queue object
  item = malloc(sizeof(struct entry));
  item->data = &map[x][y];
  // Enqueue the first node into the queue
  STAILQ_INSERT_HEAD(&head, item, next);
  // printf("\n limit - c = %d", limit - c);
  while (STAILQ_EMPTY(&head) == 0) {
    item = STAILQ_FIRST(&head);
    i = (*item->data).X;
    j = (*item->data).Y;
    // printf("\n item has coord: %d,%d", i, j);
    // if value is < 0, it is unvisited
    // west 1
    if (map[i - 1][j].value < 0) {
      // set values for the map item
      map[i - 1][j].value = map[i][j].value - 1;
      map[i - 1][j].pX = i;
      map[i - 1][j].pY = j;
      map[i - 1][j].X = i - 1;
      map[i - 1][j].Y = j;
      // crate a new link object
      nItem = malloc(sizeof(struct entry));
      nItem->data = &map[i - 1][j];
      // queue the new item into the link
      STAILQ_INSERT_TAIL(&head, nItem, next);
    }
    // east 1
    if (map[i + 1][j].value < 0) {
      // set values for the map item
      map[i + 1][j].value = map[i][j].value - 1;
      map[i + 1][j].pX = i;
      map[i + 1][j].pY = j;
      map[i + 1][j].X = i + 1;
      map[i + 1][j].Y = j;
      // crate a new link object
      nItem = malloc(sizeof(struct entry));
      nItem->data = &map[i + 1][j];
      // queue the new item into the link
      STAILQ_INSERT_TAIL(&head, nItem, next);
    }
    // south 1
    if (map[i][j - 1].value < 0) {
      // set values for the map item
      map[i][j - 1].value = map[i][j].value - 1;
      map[i][j - 1].pX = i;
      map[i][j - 1].pY = j;
      map[i][j - 1].X = i;
      map[i][j - 1].Y = j - 1;
      // crate a new link object
      nItem = malloc(sizeof(struct entry));
      nItem->data = &map[i][j - 1];
      // queue the new item into the link
      STAILQ_INSERT_TAIL(&head, nItem, next);
    }
    // north 1
    if (map[i][j + 1].value < 0) {
      // set values for the map item
      map[i][j + 1].value = map[i][j].value - 1;
      map[i][j + 1].pX = i;
      map[i][j + 1].pY = j;
      map[i][j + 1].X = i;
      map[i][j + 1].Y = j + 1;
      // crate a new link object
      nItem = malloc(sizeof(struct entry));
      nItem->data = &map[i][j + 1];
      // queue the new item into the link
      STAILQ_INSERT_TAIL(&head, nItem, next);
    }
    // dequeue the vertex from the queue
    if ((*item->data).value < c && (*item->data).value >= 0)
      c = (*item->data).value;
    STAILQ_REMOVE_HEAD(&head, next);
    free(item);
    // printf("\n");
    // printMap(sizeX, sizeY, map);
    if (c == 0)
      break;
  }
  // queue deletion
  item = STAILQ_FIRST(&head);
  while (item != NULL) {
    nItem = STAILQ_NEXT(item, next);
    free(item);
    item = nItem;
  }
  return;
}

void printQueue(struct listHead *head, struct entry *item) {
  printf("\nPrinting queue:");
  item = STAILQ_FIRST(head);
  while (item != NULL) {
    printf("\n(%d, %d), value:%d, cost: %d", (*item->data).X, (*item->data).Y,
           (*item->data).value, (*item->data).cost);
    item = STAILQ_NEXT(item, next);
  }
  return;
}

// A cost aware and better version of BFS()
void BFScost(int sizeX, int sizeY, NODE map[sizeX][sizeY], int x, int y,
             int limit) {
  int i, j, c = limit;
  map[x][y].value = limit;
  map[x][y].pX = -2;
  map[x][y].pY = -2;
  map[x][y].X = x;
  map[x][y].Y = y;

  struct listHead head; // Define the head of the queue
  STAILQ_INIT(&head);   // initalize the head
  struct entry *item;   // create queue object
  struct entry *nItem;  // new item for later
  // Fill queue object
  item = malloc(sizeof(struct entry));
  item->data = &map[x][y];
  // Enqueue the first node into the queue
  STAILQ_INSERT_HEAD(&head, item, next);
  // printf("\n limit - c = %d", limit - c);
  while (STAILQ_EMPTY(&head) == 0) {
    item = STAILQ_FIRST(&head);
    i = (*item->data).X;
    j = (*item->data).Y;
    if (map[i][j].value > 0) {
      // printf("\n item has coord: %d,%d", i, j);
      // if value is < 0, it is unvisited
      // west 1
      if (map[i - 1][j].value <= 0) {
        // set values for the map item
        map[i - 1][j].value = map[i][j].value - map[i - 1][j].cost;
        map[i - 1][j].pX = i;
        map[i - 1][j].pY = j;
        map[i - 1][j].X = i - 1;
        map[i - 1][j].Y = j;
        // crate a new link object
        nItem = malloc(sizeof(struct entry));
        nItem->data = &map[i - 1][j];
        // queue the new item into the link
        STAILQ_INSERT_TAIL(&head, nItem, next);
      }
      // east 1
      if (map[i + 1][j].value <= 0) {
        // set values for the map item
        map[i + 1][j].value = map[i][j].value - map[i + 1][j].cost;
        map[i + 1][j].pX = i;
        map[i + 1][j].pY = j;
        map[i + 1][j].X = i + 1;
        map[i + 1][j].Y = j;
        // crate a new link object
        nItem = malloc(sizeof(struct entry));
        nItem->data = &map[i + 1][j];
        // queue the new item into the link
        STAILQ_INSERT_TAIL(&head, nItem, next);
      }
      // south 1
      if (map[i][j - 1].value <= 0) {
        // set values for the map item
        map[i][j - 1].value = map[i][j].value - map[i][j - 1].cost;
        map[i][j - 1].pX = i;
        map[i][j - 1].pY = j;
        map[i][j - 1].X = i;
        map[i][j - 1].Y = j - 1;
        // crate a new link object
        nItem = malloc(sizeof(struct entry));
        nItem->data = &map[i][j - 1];
        // queue the new item into the link
        STAILQ_INSERT_TAIL(&head, nItem, next);
      }
      // north 1
      if (map[i][j + 1].value <= 0) {
        // set values for the map item
        map[i][j + 1].value = map[i][j].value - map[i][j + 1].cost;
        map[i][j + 1].pX = i;
        map[i][j + 1].pY = j;
        map[i][j + 1].X = i;
        map[i][j + 1].Y = j + 1;
        // crate a new link object
        nItem = malloc(sizeof(struct entry));
        nItem->data = &map[i][j + 1];
        // queue the new item into the link
        STAILQ_INSERT_TAIL(&head, nItem, next);
      }
    }
    // dequeue the vertex from the queue
    STAILQ_REMOVE_HEAD(&head, next);
    // printf("\n");
    // printMap(sizeX, sizeY, map);
    memset(item, 0, sizeof(struct entry));
    /*
    printQueue(&head, item);
    item = STAILQ_FIRST(&head);
    if (item != NULL) {
      printf("\n");
      printMapQueue(sizeX, sizeY, map, &head);
      printf("\n");
    }*/
  }
  // queue deletion
  item = STAILQ_FIRST(&head);
  while (item != NULL) {
    nItem = STAILQ_NEXT(item, next);
    free(item);
    item = nItem;
  }
  return;
}

void findPath(int sizeX, int sizeY, NODE map[sizeX][sizeY], int x, int y) {
  int i, j, final = 0, temp;
  setMap(sizeX, sizeY, map, -1);
  i = x;
  j = y;
  map[i][j].value = final;
  while (map[i][j].pX >= 0 && map[i][j].pY >= 0) {
    map[map[i][j].pX][map[i][j].pY].value = ++final;
    temp = map[i][j].pX;
    j = map[i][j].pY;
    i = temp;
  }
  return;
}
int main() {
  int sizeX = 20;
  int sizeY = 20;
  NODE map[sizeX][sizeY];
  // setup the map
  setMap(sizeX, sizeY, map, -1);
  resetPar(sizeX, sizeY, map);
  printMap(sizeX, sizeY, map);
  printf("\n");
  // run BFS on the map
  BFS(sizeX, sizeY, map, 4, 4, 3);
  printMap(sizeX, sizeY, map);
  // generate a path from the tree generated
  findPath(sizeX, sizeY, map, 6, 5);
  printf("\n");
  printMap(sizeX, sizeY, map);
  // reset the map
  resetPar(sizeX, sizeY, map);
  setMap(sizeX, sizeY, map, -1);
  printf("\n");
  printMap(sizeX, sizeY, map);
  printf("\n");
  BFS(sizeX, sizeY, map, 4, 5, 3);
  printMap(sizeX, sizeY, map);
  // rest the map to try a cost aware BFS
  printf("\nSetting costs\nResetting map");
  resetPar(sizeX, sizeY, map);
  setMap(sizeX, sizeY, map, -1);
  // set the cost of all nodes to 2 instead of 1
  setCostUni(sizeX, sizeY, map, 1);
  map[10][13].cost = 2;
  map[8][6].cost = 3;
  map[10][7].cost = 2;
  map[11][10].cost = 2;
  map[12][10].cost = 2;
  map[13][10].cost = 2;
  map[14][10].cost = 2;
  map[15][10].cost = 2;
  // run the cost aware version of BFS on the map
  BFScost(sizeX, sizeY, map, 10, 10, 6);
  printf("\n");
  printMap(sizeX, sizeY, map);
  findPath(sizeX, sizeY, map, 6, 8);
  printf("\n");
  printMap(sizeX, sizeY, map);
  return 0;
}
