#pragma once
#include "framework/Object.h"
#include "framework/Core.h"
#include <functional>

namespace ly {

	struct TimerHandle {
	public:
		TimerHandle();
		unsigned int GetTimerKey() const { return mTimerKey; }
	private:
		unsigned int mTimerKey;
		static unsigned int timerKeyCounter;
		static unsigned int GetNextTimerKey() { return ++timerKeyCounter; };
	};

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs);

	struct TimerHandleHashFunction {
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const {
			return timerHandle.GetTimerKey();
		}
	};

	struct Timer {
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);
		void TickTime(float deltaTime);
		bool Expired() const;
		void SetExpired();
	private:
		std::pair<weak<Object>, std::function<void()>> mListener;
		float mDuration;
		bool mRepeat;
		float mTimeCounter;
		bool mIsExpired;

	};

	class TimerManager {
	public:
		static TimerManager& Get();
		template<typename ClassName>
		TimerHandle SetTimer(weak<Object> weakRef, void(ClassName::* callback)(), float duration, bool repeat = false) {
			TimerHandle newHandle{};
			mTimers.insert({ newHandle, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat) });
			return newHandle;

		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerHandle);

	protected:
		TimerManager();
	private:
		static unique<TimerManager> timerManager;
		Dictionary<TimerHandle, Timer, TimerHandleHashFunction> mTimers;

	};
}