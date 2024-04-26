/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 * Copyright (c) 2021 Nuclei Limited. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Provide a task example.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include "task_sample.h"
#include "nuclei_sdk_hal.h"
#include "los_config.h"
#include "los_debug.h"
#include "los_interrupt.h"
#include "los_arch_interrupt.h"
#include "los_task.h"
#include "los_tick.h"
#include "securec.h"
#include "los_memory.h"
#include "los_ramfs.h"
#include "los_vfs.h"

void ramfs_task_sample(void) {
    int fd = -1;
    // 初始化 RAM 文件系统
    if (ramfs_init() != LOS_OK) {
        printf("文件初始化系统失败\n");
        return;
    }

    // 挂载文件系统到指定路径
    if (ramfs_mount("/ramfs",2048) != LOS_OK) {
        printf("文件系统挂载失败\n");
        return;
    }
    //创建文件目录
    if (los_mkdir("/ramfs/fcm", 00700) != LOS_OK) {
        printf("目录创建失败\n");
    } 


    // 写入文件
    fd = los_open("/ramfs/fcm/hello.txt",00777);
    if (fd < 0) {
        printf("打开失败\n");
        return;
    }
    
    const char* content = "你好!!!!\n";
    ssize_t ret = los_write(fd, content, strlen(content));
    if (ret < 0) {
        printf("写入失败\n");
        los_close(fd);
        return;
    }
    los_close(fd);

    // 读取文件并输出内容
    fd = los_open("/ramfs/fcm/hello.txt", O_RDONLY);
    if (fd < 0) {
        printf("读取失败\n");
        return;
    }

    char buffer[256];
    ssize_t bytesRead;
    while ((bytesRead = los_read(fd, buffer, sizeof(buffer))) > 0) {
        printf("输出内容：%.*s", (int)bytesRead, buffer);
    }
    los_close(fd);
}

void create_ramfs_task(void) {
    UINT32 taskID;
    TSK_INIT_PARAM_S task_init_param;

    // 初始化任务参数
    memset(&task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)ramfs_task_sample;
    task_init_param.uwStackSize = 0x800;  // 设置任务栈大小
    task_init_param.pcName = "ramfs_task";
    task_init_param.usTaskPrio = 1;

    // 创建任务
    UINT32 uwRet = LOS_TaskCreate(&taskID, &task_init_param);
    if (uwRet != LOS_OK) {
        printf("Task creation failed\n");
        // 处理任务创建失败的情况
    }
}