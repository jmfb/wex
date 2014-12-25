#pragma once
#include "Point.h"
#include "Size.h"
#include <string>
#include <stack>
#include <map>
#include <functional>

namespace Wex
{
	class MessageMap
	{
	public:
		MessageMap() = default;
		MessageMap(const MessageMap& rhs) = delete;
		~MessageMap() = default;

		MessageMap& operator=(const MessageMap& rhs) = delete;

		bool Process(
			HWND hwnd,
			UINT msg,
			WPARAM wparam,
			LPARAM lparam,
			LRESULT& result);

		virtual void OnActivate(short state, bool minimized, HWND hwnd);
		virtual void OnActivateApp(bool activated, unsigned long threadid);
		virtual void OnCancelMode();
		virtual void OnCaptureChanged(HWND hwnd);
		virtual void OnChar(int c, int count, unsigned long flags);
		virtual int OnCharToItem(int c, int index, HWND hwnd);
		virtual void OnChildActivate();
		virtual void OnClose();
		virtual void OnCommand(WORD id, WORD code, HWND from);
		virtual int OnCompareItem(int id, COMPAREITEMSTRUCT* cis);
		virtual void OnContextMenu(HWND hwnd, const Point& pt);
		virtual void OnCopy();
		virtual bool OnCopyData(HWND hwnd, COPYDATASTRUCT* cds);
		virtual bool OnCreate(CREATESTRUCT* cs);
		virtual HBRUSH OnCtlColorBtn(HDC hdc, HWND hwnd);
		virtual HBRUSH OnCtlColorEdit(HDC hdc, HWND hwnd);
		virtual HBRUSH OnCtlColorDlg(HDC hdc, HWND hwnd);
		virtual HBRUSH OnCtlColorListBox(HDC hdc, HWND hwnd);
		virtual HBRUSH OnCtlColorScrollBar(HDC hdc, HWND hwnd);
		virtual HBRUSH OnCtlColorStatic(HDC hdc, HWND hwnd);
		virtual void OnCut();
		virtual void OnDeleteItem(int id, DELETEITEMSTRUCT* dis);
		virtual void OnDestroy();
		virtual void OnDevModeChange(const std::string& devname);
		virtual void OnDisplayChange(int bpp, const Size& size);
		virtual void OnDrawItem(int id, DRAWITEMSTRUCT* dis);
		virtual void OnDropFiles(HDROP drop);
		virtual void OnEnable(bool enabled);
		virtual void OnEndSession(bool ending, bool shutdown);
		virtual void OnEnterIdle(int why, HWND hwnd);
		virtual void OnEnterMenuLoop(bool viatrack);
		virtual void OnEnterSizeMove();
		virtual bool OnEraseBkgnd(HDC hdc);
		virtual void OnExitMenuLoop(bool shortcut);
		virtual void OnExitSizeMove();
		virtual int OnGetDlgCode(MSG* msg);
		virtual void OnGetMinMaxInfo(MINMAXINFO* mmi);
		virtual void OnHelp(HELPINFO* hi);
		virtual void OnHScroll(int code, int pos, HWND hwnd);
		virtual void OnIconEraseBkgnd(HDC hdc);
		virtual bool OnInitDialog(HWND hwnd, LPARAM lparam);
		virtual void OnInitMenu(HMENU menu);
		virtual void OnInitMenuPopup(HMENU menu, int index, bool system);
		virtual void OnKeyDown(int c, int count, unsigned long flags);
		virtual void OnKeyUp(int c, int count, unsigned long flags);
		virtual void OnKillFocus(HWND hwnd);
		virtual void OnLButtonDblClk(const Point& pt, unsigned long flags);
		virtual void OnLButtonDown(const Point& pt, unsigned long flags);
		virtual void OnLButtonUp(const Point& pt, unsigned long flags);
		virtual void OnMButtonDblClk(const Point& pt, unsigned long flags);
		virtual void OnMButtonDown(const Point& pt, unsigned long flags);
		virtual void OnMButtonUp(const Point& pt, unsigned long flags);
		virtual void OnMDIActivate(HWND activated, HWND deactivated);
		virtual void OnMeasureItem(int id, MEASUREITEMSTRUCT* mis);
		virtual int OnMenuChar(int c, int type, HMENU menu);
		virtual void OnMenuSelect(int id, int flags, HMENU menu);
		virtual int OnMouseActivate(HWND hwnd, int hittest, UINT msg);
		virtual void OnMouseLeave();
		virtual void OnMouseMove(const Point& pt, unsigned long flags);
		virtual bool OnMouseWheel(const Point& pt, short delta, unsigned long flags);
		virtual void OnMove(const Point& pt);
		virtual bool OnMoving(RECT* rect);
		virtual LRESULT OnNotify(NMHDR* hdr);
		virtual void OnPaint();
		virtual HCURSOR OnQueryDragIcon();
		virtual bool OnQueryEndSession();
		virtual void OnRButtonDblClk(const Point& pt, unsigned long flags);
		virtual void OnRButtonDown(const Point& pt, unsigned long flags);
		virtual void OnRButtonUp(const Point& pt, unsigned long flags);
		virtual bool OnSetCursor(HWND hwnd, int hittest, UINT msg);
		virtual void OnSetFocus(HWND hwnd);
		virtual void OnShowWindow(bool show, int status);
		virtual void OnSize(int type, const Size& size);
		virtual bool OnSizing(int side, RECT* rect);
		virtual void OnStyleChanged(int type, STYLESTRUCT* ss);
		virtual void OnStyleChanging(int type, STYLESTRUCT* ss);
		virtual void OnSysChar(int c, int count, unsigned long flags);
		virtual void OnSysColorChange();
		virtual void OnSysCommand(int id, const Point& pt);
		virtual void OnSysKeyDown(int c, int count, unsigned long flags);
		virtual void OnSysKeyUp(int c, int count, unsigned long flags);
		virtual void OnTimeChange();
		virtual void OnTimer(int id);
		virtual int OnVKeyToItem(int c, int index, HWND hwnd);
		virtual void OnVScroll(int code, int pos, HWND hwnd);
		virtual void OnWindowPosChanged(WINDOWPOS* wp);
		virtual void OnWindowPosChanging(WINDOWPOS* wp);

