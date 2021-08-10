/**
 * @file TasksGroup.cpp
 * @author Antoni Wielgus
 * @date 2021-08-09
 */

#include "../Common/TasksGroup.h"

using namespace Common;


TasksGroup::TasksGroup(uint8_t maxTasksAmount)
    : MaxTasksAmount(maxTasksAmount)
{
    if (MaxTasksAmount > 0)
        tasksArray = new IExecutable* [maxTasksAmount];
}

TasksGroup::~TasksGroup()
{
    if (MaxTasksAmount > 0)
        delete[] tasksArray;
}

bool TasksGroup::addTask(IExecutable* task)
{
    if (tasksAmount >= MaxTasksAmount)
        return false;

    tasksArray[tasksAmount] = task;
    tasksAmount++;

    return true;
}

void TasksGroup::execute()
{
    for (uint8_t i = 0; i < tasksAmount; i++)
        tasksArray[i]->execute();
}


