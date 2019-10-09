

Examples:

Here's a one-shot timer. To use it, simply enable it.

class OneShotTimer : public PeriodicTask {
    OneShotTimer()
     : PeriodicTask(500),
     {}

    virtual void init() { PeriodicTask::doInit(); disableTask(); } // you must call this in your setup() func

protected:
  virtual void doTask() { disableTask(); } // we are done now - one shot timer
};

OneShotTimer timer;

// in setup/init()
timer.init();

// in loop/run()
timer.run();

// start timer
timer.enableTask(true);