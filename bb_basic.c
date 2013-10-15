#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fori(i,start,end) for((i)=(start);(i)<(end);(i)++)
#define max(a,b) (((a)>(b))?(a):(b))

struct Item
{
  int weight;
  int value;
};

struct Item *g_items;
int g_items_count;
int g_best_value;

void load_items(const char *file, int *capacity)
{
  FILE *input = fopen(file, "r");
  fscanf(input, "%d", &g_items_count);
  fscanf(input, "%d", capacity);

  g_items = (struct Item *)malloc((g_items_count) * sizeof(struct Item));

  int i;
  fori(i,0,g_items_count)
  {
    fscanf(input, "%d %d\n", &g_items[i].weight, &g_items[i].value);
  }

  fclose(input);
}

double count_rest(int from, int rest_capacity, int orig)
{
  double temp = orig;
  int i;

  if (rest_capacity < 0)
    return orig;

  fori(i,from,g_items_count)
  {
    if (rest_capacity < g_items[i].weight)
    {
      temp += ((double)g_items[i].value / g_items[i].weight * rest_capacity);
      return temp;
    }
    else
    {
      temp += g_items[i].value;
      rest_capacity -= g_items[i].weight;
    }
  }

  return temp;
}

#define EPS 1e-8
void bb(int capacity, int value, double estimate, int i)
{
  //printf("    capacity: %d\n", capacity);
  //printf("       value: %d\n", value);
  //printf("    estimate: %d\n", estimate);

  if (estimate - EPS < g_best_value || capacity < 0)
  {
    //printf("    -- Branch not accepted\n");
    return;
  }


  //printf("    best value: %d\n", g_best_value);

  if (i < g_items_count)
  {
    //printf("Item: %d\n", i+1);

    bb(capacity - g_items[i].weight, value + g_items[i].value,
      count_rest(i+1, capacity - g_items[i].weight, value + g_items[i].value),
      i+1);
    bb(capacity, value, count_rest(i+1, capacity, value), i+1);
  }
  else if(value > g_best_value)
  {
    g_best_value = value;
  }
}

int solve(int capacity)
{

  bb(capacity, 0, count_rest(0, capacity, 0), 0);

  return g_best_value;
}

int comp(const void *elem1, const void *elem2)
{
    struct Item f = *((struct Item*)elem1);
    struct Item s = *((struct Item*)elem2);

    double ratio_f = (double)f.value / f.weight;
    double ratio_s = (double)s.value / s.weight;

    if (ratio_f < ratio_s) return 1;
    if (ratio_s > ratio_f) return -1;

    return 0;
}

void knapsack(const char *file)
{
  int capacity;

  load_items(file, &capacity);
  int i;

  qsort(g_items, g_items_count, sizeof(struct Item), comp);

  int value = solve(capacity);
  printf("Total value: %d\n", g_best_value);

  free(g_items);
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
