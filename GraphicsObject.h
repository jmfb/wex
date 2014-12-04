#pragma once
#include "ScopedResource.h"

namespace Wex
{
	class GraphicsObjectPolicy
	{
	public:
		using Resource = HGDIOBJ;
		static constexpr Resource Default = nullptr;
		static void Release(Resource resource);
	};

	template <typename SpecificHandle>
	class GraphicsObject : public ScopedResource<GraphicsObjectPolicy>
	{
	public:
		GraphicsObject() = default;
		using ScopedResource<GraphicsObjectPolicy>::ScopedResource;
		GraphicsObject(SpecificHandle handle)
			: ScopedResource<GraphicsObjectPolicy>{ handle }
		{
		}
		~GraphicsObject() = default;

		operator SpecificHandle() const
		{
			return reinterpret_cast<SpecificHandle>(Get());
		}

	private:
		friend class GraphicsObjectTest;
	};
}

