/*
 *  memory-allocator.c
 *  libcurie
 *
 *  Created by Magnus Deininger on 15/06/2008.
 *  Copyright 2008 Magnus Deininger. All rights reserved.
 *
 */

/*
 * Copyright (c) 2008, 2009, Magnus Deininger All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer. *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution. *
 * Neither the name of the project nor the names of its contributors may
 * be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <curie/memory.h>
#include <curie/tree.h>

void *aalloc   (unsigned long size) {
    if (size < CURIE_POOL_CUTOFF) {
        struct memory_pool pool = MEMORY_POOL_INITIALISER(size);

        return get_pool_mem (&pool);
    } else {
        return get_mem (calculate_aligned_memory_size (size));
    }
}

void *arealloc (unsigned long size, void *p, unsigned long new_size) {
    unsigned long msize = calculate_aligned_memory_size (size);
    unsigned long mnew_size = calculate_aligned_memory_size (new_size);

    if (msize != mnew_size) {
        if ((msize >= CURIE_POOL_CUTOFF) &&
            (mnew_size >= CURIE_POOL_CUTOFF)) {
            return resize_mem (msize, p, mnew_size);
        } else {
            unsigned int *new_location = (unsigned int *)aalloc(mnew_size);
            if (new_location == (unsigned int *)0)
            {
                afree (msize, p);
                return (void *)0;
            }
            else
            {
                unsigned int *old_location = (unsigned int *)p;
                int copysize = (int)((msize < mnew_size) ? msize : mnew_size);

                copysize = (int)((copysize / sizeof(int))
                        + (((copysize % sizeof(int)) == 0) ? 0 : 1));

                for(int i = 0; i < copysize; i++) {
                    /* copy in chunks of ints */
                    new_location[i] = old_location[i];
                }

                afree (msize, p);

                return (void*)new_location;
            }
        }
    }

    return p;
}

void afree     (unsigned long size, void *p) {
    if (size < CURIE_POOL_CUTOFF) {
        free_pool_mem (p);
    } else {
        free_mem (calculate_aligned_memory_size (size), p);
    }
}
