#pragma once
#include "Rect.h"
#include "Point.h"
#include <string>
#include <utility>

namespace Wex
{
	class Window
	{
	public:
		Window() = default;
		Window(HWND handle);
		Window(const Window& rhs) = default;
		~Window() = default;

		Window& operator=(const Window& rhs) = default;

		operator HWND() const;
		void SetHandle(HWND value);
		HWND GetHandle() const;
		bool IsValid() const;

		int MsgBox(
			const std::string& message,
			const std::string& title = "",
			unsigned int flags = MB_OK) const;

		//Create/Destroy
		static HWND Create(
			const char* cls,
			HWND parent = 0,
			const std::string& name = "",
			unsigned long style = 0,
			unsigned long exstyle = 0,
			const Rect& rc = Rect::UseDefault,
			HMENU menu = 0,
			void* param = 0);
		void Destroy();

		//Send Message Variations
		template <typename TW, typename TL>
		LRESULT Send(UINT msg, TW wparam, TL lparam) const
		{
			AssertIsValid();
			return ::SendMessage(handle, msg, (WPARAM)wparam, (LPARAM)lparam);
		}
		template <typename TW>
		LRESULT Send(UINT msg, TW wparam) const
		{
			return Send<TW,LPARAM>(msg, wparam, 0);
		}
		LRESULT Send(UINT msg) const;

		//Post Message Variations
		template <typename TW, typename TL>
		bool Post(UINT msg, TW wparam, TL lparam) const
		{
			AssertIsValid();
			return ::PostMessage(handle, msg, (WPARAM)wparam, (LPARAM)lparam) != 0;
		}
		template <typename TW>
		bool Post(UINT msg, TW wparam) const
		{
			return Post<TW,LPARAM>(msg, wparam, 0);
		}
		bool Post(UINT msg) const;

		//Generic Properties
		LONG_PTR GetLong(int index) const;
		LONG_PTR SetLong(int index, LONG_PTR value) const;

		//Window Properties
		WNDPROC GetProc() const;
		WNDPROC SetProc(WNDPROC proc) const;
		LONG_PTR GetData() const;
		LONG_PTR SetData(LONG_PTR data) const;
		unsigned long GetStyle() const;
		unsigned long SetStyle(unsigned long style) const;
		unsigned long GetExStyle() const;
		unsigned long SetExStyle(unsigned long exstyle) const;
		int GetId() const;
		int SetId(int id) const;

		//Dialog Properties
		DLGPROC GetDlgProc() const;
		DLGPROC SetDlgProc(DLGPROC proc) const;
		LRESULT GetResult() const;
		LRESULT SetResult(LRESULT result) const;
		unsigned long GetUser() const;
		unsigned long SetUser(unsigned long user) const;

		//Style Change
		unsigned long ModifyStyle(unsigned long add, unsigned long remove = 0) const;
		unsigned long ModifyExStyle(unsigned long add, unsigned long remove = 0) const;

		//Text Operations
		void SetText(const std::string& text) const;
		std::string GetText() const;
		int GetTextLength() const;

