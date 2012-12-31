#include "EntityResourceManager.h"

EntityResourceManager::EntityResourceManager()
{

}

void EntityResourceManager::init(TextureManager &textureManager, SoundManager &soundManager)
{
	this->textureManagerPtr = &textureManager;
	this->soundManagerPtr = &soundManager;
}


EntityResourceManager::~EntityResourceManager()
{
}

void EntityResourceManager::Flush()
{
	for(it = resourceMap.begin(); it != resourceMap.end(); it++)
	{
		it->second->Flush();
	}
	GameResourceManager<Entity>::Flush();
}

void EntityResourceManager::loadResource(const std::string filepath)
{
	//open up the file
	std::filebuf fb;
	fb.open(filepath, std::ios::in);

	//try to parse it
	Json::Value root;
	Json::Reader reader;
	bool parseSuccessful = reader.parse(std::istream(&fb), root);
	//now we have it parsed we can close it
	fb.close();

	if(!parseSuccessful)
	{
		std::cerr << "Unable to load entity: " << filepath << std::endl;
		std::cerr << reader.getFormattedErrorMessages() << std::endl;
		return;
	}

	Entity *entityPtr = loadType(root);
	if(entityPtr == NULL)
	{
		std::cerr << "Invalid type in entity file " << filepath << std::endl;
		return;
	}

	loadGenerics(*entityPtr, root);
	loadDamagingEntity(*entityPtr, root);
	loadCharacter(*entityPtr, root);

	std::string behaviour = root.get("behaviour", "").asString();
	if(!behaviour.empty())
	{
		loadBehaviour(*entityPtr, root);
	}

	Json::Value animations = root["animations"];
	if(animations.size() > 0)
	{
		loadAnimations(*entityPtr, root);
	}

	Json::Value abilities = root["abilities"];
	if(abilities.size() > 0)
	{
		loadAbilities(*entityPtr, root);
	}

	resourceMap[filepath] = entityPtr;
}

Entity *EntityResourceManager::loadType(Json::Value &root)
{
	Json::Value entityType;
	entityType = root.get("type", NULL);
	if(entityType == NULL)
	{
		return NULL;
	}

	Entity *entityPtr = NULL;
	
	//read from file
	std::string type = entityType.asString();
	if(type.compare("player") == 0)
	{
		entityPtr = new Player();
		entityPtr->setType(PLAYER);
	}
	else if(type.compare("enemy") == 0)
	{
		entityPtr = new Enemy();
		entityPtr->setType(ENEMY);
	}
	else if(type.compare("damaging") == 0)
	{
		entityPtr = new DamagingEntity();
		entityPtr->setType(DAMAGING_ENTITY);
	}
	else if(type.compare("wall") == 0)
	{
		entityPtr = new Wall();
		entityPtr->setType(WALL);
	}
	else
	{
		//invalid type, stop right here criminal scum
		return NULL;
	}

	//if we got to here it was a valid type
	return entityPtr;
}

void EntityResourceManager::loadGenerics(Entity &entity, Json::Value &root)
{
	//Remember, we are just loading a template. The object we are building will never be active.
	//We will simply be copying this template when needed when loading or spawning entities.

	entity.Load(*textureManagerPtr->getResource(root["texture"].asString()));
	entity.setActive(false);
	entity.setColliding(false);
	entity.setPos(sf::Vector2f());
	
	Json::Value scale = root.get("scale", -1);
	entity.setScale((scale == -1) ? sf::Vector2f(1.0f, 1.0f) : sf::Vector2f(scale["x"].asFloat(), scale["y"].asFloat()));

	//if speed is -1, it means the entity was not given a speed, therefore the speed is (0, 0)
	Json::Value speed = root.get("speed", -1);
	entity.setSpeed((speed == -1) ? sf::Vector2f() : sf::Vector2f(speed["x"].asFloat(), speed["y"].asFloat()));

	std::string hitSoundFilepath = root.get("hitSound", "").asString();
	entity.setHitSoundFilepath(hitSoundFilepath);

	std::string hitEmitterFilepath = root.get("hitEmitter", "").asString();
	entity.setHitEmitterFilepath(hitEmitterFilepath);
}

