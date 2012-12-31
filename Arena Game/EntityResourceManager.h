/*
Have a map from string to entity *, which is a template.
The build functions will then make a new entity and copy from the template
the build function will set any values that aren't in the template, such as position,
and then return the new entity
*/


#ifndef ENTITYRESOURCEMANAGER_H_
#define ENTITYRESOURCEMANAGER_H_

#include "GameResourceManager.h"
#include "json\json.h"
#include <fstream>

#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "DamagingEntity.h"

#include "TextureManager.h"
#include "SoundManager.h"

class EntityResourceManager : public GameResourceManager<Entity>
{
public:
	EntityResourceManager();
	~EntityResourceManager();

	virtual void Flush();

	void init(TextureManager &textureManager, SoundManager &soundManager);

	virtual void loadResource(const std::string filepath);

private:
	TextureManager *textureManagerPtr;
	SoundManager *soundManagerPtr;

	//This will load the type of the entity so we can create the correct object
	Entity *loadType(Json::Value &root);
	//Load the generic values that all entities will have
	void loadGenerics(Entity &entity, Json::Value &root);
	//load other components that are specific to certain entities
	void loadAnimations(Entity &entity, Json::Value &root);
	void loadAbilities(Entity &entity, Json::Value &root);
	void loadBehaviour(Entity &entity, Json::Value &root);
	void loadDamagingEntity(Entity &entity, Json::Value &root);
	void loadCharacter(Entity &entity, Json::Value &root);
};

#endif

