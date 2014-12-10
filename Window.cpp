#include "WindowsInclude.h"
#include "Window.h"
#include "ProcessInstance.h"
#include "WindowsException.h"
#include <memory>

namespace Wex
{
	Window::Window(HWND handle)
		: handle(handle)
	{
	}

	Window::operator HWND() const
	{
		return handle;
	}

	void Window::SetHandle(HWND value)
	{
		handle = value;
	}

	HWND Window::GetHandle() const
	{
		return handle;
	}

	bool Window::IsValid() const
	{
		return ::IsWindow(handle) != 0;
	}

	int Window::MsgBox(
		const std::string& message,
		const std::string& title,
		unsigned int flags) const
	{
		AssertIsValidOrNull();
		return ::MessageBox(handle, message.c_str(), title.c_str(), flags);
	}

	HWND Window::Create(
		const char* cls,
		HWND parent,
		const std::string& name,
		unsigned long style,
		unsigned long exstyle,
		const Rect& rc,
		HMENU menu,
		void* param)
	{
		return ::CreateWindowEx(
			exstyle,
			cls,
			name.c_str(),
			style,
			rc.left,
			rc.top,
			rc.GetWidth(),
			rc.GetHeight(),
			parent,
			menu,
			ProcessInstance::Get(),
			param);
	}

	LRESULT Window::Send(UINT msg) const
	{
		return Send<WPARAM>(msg, 0);
	}

	bool Window::Post(UINT msg) const
	{
		return Post<WPARAM>(msg, 0);
	}

	LONG_PTR Window::GetLong(int index) const
	{
		AssertIsValid();
		return ::GetWindowLongPtr(handle, index);
	}
	LONG_PTR Window::SetLong(int index, LONG_PTR value) const
	{
		AssertIsValid();
		return ::SetWindowLongPtr(handle, index, value);
	}

	WNDPROC Window::GetProc() const
	{
		return reinterpret_cast<WNDPROC>(GetLong(GWLP_WNDPROC));
	}
	WNDPROC Window::SetProc(WNDPROC proc) const
	{
		return reinterpret_cast<WNDPROC>(SetLong(GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(proc)));
	}
	LONG_PTR Window::GetData() const
	{
		return GetLong(GWLP_USERDATA);
	}
	LONG_PTR Window::SetData(LONG_PTR data) const
	{
		return SetLong(GWLP_USERDATA, data);
	}
	unsigned long Window::GetStyle() const
	{
		return GetLong(GWL_STYLE);
	}
	unsigned long Window::SetStyle(unsigned long style) const
	{
		return SetLong(GWL_STYLE, style);
	}
	unsigned long Window::GetExStyle() const
	{
		return GetLong(GWL_EXSTYLE);
	}
	unsigned long Window::SetExStyle(unsigned long exstyle) const
	{
		return SetLong(GWL_EXSTYLE, exstyle);
	}
	int Window::GetId() const
	{
		return GetLong(GWLP_ID);
	}
	int Window::SetId(int id) const
	{
		return SetLong(GWLP_ID, id);
	}

	DLGPROC Window::GetDlgProc() const
	{
		return reinterpret_cast<DLGPROC>(GetLong(DWLP_DLGPROC));
	}
	DLGPROC Window::SetDlgProc(DLGPROC proc) const
	{
		return reinterpret_cast<DLGPROC>(SetLong(DWLP_DLGPROC, reinterpret_cast<LONG_PTR>(proc)));
	}
	LRESULT Window::GetResult() const
	{
		return GetLong(DWLP_MSGRESULT);
	}
	LRESULT Window::SetResult(LRESULT result) const
	{
		return SetLong(DWLP_MSGRESULT, result);
	}
	unsigned long Window::GetUser() const
	{
		return GetLong(DWLP_USER);
	}
	unsigned long Window::SetUser(unsigned long user) const
	{
		return SetLong(DWLP_USER, user);
	}

	unsigned long Window::ModifyStyle(unsigned long add, unsigned long remove) const
	{
		return SetStyle((GetStyle() | add) & ~remove);
	}
	unsigned long Window::ModifyExStyle(unsigned long add, unsigned long remove) const
	{
		return SetExStyle((GetExStyle() | add) & ~remove);
	}

