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

#ifndef _IFC_H_
#define _IFC_H_

__BEGIN_DECLS

extern int ifc_set_txq_state(const char *ifname, int state);
extern int ifc_ccmni_md_cfg(const char *ifname, int md_id);
int ifc_enable_ack_prio(int enable);

__END_DECLS

#endif /* _IFC_H_ */
