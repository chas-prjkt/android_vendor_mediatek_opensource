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

#ifndef MTK_ROI_H_
#define MTK_ROI_H_

#include <media/stagefright/ACodec.h>
#include <utils/RefBase.h>

namespace android {

class MtkRoi : public RefBase
{
public:
    MtkRoi();
    status_t setRoiParameters(const sp<IOMXNode> &spNode, const sp<AMessage> &msg);

private:
    int32_t mRoiOnMode;
};

}  // namespace android

#endif  // MTK_ROI_H_