	void Window::SetText(const std::string& text) const
	{
		AssertIsValid();
		::SetWindowText(handle, text.c_str());
	}
	std::string Window::GetText() const
	{
		AssertIsValid();
		auto length = ::GetWindowTextLength(handle);
		if (length <= 0)
			return "";
		std::unique_ptr<char[]> buffer{ new char[length + 1] };
		::GetWindowText(handle, buffer.get(), length + 1);
		return buffer.get();
	}
	int Window::GetTextLength() const
	{
		AssertIsValid();
		return ::GetWindowTextLength(handle);
	}

	Window Window::GetDlgItem(int id) const
	{
		AssertIsValid();
		return { ::GetDlgItem(handle, id) };
	}

	void Window::Destroy()
	{
		AssertIsValid();
		::DestroyWindow(handle);
		handle = nullptr;
	}

	void Window::SetFont(HFONT font, bool redraw) const
	{
		AssertIsValid();
		Send(WM_SETFONT, font, MAKELPARAM(redraw ? TRUE : FALSE, 0));
	}

	HFONT Window::GetFont() const
	{
		AssertIsValid();
		return reinterpret_cast<HFONT>(Send(WM_GETFONT));
	}

	HMENU Window::GetMenu() const
	{
		AssertIsValid();
		return ::GetMenu(handle);
	}

	bool Window::SetMenu(HMENU menu) const
	{
		AssertIsValid();
		return ::SetMenu(handle, menu) != 0;
	}

	bool Window::DrawMenuBar() const
	{
		AssertIsValid();
		return ::DrawMenuBar(handle) != 0;
	}

	HMENU Window::GetSystemMenu(bool revert) const
	{
		AssertIsValid();
		return ::GetSystemMenu(handle, revert ? TRUE : FALSE);
	}

	bool Window::HiliteMenuItem(HMENU menu, UINT item, UINT hilite) const
	{
		AssertIsValid();
		return ::HiliteMenuItem(handle, menu, item, hilite) != 0;
	}

	bool Window::IsMinimized() const
	{
		AssertIsValid();
		return ::IsIconic(handle) != 0;
	}

	bool Window::IsMaximized() const
	{
		AssertIsValid();
		return ::IsZoomed(handle) != 0;
	}

	bool Window::Move(int x, int y, int w, int h, bool repaint) const
	{
		AssertIsValid();
		return ::MoveWindow(handle, x, y, w, h, repaint ? TRUE : FALSE) != 0;
	}

	bool Window::Move(const Rect& rc, bool repaint) const
	{
		AssertIsValid();
		return Move(rc.left, rc.top, rc.GetWidth(), rc.GetHeight(), repaint);
	}

	bool Window::SetPos(HWND hwnd, int x, int y, int cx, int cy, UINT flags) const
	{
		AssertIsValid();
		return ::SetWindowPos(handle, hwnd, x, y, cx, cy, flags) != 0;
	}

	bool Window::SetPos(HWND hwnd, const Rect& rc, UINT flags) const
	{
		AssertIsValid();
		return SetPos(hwnd, rc.left, rc.top, rc.GetWidth(), rc.GetHeight(), flags);
	}

	UINT Window::Arrange() const
	{
		AssertIsValid();
		return ::ArrangeIconicWindows(handle);
	}

	bool Window::BringToTop() const
	{
		AssertIsValid();
		return ::BringWindowToTop(handle) != 0;
	}

	Rect Window::GetRect() const
	{
		AssertIsValid();
		Rect rc;
		::GetWindowRect(handle, &rc);
		return rc;
	}

	Rect Window::GetClient() const
	{
		AssertIsValid();
		Rect rc;
		::GetClientRect(handle, &rc);
		return rc;
	}

	WINDOWPLACEMENT Window::GetPlacement() const
	{
		AssertIsValid();
		WINDOWPLACEMENT wp;
		wp.length = sizeof(wp);
		::GetWindowPlacement(handle, &wp);
		return wp;
	}

	bool Window::SetPlacement(const WINDOWPLACEMENT& wp) const
	{
		AssertIsValid();
		return ::SetWindowPlacement(handle, &wp) != 0;
	}

