#include <stdio.h>

int main(){
    float x1, y1, x2, y2, x3, y3;

    scanf("%f %f", &x1, &y1);
    scanf("%f %f", &x2, &y2);
    scanf("%f %f", &x3, &y3);

    float xmin = x1;
    if(x2 < xmin) xmin = x2;
    if(x3 < xmin) xmin = x3;

    float xmax = x1;
    if(x2 > xmax) xmax = x2;
    if(x3 > xmax) xmax = x3;

    float ymin = y1;
    if(y2 < ymin) ymin = y2;
    if(y3 < ymin) ymin = y3;

    float ymax = y1;
    if(y2 > ymax) ymax = y2;
    if(y3 > ymax) ymax = y3;

    // Ceil the minimums
    if(xmin > 0 && xmin != (int)xmin) xmin = (int)xmin + 1;
    else xmin = (int)xmin;

    if(ymin > 0 && ymin != (int)ymin) ymin = (int)ymin + 1;
    else ymin = (int)ymin;

    int count = 0;

    for(int x = xmin; x <= (int)xmax; x++){
        for(int y = ymin; y <= (int)ymax; y++){
            float cross1 = (x-x1)*(y2-y1) - (y-y1)*(x2-x1);
            float cross2 = (x-x2)*(y3-y2) - (y-y2)*(x3-x2);
            float cross3 = (x-x3)*(y1-y3) - (y-y3)*(x1-x3);

            if(((cross1 > 0) & (cross2 > 0) & (cross3 > 0)) | ((cross1 < 0) & (cross2 < 0) & (cross3 < 0)))
                count++;
        }
    }

    printf("%d\n", count);
}