void EntityResourceManager::loadAnimations(Entity &entity, Json::Value &root)
{
	//Lets just confirm that the entity is an animated entity...
	AnimatedEntity *animatedEntityPtr = dynamic_cast<AnimatedEntity*>(&entity);
	//If it's null, then either the entity type is wrong or they have accidentally
	//provided an animation file for a non-animated entity
	if(animatedEntityPtr == NULL)
	{
		return;
	}

	Json::Value animations = root.get("animations", NULL);
	if(animations == NULL)
	{
		return;
	}

	std::map<std::string, Animation*> *animationListPtr = new std::map<std::string, Animation*>();
	//if the entity has no animation, size will be 0, which is a problem since it's an animated entity!
	for(unsigned int i = 0; i < animations.size(); i++)
	{
		Animation *animationPtr = new Animation();
		Json::Value animation = animations[i];
		
		std::string name = animation["name"].asString();

		//first see if there are any rows, if there isn't, size will be 0
		Json::Value rows = animation["rows"];
		for(unsigned int j = 0; j < rows.size(); j++)
		{
			Json::Value row = rows[j];
			sf::Vector2i origin(row["origin"]["x"].asInt(), row["origin"]["y"].asInt());
			unsigned int numFrames = row["frameCount"].asUInt();
			sf::Vector2i frameSize(row["frameSize"]["width"].asInt(), row["frameSize"]["height"].asInt());
			sf::Time duration = sf::milliseconds(row["frameDuration"].asInt());

			animationPtr->addRow(origin, numFrames, frameSize, duration);
		}

		//now check for any individual frames
		Json::Value frames = animation["frames"];
		for(unsigned int j = 0; j < frames.size(); j++)
		{
			Json::Value frame = frames[j];
			Json::Value rect = frame["rect"];
			
			sf::Time duration = sf::milliseconds(frame["duration"].asUInt());
			sf::IntRect frameRect(rect["left"].asInt(), rect["top"].asInt(),
				rect["width"].asInt(), rect["height"].asInt());

			animationPtr->addFrame(duration, frameRect);
		}
		(*animationListPtr)[name] = animationPtr;
		animatedEntityPtr->setFrame(animationListPtr->at(name)->getFrameAt(0)->rect);
	}

	animatedEntityPtr->initAnimation(animationListPtr);
}

void EntityResourceManager::loadAbilities(Entity &entity, Json::Value &root)
{
	//Lets just confirm that the entity has an ability manager
	Character *characterPtr = dynamic_cast<Character*>(&entity);
	//If it's null, then either the entity type is wrong or they have accidentally
	//provided an abilities file for a entity that does not have abilities
	if(characterPtr == NULL)
	{
		return;
	}

	//read abilities
	Json::Value abilities = root["abilities"];

	//if the entity has no animation, size will be 0
	for(unsigned int i = 0; i < abilities.size(); i++)
	{
		Json::Value abilityValue = abilities[i];
		Ability *abilityPtr = new Ability();

		//set ability attributes...
		/*key : default value
		name :
		entityFilepath: 
		damageMultiplier : 1
		spawnOffset : 0, 0
		numEntities : 1
		angle : 0
		rateOfFire
		*/

		std::string entityFilepath = abilityValue.get("entityFilepath", "").asString();
		abilityPtr->setEntityFilepath(entityFilepath);

		std::string soundFilepath = abilityValue.get("soundFilepath", "").asString();
		if(!soundFilepath.empty())
		{
			const sf::SoundBuffer *ptr = soundManagerPtr->getResource(soundFilepath);
			if(ptr != NULL)
			{
				abilityPtr->setSound(sf::Sound(*ptr));
			}
		}

		float damageMultiplier = abilityValue.get("damageMultiplier", 1.0f).asFloat();
		abilityPtr->setDamageMultiplier(damageMultiplier);		

		Json::Value offset = abilityValue.get("spawnOffset", -1);
		sf::Vector2f spawnOffset = (offset == -1) ? sf::Vector2f() : sf::Vector2f(offset["x"].asFloat(), offset["y"].asFloat());
		abilityPtr->setSpawnOffset(spawnOffset);

		unsigned int numEntities = abilityValue.get("numEntities", 1).asUInt();
		abilityPtr->setNumEntities(numEntities);

		float angle = abilityValue.get("angle", 0).asFloat();
		abilityPtr->setAngleBetweenEntities(angle);

		sf::Time rateOfFireLama(sf::milliseconds(abilityValue["rateOfFire"].asInt()));
		abilityPtr->setRateOfFire(rateOfFireLama);

		characterPtr->addAbility(abilityPtr);
	}
}

