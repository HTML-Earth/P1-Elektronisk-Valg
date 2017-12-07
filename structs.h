#define MAX_CHARS 100


typedef struct{
    char navn[MAX_CHARS];
    int stemmer;
}kandidat; 

typedef struct{
    kandidat *kandidater;
    char valgkreds_navn[MAX_CHARS];
    int antal_kandidater;
}stemmeseddel;

typedef struct{
  char vote[10000];
} single_vote;





