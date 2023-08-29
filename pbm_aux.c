#include "pbm.h"
#include <stdlib.h>

PPMImage* new_ppmimage(unsigned int w, unsigned int h, unsigned int m)
{
	PPMImage* ppm = (PPMImage*)malloc(sizeof(PPMImage));
	ppm->height = h;
	ppm->width = w;
	ppm->max = m;
	for (int i = 0; i < 3; i++) {
		ppm->pixmap[i] = (unsigned int**)malloc(ppm->height * sizeof(unsigned int*));
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < ppm->height; j++) {
			ppm->pixmap[i][j] = (unsigned int*)malloc(ppm->width * sizeof(unsigned int));
		}
	}

	return ppm;

}

PBMImage* new_pbmimage(unsigned int w, unsigned int h)
{
	PBMImage* pbm = (PBMImage*)malloc(sizeof(PBMImage));
	pbm->width = w;
	pbm->height = h;

	pbm->pixmap = (unsigned int**)malloc(pbm->height * sizeof(unsigned int*));
	for (int i = 0; i < pbm->height; i++) {
		pbm->pixmap[i] = (unsigned int*)malloc(pbm->width * sizeof(unsigned int));
	}
	return pbm;


}

PGMImage* new_pgmimage(unsigned int w, unsigned int h, unsigned int m)
{
	PGMImage* pgm = (PGMImage*)malloc(sizeof(PGMImage));
	pgm->width = w;
	pgm->height = h;
	pgm->max = m;

	pgm->pixmap = (unsigned int**)malloc(pgm->height * sizeof(unsigned int*));
	for (int i = 0; i < pgm->height; i++) {
		pgm->pixmap[i] = (unsigned int*)malloc(pgm->width * sizeof(unsigned int));
	}
	return pgm;



}

void del_ppmimage(PPMImage* p)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < p->height; j++) {
			free(p->pixmap[i][j]);
		}
		free(p->pixmap[i]);
	}
	free(p);
}

void del_pgmimage(PGMImage* p)
{
	for (int i = 0; i < p->height; i++) {
		free(p->pixmap[i]);
	}

	free(p->pixmap);
	free(p);
}

void del_pbmimage(PBMImage* p)
{
	for (int i = 0; i < p->height; i++) {
		free(p->pixmap[i]);
	}

	free(p->pixmap);
	free(p);
}

