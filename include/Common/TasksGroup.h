/**
 * @file TasksGroup.h
 * @author Antoni Wielgus
 * @brief This classes is used to group tasks into one
 * @date 2021-08-09
 */

#ifndef TASKSGROUP_H
#define TASKSGROUP_H

#include <IExecutable.h>
#include <cstdint>


namespace Common
{
    class TasksGroup : public IExecutable
    {
        IExecutable** tasksArray;
        const uint8_t MaxTasksAmount;
        uint8_t tasksAmount = 0;


    public:
        TasksGroup(uint8_t maxTasksAmount)
            : MaxTasksAmount(maxTasksAmount)
        {
            tasksArray = new IExecutable* [MaxTasksAmount];
        }

        TasksGroup(const TasksGroup&) = delete;
        TasksGroup& operator=(const TasksGroup&) = delete;

        ~TasksGroup()
        {
            delete[] tasksArray;
        }

        bool addTask(IExecutable* task)
        {
            if (tasksAmount >= MaxTasksAmount)
                return false;

            tasksArray[tasksAmount] = task;
            tasksAmount++;
            return true;
        }

        void execute() override
        {
            for (uint8_t i = 0; i < tasksAmount; ++i)
                tasksArray[i]->execute();
        }
    };
}


#endif
