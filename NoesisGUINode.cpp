#include "NoesisGUINode.h"

#import <CoreFoundation/CoreFoundation.h>


using namespace cocos2d;
using namespace Noesis;


class OpenGLState
{
public:
    void Store()
    {
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &_unpackAlignment);
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_frameBuffer);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &_renderBuffer);
        glGetIntegerv(GL_VIEWPORT, _viewport);

        glGetFloatv(GL_COLOR_CLEAR_VALUE, _clearColors);
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &_clearDepth);
        glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &_clearStencil);

        glGetBooleanv(GL_COLOR_WRITEMASK, _colorWriteMask);

        _dither = glIsEnabled(GL_DITHER);
        _sampleAlphaToCoverage = glIsEnabled(GL_SAMPLE_ALPHA_TO_COVERAGE);
        _sampleCoverage = glIsEnabled(GL_SAMPLE_COVERAGE);

        _depthTest = glIsEnabled(GL_DEPTH_TEST);
        glGetBooleanv(GL_DEPTH_WRITEMASK, &_depthWrite);
        glGetIntegerv(GL_DEPTH_FUNC, &_depthFunc);

        _stencilTest = glIsEnabled(GL_STENCIL_TEST);
        glGetIntegerv(GL_STENCIL_FAIL, &_stencilTestFailOp);
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_FAIL, &_stencilTestSPDF);
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &_stencilTestSPDP);
        glGetIntegerv(GL_STENCIL_FUNC, &_stencilFunc);
        glGetIntegerv(GL_STENCIL_REF, &_stencilRef);
        glGetIntegerv(GL_STENCIL_VALUE_MASK, &_stencilMask);
        glGetIntegerv(GL_STENCIL_WRITEMASK, &_stencilWriteMask);

        _scissorTest = glIsEnabled(GL_SCISSOR_TEST);
        _cullFaceEnabled = glIsEnabled(GL_CULL_FACE);
        glGetIntegerv(GL_CULL_FACE_MODE, &_cullFaceMode);

        _blendEnabled = glIsEnabled(GL_BLEND);
        glGetIntegerv(GL_BLEND_EQUATION_RGB, &_blendEquation);
        glGetIntegerv(GL_BLEND_SRC_RGB, &_blendSource);
        glGetIntegerv(GL_BLEND_DST_RGB, &_blendDestination);

        glGetIntegerv(GL_ACTIVE_TEXTURE, &_activeTexture);

        for (NsSize i = 0; i < 4; i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &(_boundTexture[i]));
        }

        glGetIntegerv(GL_CURRENT_PROGRAM, &_currentProgram);

        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &_arrayBuffer);
        for (NsSize i = 0; i < 6; i++)
        {
            glGetVertexAttribiv(i, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &(_vertexAttribsEnabled[i]));
        }

        glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &_elementArrayBuffer);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING_OES, &_vertexArrayBuffer);
    }

    void Restore()
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, _unpackAlignment);
	
        glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);

        glViewport(_viewport[0], _viewport[1], _viewport[2], _viewport[3]);

        glClearColor(_clearColors[0], _clearColors[1], _clearColors[2], _clearColors[3]);
        glClearDepth(_clearDepth);

        glClearStencil(_clearStencil);
        glColorMask(_colorWriteMask[0], _colorWriteMask[1], _colorWriteMask[2], _colorWriteMask[3]);

        _dither ? glEnable(GL_DITHER) : glDisable(GL_DITHER);
        _sampleAlphaToCoverage ? glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) : glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);

        _sampleCoverage ? glEnable(GL_SAMPLE_COVERAGE) : glDisable(GL_SAMPLE_COVERAGE);

        _depthTest ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

        glDepthMask(_depthWrite);
        glDepthFunc(_depthFunc);
        _stencilTest ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
        glStencilOp(_stencilTestFailOp, _stencilTestSPDF, _stencilTestSPDP);
        glStencilFunc(_stencilFunc, _stencilRef, _stencilMask);
        glStencilMask(_stencilWriteMask);
        _scissorTest ? glEnable(GL_SCISSOR_TEST) : glDisable(GL_SCISSOR_TEST);
        _cullFaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        glCullFace(_cullFaceMode);
        _blendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
        glBlendEquation(_blendEquation);
        glBlendFunc(_blendSource, _blendDestination);
        for (NsSize i = 0; i < 4; i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, _boundTexture[i]);
        }

        glActiveTexture(_activeTexture);

        glUseProgram(_currentProgram);

        glBindVertexArray(_vertexArrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _arrayBuffer);
        for (NsSize i = 0; i < 6; i++)
        {
            _vertexAttribsEnabled[i] ? glEnableVertexAttribArray(i) : glDisableVertexAttribArray(i);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementArrayBuffer);
        glBindVertexArrayOES(_vertexArrayBuffer);
    }

