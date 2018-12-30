#include <unistd.h>

int main()
{
    int i, j;
    int data[10][10];

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            data[i][j] = (j*j) + (2*i);
        }
    }

    heatmap(data, 10, 10, 2, 2);

    sleep(4);
}