void EntityResourceManager::loadBehaviour(Entity &entity, Json::Value &root)
{
	Enemy *enemyPtr = dynamic_cast<Enemy*>(&entity);

	if(enemyPtr != NULL)
	{
		std::string behaviour = root["behaviour"].asString();
		if(behaviour.compare("simple") == 0)
		{
			enemyPtr->setBehaviour(new SimpleAI());
		}
		else if(behaviour.compare("advanced") == 0)
		{
			enemyPtr->setBehaviour(new AdvancedAI());
		}
		else if(behaviour.compare("rammer") == 0)
		{
			enemyPtr->setBehaviour(new RammerAI());
		}
		else if(behaviour.compare("splitter") == 0)
		{
			enemyPtr->setBehaviour(new SplitterAI());
		}
		else if(behaviour.compare("splitlet") == 0)
		{
			enemyPtr->setBehaviour(new SplitletsAI());
		}
		else if(behaviour.compare("fleeing") == 0)
		{
			enemyPtr->setBehaviour(new FleeingAI());
		}
		else if(behaviour.compare("gravity") == 0)
		{
			enemyPtr->setBehaviour(new GravityAI());
		}
		else if(behaviour.compare("defensive") == 0)
		{
			enemyPtr->setBehaviour(new DefensiveAI());
		}
	}
}

void EntityResourceManager::loadDamagingEntity(Entity &entity, Json::Value &root)
{
	DamagingEntity *damagingPtr = dynamic_cast<DamagingEntity*>(&entity);

	if(damagingPtr != NULL)
	{
		std::string subType = root["subtype"].asString();
		if(subType.compare("melee") == 0)
		{
			damagingPtr->setSubType(DamagingEntity::MELEE);
		}
		else if(subType.compare("projectile") == 0)
		{
			damagingPtr->setSubType(DamagingEntity::PROJECTILE);
		}
		else if(subType.compare("trap") == 0)
		{
			damagingPtr->setSubType(DamagingEntity::TRAP);
		}

		int lifetime = root.get("lifetime", -1).asInt();
		damagingPtr->setLifeTime(sf::milliseconds(lifetime));

		float damage = root.get("damage", 0).asFloat();
		damagingPtr->setDamage(damage);
	}
}

void EntityResourceManager::loadCharacter(Entity &entity, Json::Value &root)
{
	Character *characterPtr = dynamic_cast<Character*>(&entity);

	if(characterPtr != NULL)
	{
		float hitDamage = root.get("hitDamage", 0).asFloat();
		characterPtr->setHitDamage(hitDamage);

		float health = root.get("health", 0).asFloat();
		characterPtr->setHealth(health);
		characterPtr->setMaxHealth(health);

		int deathScore = root.get("deathScore", 0).asInt();
		characterPtr->setDeathScore(deathScore);
	}
}
