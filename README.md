# Cocos2d-x bindings for noesisGUI
This code integrates the UI middleware noesisGUI with Cocos2d-x. The implementation contains a custom implementation of *cocos2d::Node* that holds a noesisGUI renderer.

It can be used as follows:

```c++
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // add a menu item with "X" image, which is clicked to quit the program

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
      CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - (closeItem->getContentSize().width * 0.5),
	    origin.y + (closeItem->getContentSize().height * 0.8)));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // add a label shows "Hello World"
    
    // create and initialize a label
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setScale(0.5, 0.5);
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height * 0.7 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    /////////////////////////////
    // NoesisGUI
    _uiNode = new NoesisGUINode("Data/ComboBox.xaml");
    this->addChild(_uiNode);

    return true;
}
```
