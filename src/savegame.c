#include "savegame.h"

void save(match *m,const char *file){
    FILE *f;
    f=fopen(file,"wb");
    if(f == NULL){
        perror("fopen()");
        return;
    }

    fwrite(&m->no,sizeof(m->no),1,f);
    fwrite(&m->dim,sizeof(m->dim),1,f);
    fwrite(&m->mode,sizeof(m->mode),1,f);
    fwrite(&m->color,sizeof(m->color),1,f);
    fwrite(&m->difficulty,sizeof(m->difficulty),1,f);


    fwrite(m->current,sizeof(position),1,f);
    fwrite(m->past,sizeof(position),m->no,f);
    
    fclose(f);
}

void load(match *m,const char *file){
    FILE *f;
    f=fopen(file,"rb");
    if(f == NULL){
        perror("fopen()");
        return;
    }

    fread(&m->no,sizeof(m->no),1,f);
    fread(&m->dim,sizeof(m->dim),1,f);
    fread(&m->mode,sizeof(m->mode),1,f);
    fread(&m->color,sizeof(m->color),1,f);
    fread(&m->difficulty,sizeof(m->difficulty),1,f);

    m->current = malloc(sizeof(position));
    if(m->current == NULL){
        perror("malloc()");
        exit(1);
    }

    m->past = malloc(m->dim * sizeof(position));
    if(m->past == NULL){
        perror("malloc()");
        exit(1);
    }

    fread(m->current,sizeof(position),1,f);
    fread(m->past,sizeof(position),m->no,f);
    
    fclose(f);
}