	protected:
		void InstallDefault(WNDPROC proc);
		WNDPROC RemoveDefault();
		bool IsInNestedCall() const;
		void NotHandled();

		LRESULT DoDefault();
		LRESULT DoDefault(
			HWND hwnd,
			UINT msg,
			WPARAM wparam,
			LPARAM lparam);

		template <typename MemberFunction>
		void HandleCommand(WORD id, WORD code, MemberFunction memberFunction)
		{
			commandHandlers[{ id, code }] = CreateCommandHandler(memberFunction);
		}
		template <typename MemberFunction>
		void HandleCommand(WORD id, MemberFunction memberFunction)
		{
			commandHandlers[{ id, 0 }] = CreateCommandHandler(memberFunction);
			commandHandlers[{ id, 1 }] = CreateCommandHandler(memberFunction);
		}
		template <typename MemberFunction>
		void HandleNotify(UINT id, UINT code, MemberFunction memberFunction)
		{
			notifyHandlers[{ id, code }] = CreateNotifyHandler(memberFunction);
		}

	private:
		using CommandHandler = std::function<void(WORD,WORD,HWND)>;

		template <typename Class>
		CommandHandler CreateCommandHandler(void (Class::*memberFunction)())
		{
			return [=](WORD id, WORD code, HWND from)
			{
				(dynamic_cast<Class*>(this)->*memberFunction)();
			};
		}

		template <typename Class>
		CommandHandler CreateCommandHandler(void (Class::*memberFunction)(WORD,WORD,HWND))
		{
			return [=](WORD id, WORD code, HWND from)
			{
				(dynamic_cast<Class*>(this)->*memberFunction)(id, code, from);
			};
		}

		using NotifyHandler = std::function<LRESULT(NMHDR*)>;

		template <typename Class>
		NotifyHandler CreateNotifyHandler(void (Class::*memberFunction)())
		{
			return [=](NMHDR* hdr) -> LRESULT
			{
				(dynamic_cast<Class*>(this)->*memberFunction)();
				return 0;
			};
		}

		template <typename Class>
		NotifyHandler CreateNotifyHandler(LRESULT (Class::*memberFunction)())
		{
			return [=](NMHDR* hdr)
			{
				return (dynamic_cast<Class*>(this)->*memberFunction)();
			};
		}

		template <typename Class>
		NotifyHandler CreateNotifyHandler(void (Class::*memberFunction)(NMHDR*))
		{
			return [=](NMHDR* hdr)
			{
				(dynamic_cast<Class*>(this)->*memberFunction)(hdr);
				return 0;
			};
		}

		template <typename Class>
		NotifyHandler CreateNotifyHandler(LRESULT (Class::*memberFunction)(NMHDR*))
		{
			return [=](NMHDR* hdr)
			{
				return (dynamic_cast<Class*>(this)->*memberFunction)(hdr);
			};
		}

	private:
		friend class MessageMapTest;
		std::stack<bool> handledStack;
		std::stack<MSG> messageStack;
		WNDPROC defaultProcedure = nullptr;
		std::map<std::pair<WORD,WORD>, CommandHandler> commandHandlers;
		std::map<std::pair<UINT,UINT>, NotifyHandler> notifyHandlers;
	};
}

