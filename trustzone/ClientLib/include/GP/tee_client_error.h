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

#ifndef __TEE_CLIENT_ERROR_H__
#define __TEE_CLIENT_ERROR_H__

#define TEEC_SUCCESS                      ((TEEC_Result)0x00000000)

/**
 * Generic error code : Generic error
 **/
#define TEEC_ERROR_GENERIC                ((TEEC_Result)0xFFFF0000)

/**
 * Generic error code : The underlying security system denies the access to the
 * object
 **/
#define TEEC_ERROR_ACCESS_DENIED          ((TEEC_Result)0xFFFF0001)

/**
 * Generic error code : The pending operation is cancelled.
 **/
#define TEEC_ERROR_CANCEL                 ((TEEC_Result)0xFFFF0002)

/**
 * Generic error code : The underlying system detects a conflict
 **/
#define TEEC_ERROR_ACCESS_CONFLICT        ((TEEC_Result)0xFFFF0003)

/**
 * Generic error code : Too much data for the operation or some data remain
 * unprocessed by the operation.
 **/
#define TEEC_ERROR_EXCESS_DATA            ((TEEC_Result)0xFFFF0004)

/**
 * Generic error code : Error of data format
 **/
#define TEEC_ERROR_BAD_FORMAT             ((TEEC_Result)0xFFFF0005)

/**
 * Generic error code : The specified parameters are invalid
 **/
#define TEEC_ERROR_BAD_PARAMETERS         ((TEEC_Result)0xFFFF0006)

/**
 * Generic error code : Illegal state for the operation.
 **/
#define TEEC_ERROR_BAD_STATE              ((TEEC_Result)0xFFFF0007)

/**
 * Generic error code : The item is not found
 **/
#define TEEC_ERROR_ITEM_NOT_FOUND         ((TEEC_Result)0xFFFF0008)

/**
 * Generic error code : The specified operation is not implemented
 **/
#define TEEC_ERROR_NOT_IMPLEMENTED        ((TEEC_Result)0xFFFF0009)

/**
 * Generic error code : The specified operation is not supported
 **/
#define TEEC_ERROR_NOT_SUPPORTED          ((TEEC_Result)0xFFFF000A)

/**
 * Generic error code : Insufficient data is available for the operation.
 **/
#define TEEC_ERROR_NO_DATA                ((TEEC_Result)0xFFFF000B)

/**
 * Generic error code : Not enough memory to perform the operation
 **/
#define TEEC_ERROR_OUT_OF_MEMORY          ((TEEC_Result)0xFFFF000C)

/**
 * Generic error code : The service is currently unable to handle the request;
 * try later
 **/
#define TEEC_ERROR_BUSY                   ((TEEC_Result)0xFFFF000D)

/**
 * Generic communication error
 **/
#define TEEC_ERROR_COMMUNICATION          ((TEEC_Result)0xFFFF000E)

/**
 * Generic error code : security violation
 **/
#define TEEC_ERROR_SECURITY               ((TEEC_Result)0xFFFF000F)

/**
 * Generic error code : the buffer is too short
 **/
#define TEEC_ERROR_SHORT_BUFFER           ((TEEC_Result)0xFFFF0010)

/**
 * Error of communication: The target of the connection is dead
 **/
#define TEEC_ERROR_TARGET_DEAD            ((TEEC_Result)0xFFFF3024)

/**
 * File system error code: not enough space to complete the operation.
 **/
#define TEEC_ERROR_STORAGE_NO_SPACE       ((TEEC_Result)0xFFFF3041)

#endif /* __TEE_CLIENT_ERROR_H__ */
