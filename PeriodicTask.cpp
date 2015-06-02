#include "PeriodicTask.h"

#include <Arduino.h>

void PeriodicTask::doInit()
{
  setNextExpiration(mTimeInterval);
}

void PeriodicTask::setTimeInterval(unsigned long timeInterval)
{
  mTimeInterval = timeInterval;
  setNextExpiration(mTimeInterval);
}

void PeriodicTask::enableTask(bool runNow)
{
  mEnabled = true;
   // set expiration time to something current, not zero - otherwise, during the latter half of micros, the task will not run (long)micros() is negative)
  setNextExpiration(mTimeInterval, runNow);
}

void PeriodicTask::run()
{
  if (!mEnabled) return; // disabled, return as to not take any more processing time

  // handles rollover, see - http://arduino.cc/playground/Code/TimingRollover
  if (((long)(currentTime() - mExpirationTime)) > 0) // time to execute task
  {
    // doTask may change our time interval, so we do it first
    doTask();
    setNextExpiration(mTimeInterval); // set time for next task
  }
  // else wait till next time
}

unsigned long PeriodicTask::currentTime() const
{
  return mUseMillis? millis() : micros();
}

void PeriodicTask::setNextExpiration(unsigned long timeInterval, bool runImmediately)
{
  mExpirationTime = (runImmediately)? currentTime() : currentTime() + timeInterval;
}

