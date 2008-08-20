/*
 *  multiplex-process.c
 *  curie-libc
 *
 *  Created by Magnus Deininger on 10/08/2008.
 *  Copyright 2008 Magnus Deininger. All rights reserved.
 *
 */

/*
 * Copyright (c) 2008, Magnus Deininger All rights reserved.
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

#include "curie/multiplex.h"
#include "curie/exec.h"
#include "curie/main.h"

static void mx_on_death(struct exec_context *cx, void *d) {
    if (cx->exitstatus == 4)
        a_exit (0);

    a_exit (2);
}

int a_main(void) {
    struct exec_context *context;
    struct exec_call *call;

    multiplex_process();

    call = create_exec_call();
    call->options |= EXEC_CALL_NO_IO;
    context = execute(call);

    if (context->pid < 0) {
        return 3;
    } else if (context->pid == 0) {
        return 4;
    }

    multiplex_add_process(context, mx_on_death, (void *)0);

    while (multiplex() == mx_ok);

    return 1;
}