	Point Window::ToScreen(const Point& pt) const
	{
		AssertIsValid();
		Point retval = pt;
		::ClientToScreen(handle, &retval);
		return retval;
	}

	Rect Window::ToScreen(const Rect& rc) const
	{
		AssertIsValid();
		return { ToScreen(rc.GetTopLeft()), rc.GetSize() };
	}

	Point Window::ToClient(const Point& pt) const
	{
		AssertIsValid();
		Point retval = pt;
		::ScreenToClient(handle, &retval);
		return retval;
	}

	Rect Window::ToClient(const Rect& rc) const
	{
		AssertIsValid();
		return { ToClient(rc.GetTopLeft()), rc.GetSize() };
	}

	void Window::Print(HDC hdc, unsigned long flags) const
	{
		AssertIsValid();
		Send(WM_PRINT, hdc, flags);
	}

	void Window::PrintClient(HDC hdc, unsigned long flags) const
	{
		AssertIsValid();
		Send(WM_PRINTCLIENT, hdc, flags);
	}

	bool Window::UpdateWindow() const
	{
		AssertIsValid();
		return ::UpdateWindow(handle) != 0;
	}

	void Window::SetRedraw(bool redraw) const
	{
		AssertIsValid();
		Send(WM_SETREDRAW, redraw ? TRUE : FALSE);
	}

	Rect Window::GetUpdateRect(bool erase) const
	{
		AssertIsValid();
		Rect rc;
		::GetUpdateRect(handle, &rc, erase ? TRUE : FALSE);
		return rc;
	}

	bool Window::HasUpdateRect() const
	{
		AssertIsValid();
		return ::GetUpdateRect(handle, 0, FALSE) != 0;
	}

	int Window::GetUpdateRgn(HRGN rgn, bool erase) const
	{
		AssertIsValid();
		return ::GetUpdateRgn(handle, rgn, erase ? TRUE : FALSE);
	}

	bool Window::Invalidate(bool erase) const
	{
		AssertIsValid();
		return ::InvalidateRect(handle, 0, erase ? TRUE : FALSE) != 0;
	}

	bool Window::Invalidate(const Rect& rc, bool erase) const
	{
		AssertIsValid();
		return ::InvalidateRect(handle, &rc, erase ? TRUE : FALSE) != 0;
	}

	bool Window::Validate() const
	{
		AssertIsValid();
		return ::ValidateRect(handle, 0) != 0;
	}

	bool Window::Validate(const Rect& rc) const
	{
		AssertIsValid();
		return ::ValidateRect(handle, &rc) != 0;
	}

	void Window::Invalidate(HRGN rgn, bool erase) const
	{
		AssertIsValid();
		::InvalidateRgn(handle, rgn, erase ? TRUE : FALSE);
	}

	bool Window::Validate(HRGN rgn) const
	{
		AssertIsValid();
		return ::ValidateRgn(handle, rgn) != 0;
	}

	bool Window::Show(int show) const
	{
		AssertIsValid();
		return ::ShowWindow(handle, show) != 0;
	}

	bool Window::IsVisible() const
	{
		AssertIsValid();
		return ::IsWindowVisible(handle) != 0;
	}

	bool Window::ShowOwnedPopups(bool show) const
	{
		AssertIsValid();
		return ::ShowOwnedPopups(handle, show ? TRUE : FALSE) != 0;
	}

	bool Window::LockUpdate(bool lock) const
	{
		AssertIsValid();
		return ::LockWindowUpdate(lock ? handle : 0) != 0;
	}

	bool Window::Redraw(const RECT* rc, HRGN rgn, unsigned long flags) const
	{
		AssertIsValid();
		return ::RedrawWindow(handle, rc, rgn, flags) != 0;
	}

	int Window::SetTimer(int id, unsigned long period, TIMERPROC proc) const
	{
		AssertIsValid();
		return ::SetTimer(handle, id, period, proc);
	}

	bool Window::KillTimer(int id) const
	{
		AssertIsValid();
		return ::KillTimer(handle, id) != 0;
	}

	bool Window::IsEnabled() const
	{
		AssertIsValid();
		return ::IsWindowEnabled(handle) != 0;
	}

