#include "DataManager.h"

DataManager* gpDataManager = nullptr;

DataManager::~DataManager( void )
{
    term();
}

void DataManager::init( void )
{
    _configDir = "assets/config/";
    _sheetDir  = "assets/sheets/";
    _configExt = ".cfg";

    _pRoot = New ConfigObject();

    load("main");

    loadAssets(*ArrayList<string>().add("Game")->add("Assets"));
               
    loadAssets(*ArrayList<string>().add("Game")->add("Toast")->add("Assets"));
    loadAssets(*ArrayList<string>().add("Game")->add("Curl")->add("Assets"));
    loadAssets(*ArrayList<string>().add("Game")->add("Wolf")->add("Assets"));
    loadAssets(*ArrayList<string>().add("Game")->add("Ghost")->add("Assets"));
}

void DataManager::term( void )
{
    Map<ConfigKey, Texture*>::Iterator   texIt;
    Map<ConfigKey, Animation*>::Iterator animIt;

    for (texIt = Textures.begin(); texIt != Textures.end(); ++texIt)
    {
        delete texIt->second;
    }

    for (animIt = Animations.begin(); animIt != Animations.end(); ++animIt)
    {
        delete animIt->second;
    }

    for (unsigned int i = 0; i < Sprites.size(); ++i)
    {
        delete Sprites[i];
    }

    Textures.clear();
    Animations.clear();
    Sprites.clear();

    delete _pRoot;
}

void DataManager::load( string filename )
{
    parseFile(filename, _pRoot);
}

void DataManager::loadAssets( ArrayList<ConfigKey> path)
{
    ConfigObject* pObject = getObject(path);

    if (pObject == nullptr)
        return;

    ConfigObject
        *pTextureObj   = pObject->getObject("Textures"),
        *pAnimationObj = pObject->getObject("Animations");

    ArrayList<ConfigKey>
        textureKeys   = pTextureObj->getItemKeys(),
        animationKeys = pAnimationObj->getItemKeys();

    ConfigObject* object;
    ConfigKey     key;

    string filename;
    for (unsigned int i = 0; i < textureKeys.size(); ++i)
    {
        key      = textureKeys[i];
        object   = pTextureObj->getObject(key);
        filename = object->getString("File");

        if (filename.length() == 0)
            continue;

        Textures.add(key, New Texture());
        Textures[key]->init(_sheetDir + filename);
    }
    
    string   textureKey;
    Texture* texture;
    bool     loop;
    bool     autoPos;
    int      frames;
    int      framesPerRow;
    Vector2  frameSize;
    ArrayList<ConfigObject*>* frameOrder;
    for (unsigned int i = 0; i < animationKeys.size(); ++i)
    {
        key      = animationKeys[i];
        object   = pAnimationObj->getObject(key);

        textureKey   = object->getString ("Texture");
        frames       = object->getInt    ("Frames",        1);
        framesPerRow = object->getInt    ("FramesPerRow", -1);
        loop         = object->getBool   ("Loop",         false);
        autoPos      = object->getBool   ("AutoPos",      false);
        frameSize    = object->getVector2("FrameSize");
        frameOrder   = &object->getObjectList("Order");

        if (textureKey.length() == 0 || !Textures.contains(textureKey))
        {
            stringstream ss;
            ss << "Invalid Texture: " << texture;
            ERR(toString(), ss.str())
            continue;
        }

        if (!autoPos) // TODO: Add manual positioning
            continue;

        if (filename.length() == 0)
            continue;

        texture = Textures[textureKey];

        ArrayList<Rect> frameRects;
        Rect rect = Rect(Vector2::ZERO, frameSize);

        int col = 0;
        for (int i = 0; i < frames; ++i, ++col)
        {
            frameRects.add(rect);

            rect.X += frameSize.width();
            if (framesPerRow != -1 && col == framesPerRow)
            {
                col = 0;
                rect.X = 0;
                rect.Y += frameSize.height();
            }
        }

        ArrayList<Sprite*> frameSprites;

        ConfigObject* orderObject;
        Sprite*       sprite;
        int           rectInd;
        float        frameSpeed;
        for (unsigned int i = 0; i < frameOrder->size(); ++i)
        {
            orderObject = frameOrder->at(i);
            rectInd     = orderObject->getInt("Frame", -1);
            frameSpeed  = orderObject->getFloat("Speed");

            if (!between(rectInd, 0, (int)frameRects.size()))
                continue;
            
            sprite = New Sprite();
            Sprites.add(sprite);

            sprite->init(texture, frameRects[rectInd], (double)frameSpeed);
        }

        Animations.add(key, New Animation());
        Animations[key]->init(frameSprites, loop);
    }
}

