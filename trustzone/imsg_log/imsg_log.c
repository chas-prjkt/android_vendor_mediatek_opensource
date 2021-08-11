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

#include <time.h>
#include <imsg_log.h>
#include <android/log.h>

#define KMSG_DEV_FILE       "/dev/kmsg"
#define LOG_BUF_MAX  512

static int kernel_log_fd = -1;

static void kernel_log_init()
{
    if (kernel_log_fd >= 0)
        return;

    kernel_log_fd = open(KMSG_DEV_FILE, O_WRONLY);

    if (kernel_log_fd < 0) {
        IMSG_PRINT_MAINLOG("fail to open %s!\n", KMSG_DEV_FILE);
        return;
    }
    fcntl(kernel_log_fd, F_SETFD, FD_CLOEXEC);
}

void kernel_log_write(const char *fmt, ...)
{
    va_list ap;
    char buf[LOG_BUF_MAX] = {0};

    kernel_log_init();

    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF_MAX, fmt, ap);
    buf[LOG_BUF_MAX - 1] = 0;
    write(kernel_log_fd, buf, strlen(buf));
    va_end(ap);
}

int imsg_log_write(int prio, const char *tag,
                   const char *fmt, ...)
{
    va_list ap;
    char buf[LOG_BUF_MAX];

    va_start(ap, fmt);
    vsnprintf(buf, LOG_BUF_MAX, fmt, ap);
    va_end(ap);

    return __android_log_write(prio, tag, buf);
}
