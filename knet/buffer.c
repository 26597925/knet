/*
 * Copyright (c) 2014-2015, dennis wang
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL dennis wang BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "buffer.h"


struct _buffer_t {
    char*    ptr;
    uint32_t len;
    uint32_t pos;
};

buffer_t* buffer_create(uint32_t size) {
    buffer_t* sb = create(buffer_t);
    verify(sb);
    if (!sb) {
        return 0;
    }
    sb->ptr = create_raw(size);
    verify(sb->ptr);
    if (!sb->ptr) {
        buffer_destroy(sb);
    }
    sb->pos = 0;
    sb->len = size;
    return sb;
}

void buffer_destroy(buffer_t* sb) {
    verify(sb);
    if (!sb) {
        return;
    }
    if (sb->ptr) {
        destroy(sb->ptr);
    }
    if (sb) {
        destroy(sb);
    }
}

uint32_t buffer_put(buffer_t* sb, const char* temp, uint32_t size) {
    verify(sb);
    verify(temp);
    verify(size);
    if (!sb || !temp || !size) {
        return 0;
    }
    if (size > sb->len - sb->pos) {
        return 0;
    }
    memcpy(sb->ptr + sb->pos, temp, size);
    sb->pos += size;
    return size;
}

uint32_t buffer_get_length(buffer_t* sb) {
    verify(sb);
    if (!sb) {
        return 0;
    }
    return sb->pos;
}

uint32_t buffer_get_max_size(buffer_t* sb) {
    verify(sb);
    if (!sb) {
        return 0;
    }
    return sb->len;
}

int buffer_enough(buffer_t* sb, uint32_t size) {
    verify(sb);
    if (!sb) {
        return 0;
    }
    return (sb->pos + size > sb->len);
}

char* buffer_get_ptr(buffer_t* sb) {
    verify(sb);
    if (!sb) {
        return 0;
    }
    return sb->ptr;
}

void buffer_adjust(buffer_t* sb, uint32_t gap) {
    verify(sb); /* gap����Ϊ0 */
    if (!sb) {
        return;
    }
    sb->ptr += gap;
}

void buffer_clear(buffer_t* sb) {
    verify(sb);
    if (!sb) {
        return;
    }
    if (!sb->ptr) {
        return;
    }
    sb->ptr = sb->ptr - sb->pos;
    sb->pos = 0;
}
