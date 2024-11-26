///////////////////////////////////////////////////////////
//  Thread.h
//  Implementation of the Class Thread
//  Created on:      23-Nov-2024 4:08:04 PM
//  Original author: Tuyen
///////////////////////////////////////////////////////////

#if !defined(EA_CF6CCB64_30C8_47bc_8458_9ED667EB872E__INCLUDED_)
#define EA_CF6CCB64_30C8_47bc_8458_9ED667EB872E__INCLUDED_

#include <mutex>
#ifdef _WINDOWS
#include <Windows.h>
typedef HANDLE ThreadHandle;
#else // ! _WINDOWS
#include <pthread.h>
typedef pthread_t *ThreadHandle;
#endif //_WINDOWS

#define InvalidThreadHandle (ThreadHandle)(nullptr)

namespace T
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Thread
	{

	public:
		/**
		 * Destructor
		 */
		virtual ~Thread();
		/**
		 * Create thread
		 */
		virtual bool Create(int stackSize = 0);
		/**
		 * Return thread's handle
		 */
		inline ThreadHandle handle()
		{
			return mHandle;
		}
		/**
		 * Wait until thread exit
		 */
		int Wait();
		/**
		 * Stop thread run loop
		 */
		void Stop();
		/**
		 * Return running status
		 */
		bool isRunning();
		/**
		 * Return thread's exit code
		 */
#ifdef _WINDOWS
		inline DWORD exitCode() { return mExitCode; }
#else  //! _WINDOWS
		inline int exitCode() { return mExitCode; }
#endif //_WINDOWS
	private:
		ThreadHandle mHandle;
		bool mRunning;
		std::mutex mMutex;
#ifdef _WINDOWS
		friend static DWORD WINAPI ThreadProc(LPVOID lpParam);
		static DWORD WINAPI ThreadProc(LPVOID lpParam);
		DWORD mExitCode;
#else  // ! _WINDOWS
		pthread_t mThread;
		friend void *ThreadProc(void *lpParam);
		static void *ThreadProc(void *lpParam);
		int mExitCode;
#endif //_WINDOWS
	protected:
		/**
		 * Initialize data at subclass. Return false to break running thread
		 */
		virtual bool onInitialize() { return true; }
		/**
		 * Run loop. Overwrite the method in subclass to run own tasks.
		 */
		virtual int onRun() { return 0; }
		/**
		 * Callback method that will be called when thread is finished and success.
		 */
		virtual void onSuccess() { ; }

		/**
		 * Callback method that will be called when thread is finished due to a failure.
		 */
		virtual int onFailure() { return 1; }
		/**
		 * Constructor
		 */
		explicit Thread();
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // !defined(EA_CF6CCB64_30C8_47bc_8458_9ED667EB872E__INCLUDED_)
