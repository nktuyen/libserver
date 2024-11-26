///////////////////////////////////////////////////////////
//  Thread.cpp
//  Implementation of the Class Thread
//  Created on:      23-Nov-2024 4:08:04 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#include "Thread.hpp"
#include "Logger.hpp"

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _WINDOWS
	DWORD WINAPI Thread::ThreadProc(LPVOID lpParam)
	{
#else  // ! _WINDOWS
	void *Thread::ThreadProc(void *lpParam)
	{
#endif //_WINDOWS
		Thread *pThread = nullptr;
		try
		{
			pThread = reinterpret_cast<Thread *>(lpParam);
		}
		catch (...)
		{
		}

		if (pThread != nullptr)
		{
			if (!pThread->onInitialize())
			{
				pThread->mExitCode = pThread->onFailure();
			}
			else
			{
				pThread->mRunning = true;
				pThread->mExitCode = pThread->onRun();
				pThread->mRunning = false;
				if (pThread->mExitCode != 0)
					pThread->mExitCode = pThread->onFailure();
				else
					pThread->onSuccess();
			}
#ifdef _WINDOWS
			return pThread->mExitCode;
#else
			return &pThread->mExitCode;
#endif //_WINDOWS
		}
#ifdef _WINDOWS
		return 0;
#else
		return nullptr;
#endif //_WINDOWS
	}

	/**
	 * Constructor
	 */
	Thread::Thread()
		: mHandle(InvalidThreadHandle), mExitCode(0)
	{
		FI();

		FO();
	}

	/**
	 * Destructor
	 */
	Thread::~Thread()
	{
		FI();
		FO();
	}

	/**
	 * Create thread
	 */
	bool Thread::Create(int stackSize)
	{
		FI();

		if (mHandle != InvalidThreadHandle)
		{
			FO();
			throw;
		}
		int res = 0;
#ifdef _WINDOWS
		mHandle = CreateThread(nullptr, stackSize, &Thread::ThreadProc, this, 0, nullptr);
#else  // ! _WINDOWS
		pthread_attr_t attr = {0};
		res = pthread_attr_init(&attr);
		if (stackSize > 0)
		{
			res = pthread_attr_setstacksize(&attr, stackSize);
		}
		mHandle = &mThread;
		res = pthread_create(mHandle, &attr, &Thread::ThreadProc, this);
		pthread_attr_destroy(&attr);
#endif //_WINDOWS

		FO();
		return res == 0 && mHandle != InvalidThreadHandle;
	}

	/**
	 * Wait until thread exit
	 */
	int Thread::Wait()
	{
		FI();
		int retval = 0;
		int *ref = &retval;
#ifdef _WINDOWS
		DWORD res = 0;
		if (WaitForSingleObject(mHandle, INFINITE) == WAIT_OBJECT_0)
		{
			if (!GetExitCodeThread(mHandle, &res))
				res = 0;
		}
#else  // ! _WINDOWS
		int res = pthread_join(*mHandle, (void **)&ref);
#endif //_WINDOWS

		FO();
		return res;
	}

	/**
	 * Stop thread run loop
	 */
	void Thread::Stop()
	{
		FI();
		std::lock_guard<std::mutex> locker(mMutex);
		mRunning = false;
		FO();
	}

	/**
	 * Return running status
	 */
	bool Thread::isRunning()
	{
		bool res = false;
		std::lock_guard<std::mutex> locker(mMutex);
		res = mRunning;
		return res;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
}