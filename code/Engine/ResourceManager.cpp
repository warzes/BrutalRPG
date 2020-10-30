#include "stdafx.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "Allocators.h"
#include "Logger.h"


void ResourceManager::create(ResourceType type, ResourceManagerHub& owner)
{
	owner.add(type, this);
	m_owner = &owner;
}

void ResourceManager::destroy()
{
	for (auto iter = m_resources.begin(), end = m_resources.end(); iter != end; ++iter)
	{
		Resource* resource = iter.value();
		if (!resource->isEmpty())
		{
			SE_LOG_ERROR(std::string("Leaking resource ") + resource->getPath().c_str());
		}
		destroyResource(*resource);
	}
	m_resources.clear();
}

Resource* ResourceManager::get(const Path& path)
{
	ResourceTable::iterator it = m_resources.find(path.getHash());

	if (m_resources.end() != it)
	{
		return *it;
	}

	return nullptr;
}

Resource* ResourceManager::load(const Path& path)
{
	if (!path.isValid()) return nullptr;
	Resource* resource = get(path);

	if (nullptr == resource)
	{
		resource = createResource(path);
		m_resources.insert(path.getHash(), resource);
	}

	if (resource->isEmpty() && resource->m_desired_state == Resource::State::EMPTY)
	{
		if (m_owner->onBeforeLoad(*resource) == ResourceManagerHub::LoadHook::Action::DEFERRED)
		{
			resource->m_desired_state = Resource::State::READY;
			resource->incRefCount(); // for hook
			resource->incRefCount(); // for return value
			return resource;
		}
		resource->doLoad();
	}

	resource->incRefCount();
	return resource;
}

void ResourceManager::removeUnreferenced()
{
	if (!m_is_unload_enabled) return;

	Array<Resource*> to_remove(m_allocator);
	for (auto* i : m_resources)
	{
		if (i->getRefCount() == 0) to_remove.push(i);
	}

	for (auto* i : to_remove)
	{
		m_resources.erase(i->getPath().getHash());
		destroyResource(*i);
	}
}

void ResourceManager::reload(const Path& path)
{
	Resource* resource = get(path);
	if (resource) reload(*resource);
}

void ResourceManager::reload(Resource& resource)
{
	resource.doUnload();
	if (m_owner->onBeforeLoad(resource) == ResourceManagerHub::LoadHook::Action::DEFERRED)
	{
		resource.m_desired_state = Resource::State::READY;
		resource.incRefCount(); // for hook
		resource.incRefCount(); // for return value
	}
	else {
		resource.doLoad();
	}
}

void ResourceManager::enableUnload(bool enable)
{
	m_is_unload_enabled = enable;
	if (!enable) return;

	for (auto* resource : m_resources)
	{
		if (resource->getRefCount() == 0)
		{
			resource->doUnload();
		}
	}
}

ResourceManager::ResourceManager(IAllocator& allocator)
	: m_resources(allocator)
	, m_allocator(allocator)
	, m_owner(nullptr)
	, m_is_unload_enabled(true)
{ }

ResourceManager::~ResourceManager()
{
	ASSERT(m_resources.empty());
}

ResourceManagerHub::ResourceManagerHub(IAllocator& allocator)
	: m_resource_managers(allocator)
	, m_allocator(allocator)
	, m_load_hook(nullptr)
	, m_file_system(nullptr)
{
}

ResourceManagerHub::~ResourceManagerHub() = default;


void ResourceManagerHub::init(FileSystem & fs)
{
	m_file_system = &fs;
}

Resource* ResourceManagerHub::load(ResourceType type, const Path & path)
{
	ResourceManager* manager = get(type);
	if (!manager) return nullptr;
	return load(*manager, path);
}

Resource* ResourceManagerHub::load(ResourceManager & manager, const Path & path)
{
	return manager.load(path);
}

ResourceManager* ResourceManagerHub::get(ResourceType type)
{
	auto iter = m_resource_managers.find(type.type);
	if (!iter.isValid()) return nullptr;
	return iter.value();
}

void ResourceManagerHub::LoadHook::continueLoad(Resource & resource)
{
	ASSERT(resource.isEmpty());
	resource.decRefCount(); // release from hook
	resource.m_desired_state = Resource::State::EMPTY;
	resource.doLoad();
}

void ResourceManagerHub::setLoadHook(LoadHook * hook)
{
	ASSERT(!m_load_hook || !hook);
	m_load_hook = hook;
}

ResourceManagerHub::LoadHook::Action ResourceManagerHub::onBeforeLoad(Resource & resource) const
{
	return m_load_hook ? m_load_hook->onBeforeLoad(resource) : LoadHook::Action::IMMEDIATE;
}

void ResourceManagerHub::add(ResourceType type, ResourceManager * rm)
{
	m_resource_managers.insert(type.type, rm);
}

void ResourceManagerHub::remove(ResourceType type)
{
	m_resource_managers.erase(type.type);
}

void ResourceManagerHub::removeUnreferenced()
{
	for (auto* manager : m_resource_managers)
	{
		manager->removeUnreferenced();
	}
}

void ResourceManagerHub::enableUnload(bool enable)
{
	for (auto* manager : m_resource_managers)
	{
		manager->enableUnload(enable);
	}
}

void ResourceManagerHub::reload(const Path & path)
{
	for (auto* manager : m_resource_managers)
	{
		manager->reload(path);
	}
}