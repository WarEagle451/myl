#pragma once
#include <myl/defines.hpp>
#ifdef MYL_EXPERIMENTAL

#include <atomic>
#include <functional>
#include <future>
#include <deque>
#include <mutex>
#include <thread>
#include <type_traits>
#include <vector>

namespace myl {
	class thread_pool {
		std::vector<std::thread> m_threads;
		std::deque<std::function<void()>> m_jobs;
		std::mutex m_job_mutex;
		std::condition_variable m_job_done;
		std::condition_variable m_job_available;
		std::atomic<usize> m_job_count;
		std::atomic_bool m_running = true;
		std::atomic_bool m_waiting = false;
	public:
		thread_pool(const usize a_count = std::thread::hardware_concurrency()) {
			usize count = a_count == 0 ?
				(std::thread::hardware_concurrency() == 0 ? 1 : std::thread::hardware_concurrency()) :
				a_count;

			m_threads.reserve(count);
			for (usize i = 0; i != count; ++i)
				m_threads.push_back(std::thread(&loop, this));
		}

		~thread_pool() {
			// Finsh all jobs
			wait();

			// Notify all threads to exit and destroy
			m_running = false;
			m_job_available.notify_all();

			for (auto& t : m_threads)
				t.join();
		}

		thread_pool(const thread_pool&) = delete;
		auto operator=(const thread_pool&) -> thread_pool& = delete;

		MYL_NO_DISCARD auto jobs() const -> usize { return m_job_count; }
		MYL_NO_DISCARD auto jobs_waiting() const -> usize { std::scoped_lock l(m_job_mutex); return m_jobs.size(); }
		MYL_NO_DISCARD auto jobs_running() const -> usize { std::scoped_lock l(m_job_mutex); return m_job_count - m_jobs.size(); }
		MYL_NO_DISCARD auto threads() const -> usize { return m_threads.size(); }

		///template<typename Func, typename... Args>
		///auto push(Func a_func, Args&&... a_args) -> std::future<void()> { /// MYTodo: Must be a way to have std::future<decltype(a_func(a_args...)) to have return a future for functions
		///	auto lambda = [a_func, a_args...]() -> void { a_func(std::forward<decltype(a_args)>(a_args)...); };
		///
		///}

		template<typename Func, typename... Args>
		MYL_NO_DISCARD auto push(Func a_func, Args&&... a_args) -> std::future<decltype(a_func(a_args...))()> {
			using return_type = decltype(a_func(a_args...));

			std::shared_ptr<std::promise<return_type>> promise = std::make_shared<std::promise<return_type>>();
			auto job = [promise, a_func, a_args...]() -> void {
				if constexpr (std::is_void_v<return_type>) {
					a_func(std::forward<Args>(a_args)...);
					promise->set_value();
				}
				else
					promise->set_value(a_func(std::forward<Args>(a_args)...));
			};

			++m_job_count;
			{
				std::scoped_lock l(m_job_mutex);
				m_jobs.push_back(job);
			}

			m_job_available.notify_one(); // Notify a thread that a job is queued
			return promise->get_future();
		}

		//@brief Waits for all jobs to be completed
		void wait() {
			m_waiting = true;
			std::unique_lock<std::mutex> l(m_job_mutex);
			m_job_done.wait(l, [this] { return m_job_count - m_jobs.size() == 0; }); // No jobs are running
			m_waiting = false;
		}
	private:
		void loop() {
			while (m_running) {
				/// MYTodo: If a deadlock occurs, it will be here, test with 2000 threads
				std::unique_lock<std::mutex> l(m_job_mutex);
				m_job_available.wait(l, [this] { return !m_jobs.empty() || !m_running; });
				if (!m_running && m_jobs.empty()) // Will exit if the thread pool is destroyed and no jobs are left
					return;

				auto job = std::move(m_jobs.front());
				m_jobs.pop_front();
				l.unlock();

				job();
				--m_job_count;

				l.lock();
				if (m_waiting)
					m_job_done.notify_one();
			}
		}
	};
}
#endif