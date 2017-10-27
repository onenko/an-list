/*
** ALEX NENKO STD SOFTWARE
**
** File: an-list.h - macroses to facilitate AN-LIST management
**
** Oct 1991 Alex Nenko     - written
** Dec 2002 Alex Nenko     - comments, usage
** Apr 2003 Alex Nenko     - 2 bugs in examples in comments :)
**
** NOTE. AN-LIST macroses work with 2-directional list of objects.
**       Objects are described by 'struct', that MUST contain two
**       pointer fields 'pnext' and 'pprev':
**              struct X { struct X * pnext, * pprev;  ... };
*/

#ifndef _AN_LIST_H_
#  define _AN_LIST_H_

#define AN_LIST_Init(x)         {(x)->pnext=(x)->pprev=(x);     }
#define AN_LIST_IsEmpty(x)      ((x)->pnext==(x)                )
/* insert y after x     */
#define AN_LIST_Insert(x,y)     {((y)->pnext=(x)->pnext)->pprev=(y);\
                                 ((x)->pnext=(y))->pprev=(x);   }
/* insert y B4 x        */
#define AN_LIST_InsertB4(x,y)   {((y)->pprev=(x)->pprev)->pnext=(y);\
                                 ((x)->pprev=(y))->pnext=(x);   }
/* exclude x from list  */
#define AN_LIST_Exclude(x)      {((x)->pprev)->pnext=(x)->pnext;\
                                 ((x)->pnext)->pprev=(x)->pprev;}

/* go through all objects of a list - WARNING !! See NOTE after examples */
#define for_AN_LIST_Elements(x,y) for( y = (x)->pnext; y != (x); y = (y)->pnext)
#define for_AN_LIST_ElementsSafe(x,y,z) for(y=(x)->pnext,z=(y)->pnext;y!=(x);y=z,z=(y)->pnext)

/*
** Examples.
**      struct X seed, * px;
** Initialize:
**      AN_LIST_Init( & seed);
** Insert object 'px' to head:
**      AN_LIST_Insert( & seed, px);
** Insert object 'px' to tail:
**      AN_LIST_Insert( seed.pprev, px); -- NO ! MACROS DOES NOT WORK !
**      AN_LIST_InsertB4( & seed, px);   -- This is OK !
** Go through all objects of a list: (WARNING !! See NOTE after examples !)
**      for( px = seed->pnext; px != seed; px = px->pnext)
**      {...}
** or                                (WARNING !! See NOTE after examples !)
**      for_AN_LIST_Elements( & seed, px)
**      {...}
** Empty a list:
**      while( ! AN_LIST_IsEmpty( & seed))
**      {
**        px = seed.pnext;
**        AN_LIST_Exclude( px);
**        free( px);    -- or leave alive if you want
**      }
**
** WARNING !! If you brouse the list
**      for( px = seed->pnext; px != seed; px = px->pnext)
**      for_AN_LIST_Elements( & seed, px);
** AND KILL any 'px', then you will got an error in 'px = px->pnext'.
** Do it in following way:
**      some_AN_LIST_type pxnext;
**      for( px = seed->pnext; px != seed; px = pxnext)
**      {
**        pxnext = px->pnext;
**        AN_LIST_Exclude( px);
**        free( px);
**      }
** or
**      some_AN_LIST_type px, pxn;
**      for_AN_LIST_ElementsSafe(& seed,px,pxn)
**      {
**        AN_LIST_Exclude( px);
**        free( px);
**      }
*/
#endif /* _AN_LIST_H_ */
