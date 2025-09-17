#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
int main() {
    const double pi = 3.14159265358979323846;
    const double x_approach = 30 / pi;
    const double y_approach = 15;
    const int ten_num = 10;
    const float start_out = 0.5;
    const int end_out = 6;
    const int hatch_out = 30;
    const int number_out = 10;
    const int lines_out = 22;
    double y_result;
    double x_result;
    double y_out;
    double x_out;
    double max_result = -100;
    int i;
    int graph_driver, graph_mode, graph_error_code;
    int max_x;
    int max_y;
    char symbols_out[10];
    char maximum_out[50];

    graph_driver = DETECT;
    detectgraph(&graph_driver, &graph_mode);
    initgraph(&graph_driver, &graph_mode, NULL);

    graph_error_code = graphresult();
    if (graph_error_code != grOk) {
        printf("Error: %s\n", grapherrormsg(graph_error_code));
        getch();
        return 255;
    }

    max_x = getmaxx();
    max_y = getmaxy();
    setviewport(0, 0, max_x, max_y, 0);
    setlinestyle(0, 0, 3);
    line(lines_out, max_y, lines_out, 0);            // vert
    line(lines_out, max_y / 2, max_x, max_y / 2);        // gorizont

    for (i = 0; i <= end_out; i++) {
        sprintf(symbols_out, "%dPI", i);
        outtextxy(lines_out + hatch_out * i, max_y / 2 + ten_num, symbols_out);
        line(lines_out + hatch_out * i, max_y / 2 + ten_num / 2, lines_out + hatch_out * i, max_y / 2 - ten_num / 2);
    }

    for (i = -number_out; i <= number_out; i++) {
        sprintf(symbols_out, "%d", i);
        outtextxy(0, max_y / 2 - hatch_out * i / 2 - ten_num / 2, symbols_out);
        line(lines_out + ten_num / 2, max_y / 2 - hatch_out * i / 2, lines_out - ten_num / 2, max_y / 2 - hatch_out * i / 2);
    }

    setlinestyle(3, 0, 3);
    line(lines_out + hatch_out * start_out, max_y, lines_out + hatch_out * start_out, 0); 
    setlinestyle(0, 0, 3);
    setviewport(0, 0, max_x, max_y, 0);
    // graph
    for (x_result = start_out * pi; x_result <= end_out * pi; x_result += 0.001) {
        y_result = pow(sin(x_result), 3) + pow(cos(x_result), 3); 
        x_out = x_result * x_approach;
        y_out = y_result * y_approach;
        if (y_result > max_result) {
            max_result = y_result;
        }
        putpixel(lines_out + x_out, max_y / 2 - y_out, 4);
    }

    setlinestyle(3, 0, 3);
    line(lines_out + hatch_out * end_out, max_y, lines_out + hatch_out * end_out, 0);
  
    sprintf(maximum_out, "Max function value: %f", max_result);
    outtextxy(max_x / 3, max_y - lines_out, maximum_out);
    getch();
    closegraph();
    return 0;
}