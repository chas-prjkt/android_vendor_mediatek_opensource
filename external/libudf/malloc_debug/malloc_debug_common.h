/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Contains declarations of types and constants used by malloc leak
 * detection code in both, libc and libc_malloc_debug libraries.
 */
#ifndef MALLOC_DEBUG_COMMON_H
#define MALLOC_DEBUG_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

// sync HAVE_DEPRECATED_MALLOC_FUNCS definition
#include <stdlib.h>
#include <private/bionic_config.h>  // bionic/libc

#define HASHTABLE_SIZE      1543
#define BACKTRACE_SIZE      32
/* flag definitions, currently sharing storage with "size" */
#define SIZE_FLAG_ZYGOTE_CHILD  (1<<31)
#define SIZE_FLAG_MASK          (SIZE_FLAG_ZYGOTE_CHILD)

#define MAX_SIZE_T           (~(size_t)0)

// =============================================================================
// Structures
// =============================================================================

typedef struct HashEntry HashEntry;
struct HashEntry {
    size_t slot;
    HashEntry* prev;
    HashEntry* next;
    size_t numEntries;
    // fields above "size" are NOT sent to the host
    size_t size;
    size_t allocations;
    intptr_t backtrace[0];
};

typedef struct HashTable HashTable;
struct HashTable {
    size_t count;
    HashEntry* slots[HASHTABLE_SIZE];
};

/* Entry in malloc dispatch table. need sync with malloc_debug_common.h*/
#ifndef STRUCT_MALLINFO_DECLARED
#define STRUCT_MALLINFO_DECLARED 1
struct mallinfo {
  size_t arena;    /* Total number of non-mmapped bytes currently allocated from OS. */
  size_t ordblks;  /* Number of free chunks. */
  size_t smblks;   /* (Unused.) */
  size_t hblks;    /* (Unused.) */
  size_t hblkhd;   /* Total number of bytes in mmapped regions. */
  size_t usmblks;  /* Maximum total allocated space; greater than total if trimming has occurred. */
  size_t fsmblks;  /* (Unused.) */
  size_t uordblks; /* Total allocated space (normal or mmapped.) */
  size_t fordblks; /* Total free space. */
  size_t keepcost; /* Upper bound on number of bytes releasable by malloc_trim. */
};
#endif  /* STRUCT_MALLINFO_DECLARED */

typedef void* (*MallocDebugCalloc)(size_t, size_t);
typedef void (*MallocDebugFree)(void*);
typedef struct mallinfo (*MallocDebugMallinfo)(void);
typedef void* (*MallocDebugMalloc)(size_t);
typedef size_t (*MallocDebugMallocUsableSize)(const void*);
typedef void* (*MallocDebugMemalign)(size_t, size_t);
typedef int (*MallocDebugPosixMemalign)(void**, size_t, size_t);
#if defined(HAVE_DEPRECATED_MALLOC_FUNCS)
typedef void* (*MallocDebugPvalloc)(size_t);
#endif
typedef void* (*MallocDebugRealloc)(void*, size_t);
#if defined(HAVE_DEPRECATED_MALLOC_FUNCS)
typedef void* (*MallocDebugValloc)(size_t);
#endif
typedef int (*MallocIterate)(uintptr_t, size_t,
             void (*)(uintptr_t, size_t, void*), void*);
typedef void (*MallocDisable)(void);
typedef void (*MallocEnable)(void);

struct MallocDebug {
  MallocDebugCalloc calloc;
  MallocDebugFree free;
  MallocDebugMallinfo mallinfo;
  MallocDebugMalloc malloc;
  MallocDebugMallocUsableSize malloc_usable_size;
  MallocDebugMemalign memalign;
  MallocDebugPosixMemalign posix_memalign;
#if defined(HAVE_DEPRECATED_MALLOC_FUNCS)
  MallocDebugPvalloc pvalloc;
#endif
  MallocDebugRealloc realloc;
#if defined(HAVE_DEPRECATED_MALLOC_FUNCS)
  MallocDebugValloc valloc;
#endif
  MallocIterate malloc_iterate;
  MallocDisable malloc_disable;
  MallocEnable malloc_enable;
};

typedef struct MallocDebug MallocDebug;


/* Malloc debugging initialization routine.
 * This routine must be implemented in .so modules that implement malloc
 * debugging. This routine is called once per process from malloc_init_impl
 * routine implemented in bionic/libc/bionic/malloc_debug_common.c when malloc
 * debugging gets initialized for the process.
 * Return:
 *  0 on success, -1 on failure.
 */
//typedef int (*MallocDebugInit)(void);

#ifdef __cplusplus
};  /* end of extern "C" */
#endif

#endif  // MALLOC_DEBUG_COMMON_H
