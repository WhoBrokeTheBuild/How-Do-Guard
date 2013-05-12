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
	loadMovementConfig("movement.cfg");

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
				int numFrames = -1;
				vector<Sprite*> frames;
				bool autoFrames = false;
				int framesPerRow = -1;
				Rect frameSize;

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
					pieces = strSplit(pieces[1], ' ', 2);

					if (pieces.size() == 1)
					{
						numFrames = toInt(pieces[0]);
					}
					else if (pieces.size() == 2)
					{
						numFrames = toInt(pieces[0]);

						if (pieces[1] == "Auto")
						{
							autoFrames = true;
						}
					}
				}
				else
					continue;

				if (numFrames == -1)
					continue;

				if (autoFrames)
				{
					do 
					{
						line = getNextLine(assetFile);

						pieces = strSplit(line, ' ', 2);

						if (pieces[0] == "FramesPerRow")
						{
							framesPerRow = toInt(pieces[1]);
						}
						else if (pieces[0] == "FrameSize")
						{
							pieces = strSplit(pieces[1], ' ', 2);

							if (pieces.size() < 2)
								continue;

							frameSize = Rect(0, 0, toFloat(pieces[0]), toFloat(pieces[1]));
						}
					} 
					while (line != "" && pieces[0] != "FrameOrder");

					if (line == "")
						return;

					vector<Rect> tmpFrames;
					Rect tmpRect = frameSize;

					int col = 0;
					for (int i = 0; i < numFrames; ++i)
					{
						tmpFrames.push_back(tmpRect);
						tmpRect.X += frameSize.Width;
						col++;
						if (framesPerRow != -1 && col == framesPerRow)
						{
							col = 0;
							tmpRect.X = 0;
							tmpRect.Y += frameSize.Height;
						}
					}

					int numFramesInOrder = toInt(pieces[1]);

					for (int i = 0; i < numFramesInOrder; ++i)
					{
						line = getNextLine(assetFile);

						pieces = strSplit(line, ' ', 2);

						if (pieces[0] != "Frame")
							continue;

						pieces = strSplit(pieces[1], ' ', 2);

						int rectInd = toInt(pieces[0]) - 1;
						rectInd = clamp(rectInd, 0, (int)tmpFrames.size());
						float speed = toFloat(pieces[1]);

						Sprite *sprite = New Sprite();
						sprite->init(pTextures->get(texKey), tmpFrames[rectInd], speed);

						pSprites->add(sprite);

						frames.push_back(sprite);
					}
				}
				else
				{
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
	GameInputType type;
	VerticalState vertState, newVertState;
	PlayerState before, after;
	string line;
	vector<string> pieces;
	pair<GameInput, GameInputType> inputTypePair;
	int index;

	do 
	{
		line = getNextLine(stateFile);

		pieces = strSplit(line, ' ', 2);

		if (pieces.size() < 2)
			continue;

		if (pieces[0] == "Input")
		{
			pieces = strSplit(pieces[1], ' ', 2);

			input = INVALID_GAME_INPUT;
			type = INVALID_GAME_INPUT_TYPE;

			index = arrayIndexOf(NUM_GAME_INPUTS, GAME_INPUT_NAMES, pieces[0]);
			if (index != -1)
			{
				input = (GameInput)index;
			}

			index = arrayIndexOf(NUM_GAME_INPUT_TYPES, GAME_INPUT_TYPE_NAMES, pieces[1]);
			if (index != -1)
			{
				type = (GameInputType)index;
			}

			if (input == INVALID_GAME_INPUT)
				continue;

			inputTypePair = pair<GameInput, GameInputType>(input, type);
			data.insert(pair<pair<GameInput, GameInputType>, VerticalPlayerStateMap>(inputTypePair, VerticalPlayerStateMap()));
		}
		else if (pieces[0] == "VertState")
		{
			index = arrayIndexOf(NUM_VERTICAL_STATES, VERTICAL_STATE_NAMES, pieces[1]);
			if (index != -1)
			{
				vertState = (VerticalState)index;
				data[inputTypePair].insert(pair<VerticalState, PlayerStateChangeList>(vertState, PlayerStateChangeList()));
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

			data[inputTypePair][vertState].push_back(PlayerStateChange(before, after, newVertState));
		}

	} 
	while (line.size() != 0);

	PlayerStateData.insert(pair<ItemKey, PlayerStateMap>("toast", data));

	stateFile.close();
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

float DataManager::getFloat( string key )
{
	if (mapContainsKey(_floatConfig, key))
	{
		return _floatConfig[key];
	}
	return -1.0f;
}

void DataManager::loadMovementConfig( string filename )
{
	stringstream fullFilename;
	fullFilename << "assets/config/" << filename;

	ifstream moveFile(fullFilename.str().c_str());

	string line;
	vector<string> pieces;

	do 
	{
		line = getNextLine(moveFile);

		pieces = strSplit(line, ' ', 2);

		if (pieces.size() < 2)
			continue;

		_floatConfig.insert(pair<string, float>(pieces[0], toFloat(pieces[1])));
	}
	while (line.length() != 0);

	moveFile.close();
}
