#include "WindowsInclude.h"
#include "GraphicsObject.h"

namespace Wex
{
	void GraphicsObjectPolicy::Release(Resource resource)
	{
		::DeleteObject(resource);
	}
}

