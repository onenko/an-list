# an-list
Tiny implementation of bidirectional linked list in C.

It's so tiny that no reason to create .c or library,
the implementation is just one header file.

### Main functionality of a list

- initialize list;
- insert element;
- exclude element;
- test if empty.

Above functionality takes 8 lines of code. Here are these lines:

```C
#define AN_LIST_Init(x)         {(x)->next=(x)->prev=(x);     }
#define AN_LIST_IsEmpty(x)      ((x)->next==(x))

#define AN_LIST_Insert(x,y)     {((y)->next=(x)->next)->prev=(y);\
                                 ((x)->next=(y))->prev=(x);   }

#define AN_LIST_InsertB4(x,y)   {((y)->prev=(x)->prev)->next=(y);\
                                 ((x)->prev=(y))->next=(x);   }

#define AN_LIST_Exclude(x)      {((x)->prev)->next=(x)->next;\
                                 ((x)->next)->prev=(x)->prev;}
```

### How it works
 
Macroses work with 2-directional list of elements.
Every element (which is struct or class) must contain list pointers.
This is known as invasive list implementation,
and this is the limitation of the approach.

Elements are described by 'struct', that MUST contain two
pointer fields 'pnext' and 'pprev':

```C
struct X {
    struct X * pnext, * pprev;
    // Some other fields of object    
};
```


### Examples

```C
struct X seed;  // fake element as head
struct X * px;  // our working pointer

AN_LIST_Init( & seed);  // initialized

// Insert object 'px' to head
AN_LIST_Insert( & seed, px);

// Insert object 'px' to tail
AN_LIST_InsertB4( & seed, px);


// Go through all objects of a list
for( px = seed->pnext; px != seed; px = px->pnext)
{ ... }

// Go through all objects of a list - alternative
for_AN_LIST_Elements( & seed, px)
{ ... }

// Empty a list
while( ! AN_LIST_IsEmpty( & seed))
{
    px = seed.pnext;
    AN_LIST_Exclude( px);
    free( px);    // or leave alive if you want
}

// Safe traversing with delete
struct X * px, * pxn;
for_AN_LIST_ElementsSafe( & seed, px, pxn)
{
    AN_LIST_Exclude( px);
    free( px);
}
```

### Limitations (once again)

1. An-list can't handle directly any arbitrary structures, because these
structures must contain member fields * pprev and * pnext (remember, this is invasive implementation);
2. List head is implemented as element (object) instead of pointer to object;
 so one element is sacrificed to be the head (seed) of a list - may be important for big data structures.

Example of bad code - wrong attempt to insert element to end of list:
```C
AN_LIST_Insert( seed.pprev, px); -- NO ! MACROS DOES NOT WORK !
```
Proper implementation:
 ```C
AN_LIST_InsertB4( & seed, px); 
 ```

Example of bad code - wrong attempt to delete element in traverse loop:
```C
for( px = seed->pnext; px != seed; px = px->pnext)
{
    AN_LIST_Exclude( px);
    free( px);
}
```

Safe traversing macro is for_AN_LIST_ElementsSafe (demonstrated above).

### More information

available on [http://www.nenko.net/soft/an-list/en/](http://www.nenko.net/soft/an-list/en/) page.
