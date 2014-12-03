#pragma once

namespace Wex
{
	class ProcessInstance
	{
	private:
		ProcessInstance() = default;
		ProcessInstance(const ProcessInstance& rhs) = delete;
		~ProcessInstance() = default;

		ProcessInstance& operator=(const ProcessInstance& rhs) = delete;

	public:
		static void Initialize(HINSTANCE instance);
		static HINSTANCE Get();

	private:
		static ProcessInstance& GetSingleton();
		static void InitializeAllCommonControls();

	private:
		friend class ProcessInstanceTest;
		HINSTANCE handle = nullptr;
	};
}

