#include "WindowsInclude.h"
#include "MessageMap.h"

namespace Wex
{
	bool MessageMap::Process(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam,
		LRESULT& result)
	{
		result = 0;
		handledStack.push(true);
		messageStack.push({ hwnd, msg, wparam, lparam });
		switch(msg)
		{
		case WM_ACTIVATE:
			OnActivate(LOWORD(wparam), HIWORD(wparam) != 0, reinterpret_cast<HWND>(lparam));
			break;

		case WM_ACTIVATEAPP:
			OnActivateApp(wparam != 0, lparam);
			break;

		case WM_CANCELMODE:
			OnCancelMode();
			break;

		case WM_CAPTURECHANGED:
			OnCaptureChanged(reinterpret_cast<HWND>(lparam));
			break;

		case WM_CHAR:
			OnChar(wparam, LOWORD(lparam), lparam & 0xffff0000);
			break;

		case WM_CHARTOITEM:
			result = OnCharToItem(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HWND>(lparam));
			break;

		case WM_CHILDACTIVATE:
			OnChildActivate();
			break;

		case WM_CLOSE:
			OnClose();
			break;

		case WM_COMMAND:
			OnCommand(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HWND>(lparam));
			break;

		case WM_COMPAREITEM:
			result = OnCompareItem(wparam, reinterpret_cast<COMPAREITEMSTRUCT*>(lparam));
			break;

		case WM_CONTEXTMENU:
			OnContextMenu(reinterpret_cast<HWND>(wparam), { lparam });
			break;

		case WM_COPY:
			OnCopy();
			break;

		case WM_COPYDATA:
			if (OnCopyData(reinterpret_cast<HWND>(wparam), reinterpret_cast<COPYDATASTRUCT*>(lparam)))
				result = TRUE;
			break;

		case WM_CREATE:
			if (!OnCreate(reinterpret_cast<CREATESTRUCT*>(lparam)))
				result = -1;
			break;

		case WM_CTLCOLORBTN:
			result = reinterpret_cast<LRESULT>(OnCtlColorBtn(
				reinterpret_cast<HDC>(wparam),
				reinterpret_cast<HWND>(lparam)));
			break;

		case WM_CTLCOLOREDIT:
			result = reinterpret_cast<LRESULT>(OnCtlColorEdit(
				reinterpret_cast<HDC>(wparam),
				reinterpret_cast<HWND>(lparam)));
			break;

		case WM_CTLCOLORDLG:
			result = reinterpret_cast<LRESULT>(OnCtlColorDlg(
				reinterpret_cast<HDC>(wparam),
				reinterpret_cast<HWND>(lparam)));
			break;

		case WM_CTLCOLORLISTBOX:
			result = reinterpret_cast<LRESULT>(OnCtlColorListBox(
				reinterpret_cast<HDC>(wparam),
				reinterpret_cast<HWND>(lparam)));
			break;

		case WM_CTLCOLORSCROLLBAR:
			result = reinterpret_cast<LRESULT>(OnCtlColorScrollBar(
				reinterpret_cast<HDC>(wparam),
				reinterpret_cast<HWND>(lparam)));
			break;

		case WM_CTLCOLORSTATIC:
			result = reinterpret_cast<LRESULT>(OnCtlColorStatic(
				reinterpret_cast<HDC>(wparam),
				reinterpret_cast<HWND>(lparam)));
			break;

		case WM_CUT:
			OnCut();
			break;

		case WM_DELETEITEM:
			OnDeleteItem(wparam, reinterpret_cast<DELETEITEMSTRUCT*>(lparam));
			break;

		case WM_DESTROY:
			OnDestroy();
			break;

		case WM_DEVMODECHANGE:
			OnDevModeChange(reinterpret_cast<const char*>(lparam));
			break;

		case WM_DISPLAYCHANGE:
			OnDisplayChange(wparam, { lparam });
			break;

		case WM_DRAWITEM:
			OnDrawItem(wparam, reinterpret_cast<DRAWITEMSTRUCT*>(lparam));
			break;

		case WM_DROPFILES:
			OnDropFiles(reinterpret_cast<HDROP>(wparam));
			break;

		case WM_ENABLE:
			OnEnable(wparam != 0);
			break;

		case WM_ENDSESSION:
			OnEndSession(wparam != 0, (lparam & ENDSESSION_LOGOFF) != ENDSESSION_LOGOFF);
			break;

		case WM_ENTERIDLE:
			OnEnterIdle(wparam, reinterpret_cast<HWND>(lparam));
			break;

		case WM_ENTERMENULOOP:
			OnEnterMenuLoop(wparam != 0);
			break;

		case WM_ENTERSIZEMOVE:
			OnEnterSizeMove();
			break;

		case WM_ERASEBKGND:
			if (OnEraseBkgnd(reinterpret_cast<HDC>(wparam)))
				result = TRUE;
			break;

		case WM_EXITMENULOOP:
			OnExitMenuLoop(wparam != 0);
			break;

		case WM_EXITSIZEMOVE:
			OnExitSizeMove();
			break;

		case WM_GETDLGCODE:
			result = OnGetDlgCode(reinterpret_cast<MSG*>(lparam));
			break;

		case WM_GETMINMAXINFO:
			OnGetMinMaxInfo(reinterpret_cast<MINMAXINFO*>(lparam));
			break;

		case WM_HELP:
			OnHelp(reinterpret_cast<HELPINFO*>(lparam));
			result = TRUE;
			break;

		case WM_HSCROLL:
			OnHScroll(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HWND>(lparam));
			break;

		case WM_ICONERASEBKGND:
			OnIconEraseBkgnd(reinterpret_cast<HDC>(wparam));
			break;

		case WM_INITDIALOG:
			if (OnInitDialog(reinterpret_cast<HWND>(wparam), lparam))
				result = TRUE;
			break;

		case WM_INITMENU:
			OnInitMenu(reinterpret_cast<HMENU>(wparam));
			break;

		case WM_INITMENUPOPUP:
			OnInitMenuPopup(reinterpret_cast<HMENU>(wparam), LOWORD(lparam), HIWORD(lparam) != 0);
			break;

		case WM_KEYDOWN:
			OnKeyDown(wparam, LOWORD(lparam), lparam & 0xffff0000);
			break;

		case WM_KEYUP:
			OnKeyUp(wparam, LOWORD(lparam), lparam & 0xffff0000);
			break;

		case WM_KILLFOCUS:
			OnKillFocus(reinterpret_cast<HWND>(wparam));
			break;

		case WM_LBUTTONDBLCLK:
			OnLButtonDblClk({ lparam }, wparam);
			break;

		case WM_LBUTTONDOWN:
			OnLButtonDown({ lparam }, wparam);
			break;

		case WM_LBUTTONUP:
			OnLButtonUp({ lparam }, wparam);
			break;

		case WM_MBUTTONDBLCLK:
			OnMButtonDblClk({ lparam }, wparam);
			break;

		case WM_MBUTTONDOWN:
			OnMButtonDown({ lparam }, wparam);
			break;

		case WM_MBUTTONUP:
			OnMButtonUp({ lparam }, wparam);
			break;

		case WM_MDIACTIVATE:
			OnMDIActivate(reinterpret_cast<HWND>(lparam), reinterpret_cast<HWND>(wparam));
			break;

		case WM_MEASUREITEM:
			OnMeasureItem(wparam, reinterpret_cast<MEASUREITEMSTRUCT*>(lparam));
			break;

		case WM_MENUCHAR:
			result = OnMenuChar(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HMENU>(lparam));
			break;

		case WM_MENUSELECT:
			OnMenuSelect(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HMENU>(lparam));
			break;

		case WM_MOUSEACTIVATE:
			result = OnMouseActivate(reinterpret_cast<HWND>(wparam), LOWORD(lparam), HIWORD(lparam));
			break;

		case WM_MOUSEMOVE:
			OnMouseMove({ lparam }, wparam);
			break;

		case WM_MOUSEWHEEL:
			if (OnMouseWheel({ lparam }, HIWORD(wparam), LOWORD(wparam)))
				result = TRUE;
			break;

		case WM_MOVE:
			OnMove({ lparam });
			break;

		case WM_MOVING:
			if (OnMoving(reinterpret_cast<RECT*>(lparam)))
				result = TRUE;
			break;

		case WM_NOTIFY:
			result = OnNotify(reinterpret_cast<NMHDR*>(lparam));
			break;

		case WM_PAINT:
			OnPaint();
			break;

		case WM_QUERYDRAGICON:
			result = reinterpret_cast<LRESULT>(OnQueryDragIcon());
			break;

		case WM_QUERYENDSESSION:
			if (OnQueryEndSession())
				result = TRUE;
			break;

		case WM_RBUTTONDBLCLK:
			OnRButtonDblClk({ lparam }, wparam);
			break;

		case WM_RBUTTONDOWN:
			OnRButtonDown({ lparam }, wparam);
			break;

		case WM_RBUTTONUP:
			OnRButtonUp({ lparam }, wparam);
			break;

		case WM_SETCURSOR:
			if (OnSetCursor(reinterpret_cast<HWND>(wparam), LOWORD(lparam), HIWORD(lparam)))
				result = TRUE;
			break;

		case WM_SETFOCUS:
			OnSetFocus(reinterpret_cast<HWND>(wparam));
			break;

		case WM_SHOWWINDOW:
			OnShowWindow(wparam != 0, lparam);
			break;

		case WM_SIZE:
			OnSize(wparam, { lparam });
			break;

		case WM_SIZING:
			if (OnSizing(wparam, reinterpret_cast<RECT*>(lparam)))
				result = TRUE;
			break;

		case WM_STYLECHANGED:
			OnStyleChanged(wparam, reinterpret_cast<STYLESTRUCT*>(lparam));
			break;

		case WM_STYLECHANGING:
			OnStyleChanging(wparam, reinterpret_cast<STYLESTRUCT*>(lparam));
			break;

		case WM_SYSCHAR:
			OnSysChar(wparam, LOWORD(lparam), lparam & 0xffff0000);
			break;

		case WM_SYSCOLORCHANGE:
			OnSysColorChange();
			break;

		case WM_SYSCOMMAND:
			OnSysCommand(wparam, { lparam });
			break;

		case WM_SYSKEYDOWN:
			OnSysKeyDown(wparam, LOWORD(lparam), lparam & 0xffff0000);
			break;

		case WM_SYSKEYUP:
			OnSysKeyUp(wparam, LOWORD(lparam), lparam & 0xffff0000);
			break;

		case WM_TIMECHANGE:
			OnTimeChange();
			break;

		case WM_TIMER:
			OnTimer(wparam);
			break;

		case WM_VKEYTOITEM:
			result = OnVKeyToItem(LOWORD(wparam), HIWORD(wparam), reinterpret_cast<HWND>(lparam));
			break;

		case WM_VSCROLL:
			OnVScroll(HIWORD(wparam), LOWORD(wparam), reinterpret_cast<HWND>(lparam));
			break;

		case WM_WINDOWPOSCHANGED:
			OnWindowPosChanged(reinterpret_cast<WINDOWPOS*>(lparam));
			break;

		case WM_WINDOWPOSCHANGING:
			OnWindowPosChanging(reinterpret_cast<WINDOWPOS*>(lparam));
			break;

		default:
			NotHandled();
		}

		messageStack.pop();
		auto handled = handledStack.top();
		handledStack.pop();
		return handled;
	}

