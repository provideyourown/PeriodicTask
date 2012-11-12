//--------------------------------------------------------------
// SPeriodicTask
// =========
//  Provides non-blocking scheduling periodic tasks for the
// Arduino platform.
//--------------------------------------------------------------
// Copyright (c) 2012 the artist authors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//--------------------------------------------------------------
// Contributors:
//   Scott Daniels - http://ProvideYourOwn.com
//--------------------------------------------------------------
#ifndef SPeriodicTask_h
#define SPeriodicTask_h

class Scheduler;
class Task;

#include "../Scheduler/Function.h"

/**
 * PeriodicTask is essential a thread that executes a task at prescribed intervals. Its timing is based on either millis() or micros(), which
 * unit can be set at construct time, millis is the default. It handles rollovers automatically using the technique described in http://arduino.cc/playground/Code/TimingRollover
 * To use, inherit from your class that will perform the task. This class must then implement the doTask() function, where it does its work.
 * Lastly, in order for the task to be executed, you must call myTask.run() each time in your loop() function.
 */
class SPeriodicTask {
public:
  // in creating the task it will not run until the timeInterval has expired. If you want to run it right away, call enableTask(true)
  SPeriodicTask(Scheduler& scheduler, int timeInterval, bool useMillis = true);

  void init();

  void setTimeInterval(unsigned long timeInterval);

  // you can disable a task to save processing time - remember to enable when it is needed again!
  void enableTask(bool runNow); // you can run it right away or after the expiration time has elapsed
  void disableTask();
  
  bool enabled() const { return mEnabled; }
  
  
protected:
  void thisTask() { this->doTask(); }
  virtual void doTask() = 0;
  
  void updateTask();
  
private:
  Scheduler& mScheduler;
  Task* mTask;
  bool mUseMillis; // if 0, then use micros()
  unsigned long mTimeInterval;
  bool mEnabled;

  VoidFxPtr<SPeriodicTask> mTaskFunc;
};


#endif // SPeriodicTask_h
