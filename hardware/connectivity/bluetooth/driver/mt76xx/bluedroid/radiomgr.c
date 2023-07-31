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

#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

#include "bt_mtk.h"


/**************************************************************************
 *                          F U N C T I O N S                             *
***************************************************************************/

VOID BT_Cleanup(VOID)
{
    if (SIG_ERR == signal(SIGRTMIN, SIG_DFL)) {
        LOG_ERR("Restore signal handler fails errno(%d)\n", errno);
    }
    return;
}
