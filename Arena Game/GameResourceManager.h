#ifndef GAMERESOURCEMANAGER_H_
#define GAMERESOURCEMANAGER_H_

#include <string>
#include <map>

template <typename T>
class GameResourceManager
{
public:
	inline GameResourceManager<T>()
	{
	}

	inline virtual ~GameResourceManager<T>()
	{
		Flush();
	}

	/*
	Returns a pointer to the resource from memory.
	If it is not loaded, it will atempt to load it from file and then return it
	*/
	inline const T *getResource(const std::string filepath)
	{
		if(!isLoaded(filepath))
		{
			loadResource(filepath);
		}
		return resourceMap[filepath];
	}

	/*
	Loads the resource from file. This is pure virtual as each resource
	has it's own implementation for loading a file.
	*/
	virtual void loadResource(const std::string filepath) = 0;

	//Unloads a specific resource
	inline void unloadResource(const std::string filepath)
	{
		//can only unload a resource if it's already loaded
		if(isLoaded(filepath))
		{
			delete resourceMap[filepath];
			resourceMap.erase(filepath);
		}	
	}

	//Unloads all resources in the manager
	inline virtual void Flush()
	{
		for(it = resourceMap.begin(); it != resourceMap.end(); it++)
		{
			delete it->second;
		}
		resourceMap.clear();
	}

	//Checks to see if resource is already loaded
	inline bool isLoaded(const std::string filepath) const
	{
		//return true if we find it before reaching the end, false otherwise
		return resourceMap.find(filepath) != resourceMap.end();
	}

protected:
	std::map<std::string, T*> resourceMap;
	typename std::map<std::string, T*>::const_iterator it;
};

#endif