	bool Window::Enable(bool enable) const
	{
		AssertIsValid();
		return ::EnableWindow(handle, enable ? TRUE : FALSE) != 0;
	}

	HWND Window::SetActive() const
	{
		AssertIsValid();
		return ::SetActiveWindow(handle);
	}

	HWND Window::SetCapture() const
	{
		AssertIsValid();
		return ::SetCapture(handle);
	}

	bool Window::ReleaseCapture() const
	{
		return ::ReleaseCapture() != 0;
	}

	HWND Window::SetFocus() const
	{
		AssertIsValid();
		return ::SetFocus(handle);
	}

	bool Window::SetCheck(int id, int check) const
	{
		AssertIsValid();
		return ::CheckDlgButton(handle, id, check) != 0;
	}

	bool Window::SetOption(int first, int last, int check) const
	{
		AssertIsValid();
		return ::CheckRadioButton(handle, first, last, check) != 0;
	}

	Window Window::GetNextDlgGroupItem(HWND hwnd, bool previous) const
	{
		AssertIsValid();
		return ::GetNextDlgGroupItem(handle, hwnd, previous ? TRUE : FALSE);
	}

	Window Window::GetNextDlgTabItem(HWND hwnd, bool previous) const
	{
		AssertIsValid();
		return ::GetNextDlgTabItem(handle, hwnd, previous ? TRUE : FALSE);
	}

	bool Window::IsChecked(int id, unsigned int state) const
	{
		AssertIsValid();
		return ::IsDlgButtonChecked(handle, id) == state;
	}

	int Window::GetScrollPos(int bar) const
	{
		AssertIsValid();
		return ::GetScrollPos(handle, bar);
	}

	std::pair<int,int> Window::GetScrollRange(int bar) const
	{
		AssertIsValid();
		std::pair<int, int> range;
		::GetScrollRange(handle, bar, &range.first, &range.second);
		return range;
	}

	bool Window::Scroll(int x, int y, const RECT* rc, const RECT* clip) const
	{
		AssertIsValid();
		return ::ScrollWindow(handle, x, y, rc, clip) != 0;
	}

	int Window::ScrollEx(
		int x,
		int y,
		unsigned long flags,
		const RECT* rc,
		const RECT* clip,
		HRGN rgn,
		RECT* update) const
	{
		AssertIsValid();
		return ::ScrollWindowEx(handle, x, y, rc, clip, rgn, update, flags);
	}

	int Window::SetScrollPos(int bar, int pos, bool redraw) const
	{
		AssertIsValid();
		return ::SetScrollPos(handle, bar, pos, redraw ? TRUE : FALSE);
	}

	bool Window::SetScrollRange(int bar, int minpos, int maxpos, bool redraw) const
	{
		AssertIsValid();
		return ::SetScrollRange(handle, bar, minpos, maxpos, redraw ? TRUE : FALSE) != 0;
	}

	bool Window::ShowScrollBar(int bar, bool show) const
	{
		AssertIsValid();
		return ::ShowScrollBar(handle, bar, show ? TRUE : FALSE) != 0;
	}

	bool Window::EnableScrollBar(int which, int flags) const
	{
		AssertIsValid();
		return ::EnableScrollBar(handle, which, flags) != 0;
	}

	Window Window::ChildFromPoint(const POINT& pt) const
	{
		AssertIsValid();
		return ::ChildWindowFromPoint(handle, pt);
	}

	Window Window::ChildFromPointEx(const POINT& pt, unsigned long flags) const
	{
		AssertIsValid();
		return ::ChildWindowFromPointEx(handle, pt, flags);
	}

	Window Window::GetTop() const
	{
		AssertIsValid();
		return ::GetTopWindow(handle);
	}

	Window Window::GetWindow(int which) const
	{
		AssertIsValid();
		return ::GetWindow(handle, which);
	}

	Window Window::GetLastActivePopup() const
	{
		AssertIsValid();
		return ::GetLastActivePopup(handle);
	}

	bool Window::IsChild(HWND hwnd) const
	{
		AssertIsValid();
		return ::IsChild(handle, hwnd) != 0;
	}

	Window Window::GetParent() const
	{
		AssertIsValid();
		return ::GetParent(handle);
	}

