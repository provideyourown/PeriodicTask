#include "SPeriodicTask.h"

#include <WProgram.h>

#include "../Scheduler/Scheduler.h";
#include "../Scheduler/Task.h";
#include "../Scheduler/Function.h";


SPeriodicTask::SPeriodicTask(Scheduler& scheduler, int timeInterval, bool useMillis)
 : mScheduler(scheduler), mTask(NULL), mTimeInterval(timeInterval), mUseMillis(useMillis), mEnabled(true),
   mTaskFunc(this, &SPeriodicTask::doTask)
{
  mTask = mScheduler.setInterval(&mTaskFunc, mTimeInterval);
}

void SPeriodicTask::init()
{
  mTask = mScheduler.setInterval(&mTaskFunc, mTimeInterval);
}

void SPeriodicTask::setTimeInterval(unsigned long timeInterval) 
{ 
  mTimeInterval = timeInterval;
  this->updateTask();
}

void SPeriodicTask::enableTask(bool runNow) 
{ 
  mEnabled = true; 
  this->updateTask();
  if (runNow)
    this->doTask();
}

void SPeriodicTask::disableTask()
{ 
  mEnabled = false;
  this->updateTask();
}

void SPeriodicTask::updateTask()
{
  // if we already have a task, kill it
  if (mTask) {
    mScheduler.clearInterval(mTask);
    mTask = NULL;
  }
  // only start a new task if enabled
  if (mEnabled)
    mTask = mScheduler.setInterval(&mTaskFunc, mTimeInterval);
}


