/*
 * mm_alloc.c
 *
 * Stub implementations of the mm_* routines. Remove this comment and provide
 * a summary of your allocator's design here.
 */

#include "mm_alloc.h"

#include <stdlib.h>

/* Your final implementation should comment out this macro. */
//#define MM_USE_STUBS

void* mm_malloc(size_t size)
{
#ifdef MM_USE_STUBS
//    return calloc(1, size);
#else
//#error Not implemented.


  s_block_ptr block, previous,next;
  int i=0; 
  
  block=sbrk(0);
 sbrk(40);

  
  
  while(i>0){  //find free block
    
    if((block->next!=NULL)&&(block->free==1)&&(((block->size)-size)<0))
      block=block->next;
    else if(block->free==0)
      return block;
    else 
      break;
    i++;
  }

  previous = sbrk(0);
  //block= sbrk(sizeof(struct s_block)+size);
  block->size=size;
  block->ptr=sbrk(size);
  if(block->prev!=NULL){
    block->prev=previous;
    block->next=NULL;
    previous->next=block;
    block->free=1;
  }
  else { 
    block->next=NULL;
    block->prev=NULL;
    block->free=1;
  }
  return block->ptr;
#endif
}



void* mm_realloc(void* ptr, size_t size)
{
	
}

void mm_free(void* ptr)
{
	s_block_ptr block=ptr-40;
	block->free=0;
        if(block->prev->free==0){
 	   
	
	}


}
