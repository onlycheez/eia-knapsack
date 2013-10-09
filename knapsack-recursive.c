
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Item Item;

char *g_solution;
Item *g_items;

struct _Item
{
  unsigned weight;
  unsigned value;
};

void load_items(const char *file, unsigned *items_cnt, unsigned *capacity)
{
  FILE *input = fopen(file, "r");
  fscanf(input, "%ul", items_cnt);
  fscanf(input, "%ul", capacity);

  g_items = malloc((long unsigned)(*items_cnt) * sizeof(Item));

  int i;
  for (i = 0; i < *items_cnt; i++)
  {
    fscanf(input, "%u %u\n", &(g_items[i].weight), &(g_items[i].value));
  }

  fclose(input);
}

unsigned max(unsigned a, unsigned b)
{
  return (a > b) ? a : b;
}

unsigned O(unsigned k, unsigned j)
{
  if (j == -1)
  {
    return 0;
  }

  unsigned w = g_items[j].weight;
  unsigned v = g_items[j].value;

  if (w > k)
  {
    return O(k, j - 1);
  }

  //return max(O(k, j - 1), O(k - w, j - 1) + v);
  unsigned a = O(k, j - 1);
  unsigned b = O(k - w, j - 1) + v;
  if (b > a)
  {
    g_solution[j] = 1;
    return b;
  }
  else
  {
    return a;
  }
}

unsigned solve(unsigned items_cnt, unsigned capacity)
{
  g_solution = malloc(items_cnt * sizeof(Item));
  memset(g_solution, 0, items_cnt * sizeof(Item));
  return O(capacity, items_cnt - 1);
}

void knapsack(const char *file)
{
  unsigned capacity, items_cnt;

  load_items(file, &items_cnt, &capacity);

  unsigned value = solve(items_cnt, capacity);
  printf("Total value: %u\n", value);

  int i;
  for (i = 0; i < items_cnt; i++)
  {
    printf("%d ", g_solution[i]);
  }

  printf("\n");

  free(g_items);
  free(g_solution);
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    printf("Missing input file.\n");
    return 1;
  }

  knapsack(argv[1]);

  return 0;
}

