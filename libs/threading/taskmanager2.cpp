#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#include <Windows.h>
#include "taskmanager2.h"

	DEFINE_SINGLETON(taskmanager);

	unsigned WINAPI poolrun(void* i_param)
	{
		taskmanager* tm=(taskmanager*)i_param;
		tm->run();
		return 0;
	}

	taskmanager::taskmanager(const taskmanagerdesc* i_desc)
	{
		m_incompletetasknum=0;

		m_workevent= CreateSemaphore(NULL,0,10000,NULL);
		m_exitevent= CreateEvent(NULL,TRUE,FALSE,NULL);

		for (unsigned n=0; n<REF_COUNT;++n)
		{
			m_ref_index.push(n);
			m_ref_event[n]=CreateEvent(NULL,TRUE,FALSE,NULL);
			m_ref_buf[n]=0;
		}

		if (i_desc->m_threadnum)
			m_threadbuf.resize(i_desc->m_threadnum);

		for (unsigned n=0; n<m_threadbuf.size();++n)
		{
			m_threadbuf[n].start(&poolrun,this);

			char str[256]; sprintf(str,"working thread #%d",n+1);
			m_threadbuf[n].set_name(string(str));
		}

	}

	taskmanager::~taskmanager()
	{
		exit();
	}

	void taskmanager::flush()
	{
		while (m_incompletetasknum) SwitchToThread();
		m_taskbuf.clear();
	}

	void taskmanager::exit()
	{
		if (m_threadbuf.size())
		{
			SetEvent(m_exitevent);

			for (unsigned n=0; n<m_threadbuf.size(); ++n)
				m_threadbuf[n].join();
		}
		CloseHandle(m_exitevent);
		CloseHandle(m_workevent);
	}

	void taskmanager::run()
	{
		for(;;)
		{
			int exit=wait_for_task_or_exit();

			if (exit)
				return;

			task_t* t=get_task();

			t->run();
			post_process(t);
		}
	}

	int taskmanager::wait_for_task_or_exit()
	{
		const HANDLE waitFor[]={m_workevent,m_exitevent};
		return WaitForMultipleObjects(2,waitFor,FALSE,INFINITE) - WAIT_OBJECT_0;
	}

	task_t* taskmanager::get_task()
	{
		return m_taskbuf.pop();
	}

	void taskmanager::post_process(task_t* i_task)
	{
		InterlockedDecrement((long*)&m_incompletetasknum);
		int refval=InterlockedDecrement((long*)(m_ref_buf+i_task->m_ref_index));

		if (!refval)
			SetEvent(m_ref_event[i_task->m_ref_index]);

		m_allocator.deallocate(i_task);
	}


#ifdef _DEBUG
	static long g_check=0;
#endif

#if 1
	void taskmanager::spawn_task(task_t* i_task)
	{

		assertion(!m_incompletetasknum);
		unsigned ref_index=m_ref_index.pop();

#ifdef _DEBUG
		int lcheck=InterlockedIncrement(&g_check);
		assertion(lcheck==1);
#endif
		assertion(!m_ref_buf[ref_index]);
		m_ref_buf[ref_index]=1;

		i_task->m_ref_index=ref_index;
		m_taskbuf.push(i_task);
		InterlockedIncrement((long*)&m_incompletetasknum);
#ifdef _DEBUG
		InterlockedDecrement(&g_check);
#endif

		ReleaseSemaphore(m_workevent,1,NULL);


		for(;;)
		{
			const HANDLE waitFor[]={m_ref_event[ref_index],m_workevent};
			unsigned ret=WaitForMultipleObjects(2,waitFor,FALSE,INFINITE) - WAIT_OBJECT_0;

			if (!ret)
			{
				ResetEvent(m_ref_event[ref_index]);
				m_ref_index.push(ref_index);
				assertion(!m_incompletetasknum);
				return;
			}

			task_t* t=get_task();

			t->run();
			post_process(t);
		}
	}
#endif
	void taskmanager::spawn_tasks(task_t* i_tasks[], unsigned i_tasknum)
	{
//		m_taskmutex.lock();
		assertion(!m_incompletetasknum);
		unsigned ref_index=m_ref_index.pop();
		assertion(!m_ref_buf[ref_index]);

		m_ref_buf[ref_index]=i_tasknum;
		InterlockedExchangeAdd((long*)&m_incompletetasknum,i_tasknum);
//		m_incompletetasknum+=i_tasknum;

		for (unsigned n=0; n<i_tasknum; ++n)
		{
			i_tasks[n]->m_ref_index=ref_index;
			m_taskbuf.push(i_tasks[n]);
		}
		ReleaseSemaphore(m_workevent,i_tasknum,NULL);
//		m_taskmutex.unlock();

		for(;;)
		{
			const HANDLE waitFor[]={m_ref_event[ref_index],m_workevent};
			unsigned ret=WaitForMultipleObjects(2,waitFor,FALSE,INFINITE) - WAIT_OBJECT_0;

			if (!ret)
			{
				ResetEvent(m_ref_event[ref_index]);
				m_ref_index.push(ref_index);
				assertion(!m_incompletetasknum);
				return;
			}

			task_t* t=get_task();

			t->run();
			post_process(t);
		}

	}
