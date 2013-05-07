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
	fullFilename << "assets/config/" << filename;

	ifstream mainFile(fullFilename.str());

	if (!mainFile.is_open())
		return;

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
	fullFilename << "assets/config/" << filename;

	ifstream assetFile(fullFilename.str().c_str());

	stringstream ss;

	string line;
	while(!assetFile.eof())
	{
		getline(assetFile, line);

		if (line[0] == '#')
			continue;

		vector<string> pieces = strSplit(line, ' ', 2);

		if (pieces.size() == 2)
		{
			if (pieces[0] == "Texture")
			{
				ItemKey key = pieces[1];

				while (!assetFile.eof())
				{
					getline(assetFile, line);

					if (line.length() == 0)
						continue;
					else
						break;
				}

				if (assetFile.eof())
					continue;

				pieces = strSplit(line, ' ', 2);

				if (pieces[0] == "File")
				{
					ss.str("");
					ss << "assets/sheets/" << pieces[1];
					pTextures->addEmpty(key)->init(ss.str());
				}
				else
					continue;
			}
			else if (pieces[0] == "Animation")
			{
				ItemKey key = pieces[1];
				ItemKey texKey = "";
				int numFrames;
				vector<Sprite*> frames;

				while (!assetFile.eof())
				{
					getline(assetFile, line);

					if (line.length() == 0)
						continue;
					else
						break;
				}

				if (assetFile.eof())
					continue;

				pieces = strSplit(line, ' ', 2);

				if (pieces[0] == "Texture")
				{
					texKey = pieces[1];
				}
				else
					continue;

				while (!assetFile.eof())
				{
					getline(assetFile, line);

					if (line.length() == 0)
						continue;
					else
						break;
				}

				if (assetFile.eof())
					continue;

				pieces = strSplit(line, ' ', 2);

				if (pieces[0] == "Frames")
				{
					numFrames = toInt(pieces[1]);
				}
				else
					continue;

				if (numFrames == -1)
					continue;

				for (int i = 0; i < numFrames; ++i)
				{
					Rect rect;
					double speed;

					while (!assetFile.eof())
					{
						getline(assetFile, line);

						if (line.length() == 0)
							continue;
						else
							break;
					}

					if (assetFile.eof())
						break;

					pieces = strSplit(line, ' ', 2);

					if (pieces[0] == "Rect")
					{
						pieces = strSplit(pieces[1], ' ', 4);
						rect = Rect(toFloat(pieces[0]), toFloat(pieces[1]), toFloat(pieces[2]), toFloat(pieces[3]));
					}
					else
						break;

					while (!assetFile.eof())
					{
						getline(assetFile, line);

						if (line.length() == 0)
							continue;
						else
							break;
					}

					if (assetFile.eof())
						break;

					pieces = strSplit(line, ' ', 2);

					if (pieces[0] == "Speed")
					{
						speed = toFloat(pieces[1]);
					}
					else
						break;

					Sprite *sprite = New Sprite();
					sprite->init(pTextures->get(texKey), rect, speed);

					pSprites->add(sprite);

					frames.push_back(sprite);
				}

				pAnimations->addEmpty(key)->init(frames, true, true);
			}
		}
	}

	assetFile.close();
}
