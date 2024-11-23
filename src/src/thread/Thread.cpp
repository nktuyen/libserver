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
				pThread->mExitCode = pThread->onRun();
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
		: mExitCode(0)
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
	bool Thread::Create(int statckSize)
	{
		FI();
		FO();
		return false;
	}

	/**
	 * Wait until thread exit
	 */
	int Thread::Wait()
	{
		FI();
		FO();
		return 0;
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
		FI();
		bool res = false;
		std::lock_guard<std::mutex> locker(mMutex);
		res = mRunning;
		FO();
		return res;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
}