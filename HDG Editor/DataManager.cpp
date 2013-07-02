#include "DataManager.h"

DataManager* gpDataManager = nullptr;
ConfigLevel DataManager::_config = ConfigLevel();

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

    BaseDir = "../HowDoGuard/";

    pAnimations = New Manager<Animation>();
    pAnimations->init();

    pSprites = New Manager<Sprite>();
    pSprites->init();

    pTextures = New Manager<Texture>();
    pTextures->init();

    reload();

    INF(toString(), "Finished Init");
}

void DataManager::term( void )
{
    delete pAnimations;
    delete pSprites;
    delete pTextures;
}

void DataManager::reload( void )
{
    _config.clear();

    pAnimations->clear();
    pSprites->clear();
    pTextures->clear();

    loadConfig("main.cfg");
}

void DataManager::loadConfig( string filename, vector<string> levels /*= vector<string>()*/ )
{
    ifstream file(BaseDir + "assets/config/" + filename);

    string line = "";
    string listName = "";

    while (!file.eof())
    {
        getline(file, line);

        if (line.length() == 0 || line[0] == '#')
            continue;

        if (line[0] == '!')
        {
            vector<string> split = strSplit(line, ' ', 2);

            if (split.size() < 2)
                continue;

            if (split[0] == "!Load")
            {
                loadConfig(split[1], levels);
            }
            else if (split[0] == "!LoadAsset")
            {
                loadAssets(split[1], levels);
            }
            else if (split[0] == "!Start")
            {
                levels.push_back(split[1]);
            }
            else if (split[0] == "!End")
            {
                levels.pop_back();
            }
            else if (split[0] == "!StartList")
            {
                listName = split[1];
                getLevel(levels)->addList(listName);
            }
            else if (split[0] == "!EndList")
            {
                listName = "";
            }
        }
        else
        {
            parseConfigLine(line, levels, listName);
        }
    }

    file.close();
}

void DataManager::loadAssets( string filename, vector<string> levels /*= vector<string>()*/ )
{
    ifstream file(BaseDir + "assets/config/" + filename);

    ConfigLevel *assetsLevel;
    vector<ConfigValue>
        *texturesList,
        *animationsList;

    assetsLevel = getLevel(levels)->addLevel("assets");

    texturesList   = assetsLevel->addList("textures");
    animationsList = assetsLevel->addList("animations");

    stringstream ss;
    string line;

    while (!file.eof())
    {
        getline(file, line);

        if (line.length() == 0 || line[0] == '#')
            continue;

        vector<string> pieces = strSplit(line, ' ', 2);

        if (pieces.size() == 2)
        {
            if (pieces[0] == "Texture")
            {
                ItemKey key = pieces[1];

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "File")
                {
                    ss.str("");
                    ss << BaseDir << "assets/sheets/" << pieces[1];
                    pTextures->addEmpty(key)->init(ss.str());

                    texturesList->push_back(key);
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
                Size frameSize = Size::ZERO;

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "Texture")
                {
                    texKey = pieces[1];
                }
                else
                    continue;

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "Loop")
                {
                    loop = (pieces[1][0] == 'T');
                }
                else
                    continue;

                do
                {
                    getline(file, line);

                    if (file.eof())
                        break;

                    if (line[0] == '#')
                        continue;
                }
                while (line.length() == 0);

                if (line.length() == 0)
                    break;

                pieces = strSplit(line, ' ', 2);

                if (pieces[0] == "Frames")
                {
                    pieces = strSplit(pieces[1], ' ', 2);

                    if (pieces.size() == 1)
                    {
                        numFrames = parseInt(pieces[0]);
                    }
                    else if (pieces.size() == 2)
                    {
                        numFrames = parseInt(pieces[0]);

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
                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] == "FramesPerRow")
                        {
                            framesPerRow = parseInt(pieces[1]);
                        }
                        else if (pieces[0] == "FrameSize")
                        {
                            if (pieces.size() < 2)
                                continue;

                            frameSize = parseVector2(pieces[1]);
                        }
                    } 
                    while (line.length() != 0 && pieces[0] != "FrameOrder");

                    if (line.length() == 0)
                        return;

                    vector<Rect> tmpFrames;
                    Rect tmpRect = Rect(Vector2::ZERO, frameSize);

                    int col = 0;
                    for (int i = 0; i < numFrames; ++i)
                    {
                        tmpFrames.push_back(tmpRect);
                        tmpRect.X += frameSize.width();
                        col++;
                        if (framesPerRow != -1 && col == framesPerRow)
                        {
                            col = 0;
                            tmpRect.X = 0;
                            tmpRect.Y += frameSize.height();
                        }
                    }

                    int numFramesInOrder = parseInt(pieces[1]);

                    for (int i = 0; i < numFramesInOrder; ++i)
                    {
                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] != "Frame")
                            continue;

                        pieces = strSplit(pieces[1], ' ', 2);

                        int rectInd = parseInt(pieces[0]) - 1;
                        rectInd = clamp(rectInd, 0, (int)tmpFrames.size());
                        float speed = parseFloat(pieces[1]);

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

                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] == "Rect")
                        {
                            rect = parseRect(pieces[1]);
                        }
                        else
                            break;

                        do
                        {
                            getline(file, line);

                            if (file.eof())
                                break;

                            if (line[0] == '#')
                                continue;
                        }
                        while (line.length() == 0);

                        if (line.length() == 0)
                            break;

                        pieces = strSplit(line, ' ', 2);

                        if (pieces[0] == "Speed")
                        {
                            speed = parseFloat(pieces[1]);
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

                animationsList->push_back(key);
            }
        }
    }

    file.close();
}

