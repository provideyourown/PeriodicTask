#ifndef PeriodicTask_h
#define PeriodicTask_h


/**
 * PeriodicTask is essential a thread that executes a task at prescribed intervals. Its timing is based on either millis() or micros(), which
 * unit can be set at construct time, millis is the default. It handles rollovers automatically using the technique described in http://arduino.cc/playground/Code/TimingRollover
 * To use, inherit from your class that will perform the task. This class must then implement the doTask() function, where it does its work.
 * Lastly, in order for the task to be executed, you must call myTask.run() each time in your loop() function.
 */
class PeriodicTask {
public:
  // in creating the task it will not run until the timeInterval has expired. If you want to run it right away, call enableTask(true)
  PeriodicTask(int timeInterval, bool useMillis = true)
 : mUseMillis(useMillis), mTimeInterval(timeInterval), mExpirationTime(0), mEnabled(true) {}

  virtual void init() = 0; // you must call this in your setup() func

  void setTimeInterval(unsigned long timeInterval);

  // you can disable a task to save processing time - remember to enable when it is needed again!
  void enableTask(bool runNow); // you can run it right away or after the expiration time has elapsed
  void disableTask() { mEnabled = false; }

  bool enabled() const { return mEnabled; }

  virtual void run(); // call this once each time in your loop() func

protected:
  virtual void doTask() = 0;

  void doInit(); // you must call this in child class's init() func

  unsigned long currentTime() const;

  void setNextExpiration(bool runImmediately = false);


private:
  bool mUseMillis; // if 0, then use micros()
  unsigned long mTimeInterval;
  unsigned long mExpirationTime;
  bool mEnabled;
};


#endif // PeriodicTask_h
