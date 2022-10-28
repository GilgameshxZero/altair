#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

const int MAXN = 100100;

int n;

#define LEFT 0
#define RIGHT 1

struct node{
  node *child[2];
  node *parent;

  node() {
    child[0] = NULL;
    child[1] = NULL;
    parent = NULL;
  }

  int getDirection() {
    if(parent == NULL) return -1;
    if(this == parent -> child[LEFT]) return LEFT;
    if(this == parent -> child[RIGHT]) return RIGHT;
    return -1;
  }

  bool isRoot() {
    return (getDirection() == -1);
  }

  void setChild(int direction, node *c) {
    child[direction] = c;
    if(c != NULL) {
      c -> parent = this;
    }
  }

  void rotateUp() {
    int direction = getDirection();
    node *p = parent;
    if(!p -> isRoot()) {
      p -> parent -> child[p -> getDirection()] = this;
    }
    parent = p -> parent; //warning: changing parent here...
    node *pMid = child[!direction];
    p -> setChild(direction, pMid);
    setChild(!direction, p);
  }
};

node *vert[MAXN];

void splay(node *p) {
  while(!p -> isRoot()) {
    node *p1 = p -> parent;
    if(!p1 -> isRoot()) {
      if(p1 -> getDirection() == p -> getDirection()) {
        p1 -> rotateUp();
      }
      else {
        p -> rotateUp();
      }
    }
    p -> rotateUp();
  }
}
 
node *expose(node *p) {
  int num = 0;
  while(1) {
    splay(p);
    while(p -> child[RIGHT] != NULL) {
      p = p -> child[RIGHT];
    }
    splay(p);
    if(p -> parent == NULL) {
      return p; 
    }
    splay(p -> parent);
    p -> parent -> child[LEFT] = p;
  }
}

/*
 * Specifies the integer N.
 */
void init(int N) {
  n = N;
  for(int i = 0; i < N; ++i) {
    vert[i] = new node();
  }
}

/*
 * Make A the parent of B.
 */
void make_parent(int A, int B) {
  A--;
  B--;
  expose(vert[B]);
  vert[B] -> parent = vert[A];
}

/*
 * Return true if A is an ancestor of B.
 */
bool is_ancestor(int A, int B) {
  A--;
  B--;
  expose(vert[B]);
  vert[B] -> child[LEFT] = NULL;
  splay(vert[A]);
  if(vert[A] -> parent != NULL) {
    return false;
  }
  node *p = vert[B];
  while(p -> parent != NULL) {
    p = p -> parent;
  }
  if(p != vert[A]) {
    return false;
  }
  splay(vert[B]);
  return true;
}
