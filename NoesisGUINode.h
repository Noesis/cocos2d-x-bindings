#ifndef __NOESISGUI_NODE__
#define __NOESISGUI_NODE__


#include "cocos2d.h"


class NoesisGUINode: public cocos2d::Node
{
public:
    NoesisGUINode(const char* filename);

private:
    void update(float delta) override;
    void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

    void MountMainBundle() const;
    void DrawUI() const;

    bool TouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void TouchEnded(cocos2d::Touch*, cocos2d::Event*);
    void TouchMoved(cocos2d::Touch*, cocos2d::Event*);

private:
    float _time;
    cocos2d::CustomCommand _customCommand;
    Noesis::Ptr<Noesis::IRenderer> _xamlRenderer;
    Noesis::RenderCommands _uiCommands;
};

#endif
