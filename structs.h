#define MAX_CHARS 10000

/* struct containing name and amount of votes for a candidate */
typedef struct{
    char navn[MAX_CHARS];
    int stemmer;
}kandidat;

/* Struct containing a pointer to a given amount of candidates, name of the valgkreds and how many candidates in the given valgkreds */
typedef struct{
    kandidat *kandidater;
    char valgkreds_navn[MAX_CHARS];
    int antal_kandidater;
}stemmeseddel;

/* contains integer value of a vote - stored in a string */
typedef struct{
  char vote[10000];
} single_vote;