private:
	GLint _frameBuffer;
    GLint _renderBuffer;
	GLint _viewport[4];
	GLfloat _clearColors[4];
	GLfloat _clearDepth;
	GLint _clearStencil;
	GLboolean _depthTest;
	GLboolean _depthWrite;
	GLint _depthFunc;
	GLboolean _stencilTest;
	GLint _stencilTestFailOp;
	GLint _stencilTestSPDF;
	GLint _stencilTestSPDP;
	GLint _stencilFunc;
	GLint _stencilRef;
	GLint _stencilMask;
	GLint _stencilWriteMask;
	GLboolean _scissorTest;
	GLboolean _cullFaceEnabled;
	GLint _cullFaceMode;
	GLboolean _dither;
	GLboolean _sampleAlphaToCoverage;
	GLboolean _sampleCoverage;
	GLboolean _blendEnabled;
	GLint _blendEquation;
	GLint _blendSource;
	GLint _blendDestination;
	GLboolean _colorWriteMask[4];
	GLint _arrayBuffer;
	GLint _vertexAttribsEnabled[6];
	GLint _activeTexture;
	GLint _elementArrayBuffer;
	GLint _vertexArrayBuffer;
	GLint _boundTexture[4];
	GLint _currentProgram;
	GLint _unpackAlignment;
};


void ErrorHandler(const char* error, int line, const char* desc)
{
    printf("ERROR: %s", desc);
    exit(1);
}

NoesisGUINode::NoesisGUINode(const char* filename): _time(0.0f)
{
    auto touchListener = EventListenerTouchOneByOne::create();
   touchListener->onTouchBegan = CC_CALLBACK_2(NoesisGUINode::TouchBegan, this);
   touchListener->onTouchEnded = CC_CALLBACK_2(NoesisGUINode::TouchEnded, this);
   touchListener->onTouchMoved = CC_CALLBACK_2(NoesisGUINode::TouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    Noesis::GUI::InitOpenGL(ErrorHandler);
    MountMainBundle();

    Ptr<FrameworkElement> xaml = Noesis::GUI::LoadXaml<FrameworkElement>(filename);
    _xamlRenderer = Noesis::GUI::CreateRenderer(xaml.GetPtr());

    scheduleUpdate();

    // Force the first update because it is not being called by cocos
    update(0.0f);
}

void NoesisGUINode::update(float delta)
{
    Noesis::GUI::Tick();

    cocos2d::Size size = Director::getInstance()->getWinSizeInPixels();
    _xamlRenderer->SetSize(size.width, size.height);

    _time += delta;
    _xamlRenderer->Update(_time);
    _uiCommands = _xamlRenderer->WaitForUpdate();

    OpenGLState glState;
    glState.Store();
    _xamlRenderer->Render(_uiCommands.offscreenCommands.GetPtr());
    glState.Restore();
}

void NoesisGUINode::draw(cocos2d::Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(NoesisGUINode::DrawUI, this);
    renderer->addCommand(&_customCommand);
}

void NoesisGUINode::MountMainBundle() const
{
    char rootPath[PATH_MAX];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef url = CFBundleCopyBundleURL(mainBundle);
    CFStringRef str = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
    CFStringGetCString(str, rootPath, sizeof(rootPath), kCFStringEncodingUTF8);
    CFRelease(url);
    CFRelease(str);

    Noesis::GUI::AddResourceProvider(rootPath);
}

void NoesisGUINode::DrawUI() const
{
    OpenGLState glState;
    glState.Store();
    _xamlRenderer->Render(_uiCommands.commands.GetPtr());
    glState.Restore();
}

bool NoesisGUINode::TouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    NsInt x = touch->getLocationInView().x;
    NsInt y = touch->getLocationInView().y;
    _xamlRenderer->TouchDown(x, y, touch->getID());
    return true;
}

void NoesisGUINode::TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    NsInt x = touch->getLocationInView().x;
    NsInt y = touch->getLocationInView().y;
    _xamlRenderer->TouchUp(x, y, touch->getID());
}

void NoesisGUINode::TouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    NsInt x = touch->getLocationInView().x;
    NsInt y = touch->getLocationInView().y;
    _xamlRenderer->TouchMove(x, y, touch->getID());
}
