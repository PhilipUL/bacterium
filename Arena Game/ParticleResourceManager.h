#ifndef PARTICLERESOURCEMANAGER_H_
#define PARTICLERESOURCEMANAGER_H_

#include "json\json.h"
#include <fstream>

#include "ParticleEmitter.h"
#include "TextureManager.h"

class ParticleResourceManager : public GameResourceManager<ParticleEmitter>
{
public:
	ParticleResourceManager(void);
	~ParticleResourceManager(void);

	void init(TextureManager &textureManager);

	virtual void loadResource(const std::string filepath);

private:
	TextureManager *textureManagerPtr;
};

#endif