	Window Window::SetParent(HWND hwnd) const
	{
		AssertIsValid();
		return ::SetParent(handle, hwnd);
	}

	bool Window::Flash(bool invert) const
	{
		AssertIsValid();
		return ::FlashWindow(handle, invert) != 0;
	}

	bool Window::OpenClipboard() const
	{
		AssertIsValid();
		return ::OpenClipboard(handle) != 0;
	}

	bool Window::CreateCaret(HBITMAP bitmap) const
	{
		AssertIsValid();
		return ::CreateCaret(handle, bitmap, 0, 0) != 0;
	}

	bool Window::CreateSolidCaret(int w, int h) const
	{
		AssertIsValid();
		return ::CreateCaret(handle, 0, w, h) != 0;
	}

	bool Window::CreateGrayCaret(int w, int h) const
	{
		AssertIsValid();
		return ::CreateCaret(handle, reinterpret_cast<HBITMAP>(1), w, h) != 0;
	}

	bool Window::HideCaret() const
	{
		AssertIsValid();
		return ::HideCaret(handle) != 0;
	}

	bool Window::ShowCaret() const
	{
		AssertIsValid();
		return ::ShowCaret(handle) != 0;
	}

	void Window::DragAcceptFiles(bool accept) const
	{
		AssertIsValid();
		::DragAcceptFiles(handle, accept ? TRUE : FALSE);
	}

	HICON Window::SetIcon(HICON icon, bool big) const
	{
		AssertIsValid();
		return reinterpret_cast<HICON>(Send(WM_SETICON, big ? TRUE : FALSE, icon));
	}

	HICON Window::GetIcon(bool big) const
	{
		AssertIsValid();
		return reinterpret_cast<HICON>(Send(WM_GETICON, big ? TRUE : FALSE));
	}

	bool Window::WinHelp(const char* help, int cmd, unsigned long data) const
	{
		AssertIsValid();
		return ::WinHelp(handle, help, cmd, data) != 0;
	}

	bool Window::SetContextHelpId(unsigned long context) const
	{
		AssertIsValid();
		return ::SetWindowContextHelpId(handle, context) != 0;
	}

	unsigned long Window::GetContextHelpId() const
	{
		AssertIsValid();
		return ::GetWindowContextHelpId(handle);
	}

	int Window::SetHotKey(short vkey, short modifiers) const
	{
		return Send(WM_SETHOTKEY, MAKEWPARAM(vkey, modifiers));
	}

	unsigned long Window::GetHotKey() const
	{
		return Send(WM_GETHOTKEY);
	}

	SCROLLINFO Window::GetScrollInfo(int bar, unsigned long mask) const
	{
		AssertIsValid();
		SCROLLINFO info;
		info.cbSize = sizeof(info);
		info.fMask = mask;
		::GetScrollInfo(handle, bar, &info);
		return info;
	}

	int Window::SetScrollInfo(int bar, const SCROLLINFO& info, bool redraw) const
	{
		AssertIsValid();
		return ::SetScrollInfo(handle, bar, &info, redraw ? TRUE : FALSE);
	}

	bool Window::IsDlgMsg(MSG* msg) const
	{
		AssertIsValid();
		return ::IsDialogMessage(handle, msg) != 0;
	}

	void Window::NextDlgCtrl() const
	{
		Send(WM_NEXTDLGCTL);
	}

	void Window::PrevDlgCtrl() const
	{
		Send(WM_NEXTDLGCTL, 1);
	}

	void Window::GotoDlgCtrl(HWND hwnd) const
	{
		Send(WM_NEXTDLGCTL, hwnd, 1);
	}

	void Window::ResizeClient(int w, int h, bool redraw) const
	{
		auto rc = GetClient();
		if (w != -1)
			rc.right = w;
		if (h != -1)
			rc.bottom = h;
		auto style = GetStyle();
		if (::AdjustWindowRectEx(&rc, style, !(style & WS_CHILD) && (GetMenu() != 0), GetExStyle()))
			SetPos(0, rc, SWP_NOZORDER|SWP_NOMOVE|(redraw ? 0 : SWP_NOREDRAW));
	}

