#pragma once

#include "txbase/fwddecl.h"
#include <sstream>
#include <mutex>
#include <atomic>

namespace TX {
	std::string ReadAllLines(const std::string& file);

	class Timer
	{
	public:
		Timer() : beg_(clock_::now()) {}
		inline void reset() { beg_ = clock_::now(); }
		inline double elapsed() const {
			return std::chrono::duration_cast<second_>
				(clock_::now() - beg_).count();
		}

	private:
		typedef std::chrono::high_resolution_clock clock_;
		typedef std::chrono::duration<double, std::ratio<1> > second_;
		std::chrono::time_point<clock_> beg_;
	};

	class IProgressMonitor{
	public:
		virtual ~IProgressMonitor(){}
		virtual void Reset(float total) = 0;
		virtual void Update(float current) = 0;
		virtual void UpdateInc() = 0;
		virtual void Finish() = 0;
		virtual double ElapsedTime() = 0;
		virtual double RemainingTime() = 0;
		virtual float Progress() = 0;
		virtual bool InProgress() = 0;
	};

	class ProgressMonitor : public IProgressMonitor {
	public:
		ProgressMonitor(){}
		/// <summary>
		/// Reset the <paramref name="total"/> and start the timer.
		/// </summary>
		void Reset(float total);
		void Finish();
		void Update(float current);
		void UpdateInc();
		double ElapsedTime();
		double RemainingTime();
		inline float Progress() { return current_ / total_; }
		inline bool InProgress(){ return in_progress_; }
	private:
		float EstimatedProgress();
	private:
		float total_, current_, rate_per_sec_;
		bool in_progress_;
		std::atomic<double> time_since_last_update_;
		Timer timer_;
		std::mutex mutex_;
	};

	template<typename T>
	void Str_(std::ostringstream& ss, const T& obj){ ss << obj; }

	template<typename T, typename... Args>
	void Str_(std::ostringstream& ss, const T& obj, Args&&... args){
		Str_(ss, obj);
		Str_(ss, std::forward<Args>(args)...);
	}

	template<typename... Args>
	std::string Str(Args&&... args){
		std::ostringstream ss;
		Str_(ss, std::forward<Args>(args)...);
		return ss.str();
	}

	template<typename... Args>
	std::wstring WStr(Args&&... args) {
		auto str = Str(std::forward<Args>(args)...);
		return std::wstring(str.begin(), str.end());
	}
}
