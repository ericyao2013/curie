/*
 * This file is part of the kyuba.org Curie project.
 * See the appropriate repository at http://git.kyuba.org/ for exact file
 * modification records.
*/

/*
 * Copyright (c) 2008-2010, Kyuba Project Members
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#include <curie/memory.h>
#include <sievert/metadata.h>

struct metadata *metadata_from_unix
    (enum metadata_classification_unix classification,
     int uid, int gid, int mode, long atime, long mtime, long ctime,
     long size, int device, int attributes)
{
    static struct memory_pool pool =
        MEMORY_POOL_INITIALISER (sizeof (struct metadata));
    struct metadata *rv = get_pool_mem (&pool);

#warning metadata_from_unix() incomplete
    
    return rv;
}

void metadata_from_unix_closure
    (enum metadata_classification_unix classification,
     int uid, int gid, int mode, long atime, long mtime, long ctime,
     long size, int device, int attributes,
     void (*with_metadata) (struct metadata *, void *), void *aux)
{
    struct metadata metadata;

#warning metadata_from_unix_closure() incomplete

    with_metadata (&metadata, aux);
}

void metadata_to_unix
    (struct metadata *metadata,
     enum metadata_classification_unix *classification,
     int *uid, int *gid, int *mode, long *atime, long *mtime, long *ctime,
     long *size, int *device, int *attributes)
{
#warning metadata_to_unix() incomplete
}
