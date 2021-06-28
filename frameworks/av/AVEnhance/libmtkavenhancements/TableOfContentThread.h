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

#ifndef TABLE_OF_CONTENT_THREAD_H_

#define TABLE_OF_CONTENT_THREAD_H_

#include <media/stagefright/MediaErrors.h>
#include <utils/threads.h>
#include <utils/KeyedVector.h>


namespace android
{
/********************************************************
class TableOfContentThread  to build Toc table
********************************************************/


class TableOfContentThread
{
public:
    enum
    {
        TOC_TABLE_SIZE = 256,
        TOC_TABLE_INTERVAL_INTIAL = 32
    };
    struct TableEntry
    {
        Vector<off64_t> TocPos;
        Vector<int64_t> TocTS;
        Vector<off_t> PaktPos;   //for CAF format
        uint32_t size;
    };

    Mutex mLock;

    TableOfContentThread();
    virtual ~TableOfContentThread();
    //start thread  the firstFramePos
    // is the fist Frame Position except File Header.
    void startTOCThread(off64_t firstFramePos, uint32_t TocSize = TOC_TABLE_SIZE, uint32_t TocInterval = TOC_TABLE_INTERVAL_INTIAL);
    void stopTOCThread();
    // the most important function to used by TableofContentThread, this function must be implemented if
    //TableofContentThread is used to build seek table. ipCurPos is the current position to parser, this position will be modifed if
    // this position is not an valid frame position. pNextPos is the next frame
    //position reference to current position,frameTsUs is the time of one frame in us,
    virtual status_t getNextFramePos(off64_t *pCurpos, off64_t *pNextPos, int64_t *frameTsUs) = 0;
    // base class must implements this function to support sending actural duration to app.
    virtual status_t  sendDurationUpdateEvent(int64_t duration) = 0;

    //get frame pos according to targetTimeUs,pActualTimeUs and pActualPos will save
    //the actual time and pos found in toc, bMandatory indicates  whether to parse to
    //the targetTimeUs even toc is in beening built process and has not built up to targetTimeUs.
    status_t getFramePos(int64_t targetTimeUs, int64_t *pActualTimeUs, off64_t *pActualPos, bool bMandatory = false, bool bSekUseUndoneTable = false);
    //Set TOC_TABLE_SIZE and TOC_TABLE_INTERVAL_INTIAL

protected:
    bool isCAFFormat;
    off_t mFirstPaktPos;
    off_t mCurPaktPos;
    off_t mNextPaktPos;
    off_t mSeekPaktPos;

private:
    off64_t mCurFilePos;
    off64_t mNextFilePos;
    off_t mTocIntervalLeft;
    uint32_t mFrameNum;
    bool mRunning;
    pthread_t mThread;
    bool mStopped;
    TableEntry m_Toc;
    uint32_t mTocSize;
    uint32_t mEntryCount;
    bool mTocComplete;
    uint32_t mTocInterval;
    int64_t mDuration;
    int64_t mTocTimeUs;// Table Of Content Duration
    off64_t mFirstFramePos;  // differs with different format
    static void *threadWrapper(void *me);
    void threadEntry();
    status_t useAFrameToTOC();
};

}

#endif
