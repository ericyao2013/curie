/*
 * This file is part of the becquerel.org Curie project.
 * See the appropriate repository at http://git.becquerel.org/ for exact file
 * modification records.
*/

/*
 * Copyright (c) 2008-2011, Kyuba Project Members
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

#include <syscall/syscall.h>
#include <curie/main.h>
#include <curie/stack.h>

char **curie_argv        = 0;
char **curie_environment = 0;

#if defined(__GNUC__) && defined(__GNUC_MINOR__) && (((__GNUC__ == 4) && (__GNUC_VERSION__ >= 5)) || (__GNUC__ > 4))
#define UNREACHABLE __builtin_unreachable ();
#else
#define UNREACHABLE
#endif

void __start ( void ) __attribute__((used));
void cexit ( int ) __attribute__((used));
void initialise_stack ( void ) __attribute__((used));
int cmain ( void ) __attribute__((used));

void cexit (int status)
{
    sys_exit (status);
    UNREACHABLE
}

void __start ( void )
{
    __asm__ volatile
        (".globl _start\n\t"
         ".type _start, @function\n"
         "_start:\n\t"
         "xorq  %%rbp, %%rbp\n\t"
         "movq  %%rsp, %%r11\n\t"
         "addq  $0x8, %%r11\n\t"
         "movq  %%r11, %0\n\t"
         "movq  (%%rsp), %%rbx\n\t"
         "incq  %%rbx\n\t"
         "imulq $0x8, %%rbx, %%rbx\n\t"
         "addq  %%rbx, %%r11\n\t"
         "movq  %%r11, %1\n\t"
         "call initialise_stack\n\t"
         "call cmain\n\t"
         "movq %%rax, %%rdi\n\t"
         "call cexit"
         : "=m"(curie_argv), "=m"(curie_environment)
         :
         : "memory" );
    UNREACHABLE
}
