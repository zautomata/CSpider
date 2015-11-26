#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include "CS.h"

typedef struct cs_rawText_struct cs_rawText_t;
/*
key value对
*/
typedef struct param_struct {
  char *key;
  char *value;
} param_t;
/*
  请求类型:post get
*/
typedef struct request_struct {
  char *type;
  param_t *param;
} request_t;
/*
  任务
  存放要执行抓取的url
*/
typedef struct cs_task_struct {
  char *url;//存放的url
  request_t *req;
  int prior;//优先级1~10
  cs_rawText_t *data;//指向任务完成后的数据
  uv_work_t *worker;//指向执行此任务的工作线程的handle
} cs_task_t;

/*
  任务队列
*/
typedef struct cs_task_queue_struct {
  cs_task_t *task;
  struct cs_task_queue_struct *next;
  struct cs_task_queue_struct *prev;
} cs_task_queue;

/*
  原始数据
  例如html，json等，直接返回的数据
*/
struct cs_rawText_struct {
  char **data;
  char *type;//数据的类型，比如html，json
};

/*
  数据队列
*/
typedef struct cs_rawText_queue_struct {
  cs_rawText_t *data;
  struct cs_rawText_queue_struct *next;
  struct cs_rawText_queue_struct *prev;
} cs_rawText_queue;

/*data.c*/
cs_rawText_queue *initDataQueue();
cs_rawText_t *createData(const char* type);

/*task.c*/
int isTaskQueueEmpty(cs_task_queue *head);
cs_task_queue *initTaskQueue();
void createTask(cs_task_queue *head, char *url, request_t *req, int prior);
cs_task_queue *removeTask(cs_task_queue *head, cs_task_t *task);
void addTask(cs_task_queue *head, cs_task_queue *task);
void freeTask(cs_task_queue *node);

#endif
