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

#ifndef _COMMANDRESPONDOR_H
#define _COMMANDRESPONDOR_H

#include <list>
#include <sys/types.h>

namespace android {
namespace netdagent {

enum ResponseCode {
    // 200 series - Requested action has been successfully completed
	CommandOkay   = 200,
    // 400 series - The command was accepted but the requested action
    // did not take place.
    OperationFailed           = 400,
    // 500 series - The command was not accepted and the requested
    // action did not take place.
    CommandSyntaxError = 500,
};

class CommandRespondor {

public:
    CommandRespondor(int sock);
    virtual ~CommandRespondor();

    int getConnectSocket() { return mConnectSocket; }
    pid_t getPid() const { return mPid; }
    uid_t getUid() const { return mUid; }
    gid_t getGid() const { return mGid; }

    void setCmdSeq(int cmdSeq) {
        mCmdSeq = cmdSeq;
    }
    int getCmdSeq() { return mCmdSeq; }

    // Send null-terminated C strings:
	void sendMsg(int code, const char *msg, bool addErrno);

private:
    // Sending binary data. The caller should make sure this is protected
    // from multiple threads entering simultaneously.
    // returns 0 if successful, -1 if there is a 0 byte write or if any
    // other error occurred (use errno to get the error)
	int sendMsg(const char *msg);
    int mConnectSocket;
    unsigned int mCmdSeq;  //command sequence
    pid_t mPid;    // Peer process ID
    uid_t mUid;    // Peer user ID
    gid_t mGid;    // Peer group ID

};

}  // namespace netdagent
}  // namespace android

#endif
