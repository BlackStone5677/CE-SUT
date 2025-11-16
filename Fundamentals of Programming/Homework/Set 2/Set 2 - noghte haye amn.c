#include <stdio.h>

int main(){
    float x1, y1;
    float x2, y2;
    float x3, y3;

    scanf("%f %f", &x1, &y1);
    scanf("%f %f", &x2, &y2);
    scanf("%f %f", &x3, &y3);

    float xmin = (x1 < x2 ? (x1 < x3 ? x1 : x3): (x2 < x3 ? x2 : x3));
    float xmax = (x1 < x2 ? (x2 < x3 ? x3 : x2): (x1 < x3 ? x3 : x1));
    float ymin = (y1 < y2 ? (y1 < y3 ? y1 : y3): (y2 < y3 ? y2 : y3));
    float ymax = (y1 < y2 ? (y2 < y3 ? y3 : y2): (y1 < y3 ? y3 : y1));

    // Turn into integers(min -> ceil(min), max -> floor)

    xmin = (xmin > 0 && xmin !=(int)xmin) ? (int)xmin + 1 : (int)xmin;
    xmax = (xmax < 0 && xmax !=(int)xmax) ? (int)xmax - 1 : (int)xmax;
    ymin = (ymin > 0 && ymin !=(int)ymin) ? (int)ymin + 1 : (int)ymin;
    ymax = (ymax < 0 && ymax !=(int)ymax) ? (int)ymax - 1 : (int)ymax;

    int count = 0;

    for(int x = xmin; x <= xmax; x++){
        for(int y = ymin; y <= ymax; y++){
            // Calculate cross products for each vertex
            float cross1 = (x-x1)*(y2-y1) - (y-y1)*(x2-x1);
            float cross2 = (x-x2)*(y3-y2) - (y-y2)*(x3-x2);
            float cross3 = (x-x3)*(y1-y3) - (y-y3)*(x1-x3);

            // When all the cross products have the same sign, the point is inside the triangle
            if(((cross1 > 0) & (cross2 > 0) & (cross3 > 0)) | ((cross1 < 0) & (cross2 < 0) & (cross3 < 0))) count++;
        }
    }
    printf("%d\n", count);

}