#include <unistd.h>
#include <stdlib.h>
#include "gui.h"

int main()
{
    int i, j;
    int** data;

	gui_init();

	data = (int**) malloc(10*sizeof(int*));
	for( i = 0; i < 10; i++ )
	{
		data[i] = (int*) malloc(sizeof(int*));
	}

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            data[i][j] = 5;// (i+j);
        }
    }

    heatmap(data, 10, 10, 2, 2);

    sleep(4);
}