void DataManager::parseFile( string filename, ConfigObject* pBase )
{
    ifstream file(_configDir + filename + _configExt);

    struct ParseLevel
    {
        string 
            Name;

        int 
            Index;

        bool
            List;

        ParseLevel( void ) { }
        ParseLevel( string name, bool list = false ) { Name = name; List = list; }
        ParseLevel( int index, bool list = false ) { Index = index; List = list; }

    };

    bool 
        blockComment = false,
        lineComment  = false,
        inSpecial    = false,
        inList       = false,
        inType       = false,
        inName       = false,
        inValue      = false,
        hasType      = false,
        hasName      = false,
        hasValue     = false,
        endOfLine    = false;

    unsigned int 
        indent       = 0,
        spaceCount   = 0,
        tabCount     = 0;

    char 
        chCurr,
        chNext;

    string 
        type,
        name,
        value;

    ArrayList<ParseLevel> levels;

    string line;
    unsigned int lineNumber = 0;
    while (!file.eof())
    {
        getline(file, line);
        line += '\n';
        ++lineNumber;

        inSpecial = false;
        inType = false;
        inName = false;
        inValue = false;

        hasType = false;
        hasName = false;
        hasValue = false;

        lineComment = false;
        endOfLine = false;

        type = "";
        name = "";
        value = "";

        spaceCount   = 0;
        tabCount     = 0;

        for (unsigned int ind = 0; ind < line.length(); ++ind)
        {
            if (line[ind] == ' ')
                ++spaceCount;
            else if (line[ind] == '\t')
                spaceCount += 4;
            else
                break;
        }

        if (spaceCount + tabCount == line.length() - 1) // Empty Line
            continue;

        indent = (spaceCount / 4) + tabCount;

        for (unsigned int ind = spaceCount + tabCount; ind < line.length(); ++ind)
        {
            chCurr = line[ind];
            endOfLine = (ind == line.length() - 1);
            chNext = (endOfLine ? '\0' : line[ind + 1]);

            if (blockComment)
            {
                if (chCurr == '*' && !endOfLine && chNext == '/')
                {
                    blockComment = false;
                }
                else
                    continue;
            }

            if (!inValue && type == "string")
            {
                if (chCurr == '/' && !endOfLine)
                {
                    if (chNext == '/')
                    {
                        lineComment = true;
                    }
                    else if (chNext == '*')
                    {
                        blockComment = true;
                    }
                }
            }

            if (lineComment || blockComment)
            {
                inType = false;
                inName = false;
                inValue = false;
            }
            else
            {

                if (inType)
                {
                    if (chCurr == ' ' || chCurr == '\t' || chCurr == '\n')
                    {
                        inType = false;
                        hasType = true;

                        while (indent < levels.size())
                        {
                            levels.removeBack();
                        }

                        if (levels.size() > 0 && indent > 0)
                        {
                            inList = levels[indent - 1].List;
                        }
                        else
                        {
                            inList = false;
                        }
                    }
                    else
                        type += chCurr;
                }
                else if (inName)
                {
                    if (chCurr == ' ' || chCurr == '\t' || chCurr == '\n')
                    {
                        inName = false;
                        hasName = true;
                    }
                    else
                        name += chCurr;
                }
                else if (inValue)
                {
                    if ( (type == "string" && line[ind - 1] != '\\' && chCurr == '"') ||
                         (type != "string" && chCurr == '\n') )
                    {
                        inValue = false;
                        hasValue = true;
                    }
                    else
                        value += chCurr;
                }
                else
                {
                    if (chCurr == '$')
                    {
                        inType = true;
                    }
                    else if (chCurr == '#')
                    {
                        inSpecial = true;
                    }
                    else if (chCurr != ' ' && chCurr != '\t' || chCurr == '\n')
                    {
                        if (inList || hasName)
                        {
                            if (hasType && !hasValue)
                            {
                                inValue = true;

                                if (type != "string")
                                    value += chCurr;
                            }
                        }
                        else
                        {
                            if (hasType && !hasName)
                            {
                                inName = true;
                                name += chCurr;
                            }
                        }
                    }
                }
            }
        }

        if (inSpecial)
        {
            while (indent < levels.size())
            {
                levels.removeBack();
            }

            if (levels.size() > 0 && indent > 0)
            {
                inList = levels[indent - 1].List;
            }
            else
            {
                inList = false;
            }
        }

        ConfigObject*          parentObject = pBase;
        ArrayList<ConfigItem>* parentList = nullptr;

        for (unsigned int levelInd = 0; levelInd < levels.size(); ++levelInd)
        {
            ParseLevel 
                curr = levels[levelInd],
                prev = (levelInd >= 1 ? levels[levelInd - 1] : ParseLevel());

            if (curr.List)
            {
                parentList = &parentObject->_itemLists[curr.Name];
            }
            else
            {
                if (levelInd >= 1 && prev.List)
                {
                    parentObject = parentObject->_itemLists[prev.Name][curr.Index].ObjectData;
                }
                else
                {
                    parentObject = parentObject->_items[curr.Name].ObjectData;
                }
            }
        }

        if (inSpecial)
        {
            string filename = "";

            bool inQuotes = false;
            for (unsigned int i = 0; i < line.length(); ++i)
            {
                if (!inQuotes)
                {
                    if (line[i] == '"')
                    {
                        inQuotes = true;
                        continue;
                    }
                    else if (line[i] == ' ' || line[i] == '\t')
                    {
                        continue;
                    }
                }
                else
                {
                    if (line[i - 1] != '\\' && line[i] == '"')
                    {
                        break;
                    }

                    filename += line[i];
                }
            }

            if (strContains(line, "#include") && parentObject != nullptr)
            {
                parseFile(filename, parentObject);
            }
        }

        if (type == "object" || type == "list")
        {
            if (type == "list" && inList)
                continue;

            if (inList)
            {
                if (type == "object")
                {
                    parentList->add(ConfigItem(New ConfigObject()));
                    levels.add(ParseLevel(parentList->size() - 1, false));
                }
            }
            else
            {
                if (type == "object")
                {
                    parentObject->_items.add(name, ConfigItem(New ConfigObject()));
                    levels.add(ParseLevel(name, false));
                }
                else if (type == "list")
                {
                    parentObject->_itemLists.add(name, ArrayList<ConfigItem>());
                    levels.add(ParseLevel(name, true));
                }
            }

        }
        else
        {
            if (name == "Frame")
            {
                noop();
            }

            ConfigItem item;

            if (type == "")
            {
                continue;
            }

            if (type == "int")
            {
                item = ConfigItem(parseInt(value));
            }
            else if (type == "float")
            {
                item = ConfigItem(parseFloat(value));
            }
            else if (type == "bool")
            {
                item = ConfigItem(parseBool(value));
            }
            else if (type == "string")
            {
                item = ConfigItem(value);
            }
            else if (type == "vector2")
            {
                item = ConfigItem(parseVector2(value));
            }
            else if (type == "rect")
            {
                item = ConfigItem(parseRect(value));
            }
            else if (type == "circle")
            {
                item = ConfigItem(parseCircle(value));
            }
            else if (type == "color")
            {
                item = ConfigItem(parseColor(value));
            }

            if (item.Type == INVALID_CONFIG_TYPE)
                continue;

            if (inList)
            {
                if (parentList != nullptr)
                    parentList->add(item);
            }
            else
            {
                if (parentObject != nullptr)
                    parentObject->_items.add(name, item);
            }
        }
    }

    file.close();
}

ConfigObject* DataManager::getObject( ArrayList<ConfigKey> path )
{
    ConfigObject* item = _pRoot;

    for (unsigned int i = 0; i < path.size(); ++i)
    {
        if (item->hasObject(path[i]))
        {
            item = item->getObject(path[i]);
        }
        else
        {
            item = nullptr;
            break;
        }
    }

    return item;
}
