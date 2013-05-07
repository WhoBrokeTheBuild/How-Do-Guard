#include "DataManager.h"

DataManager* gpDataManager = nullptr;

DataManager::DataManager( void )
{
}

DataManager::~DataManager( void )
{
	term();
}

std::string DataManager::toString( void ) const
{
	return "Data Manager";
}

void DataManager::init( void )
{
	pAnimations = New Manager<Animation>();
	pAnimations->init();

	pSprites = New Manager<Sprite>();
	pSprites->init();

	pTextures = New Manager<Texture>();
	pTextures->init();

	loadAssets("main.cfg");
}

void DataManager::term( void )
{
	delete pAnimations;
	delete pSprites;
	delete pTextures;
}

void DataManager::loadAssets( string filename )
{
	stringstream fullFilename;
	fullFilename << "config/" << filename;

	ifstream mainFile(fullFilename.str().c_str());

	string line;
	while(!mainFile.eof())
	{
		getline(mainFile, line);

		vector<string> pieces = strSplit(line, ' ', 2);

		if (pieces.size() == 2)
		{
			if (pieces[0] == "Load")
			{
				loadAssetFile(pieces[1]);
			}
		}
	}

	mainFile.close();
}

void DataManager::loadAssetFile( string filename )
{
	stringstream fullFilename;
	fullFilename << "config/" << filename;

	ifstream assetFile(fullFilename.str().c_str());

	bool 
		addingTexture = false,
		addingSprite = false,
		addingAnimation = false;

	stringstream ss;

	string line;
	while(!assetFile.eof())
	{
		getline(assetFile, line);

		if (addingTexture)
		{

		}
		else if (addingSprite)
		{

		}
		else if (addingAnimation)
		{

		}
		else
		{
			vector<string> pieces = strSplit(line, ' ', 2);

			if (pieces.size() == 2)
			{
				if (pieces[0] == "Texture")
				{
					ss.str("assets/");
					ss << pieces[1];
					ItemKey key = pTextures->addEmpty();
					pTextures->get(key)->init(ss.str());
				}
			}
		}

	}

	assetFile.close();
}
