PeriodicTask simulates a thread that executes a task at prescribed intervals. Its timing is based on either millis() or micros(), of which unit can be set at construct time, millis is the default. It handles rollovers automatically using the technique described in http://arduino.cc/playground/Code/TimingRollover

To use, inherit from your class that will perform the task. This class must then implement the `doTask()` function, where it does its work. Lastly, in order for the task to be executed, you must call `myTask.run()` each time in your `loop()` function.

Examples:

Timer to run every 10ms:

    class MyTask : public PeriodicTask {
    public:
        MyTask() : PeriodicTask(10) {} // do task every 10 ms
    
        virtual void init() { PeriodicTask::doInit(); } // you must call this in your setup() func
    
        virtual void run() {} // (optional) - but do call this once each time in your loop() func; we overrode it so we can call SoftPWM run for our led
    
        protected:
        virtual void doTask(); // here is where you will do your task
    };
    
    MyTask mytask;
    
    void setup()
    {
        myTask.init();
    }
    
    void loop()
    {
        myTask.run();
    }
    
Here's a one-shot timer. To use it, simply enable it.


    class OneShotTimer : public PeriodicTask {
        OneShotTimer() : PeriodicTask(500) {}

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