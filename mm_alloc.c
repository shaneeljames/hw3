/*
 * mm_alloc.c
 *
 * Stub implementations of the mm_* routines. 
 * 
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
    else if(block->free==0){
		 
	return block;
    }else 
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
	void* re=mm_malloc(size);
	s_block_ptr old=ptr-40;
	s_block_ptr new=re-40;
	memcpy(re,ptr,old->size);
	mm_free(ptr);
	return 	new->ptr;
}

void mm_free(void* ptr)
{
	s_block_ptr block=ptr-40;
	block->free=0;

	if(block->next!=NULL&&block->prev!=NULL){
        
          if((block->prev->free==0)&&(block->next->free==0)){
 	  	block->size=block->prev->size + block->next->size + block->size;
		memcpy(block->ptr,block->prev->ptr,block->prev->size);
		memcpy(block->ptr,block->next->ptr,block->next->size);
		if(block->prev->prev!=NULL){
			block->prev=block->prev->prev;
			block->prev->next=block;
		}else
  			block->prev=NULL;
		if(block->next->next!=NULL){
			block->next=block->next->next;
			block->next->prev=block;
		}else
			block->next=NULL;
	}
	
	}
	else if(block->next!=NULL){
		block->size+=block->next->size;	
		memcpy(block->ptr,block->next->ptr,block->next->size);
		if(block->next->next!=NULL){
			block->next=block->next->next;
			block->next->prev=block;
		}
		else
			block->next=NULL;
	}
	
	else if(block->prev!=NULL){
		block->size+=block->prev->size;	
		memcpy(block->ptr,block->prev->ptr,block->prev->size);
		if(block->prev->prev!=NULL){
			block->prev=block->prev->prev;
			block->prev->next=block;
		}
		else
			block->next=NULL;
	}
}
