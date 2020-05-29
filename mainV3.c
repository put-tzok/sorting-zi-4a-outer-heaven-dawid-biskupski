#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10000, 15000, 20000, 25000, 30000, 35000, 40000};

void fill_increasing(int *t, unsigned int n) {
    for(int i=0; i<n; i++) {
        t[i]=i;
    }
}

void fill_decreasing(int *t, unsigned int n) {
    for(int i=n, j=0; i > 0; i--, j++) {
        t[j]=i;
    }

}

void fill_vshape(int *t, unsigned int n) {
    for(int i=0; i<n/2; i++) {
        t[i]=i+1;
    }
    for(int i=n/2, z=i; i<n; i++, z--) {
        t[i]=z;

    }
}

void selection_sort(int *t, unsigned int n) {
    int i, j, min_idx;

            for (i=0; i< n-1; i++)
            {
                min_idx = i;
                for (j = i+1; j < n; j++)
                  if (t[j] < t[min_idx])
                    min_idx = j;
                swap(&t[min_idx], &t[i]);
            }

}

void insertion_sort(int *t, unsigned int n) {
    for(int x=1, key=0, y=0; x < n; x++) {
        key = t[x];
        y= x-1;

        while(y >= 0 && t[y] > key) {
            t[y+1] = t[y];
            y--;
        }

        t[y+1] = key;
    }
}

void swap(int *x,int *y) {
	int temporary;
    temporary = *x;
    *x=*y;
    *y=temporary;
}

int divide(int *t, int low, int high) {
    int beacon = t[high];
    int x = (low - 1);

    for(int y = low; y <= high- 1; y++) {
        if(t[y] <= beacon) {
            x++;

            swap(&t[x], &t[y]);
        }
    }
    swap(&t[x + 1], &t[high]);

    return (x + 1);
}

void qs_medial(int *t, int low, int high) {
    if (low < high) {
        int pi = divide(t, low, high);

        qs_medial(t, low, pi - 1);
        qs_medial(t, pi + 1, high);
    }
}

void quick_sort(int *t, unsigned int n) {
    qs_medial(t, 0, n-1);
}

void heapify(int  tab[], unsigned int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && tab[l] > tab[largest])
        largest = l;

    if (r < n && tab[r] > tab[largest])
        largest = r;

    if (largest != i)
    {
        swap(&tab[i], &tab[largest]);

        heapify(tab, n, largest);
    }
}

void heap_sort(int *t, unsigned int n) {

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(t, n, i);


    for (int i=n-1; i>=0; i--)
    {

        swap(&t[0], &t[i]);


        heapify(t, i, 0);
    }
}

void fill_random(int *t, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void is_random(int *t, unsigned int n) {
    return;
}

void is_increasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}

void is_decreasing(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        //assert(t[i] < t[i - 1]);
    }
}

void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;

    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}

void is_sorted(int *t, unsigned int n) {
    for (unsigned int i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing,  fill_vshape };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

int main() {
    for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
        void (*sort)(int *, unsigned int) = sort_functions[i];

        for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];

            for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                unsigned int n = ns[k];
                int *t = malloc(n * sizeof(*t));

                fill(t, n);
                check(t, n);

                clock_t begin = clock();
                sort(t, n);
                clock_t end = clock();
                is_sorted(t, n);

                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                free(t);
            }
        }
    }
    return 0;
}
