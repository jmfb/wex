#pragma once
#include "Window.h"
#include "MessageMap.h"
#include "Exception.h"
#include "Rect.h"
#include "ProcessInstance.h"
#include "WindowsException.h"
#include <string>

namespace Wex
{
	template <typename Class>
	class CustomWindow : public Window, public MessageMap
	{
	public:
		CustomWindow() = default;
		CustomWindow(const CustomWindow& rhs) = delete;
		~CustomWindow() = default;

		CustomWindow& operator=(const CustomWindow& rhs) = delete;

		static ATOM GetAtom()
		{
			static auto created = false;
			if (created)
				return atom;
			created = true;
			windowClass.cbSize = sizeof(windowClass);
			windowClass.cbClsExtra = 0;
			windowClass.cbWndExtra = 0;
			windowClass.hbrBackground = nullptr;
			windowClass.hCursor = nullptr;
			windowClass.hIcon = nullptr;
			windowClass.hIconSm = nullptr;
			windowClass.hInstance = nullptr;
			windowClass.lpfnWndProc = nullptr;
			windowClass.lpszClassName = nullptr;
			windowClass.lpszMenuName = nullptr;
			windowClass.style = 0;
			Class::SetupClass(windowClass);
			windowClass.hInstance = ProcessInstance::Get();
			windowClass.lpfnWndProc = &CustomWindow<Class>::StartWindowProc;
			atom = ::RegisterClassEx(&windowClass);
			CheckLastWindowsError(atom == 0, "RegisterClassEx");
			return atom;
		}

		void Create(
			HWND parent = nullptr,
			const std::string& caption = "",
			unsigned long style = 0,
			unsigned long exstyle = 0,
			const Rect& rc = Rect::UseDefault,
			HMENU menu = nullptr,
			void* param = nullptr)
		{
			CheckError(windowBeingCreated != nullptr, 0, "Should be initially null.");
			windowBeingCreated = this;
			auto window = Window::Create(
				MAKEINTRESOURCE(GetAtom()),
				parent,
				caption,
				style,
				exstyle,
				rc,
				menu,
				param);
			CheckLastWindowsError(window == nullptr, "CreateWindowEx");
			CheckError(window != GetHandle(), 0, "Handle was not set.");
			CheckError(windowBeingCreated != nullptr, 0, "Should be set back to null.");
		}
	
		virtual void OnFinalMessage()
		{
		}
		void MarkForDestroy()
		{
			destroy = true;
		}
		void CheckForDestroy()
		{
			if (destroy && !IsInNestedCall())
				OnFinalMessage();
		}

	private:
		static LRESULT __stdcall StartWindowProc(
			HWND hwnd,
			UINT msg,
			WPARAM wparam,
			LPARAM lparam)
		{
			CheckError(windowBeingCreated == nullptr, 0, "Should be set.");
			windowBeingCreated->SetHandle(hwnd);
			windowBeingCreated->InstallDefault(&::DefWindowProc);
			windowBeingCreated->SetData(reinterpret_cast<LONG_PTR>(windowBeingCreated));
			windowBeingCreated->SetProc(&CustomWindow<Class>::WindowProc);
			windowBeingCreated = nullptr;
			return WindowProc(hwnd, msg, wparam, lparam);
		}
		
		static LRESULT __stdcall WindowProc(
			HWND hwnd,
			UINT msg,
			WPARAM wparam,
			LPARAM lparam)
		{
			auto windowData = Window{ hwnd }.GetData();
			auto instance = reinterpret_cast<CustomWindow<Class>*>(windowData);
			CheckError(instance == nullptr, 0, "Window data was null.");
			LRESULT result = 0;
			if (!instance->Process(hwnd, msg, wparam, lparam, result))
				result = instance->DoDefault(hwnd, msg, wparam, lparam);
			if (msg == WM_NCDESTROY)
				instance->MarkForDestroy();
			instance->CheckForDestroy();
			return result;
		}

	private:
		friend class CustomWindowTest;
		static WNDCLASSEX windowClass;
		static ATOM atom;
		static CustomWindow<Class>* windowBeingCreated;
		bool destroy = false;
	};

	template <typename Class>
	WNDCLASSEX CustomWindow<Class>::windowClass;

	template <typename Class>
	ATOM CustomWindow<Class>::atom = 0;

	template <typename Class>
	CustomWindow<Class>* CustomWindow<Class>::windowBeingCreated = nullptr;
}

