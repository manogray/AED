#ifndef COMPARAVEL_H_
#define COMPARAVEL_H_


typedef short (*TCompara)(void*,void*);

struct comparavel{
	void *dado;
	TCompara compara;
};

typedef struct comparavel TComparavel;

#endif /* COMPARAVEL_H_ */