		//Misc. Window Functions
		Window GetDlgItem(int id) const;
		void SetFont(HFONT font, bool redraw = true) const;
		HFONT GetFont() const;
		HMENU GetMenu() const;
		bool SetMenu(HMENU menu) const;
		bool DrawMenuBar() const;
		HMENU GetSystemMenu(bool revert) const;
		bool HiliteMenuItem(HMENU menu, UINT item, UINT hilite) const;
		bool IsMinimized() const;
		bool IsMaximized() const;
		bool Move(int x, int y, int w, int h, bool repaint = true) const;
		bool Move(const Rect& rc, bool repaint = true) const;
		bool SetPos(HWND hwnd, int x, int y, int cx, int cy, UINT flags) const;
		bool SetPos(HWND hwnd, const Rect& rc, UINT flags) const;
		UINT Arrange() const;
		bool BringToTop() const;
		Rect GetRect() const;
		Rect GetClient() const;
		WINDOWPLACEMENT GetPlacement() const;
		bool SetPlacement(const WINDOWPLACEMENT& wp) const;
		Point ToScreen(const Point& pt) const;
		Rect ToScreen(const Rect& rc) const;
		Point ToClient(const Point& pt) const;
		Rect ToClient(const Rect& rc) const;
		void Print(HDC hdc, unsigned long flags) const;
		void PrintClient(HDC hdc, unsigned long flags) const;
		bool UpdateWindow() const;
		void SetRedraw(bool redraw = true) const;
		Rect GetUpdateRect(bool erase = false) const;
		bool HasUpdateRect() const;
		int GetUpdateRgn(HRGN rgn, bool erase = false) const;
		bool Invalidate(bool erase = true) const;
		bool Invalidate(const Rect& rc, bool erase = true) const;
		bool Validate() const;
		bool Validate(const Rect& rc) const;
		void Invalidate(HRGN rgn, bool erase = true) const;
		bool Validate(HRGN rgn) const;
		bool Show(int show = SW_SHOWDEFAULT) const;
		bool IsVisible() const;
		bool ShowOwnedPopups(bool show = true) const;
		bool LockUpdate(bool lock = true) const;
		bool Redraw(
			const RECT* rc = 0,
			HRGN rgn = 0,
			unsigned long flags = RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE) const;
		int SetTimer(int id, unsigned long period, TIMERPROC proc = 0) const;
		bool KillTimer(int id) const;
		bool IsEnabled() const;
		bool Enable(bool enable = true) const;
		HWND SetActive() const;
		HWND SetCapture() const;
		bool ReleaseCapture() const;
		HWND SetFocus() const;
		bool SetCheck(int id, int check = BST_CHECKED) const;
		bool SetOption(int first, int last, int check) const;
		Window GetNextDlgGroupItem(HWND hwnd, bool previous = false) const;
		Window GetNextDlgTabItem(HWND hwnd, bool previous = false) const;
		bool IsChecked(int id, unsigned int state = BST_CHECKED) const;
		int GetScrollPos(int bar) const;
		std::pair<int,int> GetScrollRange(int bar) const;
		bool Scroll(int x, int y, const RECT* rc = 0, const RECT* clip = 0) const;
		int ScrollEx(
			int x,
			int y,
			unsigned long flags,
			const RECT* rc = 0,
			const RECT* clip = 0,
			HRGN rgn = 0,
			RECT* update = 0) const;
		int SetScrollPos(int bar, int pos, bool redraw = true) const;
		bool SetScrollRange(int bar, int minpos, int maxpos, bool redraw = true) const;
		bool ShowScrollBar(int bar, bool show = true) const;
		bool EnableScrollBar(int which, int flags = ESB_ENABLE_BOTH) const;
		Window ChildFromPoint(const POINT& pt) const;
		Window ChildFromPointEx(const POINT& pt, unsigned long flags) const;
		Window GetTop() const;
		Window GetWindow(int which) const;
		Window GetLastActivePopup() const;
		bool IsChild(HWND hwnd) const;
		Window GetParent() const;
		Window SetParent(HWND hwnd) const;
		bool Flash(bool invert) const;
		bool OpenClipboard() const;
		bool CreateCaret(HBITMAP bitmap) const;
		bool CreateSolidCaret(int w, int h) const;
		bool CreateGrayCaret(int w, int h) const;
		bool HideCaret() const;
		bool ShowCaret() const;
		void DragAcceptFiles(bool accept = true) const;
		HICON SetIcon(HICON icon, bool big = true) const;
		HICON GetIcon(bool big = true) const;
		bool WinHelp(const char* help, int cmd = HELP_CONTEXT, unsigned long data = 0) const;
		bool SetContextHelpId(unsigned long context) const;
		unsigned long GetContextHelpId() const;
		int SetHotKey(short vkey, short modifiers) const;
		unsigned long GetHotKey() const;
		SCROLLINFO GetScrollInfo(int bar, unsigned long mask = SIF_ALL) const;
		int SetScrollInfo(int bar, const SCROLLINFO& info, bool redraw = true) const;
		bool IsDlgMsg(MSG* msg) const;
		void NextDlgCtrl() const;
		void PrevDlgCtrl() const;
		void GotoDlgCtrl(HWND hwnd) const;
		void ResizeClient(int w = -1, int h = -1, bool redraw = true) const;
		int GetRgn(HRGN rgn) const;
		int SetRgn(HRGN rgn, bool redraw = false) const;
		unsigned long GetThreadId() const;
		unsigned long GetProcessId() const;
		bool ShowAsync(int show = SW_SHOWDEFAULT) const;
		void Center(HWND hwnd = 0) const;
		void Hide() const;
		Rect MapRect(HWND hwndTo, const RECT& rc) const;
		Rect MapRectToParent(const RECT& rc) const;

		bool operator==(HWND value) const;
		bool operator!=(HWND value) const;
		bool operator<=(HWND value) const;
		bool operator>=(HWND value) const;
		bool operator<(HWND value) const;
		bool operator>(HWND value) const;

	private:
		void AssertIsValid() const;
		void AssertIsValidOrNull() const;

	private:
		friend class WindowTest;
		HWND handle = nullptr;
	};
}

