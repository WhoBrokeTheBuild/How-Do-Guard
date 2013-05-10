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
	INF(toString(), "Starting Init");

	pAnimations = New Manager<Animation>();
	pAnimations->init();

	pSprites = New Manager<Sprite>();
	pSprites->init();

	pTextures = New Manager<Texture>();
	pTextures->init();

	loadAssets("main.cfg");

	INF(toString(), "Finished Init");
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
		line = getNextLine(mainFile);

		vector<string> pieces = strSplit(line, ' ', 2);

		if (pieces.size() == 2)
		{
			if (pieces[0] == "Load")
			{
				loadAssetFile(pieces[1]);
			}
		}
	}

	loadPlayerStates("toast_states.cfg");

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

				line = getNextLine(assetFile);

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
				bool loop = false;
				int numFrames;
				vector<Sprite*> frames;

				line = getNextLine(assetFile);

				pieces = strSplit(line, ' ', 2);

				if (pieces[0] == "Texture")
				{
					texKey = pieces[1];
				}
				else
					continue;

				line = getNextLine(assetFile);

				pieces = strSplit(line, ' ', 2);

				if (pieces[0] == "Loop")
				{
					loop = (pieces[1][0] == 'T');
				}
				else
					continue;

				line = getNextLine(assetFile);

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

					line = getNextLine(assetFile);

					pieces = strSplit(line, ' ', 2);

					if (pieces[0] == "Rect")
					{
						pieces = strSplit(pieces[1], ' ', 4);
						rect = Rect(toFloat(pieces[0]), toFloat(pieces[1]), toFloat(pieces[2]), toFloat(pieces[3]));
					}
					else
						break;

					line = getNextLine(assetFile);

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

				pAnimations->addEmpty(key)->init(frames, true, loop);
			}
		}
	}

	assetFile.close();
}

void DataManager::loadPlayerStates( string filename )
{
	stringstream fullFilename;
	fullFilename << "assets/config/" << filename;

	ifstream stateFile(fullFilename.str().c_str());

	PlayerStateMap data;

	GameInput input;
	VerticalState vertState, newVertState;
	PlayerState before, after;
	string line;
	vector<string> pieces;
	int index;

	do 
	{
		line = getNextLine(stateFile);

		pieces = strSplit(line, ' ', 2);

		if (pieces.size() < 2)
			continue;

		if (pieces[0] == "Input")
		{
			int index = arrayIndexOf(NUM_GAME_INPUTS, GAME_INPUT_NAMES, pieces[1]);
			if (index != -1)
			{
				input = (GameInput)index;
				data.insert(pair<GameInput, VerticalPlayerStateMap>(input, VerticalPlayerStateMap()));
			}
		}
		else if (pieces[0] == "VertState")
		{
			index = arrayIndexOf(NUM_VERTICAL_STATES, VERTICAL_STATE_NAMES, pieces[1]);
			if (index != -1)
			{
				vertState = (VerticalState)index;
				data[input].insert(pair<VerticalState, PlayerStateChangeList>(vertState, PlayerStateChangeList()));
			}
		}
		else if (pieces[0] == "AddState")
		{
			pieces = strSplit(pieces[1], ' ');

			if (pieces.size() < 2)
				continue;
			else if (pieces.size() == 2)
			{
				newVertState = vertState;
			}
			else
			{
				int index = arrayIndexOf(NUM_VERTICAL_STATES, VERTICAL_STATE_NAMES, pieces[2]);
				if (index != -1)
				{
					newVertState = (VerticalState)index;
				}
			}

			index = arrayIndexOf(NUM_PLAYER_STATES, PLAYER_STATE_NAMES, pieces[0]);
			if (index != -1)
			{
				before = (PlayerState)index;
			}

			index = arrayIndexOf(NUM_PLAYER_STATES, PLAYER_STATE_NAMES, pieces[1]);
			if (index != -1)
			{
				after = (PlayerState)index;
			}

			data[input][vertState].push_back(PlayerStateChange(before, after, newVertState));
		}

	} 
	while (line.size() != 0);

	PlayerStateData.insert(pair<ItemKey, PlayerStateMap>("toast", data));
}

string DataManager::getNextLine( ifstream& in )
{
	string line = "";

	while (!in.eof())
	{
		getline(in, line);

		if (line.length() == 0)
			continue;
		else
			break;
	}

	return line;
}
