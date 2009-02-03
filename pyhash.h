/******************** MODIFICATIONS to pyhash.h **************************
**
** Date       Who  What
** 
** 1994            Original
** 
**************************** End of List ******************************/ 

#if !defined(PYHASH_H)
#define PYHASH_H

#include "DHT/dhtbcmem.h"
#include "py.h"

/* typedefs */
typedef enum {
	SerNoSucc,
	HelpNoSuccOdd,
	HelpNoSuccEven,
	DirSucc,
	DirNoSucc,
    nr_hashwhat
} hashwhat;

typedef unsigned char byte;

enum
{
  hashbuf_length = 256
};

typedef union
{
    BCMemValue cmv;
    byte buffer[hashbuf_length];
} HashBuffer;

extern HashBuffer hashBuffers[maxply+1];

#if defined(NDEBUG)

#define validateHashBuffer()
#define invalidateHashBuffer(x)

#else
extern boolean isHashBufferValid[maxply+1];

void validateHashBuffer(void);

/* if (guard) invalidate hash buffer for ply nbply
 * (making guard a parameter prevents it from being evaluated
 * #if !defined(NDEBUG))
 * @param guard guard
 */
void invalidateHashBuffer(boolean guard);

#endif

extern void (*encode)(void);

/* exported functions */
void check_hash_assumptions(void);

void inithash (void);
void closehash (void);
void HashStats(unsigned int level, char *trailer);

typedef unsigned int hash_value_type;

boolean inhash(slice_index si,
               hashwhat what,
               hash_value_type val);
void addtohash(slice_index si,
               hashwhat what,
               hash_value_type val);

void IncHashRateLevel(void);
void DecHashRateLevel(void);

extern unsigned long int compression_counter;

#endif
