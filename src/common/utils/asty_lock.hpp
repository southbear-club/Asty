/**
 * @file asty_lock.hpp
 * @author wotsen (astralrovers@outlook.com)
 * @brief
 * @date 2021-01-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <pthread.h>
#include <time.h>
#include <mutex>

namespace asty {

namespace utils {

#ifndef DISALLOW_COPY_AND_ASSIGN

#define DISALLOW_COPY_AND_ASSIGN(Type) \
    Type(const Type&) = delete;        \
    void operator=(const Type&) = delete

#endif

/**
 * @brief 锁
 *
 */
class ILock {
public:
    virtual ~ILock() {}

    // 上锁
    virtual bool lock(void) = 0;
    // 解锁
    virtual bool unlock(void) = 0;
    // 尝试锁
    virtual bool try_lock(time_t w = -1) = 0;
    // TODO:wait
    // TODO:notyfiy
};

class CppMtxLock : public ILock {
public:
    virtual ~CppMtxLock() {}

    virtual bool lock(void) override {
        mtx_.lock();
        return true;
    }

    virtual bool unlock(void) override {
        mtx_.unlock();
        return true;
    }

    virtual bool try_lock(time_t w = -1) override { return mtx_.try_lock(); }

public:
    std::mutex mtx_;
};

class RwMutex {
public:
    RwMutex() { pthread_rwlock_init(&_mutex, nullptr); }

    ~RwMutex() { pthread_rwlock_destroy(&_mutex); }

    void rlock() { pthread_rwlock_rdlock(&_mutex); }

    void wlock() { pthread_rwlock_wrlock(&_mutex); }

    bool try_rlock() { return pthread_rwlock_tryrdlock(&_mutex) == 0; }

    bool try_wlock() { return pthread_rwlock_trywrlock(&_mutex) == 0; }

    bool try_rlock_timeout(struct timespec& t) {
        return pthread_rwlock_timedrdlock(&_mutex, &t) == 0;
    }

    bool try_wlock_timeout(struct timespec& t) {
        return pthread_rwlock_timedwrlock(&_mutex, &t) == 0;
    }

    void unlock() { pthread_rwlock_unlock(&_mutex); }

    pthread_rwlock_t* mutex() { return &_mutex; }

private:
    pthread_rwlock_t _mutex;
    DISALLOW_COPY_AND_ASSIGN(RwMutex);
};

class RMutexGuard {
public:
    explicit RMutexGuard(RwMutex& lock) : _lock(lock) { _lock.rlock(); }
    explicit RMutexGuard(RwMutex* lock) : _lock(*lock) { _lock.rlock(); }

    ~RMutexGuard() { _lock.unlock(); }

    void lock() { _lock.rlock(); }
    void unlock() { _lock.unlock(); }

private:
    RwMutex& _lock;
    DISALLOW_COPY_AND_ASSIGN(RMutexGuard);
};

class WMutexGuard {
public:
    explicit WMutexGuard(RwMutex& lock) : _lock(lock) { _lock.wlock(); }
    explicit WMutexGuard(RwMutex* lock) : _lock(*lock) { _lock.wlock(); }

    ~WMutexGuard() { _lock.unlock(); }

    void lock() { _lock.wlock(); }
    void unlock() { _lock.unlock(); }

private:
    RwMutex& _lock;
    DISALLOW_COPY_AND_ASSIGN(WMutexGuard);
};

}  // namespace utils

}  // namespace asty
