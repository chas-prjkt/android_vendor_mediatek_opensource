/*
 * Copyright (C) 2021 The Android Open Source Project
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

struct page_header {
    uint32_t page_status;
    uint32_t valid_length;
    unsigned char buffer[0];
};

struct buffer_header {
    uint32_t guard_band;
    uint32_t allocate_index;
    uint32_t free_index;
    uint32_t read_index;
    uint32_t write_index;
    uint32_t page_size;
    uint32_t data_buffer_size;
    uint32_t guard_band_e;
};

typedef int (*ccci_shm_srv_read_callback)(void);

struct ccb_ctrl_info {
    unsigned int  user_id;      /*user id from ccb start*/
    unsigned int ctrl_offset;
    unsigned int ctrl_addr;     /*phy addr*/
    unsigned int ctrl_length;
};

struct ccci_ccb_control_user {
    CCCI_USER user_id;
    struct ccb_ctrl_info ctrl_info;
    unsigned char *ctrl_base_address; /*virtual addr*/
    unsigned int buffer_num;
    unsigned char *base_address;
    unsigned int total_length;
    int fd;
    int ctrl_fd;
    struct ccci_ccb_control_buff *buffers;
};

struct ccci_ccb_control_buff {
    unsigned int dl_page_num;
    unsigned int ul_page_num;
    struct buffer_header *dl_header;
    struct buffer_header *ul_header;
    struct page_header *dl_pages;
    struct page_header *ul_pages;
};

enum {
    PAGE_STATUS_INIT = 0,
    PAGE_STATUS_ALLOC = 0x11111111,
    PAGE_STATUS_WRITE_DONE = 0x22222222,
};

enum {
    P_CORE = 0,
    VOLTE_CORE,
};

enum {
    CCB_USER_INVALID = 0,
    CCB_USER_OK,
    CCB_USER_ERR,
};

#define HEADER_MAGIC_BEFORE 0xAABBCCDD
#define HEADER_MAGIC_AFTER 0xDDBBCCAA
#define TAIL_MAGIC_BEFORE 0xEEFF0011
#define TAIL_MAGIC_AFTER 0x1100FFEE
