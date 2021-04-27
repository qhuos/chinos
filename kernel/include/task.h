#ifndef __THREAD_H
#define __THREAD_H
#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include "timer.h"
#include "trap.h"

#define TASK_DEFAULT_TIME_STEP (10) 

typedef struct __task_struct {
    pid_t pid;
    uint64_t create_time;
    int64_t left_time;
    unsigned long epc;
    unsigned long sp;
    regs task_reg;
    int flag;
    struct __task_struct *next;
    struct __task_struct *prev;
} task_struct;

//idle进程的结构
extern task_struct init_task;

//进程链表
extern task_struct *task_list;

//系统第一个进程，也就是idle进程的结构初始化
#define INIT_TASK(task)                     \
{                                           \
    .pid = 0,                               \
    .create_time = 0,                       \
    .left_time = TASK_DEFAULT_TIME_STEP,    \
    .epc = 0,                               \
    .sp = 0,                                \
    .flag = 0,                              \
    .next = &init_task,                     \
    .prev = &init_task                      \
}

/**
 * @brief 向进程调度器添加进程
 * 
 * @param[in] task 被添加的任务
 */
void add_task(task_struct *task);

/**
 * @brief 从进程调度器中删除进程
 * 
 * @param[in] task 被删除的进程
 */
void delte_task(task_struct *task);

/**
 * @brief 分配一个task_struct结构
 * 
 * @return 返回一个task_struct指针
 */
task_struct *alloc_task(void);

//指向当前的进程
extern task_struct *current;

//pid分配位图
extern uint64_t pid_bitmap[32];
#endif