void DataManager::parseConfigLine( string line, vector<string> levels, string listName )
{
    ConfigLevel *tmp = getLevel(levels);

    if (listName != "")
    {
        tmp->getList(listName)->push_back(line);
    }
    else
    {
        vector<string> parts = strSplit(line, ' ', 2);

        if (parts.size() < 2)
            return;

        tmp->addData(parts[0], parts[1]);
    }
}

ConfigValue DataManager::getData( vector<ConfigKey> name, ConfigKey dataName )
{
    ConfigLevel* tmp = getLevel(name);

    if (!tmp->containsData(dataName))
    {
        return "";
    }

    return tmp->getData(dataName);
}

vector<ConfigValue>* DataManager::getList( vector<ConfigKey> name, ConfigKey listName )
{
    ConfigLevel* tmp = getLevel(name);

    if (!tmp->containsList(listName))
    {
        tmp->addList(listName);
    }

    return tmp->getList(listName);
}

ConfigLevel* DataManager::getLevel( vector<ConfigKey> name )
{
    ConfigLevel* tmpLevel = &_config;

    for (unsigned int i = 0; i < name.size(); ++i)
    {
        if (name[i].length() == 0)
            break;

        if (!tmpLevel->containsLevel(name[i]))
        {
            tmpLevel->addLevel(name[i]);
        }

        tmpLevel = tmpLevel->getLevel(name[i]);
    }

    return tmpLevel;
}

std::string DataManager::getString( vector<ConfigKey> name )
{
    string itemName = name.back();

    name.pop_back();

    return getLevel(name)->getData(itemName);
}

int DataManager::getInt( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseInt(getLevel(name)->getData(itemName));
}

float DataManager::getFloat( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseFloat(getLevel(name)->getData(itemName));
}

double DataManager::getDouble( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseDouble(getLevel(name)->getData(itemName));
}

Vector2 DataManager::getVector2( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseVector2(getLevel(name)->getData(itemName));
}

Rect DataManager::getRect( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseRect(getLevel(name)->getData(itemName));
}

Circle DataManager::getCircle( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseCircle(getLevel(name)->getData(itemName));
}

Color DataManager::getColor( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    return parseColor(getLevel(name)->getData(itemName));
}

vector<string> DataManager::getStringList( vector<ConfigKey> name )
{
    string itemName = name.back();
    name.pop_back();

    vector<string>* items = getLevel(name)->getList(itemName);

    if (items == nullptr)
        items = &vector<string>();

    return *items;
}

vector<int> DataManager::getIntList( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<int> items = vector<int>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseInt(itemsData[i]));

    return items;
}

vector<float> DataManager::getFloatList( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<float> items = vector<float>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseFloat(itemsData[i]));

    return items;
}

vector<double> DataManager::getDoubleList( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<double> items = vector<double>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseDouble(itemsData[i]));

    return items;
}

vector<Vector2> DataManager::getVector2List( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<Vector2> items = vector<Vector2>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseVector2(itemsData[i]));

    return items;
}

vector<Rect> DataManager::getRectList( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<Rect> items = vector<Rect>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseRect(itemsData[i]));

    return items;
}

vector<Circle> DataManager::getCircleList( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<Circle> items = vector<Circle>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseCircle(itemsData[i]));

    return items;
}

vector<Color> DataManager::getColorList( vector<ConfigKey> name )
{
    vector<string> itemsData = getStringList(name);
    vector<Color> items = vector<Color>();

    for (unsigned int i = 0; i < itemsData.size(); ++i)
        items.push_back(parseColor(itemsData[i]));

    return items;
}