	int Window::GetRgn(HRGN rgn) const
	{
		AssertIsValid();
		return ::GetWindowRgn(handle, rgn);
	}

	int Window::SetRgn(HRGN rgn, bool redraw) const
	{
		AssertIsValid();
		return ::SetWindowRgn(handle, rgn, redraw ? TRUE : FALSE);
	}

	unsigned long Window::GetThreadId() const
	{
		AssertIsValid();
		return ::GetWindowThreadProcessId(handle, 0);
	}

	unsigned long Window::GetProcessId() const
	{
		AssertIsValid();
		unsigned long id = 0;
		::GetWindowThreadProcessId(handle, &id);
		return id;
	}

	bool Window::ShowAsync(int show) const
	{
		AssertIsValid();
		return ::ShowWindowAsync(handle, show) != 0;
	}

	void Window::Center(HWND hwnd) const
	{
		AssertIsValid();

		auto style = ::GetWindowLongPtr(handle, GWL_STYLE);
		if (hwnd == 0)
		{
			if (style & WS_CHILD)
				hwnd = ::GetParent(handle);
			else
				hwnd = ::GetWindow(handle, GW_OWNER);
		}

		RECT rc, area, center;
		::GetWindowRect(handle, &rc);

		if (style & WS_CHILD)
		{
			auto parent = ::GetParent(handle);
			::GetClientRect(parent, &area);
			::GetClientRect(hwnd, &center);
			::MapWindowPoints(hwnd, parent, reinterpret_cast<POINT*>(&center), 2);
		}
		else
		{
			::SystemParametersInfo(SPI_GETWORKAREA, 0, &area, 0);
			center = area;
			if (hwnd)
			{
				auto cstyle = ::GetWindowLongPtr(hwnd, GWL_STYLE);
				if ((cstyle & WS_VISIBLE) && !(cstyle & WS_MINIMIZE))
					::GetWindowRect(hwnd, &center);
			}
		}

		auto w = rc.right - rc.left, h = rc.bottom - rc.top;
		auto x = (center.left + center.right) / 2 - w / 2;
		auto y = (center.top + center.bottom) / 2 - h / 2;

		if (x < area.left)
			x = area.left;
		else if (x + w > area.right)
			x = area.right - w;

		if (y < area.top)
			y = area.top;
		else if (y + h > area.bottom)
			y = area.bottom - h;

		::SetWindowPos(handle, 0, x, y, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	}

	void Window::Hide() const
	{
		Show(SW_HIDE);
	}

	Rect Window::MapRect(HWND hwndTo, const RECT& rc) const
	{
		AssertIsValid();
		RECT retval = rc;
		::MapWindowPoints(handle, hwndTo, reinterpret_cast<POINT*>(&retval), 2);
		return retval;
	}

	Rect Window::MapRectToParent(const RECT& rc) const
	{
		AssertIsValid();
		RECT retval = rc;
		::MapWindowPoints(handle, ::GetParent(handle), reinterpret_cast<POINT*>(&retval), 2);
		return retval;
	}

	void Window::TrackMouse(unsigned long flags, unsigned long hoverTime)
	{
		TRACKMOUSEEVENT event;
		event.cbSize = sizeof(event);
		event.dwFlags = flags;
		event.hwndTrack = handle;
		event.dwHoverTime = hoverTime;
		auto result = ::TrackMouseEvent(&event);
		CheckLastWindowsError(!result, "TrackMouseEvent");
	}
	
	bool Window::operator==(HWND value) const
	{
		return handle == value;
	}

	bool Window::operator!=(HWND value) const
	{
		return handle != value;
	}

	bool Window::operator<=(HWND value) const
	{
		return handle <= value;
	}

	bool Window::operator>=(HWND value) const
	{
		return handle >= value;
	}

	bool Window::operator<(HWND value) const
	{
		return handle < value;
	}

	bool Window::operator>(HWND value) const
	{
		return handle > value;
	}

	void Window::AssertIsValid() const
	{
		if (!IsValid())
			ThrowException("handle", 0, "Window is invalid.");
	}

	void Window::AssertIsValidOrNull() const
	{
		if (handle != nullptr && !IsValid())
			ThrowException("handle", 0, "Window is invalid.");
	}
}