	void MessageMap::OnActivate(short state, bool minimized, HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnActivateApp(bool activated, unsigned long threadid)
	{
		NotHandled();
	}
	void MessageMap::OnCancelMode()
	{
		NotHandled();
	}
	void MessageMap::OnCaptureChanged(HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnChar(int c, int count, unsigned long flags)
	{
		NotHandled();
	}
	int MessageMap::OnCharToItem(int c, int index, HWND hwnd)
	{
		NotHandled();
		return 0;
	}
	void MessageMap::OnChildActivate()
	{
		NotHandled();
	}
	void MessageMap::OnClose()
	{
		NotHandled();
	}
	void MessageMap::OnCommand(WORD id, WORD code, HWND from)
	{
		auto iter = commandHandlers.find({ id, code });
		if (iter != commandHandlers.end())
			iter->second(id, code, from);
		else
			NotHandled();
	}
	int MessageMap::OnCompareItem(int id, COMPAREITEMSTRUCT* cis)
	{
		NotHandled();
		return 0;
	}
	void MessageMap::OnContextMenu(HWND hwnd, const Point& pt)
	{
		NotHandled();
	}
	void MessageMap::OnCopy()
	{
		NotHandled();
	}
	bool MessageMap::OnCopyData(HWND hwnd, COPYDATASTRUCT* cds)
	{
		NotHandled();
		return false;
	}
	bool MessageMap::OnCreate(CREATESTRUCT* cs)
	{
		NotHandled();
		return false;
	}
	HBRUSH MessageMap::OnCtlColorBtn(HDC hdc, HWND hwnd)
	{
		NotHandled();
		return nullptr;
	}
	HBRUSH MessageMap::OnCtlColorEdit(HDC hdc, HWND hwnd)
	{
		NotHandled();
		return nullptr;
	}
	HBRUSH MessageMap::OnCtlColorDlg(HDC hdc, HWND hwnd)
	{
		NotHandled();
		return nullptr;
	}
	HBRUSH MessageMap::OnCtlColorListBox(HDC hdc, HWND hwnd)
	{
		NotHandled();
		return nullptr;
	}
	HBRUSH MessageMap::OnCtlColorScrollBar(HDC hdc, HWND hwnd)
	{
		NotHandled();
		return nullptr;
	}
	HBRUSH MessageMap::OnCtlColorStatic(HDC hdc, HWND hwnd)
	{
		NotHandled();
		return nullptr;
	}
	void MessageMap::OnCut()
	{
		NotHandled();
	}
	void MessageMap::OnDeleteItem(int id, DELETEITEMSTRUCT* dis)
	{
		NotHandled();
	}
	void MessageMap::OnDestroy()
	{
		NotHandled();
	}
	void MessageMap::OnDevModeChange(const std::string& devname)
	{
		NotHandled();
	}
	void MessageMap::OnDisplayChange(int bpp, const Size& size)
	{
		NotHandled();
	}
	void MessageMap::OnDrawItem(int id, DRAWITEMSTRUCT* dis)
	{
		NotHandled();
	}
	void MessageMap::OnDropFiles(HDROP drop)
	{
		NotHandled();
	}
	void MessageMap::OnEnable(bool enabled)
	{
		NotHandled();
	}
	void MessageMap::OnEndSession(bool ending, bool shutdown)
	{
		NotHandled();
	}
	void MessageMap::OnEnterIdle(int why, HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnEnterMenuLoop(bool viatrack)
	{
		NotHandled();
	}
	void MessageMap::OnEnterSizeMove()
	{
		NotHandled();
	}
	bool MessageMap::OnEraseBkgnd(HDC hdc)
	{
		NotHandled();
		return false;
	}
	void MessageMap::OnExitMenuLoop(bool shortcut)
	{
		NotHandled();
	}
	void MessageMap::OnExitSizeMove()
	{
		NotHandled();
	}
	int MessageMap::OnGetDlgCode(MSG* msg)
	{
		NotHandled();
		return 0;
	}
	void MessageMap::OnGetMinMaxInfo(MINMAXINFO* mmi)
	{
		NotHandled();
	}
	void MessageMap::OnHelp(HELPINFO* hi)
	{
		NotHandled();
	}
	void MessageMap::OnHScroll(int code, int pos, HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnIconEraseBkgnd(HDC hdc)
	{
		NotHandled();
	}
	bool MessageMap::OnInitDialog(HWND hwnd, LPARAM lparam)
	{
		NotHandled();
		return false;
	}
	void MessageMap::OnInitMenu(HMENU menu)
	{
		NotHandled();
	}
	void MessageMap::OnInitMenuPopup(HMENU menu, int index, bool system)
	{
		NotHandled();
	}
	void MessageMap::OnKeyDown(int c, int count, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnKeyUp(int c, int count, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnKillFocus(HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnLButtonDblClk(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnLButtonDown(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnLButtonUp(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnMButtonDblClk(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnMButtonDown(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnMButtonUp(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnMDIActivate(HWND activated, HWND deactivated)
	{
		NotHandled();
	}
	void MessageMap::OnMeasureItem(int id, MEASUREITEMSTRUCT* mis)
	{
		NotHandled();
	}
	int MessageMap::OnMenuChar(int c, int type, HMENU menu)
	{
		NotHandled();
		return 0;
	}
	void MessageMap::OnMenuSelect(int id, int flags, HMENU menu)
	{
		NotHandled();
	}
	int MessageMap::OnMouseActivate(HWND hwnd, int hittest, UINT msg)
	{
		NotHandled();
		return 0;
	}
	void MessageMap::OnMouseMove(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	bool MessageMap::OnMouseWheel(const Point& pt, short delta, unsigned long flags)
	{
		NotHandled();
		return false;
	}
	void MessageMap::OnMove(const Point& pt)
	{
		NotHandled();
	}
	bool MessageMap::OnMoving(RECT* rect)
	{
		NotHandled();
		return false;
	}
	LRESULT MessageMap::OnNotify(NMHDR* hdr)
	{
		LRESULT result = 0;
		auto iter = notifyHandlers.find({ hdr->idFrom, hdr->code });
		if (iter != notifyHandlers.end())
			result = iter->second(hdr);
		else
			NotHandled();
		return result;
	}
	void MessageMap::OnPaint()
	{
		NotHandled();
	}
	HCURSOR MessageMap::OnQueryDragIcon()
	{
		NotHandled();
		return nullptr;
	}
	bool MessageMap::OnQueryEndSession()
	{
		NotHandled();
		return false;
	}
	void MessageMap::OnRButtonDblClk(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnRButtonDown(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnRButtonUp(const Point& pt, unsigned long flags)
	{
		NotHandled();
	}
	bool MessageMap::OnSetCursor(HWND hwnd, int hittest, UINT msg)
	{
		NotHandled();
		return false;
	}
	void MessageMap::OnSetFocus(HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnShowWindow(bool show, int status)
	{
		NotHandled();
	}
	void MessageMap::OnSize(int type, const Size& size)
	{
		NotHandled();
	}
	bool MessageMap::OnSizing(int side, RECT* rect)
	{
		NotHandled();
		return false;
	}
	void MessageMap::OnStyleChanged(int type, STYLESTRUCT* ss)
	{
		NotHandled();
	}
	void MessageMap::OnStyleChanging(int type, STYLESTRUCT* ss)
	{
		NotHandled();
	}
	void MessageMap::OnSysChar(int c, int count, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnSysColorChange()
	{
		NotHandled();
	}
	void MessageMap::OnSysCommand(int id, const Point& pt)
	{
		NotHandled();
	}
	void MessageMap::OnSysKeyDown(int c, int count, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnSysKeyUp(int c, int count, unsigned long flags)
	{
		NotHandled();
	}
	void MessageMap::OnTimeChange()
	{
		NotHandled();
	}
	void MessageMap::OnTimer(int id)
	{
		NotHandled();
	}
	int MessageMap::OnVKeyToItem(int c, int index, HWND hwnd)
	{
		NotHandled();
		return 0;
	}
	void MessageMap::OnVScroll(int code, int pos, HWND hwnd)
	{
		NotHandled();
	}
	void MessageMap::OnWindowPosChanged(WINDOWPOS* wp)
	{
		NotHandled();
	}
	void MessageMap::OnWindowPosChanging(WINDOWPOS* wp)
	{
		NotHandled();
	}

	void MessageMap::InstallDefault(WNDPROC proc)
	{
		defaultProcedure = proc;
	}

	WNDPROC MessageMap::RemoveDefault()
	{
		auto result = defaultProcedure;
		defaultProcedure = nullptr;
		return result;
	}

	bool MessageMap::IsInNestedCall() const
	{
		return(messageStack.size() > 1);
	}

	void MessageMap::NotHandled()
	{
		handledStack.top() = false;
	}

	LRESULT MessageMap::DoDefault()
	{
		if (messageStack.empty())
			return 0;
		const auto& currentMessage = messageStack.top();
		return DoDefault(
			currentMessage.hwnd,
			currentMessage.message,
			currentMessage.wParam,
			currentMessage.lParam);
	}
	LRESULT MessageMap::DoDefault(
		HWND hwnd,
		UINT msg,
		WPARAM wparam,
		LPARAM lparam)
	{
		if (defaultProcedure == nullptr)
			return 0;
		return ::CallWindowProc(defaultProcedure, hwnd, msg, wparam, lparam);
	}
}

