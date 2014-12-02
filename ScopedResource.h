#pragma once
#include <utility>

namespace Wex
{
	template <typename Policy>
	class ScopedResource
	{
	public:
		using Resource = typename Policy::Resource;
		
		ScopedResource() = default;
		ScopedResource(Resource resource)
			: resource(resource)
		{
		}
		ScopedResource(const ScopedResource<Policy>& rhs) = delete;
		~ScopedResource()
		{
			Release();
		}

		ScopedResource<Policy>& operator=(const ScopedResource<Policy>& rhs) = delete;
		ScopedResource<Policy>& operator=(Resource value)
		{
			Attach(value);
			return *this;
		}

		Resource Get() const
		{
			return resource;
		}
		Resource Detach()
		{
			auto result = Policy::Default;
			std::swap(resource, result);
			return result;
		}
		void Attach(Resource value)
		{
			if (resource == value)
				return;
			Release();
			resource = value;
		}
		void Release()
		{
			if (resource == Policy::Default)
				return;
			Policy::Release(Detach());
		}

		operator bool() const
		{
			return resource != Policy::Default;
		}
		Resource* operator&()
		{
			return &resource;
		}

	private:
		friend class ScopedResourceTest;
		Resource resource = Policy::Default;
	};
}

