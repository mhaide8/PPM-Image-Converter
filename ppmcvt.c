#include "pbm.h"
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    const char* input_image = NULL, * output_image = NULL;
    int o;
    int count = 0;
    char* i_input, * r_input;
    unsigned int PGM_input;
    unsigned int t_input, n_input;
    int b_op = 0;
    int g_op = 0;
    int i_op = 0;
    int r_op = 0;
    int s_op = 0;
    int m_op = 0;
    int t_op = 0;
    int n_op = 0;

    while ((o = getopt(argc, argv, "bg:i:r:smt:n:o:")) != -1) {
        switch (o) {

        case 'b':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }
            count = 1;
            b_op = 1;
            break;
        case 'g':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }

            PGM_input = (unsigned int)strtol(optarg, NULL, 10);

            if (PGM_input > 65535) {
                fprintf(stderr, "Error: Invalid max grayscale pixel value: %s; must be less than 65,536\n", optarg);
                exit(1);
            }
            count = 1;
            g_op = 1;

            break;
        case 'i':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }

            i_input = optarg;

            if (strcmp(i_input, "red") != 0 && strcmp(i_input, "blue") != 0 && strcmp(i_input, "green") != 0) {
                fprintf(stderr, "Error: Invalid channel specification: (%s); should be 'red', 'green' or 'blue'\n", i_input);
                exit(1);
            }
            count = 1;
            i_op = 1;
            break;
        case 'r':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }
            r_input = optarg;

            if (strcmp(r_input, "red") != 0 && strcmp(r_input, "blue") != 0 && strcmp(r_input, "green") != 0) {
                fprintf(stderr, "Error: Invalid channel specification: (%s); should be 'red', 'green' or 'blue'\n", r_input);
                exit(1);
            }

            count = 1;
            r_op = 1;

            break;
        case 's':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }
            count = 1;
            s_op = 1;
            break;
        case 'm':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }
            count = 1;
            m_op = 1;
            break;
        case 't':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }
            t_input = (unsigned int)strtol(optarg, NULL, 10);
            if (t_input < 1 || t_input > 8) {
                fprintf(stderr, "Error: Invalid scale factor: %d; must be 1-8\n", t_input);
                exit(1);
            }
            count = 1;
            t_op = 1;
            break;
        case 'n':
            if (count != 0) {
                fprintf(stderr, "Error: Multiple transformations specified\n");
                exit(1);
            }
            n_input = (unsigned int)strtol(optarg, NULL, 10);
            if (n_input < 1 || n_input > 8) {
                fprintf(stderr, "Error: Invalid scale factor: %d; must be 1-8\n", n_input);
                exit(1);
            }
            count = 1;
            n_op = 1;
            break;
        case 'o':
            output_image = optarg;
            break;
        default:
            fprintf(stderr, "Usage: ppmcvt [-bgirsmtno] [FILE]\n");
            count = 1;
            b_op = 1;
        }
       
         
    }

    if (output_image == NULL) {
        fprintf(stderr, "Error: No output file specified\n");
        exit(1);
    }

    input_image = argv[argc - 1];
    PPMImage* ppm = read_ppmfile(input_image);
    unsigned int h = ppm->height;
    unsigned int w = ppm->width;
    unsigned int m = ppm->max;

    if (input_image == NULL) {
        fprintf(stderr, "Error: No input file specified\n");
        exit(1);
    }


    if (b_op == 1) {
        PBMImage* pbm = new_pbmimage(w, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if ((ppm->pixmap[0][i][j] + ppm->pixmap[1][i][j] + ppm->pixmap[2][i][j]) / 3.0 < m / 2.0) {
                    pbm->pixmap[i][j] = 1;
                }
                else {
                    pbm->pixmap[i][j] = 0;
                }
            }
        }

        write_pbmfile(pbm, output_image);
        del_ppmimage(ppm);
        del_pbmimage(pbm);
        exit(0);
    }

    else if (g_op == 1) {
        PGMImage* pgm = new_pgmimage(w, h, m);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                pgm->pixmap[i][j] = (((ppm->pixmap[0][i][j] + ppm->pixmap[1][i][j] + ppm->pixmap[2][i][j]) / 3.0 ) / ppm->max) * pgm->max;
            }
        }
        write_pgmfile(pgm, output_image);
        del_ppmimage(ppm);
        del_pgmimage(pgm);
        exit(0);
    }

    else if (i_op == 1) {
        PPMImage* i_ppm = new_ppmimage(w, h, m);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                i_ppm->pixmap[0][i][j] = ppm->pixmap[0][i][j];
                i_ppm->pixmap[1][i][j] = ppm->pixmap[1][i][j];
                i_ppm->pixmap[2][i][j] = ppm->pixmap[2][i][j];
            }
        }

        if (strcmp(i_input, "red") == 0) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    i_ppm->pixmap[1][i][j] = 0;
                    i_ppm->pixmap[2][i][j] = 0;
                }
            }
        }

        if (strcmp(i_input, "green") == 0) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    i_ppm->pixmap[0][i][j] = 0;
                    i_ppm->pixmap[2][i][j] = 0;
                }
            }
        }

        if (strcmp(i_input, "blue") == 0) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    i_ppm->pixmap[0][i][j] = 0;
                    i_ppm->pixmap[1][i][j] = 0;
                }
            }
        }

        write_ppmfile(i_ppm, output_image);
        del_ppmimage(ppm);
        del_ppmimage(i_ppm);
        exit(0);
    }

    else if (r_op == 1) {

        PPMImage* r_ppm = new_ppmimage(w, h, m);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                r_ppm->pixmap[0][i][j] = ppm->pixmap[0][i][j];
                r_ppm->pixmap[1][i][j] = ppm->pixmap[1][i][j];
                r_ppm->pixmap[2][i][j] = ppm->pixmap[2][i][j];
            }
        }

        if (strcmp(r_input, "red") == 0) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    r_ppm->pixmap[0][i][j] = 0;

                }
            }
        }

        if (strcmp(r_input, "green") == 0) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    r_ppm->pixmap[1][i][j] = 0;

                }
            }
        }

        if (strcmp(r_input, "blue") == 0) {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    r_ppm->pixmap[2][i][j] = 0;

                }
            }
        }

        write_ppmfile(r_ppm, output_image);
        del_ppmimage(ppm);
        del_ppmimage(r_ppm);
        exit(0);
    }

    else if (s_op == 1) {

        PPMImage* s_ppm = new_ppmimage(w, h, m);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                s_ppm->pixmap[0][i][j] = ppm->pixmap[0][i][j];
                s_ppm->pixmap[1][i][j] = ppm->pixmap[1][i][j];
                s_ppm->pixmap[2][i][j] = ppm->pixmap[2][i][j];
            }
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
               
                s_ppm->pixmap[0][i][j] = .393 * ppm->pixmap[0][i][j] + .769 * ppm->pixmap[1][i][j] + .189 * ppm->pixmap[2][i][j];
                s_ppm->pixmap[1][i][j] = .349 * ppm->pixmap[0][i][j] + .686 * ppm->pixmap[1][i][j] + .168 * ppm->pixmap[2][i][j];
                s_ppm->pixmap[2][i][j] = .272 * ppm->pixmap[0][i][j] + .534 * ppm->pixmap[1][i][j] + .131 * ppm->pixmap[2][i][j];
                if (s_ppm->pixmap[0][i][j] > s_ppm->max) {
                    s_ppm->pixmap[0][i][j] = s_ppm->max;

                }
                if (s_ppm->pixmap[1][i][j] > s_ppm->max) {
                    s_ppm->pixmap[1][i][j] = s_ppm->max;

                }
                if (s_ppm->pixmap[2][i][j] > s_ppm->max) {
                    s_ppm->pixmap[2][i][j] = s_ppm->max;

                }
            }
        }


        write_ppmfile(s_ppm, output_image);
        del_ppmimage(ppm);
        del_ppmimage(s_ppm);
        exit(0);

    }

    else if (m_op == 1) {

        PPMImage* m_ppm = new_ppmimage(w, h, m);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                m_ppm->pixmap[0][i][j] = ppm->pixmap[0][i][j];
                m_ppm->pixmap[1][i][j] = ppm->pixmap[1][i][j];
                m_ppm->pixmap[2][i][j] = ppm->pixmap[2][i][j];
            }
        }

        int mid = w / 2;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < mid; j++) {

                m_ppm->pixmap[0][i][w - 1 - j] = m_ppm->pixmap[0][i][j];
                m_ppm->pixmap[1][i][w - 1 - j] = m_ppm->pixmap[1][i][j];
                m_ppm->pixmap[2][i][w - 1 - j] = m_ppm->pixmap[2][i][j];


            }
        }

        write_ppmfile(m_ppm, output_image);
        del_ppmimage(ppm);
        del_ppmimage(m_ppm);
        exit(0);
    }

    else if (t_op == 1) {

        int new_h;
        int new_w;

        if (h % t_input == 1) {
            new_h = h / t_input + 1;
        }

        else {
            new_h = h / t_input;
        }

        if (w % t_input == 1) {
            new_w = w / t_input + 1;
        }

        else {
            new_w = w / t_input;
        }

        PPMImage* t_ppm = new_ppmimage(new_w, new_h, m);

        for (int i = 0; i < t_ppm->height; i++) {
            for (int j = 0; j < t_ppm->width; j++) {

                t_ppm->pixmap[0][i][j] = ppm->pixmap[0][i * t_input][j * t_input];
                t_ppm->pixmap[1][i][j] = ppm->pixmap[1][i * t_input][j * t_input];
                t_ppm->pixmap[2][i][j] = ppm->pixmap[2][i * t_input][j * t_input];

            }
        }

        write_ppmfile(t_ppm, output_image);
        del_ppmimage(ppm);
        del_ppmimage(t_ppm);
        exit(0);
    }

    else if (n_op == 1) {

        int new_h;
        int new_w;

        if (h % n_input == 1) {
            new_h = h / n_input + 1;
        }

        else {
            new_h = h / n_input;
        }

        if (w % n_input == 1) {
            new_w = w / n_input + 1;
        }

        else {
            new_w = w / n_input;
        }

        PPMImage* n_ppm = new_ppmimage(w, h, m);

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                n_ppm->pixmap[0][i][j] = ppm->pixmap[0][(i % new_h) * n_input][(j % new_w) * n_input];
                n_ppm->pixmap[1][i][j] = ppm->pixmap[1][(i % new_h) * n_input][(j % new_w) * n_input];
                n_ppm->pixmap[2][i][j] = ppm->pixmap[2][(i % new_h) * n_input][(j % new_w) * n_input];
            }
        }

        write_ppmfile(n_ppm, output_image);
        del_ppmimage(ppm);
        del_ppmimage(n_ppm);
        exit(0);

    }

    return 0;
}
