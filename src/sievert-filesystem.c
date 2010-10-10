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
#include <sievert/sexpr.h>
#include <sievert/filesystem.h>

sexpr path_normalise (sexpr path)
{
    sexpr rv = sx_nil;

    if (consp (path))
    {
        rv = sx_end_of_list;

        while (consp (path))
        {
            rv = sx_set_add (rv, path_normalise (car (path)));

            path = cdr (path);
        }
    }
    else if (stringp (path))
    {
        int l = 0, i = 0, levels = 0;
        const char *s = sx_string (path);
        char *f;
        char is_start = (char)1;

        while (s[l] != (char)0)
        {
            l++;
        }

        l++;

        f = (char *)aalloc (l);
        l = 0;

        while (s[l] != (char)0)
        {
            switch (s[l])
            {
                case '/':
                    is_start = (char)1;
                    levels++;
                    f[i] = '/';
                    i++;
                    break;
                case '.':
                    if (is_start == (char)1)
                    {
                        if (s[(l+1)] == '/')
                        {
                            l++;
                            break;
                        }
                    }
                default:
                    f[i] = s[l];
                    i++;
                    is_start = (char)0;
                    break;
            }

            l++;
        }

        f[i] = (char)0;

        rv = make_string_l (f, i);

        afree (l, (void *)f);
    }

    return rv;
}

sexpr path_prefix     (sexpr list)
{
    return list;
}

sexpr path_prefix_map (sexpr path)
{
    return path;
}