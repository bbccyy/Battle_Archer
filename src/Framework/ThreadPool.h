/**********************************************************************************************************************
*
* Copyright (c) 2018 babeltime.com, Inc. All Rights Reserved
* $Id$
*
**********************************************************************************************************************/

/**
* @file $HeadURL$
* @author wuqilin
* @date $Date$
* @version $Revision$
* @brief
*
**/


#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool 
{
public:
    void Start(std::function<void()>, std::function<void()>, size_t);
    template<class F, class... Args>
    auto Enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    void StopThreadPool();
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector< std::thread > mWorkers;
    // the task queue
    std::queue< std::function<void()> > mTasks;
    
    // synchronization
    std::mutex mQueueMutex;
    std::condition_variable mCondition;
    bool mStop;
};
 
// the constructor just launches some amount of mWorkers
inline void ThreadPool::Start(std::function<void()> aInitFunc, std::function<void()> aEndFunc, size_t aThreadNum)
{
    mStop = false;
    for(size_t i = 0; i<aThreadNum; ++i)
        mWorkers.emplace_back(
            [this, aInitFunc, aEndFunc]
            {
                aInitFunc();
                for(;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->mQueueMutex);
                        this->mCondition.wait(lock,
                            [this]{ return this->mStop || !this->mTasks.empty(); });
                        if(this->mStop && this->mTasks.empty())
                            break;
                        task = std::move(this->mTasks.front());
                        this->mTasks.pop();
                    }

                    task();
                }
                aEndFunc();
            }
        );
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::Enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(mQueueMutex);

        // don't allow enqueueing after stopping the pool
        if(mStop)
            throw std::runtime_error("Enqueue on stopped ThreadPool");

        mTasks.emplace([task](){ (*task)(); });
    }
    mCondition.notify_one();
    return res;
}

// the destructor joins all threads
inline void ThreadPool::StopThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        if(mStop)
        {
            return;
        }
        mStop = true;
    }
    mCondition.notify_all();
    for(std::thread &worker: mWorkers)
        worker.join();
}

inline ThreadPool::~ThreadPool()
{
    StopThreadPool();
}
