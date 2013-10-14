#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define fori(i,start,end) for((i)=(start);(i)<(end);(i)++)

#define max(a,b) (((a)>(b))?(a):(b))

unsigned *g_weight;
unsigned *g_value;
unsigned *g_solution;

unsigned **g_table;

void load_items(const char *file, unsigned *items_count, unsigned *capacity)
{
  FILE *input = fopen(file, "r");
  fscanf(input, "%u", items_count);
  fscanf(input, "%u", capacity);

  g_weight = (unsigned*)malloc((*items_count) * sizeof(unsigned));
  g_value = (unsigned*)malloc((*items_count) * sizeof(unsigned));

  int i;
  fori(i,0,*items_count)
  {
    fscanf(input, "%u %u\n", &g_weight[i], &g_value[i]);
  }

  fclose(input);
}

unsigned solve(unsigned *items_count, unsigned *capacity)
{
  g_table = (unsigned**)malloc((*items_count + 1) * sizeof(unsigned *));
  int i;
  fori(i,0,(*items_count)+1)
  {
    g_table[i] = (unsigned*)malloc((*capacity + 1) * sizeof(unsigned));
  }

  fori(i,0,(*capacity)+1)
  {
    g_table[0][i] = 0;
  }

  int j;
  fori(i,1,(*items_count)+1)
  {

    fori(j,0,(*capacity)+1)
    {
      if (j >= g_weight[i-1])
      {
        g_table[i][j] = max(g_table[i-1][j-g_weight[i-1]] + g_value[i-1], g_table[i-1][j]);
      }
      else
      {
        g_table[i][j] = g_table[i-1][j];
      }
    }

  }

  unsigned value = g_table[*items_count][*capacity];

  fori(i,0,*items_count)
  {
    free(g_table[i]);
  }
  free(g_table);

  return value;
}

void knapsack(const char *file)
{
  unsigned capacity, items_count;

  load_items(file, &items_count, &capacity);

  g_solution = (unsigned*)malloc(items_count * sizeof(unsigned));
  memset(g_solution, 0, items_count * sizeof(unsigned));

  unsigned value = solve(&items_count, &capacity);
  printf("Total value: %u\n", value);

  int i;
  fori(i,0,items_count)
  {
    printf("%d ", g_solution[i]);
  }

  printf("\n");

  free(g_weight);
  free(g_value);
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
