    #include "LabelTest.h"
#include "../testResource.h"

enum {
    kTagTileMap = 1,
    kTagSpriteManager = 1,
    kTagAnimation1 = 1,
    kTagBitmapAtlas1 = 1,
    kTagBitmapAtlas2 = 2,
    kTagBitmapAtlas3 = 3,
};

enum {
    kTagSprite1,
    kTagSprite2,
    kTagSprite3,
    kTagSprite4,
    kTagSprite5,
    kTagSprite6,
    kTagSprite7,
    kTagSprite8,
};

//------------------------------------------------------------------
//
// AtlasDemo
//
//------------------------------------------------------------------

enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

CCLayer* nextAtlasAction();
CCLayer* backAtlasAction();
CCLayer* restartAtlasAction();

static int sceneIdx = -1; 

#define MAX_LAYER    28

CCLayer* createAtlasLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new LabelAtlasTest();
        case 1: return new LabelAtlasColorTest();
        case 2: return new Atlas3();
        case 3: return new Atlas4();
        case 4: return new Atlas5();
        case 5: return new Atlas6();
        case 6: return new AtlasBitmapColor();
        case 7: return new AtlasFastBitmap();
        case 8: return new BitmapFontMultiLine();
        case 9: return new LabelsEmpty();
        case 10: return new LabelBMFontHD();
        case 11: return new LabelAtlasHD();
        case 12: return new LabelGlyphDesigner();

        // Not a label test. Should be moved to Atlas test
        case 13: return new Atlas1();
        case 14: return new LabelTTFTest();
        case 15: return new LabelTTFMultiline();
        case 16: return new LabelTTFChinese();
        case 17: return new LabelBMFontChinese();
        case 18: return new BitmapFontMultiLineAlignment();
        case 19: return new LabelTTFA8Test();
        case 20: return new BMFontOneAtlas();
        case 21: return new BMFontUnicode();
        case 22: return new BMFontInit();
        case 23: return new TTFFontInit();
        case 24: return new Issue1343();
        case 25: return new LabelTTFAlignment();
        case 26: return new LabelBMFontBounds();
        case 27: return new TTFFontShadowAndStroke();
    }

    return NULL;
}

CCLayer* nextAtlasAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;

    CCLayer* pLayer = createAtlasLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* backAtlasAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;    
    
    CCLayer* pLayer = createAtlasLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* restartAtlasAction()
{
    CCLayer* pLayer = createAtlasLayer(sceneIdx);
    pLayer->autorelease();

    return pLayer;
} 


AtlasDemo::AtlasDemo(void)
{
}

AtlasDemo::~AtlasDemo(void)
{
}

std::string AtlasDemo::title()
{
    return "No title";
}

std::string AtlasDemo::subtitle()
{
    return "";
}

void AtlasDemo::onEnter()
{
    BaseTest::onEnter();
}

void AtlasDemo::restartCallback(CCObject* pSender)
{
    CCScene* s = new AtlasTestScene();
    s->addChild(restartAtlasAction()); 

    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void AtlasDemo::nextCallback(CCObject* pSender)
{
    CCScene* s = new AtlasTestScene();
    s->addChild( nextAtlasAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void AtlasDemo::backCallback(CCObject* pSender)
{
    CCScene* s = new AtlasTestScene();
    s->addChild( backAtlasAction() );
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
} 


//------------------------------------------------------------------
//
// Atlas1
//
//------------------------------------------------------------------
Atlas1::Atlas1()
{
    _textureAtlas = CCTextureAtlas::create(s_AtlasTest, 3); _textureAtlas->retain();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    //
    // Notice: u,v tex coordinates are inverted
    //
    ccV3F_C4B_T2F_Quad quads[] = 
    {
        {
            {{0,0,0},ccc4(0,0,255,255),{0.0f,1.0f},},                // bottom left
            {{s.width,0,0},ccc4(0,0,255,0),{1.0f,1.0f},},            // bottom right
            {{0,s.height,0},ccc4(0,0,255,0),{0.0f,0.0f},},            // top left
            {{s.width,s.height,0},{0,0,255,255},{1.0f,0.0f},},    // top right
        },        
        {
            {{40,40,0},ccc4(255,255,255,255),{0.0f,0.2f},},            // bottom left
            {{120,80,0},ccc4(255,0,0,255),{0.5f,0.2f},},            // bottom right
            {{40,160,0},ccc4(255,255,255,255),{0.0f,0.0f},},        // top left
            {{160,160,0},ccc4(0,255,0,255),{0.5f,0.0f},},            // top right
        },

        {
            {{s.width/2,40,0},ccc4(255,0,0,255),{0.0f,1.0f},},        // bottom left
            {{s.width,40,0},ccc4(0,255,0,255),{1.0f,1.0f},},        // bottom right
            {{s.width/2-50,200,0},ccc4(0,0,255,255),{0.0f,0.0f},},        // top left
            {{s.width,100,0},ccc4(255,255,0,255),{1.0f,0.0f},},        // top right
        },
        
    };
    
    
    for( int i=0;i<3;i++) 
    {
        _textureAtlas->updateQuad(&quads[i], i);
    }
}

Atlas1::~Atlas1()
{
    _textureAtlas->release();
}

void Atlas1::draw()
{
    // GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
    // GL_TEXTURE_2D

    _textureAtlas->drawQuads();

//    [textureAtlas drawNumberOfQuads:3];
    
}

std::string Atlas1::title()
{
    return "CCTextureAtlas";
}

std::string Atlas1::subtitle()
{
    return "Manual creation of CCTextureAtlas";
}

//------------------------------------------------------------------
//
// LabelAtlasTest
//
//------------------------------------------------------------------

LabelAtlasTest::LabelAtlasTest()
{
    _time = 0;

    CCLabelAtlas* label1 = CCLabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( ccp(10,100) );
    label1->setOpacity( 200 );

    CCLabelAtlas *label2 = CCLabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.plist");
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( ccp(10,200) );
    label2->setOpacity( 32 );

    schedule(schedule_selector(LabelAtlasTest::step)); 
    
}

void LabelAtlasTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    //string.format("%2.2f Test", _time);

    CCLabelAtlas* label1 = (CCLabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);

    CCLabelAtlas*label2 = (CCLabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    //string.format("%d", (int)_time);
    label2->setString(string);
}

std::string LabelAtlasTest::title()
{
    return "LabelAtlas";
}

std::string LabelAtlasTest::subtitle()
{
    return "Updating label should be fast";
}

//------------------------------------------------------------------
//
// LabelAtlasColorTest
//
//------------------------------------------------------------------
LabelAtlasColorTest::LabelAtlasColorTest()
{
    CCLabelAtlas* label1 = CCLabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label1, 0, kTagSprite1);
    label1->setPosition( ccp(10,100) );
    label1->setOpacity( 200 );
    
    CCLabelAtlas* label2 = CCLabelAtlas::create("0123456789", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label2, 0, kTagSprite2);
    label2->setPosition( ccp(10,200) );
    label2->setColor( ccRED );

    CCActionInterval* fade = CCFadeOut::create(1.0f);
    CCActionInterval* fade_in = fade->reverse();
    CCCallFunc* cb = CCCallFunc::create(this, callfunc_selector(LabelAtlasColorTest::actionFinishCallback));
    CCSequence* seq = CCSequence::create(fade, fade_in, cb, NULL);
    CCAction* repeat = CCRepeatForever::create( seq );
    label2->runAction( repeat );    

    _time = 0;
    
    schedule( schedule_selector(LabelAtlasColorTest::step) ); //:@selector(step:)];
}

void LabelAtlasColorTest::actionFinishCallback()
{
    CCLOG("Action finished");
}

void LabelAtlasColorTest::step(float dt)
{
    _time += dt;
    char string[12] = {0};
    sprintf(string, "%2.2f Test", _time);
    //std::string string = std::string::createWithFormat("%2.2f Test", _time);
    CCLabelAtlas* label1 = (CCLabelAtlas*)getChildByTag(kTagSprite1);
    label1->setString(string);
    
    CCLabelAtlas* label2 = (CCLabelAtlas*)getChildByTag(kTagSprite2);
    sprintf(string, "%d", (int)_time);
    label2->setString( string );    
}

std::string LabelAtlasColorTest::title()
{
    return "CCLabelAtlas";
}

std::string LabelAtlasColorTest::subtitle()
{
    return "Opacity + Color should work at the same time";
}


//------------------------------------------------------------------
//
// LabelTTFAlignment
//
//------------------------------------------------------------------
LabelTTFAlignment::LabelTTFAlignment()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* ttf0 = CCLabelTTF::create("Alignment 0\nnew line", "Helvetica", 12,
                                          CCSizeMake(256, 32), kCCTextAlignmentLeft);
    ttf0->setPosition(ccp(s.width/2,(s.height/6)*2));
    ttf0->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(ttf0);

    CCLabelTTF* ttf1 = CCLabelTTF::create("Alignment 1\nnew line", "Helvetica", 12,
                                          CCSizeMake(245, 32), kCCTextAlignmentCenter);
    ttf1->setPosition(ccp(s.width/2,(s.height/6)*3));
    ttf1->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(ttf1);

    CCLabelTTF* ttf2 = CCLabelTTF::create("Alignment 2\nnew line", "Helvetica", 12,
                                          CCSizeMake(245, 32), kCCTextAlignmentRight);
    ttf2->setPosition(ccp(s.width/2,(s.height/6)*4));
    ttf2->setAnchorPoint(ccp(0.5f,0.5f));
    this->addChild(ttf2);
}

std::string LabelTTFAlignment::title()
{
    return "CCLabelTTF alignment";
}

std::string LabelTTFAlignment::subtitle()
{
    return "Tests alignment values";
}
//------------------------------------------------------------------
//
// Atlas3
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
Atlas3::Atlas3()
{
    _time = 0;

    CCLayerColor* col = CCLayerColor::create( ccc4(128,128,128,255) );
    addChild(col, -10);
    
    CCLabelBMFont* label1 = CCLabelBMFont::create("Test",  "fonts/bitmapFontTest2.fnt");
    
    // testing anchors
    label1->setAnchorPoint( ccp(0,0) );
    addChild(label1, 0, kTagBitmapAtlas1);
    CCActionInterval* fade = CCFadeOut::create(1.0f);
    CCActionInterval* fade_in = fade->reverse();
    CCSequence* seq = CCSequence::create(fade, fade_in, NULL);
    CCAction* repeat = CCRepeatForever::create(seq);
    label1->runAction(repeat);
    

    // VERY IMPORTANT
    // color and opacity work OK because bitmapFontAltas2 loads a BMP image (not a PNG image)
    // If you want to use both opacity and color, it is recommended to use NON premultiplied images like BMP images
    // Of course, you can also tell XCode not to compress PNG images, but I think it doesn't work as expected
    CCLabelBMFont *label2 = CCLabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label2->setAnchorPoint( ccp(0.5f, 0.5f) );
    label2->setColor( ccRED );
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->runAction( (CCAction*)(repeat->copy()->autorelease()) );
    
    CCLabelBMFont* label3 = CCLabelBMFont::create("Test", "fonts/bitmapFontTest2.fnt");
    // testing anchors
    label3->setAnchorPoint( ccp(1,1) );
    addChild(label3, 0, kTagBitmapAtlas3);
       
    label1->setPosition( VisibleRect::leftBottom() );
    label2->setPosition( VisibleRect::center() );
    label3->setPosition( VisibleRect::rightTop() );

    schedule( schedule_selector(Atlas3::step) );//:@selector(step:)];
}

void Atlas3::step(float dt)
{
    _time += dt;
    //std::string string;
    char string[15] = {0};
    sprintf(string, "%2.2f Test j", _time);
    //string.format("%2.2f Test j", _time);
    
    CCLabelBMFont *label1 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas1);
    label1->setString(string);
    
    CCLabelBMFont *label2 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label2->setString(string);
    
    CCLabelBMFont *label3 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas3);
    label3->setString(string);

}

std::string Atlas3::title()
{
    return "CCLabelBMFont";
}

std::string Atlas3::subtitle()
{
    return "Testing alignment. Testing opacity + tint";
}

//------------------------------------------------------------------
//
// Atlas4
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
Atlas4::Atlas4()
{
    _time = 0;

    // Upper Label
    CCLabelBMFont *label = CCLabelBMFont::create("Bitmap Font Atlas", "fonts/bitmapFontTest.fnt");
    addChild(label);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    
    
    CCSprite* BChar = (CCSprite*) label->getChildByTag(0);
    CCSprite* FChar = (CCSprite*) label->getChildByTag(7);
    CCSprite* AChar = (CCSprite*) label->getChildByTag(12);
    
    
    CCActionInterval* rotate = CCRotateBy::create(2, 360);
    CCAction* rot_4ever = CCRepeatForever::create(rotate);
    
    CCActionInterval* scale = CCScaleBy::create(2, 1.5f);
    CCActionInterval* scale_back = scale->reverse();
    CCSequence* scale_seq = CCSequence::create(scale, scale_back,NULL);
    CCAction* scale_4ever = CCRepeatForever::create(scale_seq);
    
    CCActionInterval* jump = CCJumpBy::create(0.5f, CCPointZero, 60, 1);
    CCAction* jump_4ever = CCRepeatForever::create(jump);
    
    CCActionInterval* fade_out = CCFadeOut::create(1);
    CCActionInterval* fade_in = CCFadeIn::create(1);
    CCSequence* seq = CCSequence::create(fade_out, fade_in, NULL);
    CCAction* fade_4ever = CCRepeatForever::create(seq);
    
    BChar->runAction(rot_4ever);
    BChar->runAction(scale_4ever);
    FChar->runAction(jump_4ever);
    AChar->runAction(fade_4ever);
    
    
    // Bottom Label
    CCLabelBMFont *label2 = CCLabelBMFont::create("00.0", "fonts/bitmapFontTest.fnt");
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition( ccp(s.width/2.0f, 80) );
    
    CCSprite* lastChar = (CCSprite*) label2->getChildByTag(3);
    lastChar->runAction( (CCAction*)(rot_4ever->copy()->autorelease()) );
    
    schedule( schedule_selector(Atlas4::step), 0.1f);
}

void Atlas4::draw()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    ccDrawLine( ccp(0, s.height/2), ccp(s.width, s.height/2) );
    ccDrawLine( ccp(s.width/2, 0), ccp(s.width/2, s.height) );
}

void Atlas4::step(float dt)
{
    _time += dt;
    char string[10] = {0};
    sprintf(string, "%04.1f", _time);
//     std::string string;
//     string.format("%04.1f", _time);
    
    CCLabelBMFont* label1 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas2);
    label1->setString(string);
}

std::string Atlas4::title()
{
    return "CCLabelBMFont";
}

std::string Atlas4::subtitle()
{
    return "Using fonts as CCSprite objects. Some characters should rotate.";
}

//------------------------------------------------------------------
//
// Atlas5
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

Atlas5::Atlas5()
{
    CCLabelBMFont *label = CCLabelBMFont::create("abcdefg", "fonts/bitmapFontTest4.fnt");
    addChild(label);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
}

std::string Atlas5::title()
{
    return "CCLabelBMFont";
}

std::string Atlas5::subtitle()
{
    return "Testing padding";
}
//------------------------------------------------------------------
//
// Atlas6
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

Atlas6::Atlas6()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* label = NULL;
    label = CCLabelBMFont::create("FaFeFiFoFu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/2+50) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) ) ;
    
    label = CCLabelBMFont::create("fafefifofu", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/2) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );

    label = CCLabelBMFont::create("aeiou", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/2-50) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) ); 
}

std::string Atlas6::title()
{
    return "CCLabelBMFont";
}

std::string Atlas6::subtitle()
{
    return "Rendering should be OK. Testing offset";
}

//------------------------------------------------------------------
//
// AtlasBitmapColor
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
AtlasBitmapColor::AtlasBitmapColor()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelBMFont* label = NULL;
    label = CCLabelBMFont::create("Blue", "fonts/bitmapFontTest5.fnt");
    label->setColor( ccBLUE );
    addChild(label);
    label->setPosition( ccp(s.width/2, s.height/4) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );

    label = CCLabelBMFont::create("Red", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, 2*s.height/4) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    label->setColor( ccRED );

    label = CCLabelBMFont::create("G", "fonts/bitmapFontTest5.fnt");
    addChild(label);
    label->setPosition( ccp(s.width/2, 3*s.height/4) );
    label->setAnchorPoint( ccp(0.5f, 0.5f) );
    label->setColor( ccGREEN );
    label->setString("Green");
}

std::string AtlasBitmapColor::title()
{
    return "CCLabelBMFont";
}

std::string AtlasBitmapColor::subtitle()
{
    return "Testing color";
}

//------------------------------------------------------------------
//
// AtlasFastBitmap
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------

AtlasFastBitmap::AtlasFastBitmap()
{
        // Upper Label
        for( int i=0 ; i < 100;i ++ ) 
        {
            char str[6] = {0};
            sprintf(str, "-%d-", i);
            CCLabelBMFont* label = CCLabelBMFont::create(str, "fonts/bitmapFontTest.fnt");
            addChild(label);
            
            CCSize s = CCDirector::sharedDirector()->getWinSize();

            CCPoint p = ccp( CCRANDOM_0_1() * s.width, CCRANDOM_0_1() * s.height);
            label->setPosition( p );
            label->setAnchorPoint(ccp(0.5f, 0.5f));
        }
}

std::string AtlasFastBitmap::title()
{
    return "CCLabelBMFont";
}

std::string AtlasFastBitmap::subtitle()
{
    return "Creating several CCLabelBMFont with the same .fnt file should be fast";
}

//------------------------------------------------------------------
//
// BitmapFontMultiLine
//
// Use any of these editors to generate BMFonts:
//     http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
//     http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
//     http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
//     http://www.angelcode.com/products/bmfont/ (Free, Windows only)
//
//------------------------------------------------------------------
BitmapFontMultiLine::BitmapFontMultiLine()
{
    CCSize s;

    // Left
    CCLabelBMFont *label1 = CCLabelBMFont::create(" Multi line\nLeft", "fonts/bitmapFontTest3.fnt");
    label1->setAnchorPoint(ccp(0,0));
    addChild(label1, 0, kTagBitmapAtlas1);

    s = label1->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);


    // Center
    CCLabelBMFont *label2 = CCLabelBMFont::create("Multi line\nCenter", "fonts/bitmapFontTest3.fnt");
    label2->setAnchorPoint(ccp(0.5f, 0.5f));
    addChild(label2, 0, kTagBitmapAtlas2);

    s= label2->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    // right
    CCLabelBMFont *label3 = CCLabelBMFont::create("Multi line\nRight\nThree lines Three", "fonts/bitmapFontTest3.fnt");
    label3->setAnchorPoint(ccp(1, 1));
    addChild(label3, 0, kTagBitmapAtlas3);

    s = label3->getContentSize();
    CCLOG("content size: %.2fx%.2f", s.width, s.height);

    label1->setPosition(VisibleRect::leftBottom());
    label2->setPosition(VisibleRect::center());
    label3->setPosition(VisibleRect::rightTop());
}

std::string BitmapFontMultiLine::title()
{
    return "CCLabelBMFont";
}

std::string BitmapFontMultiLine::subtitle()
{
    return "Multiline + anchor point";
}

//------------------------------------------------------------------
//
// LabelsEmpty
//
//------------------------------------------------------------------
LabelsEmpty::LabelsEmpty()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::create("", "fonts/bitmapFontTest3.fnt");
    addChild(label1, 0, kTagBitmapAtlas1);
    label1->setPosition(ccp(s.width/2, s.height-100));

    // CCLabelTTF
    CCLabelTTF* label2 = CCLabelTTF::create("", "Arial", 24);
    addChild(label2, 0, kTagBitmapAtlas2);
    label2->setPosition(ccp(s.width/2, s.height/2));

    // CCLabelAtlas
    CCLabelAtlas *label3 = CCLabelAtlas::create("", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
    addChild(label3, 0, kTagBitmapAtlas3);
    label3->setPosition(ccp(s.width/2, 0+100));

    schedule(schedule_selector(LabelsEmpty::updateStrings), 1.0f);

    setEmpty = false;
}

void LabelsEmpty::updateStrings(float dt)
{
    CCLabelBMFont* label1 = (CCLabelBMFont*) getChildByTag(kTagBitmapAtlas1);
    CCLabelTTF* label2 = (CCLabelTTF*) getChildByTag(kTagBitmapAtlas2);
    CCLabelAtlas* label3 = (CCLabelAtlas*) getChildByTag(kTagBitmapAtlas3);

    if( ! setEmpty )
    {
        label1->setString("not empty");
        label2->setString("not empty");
        label3->setString("hi");

        setEmpty = true;
    }
    else
    {
        label1->setString("");
        label2->setString("");
        label3->setString("");

        setEmpty = false;
    }
}

std::string LabelsEmpty::title()
{
    return "Testing empty labels";
}

std::string LabelsEmpty::subtitle()
{
    return "3 empty labels: LabelAtlas, LabelTTF and LabelBMFont";
}

//------------------------------------------------------------------
//
// LabelBMFontHD
//
//------------------------------------------------------------------
LabelBMFontHD::LabelBMFontHD()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::create("TESTING RETINA DISPLAY", "fonts/konqa32.fnt");
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

std::string LabelBMFontHD::title()
{
    return "Testing Retina Display BMFont";
}

std::string LabelBMFontHD::subtitle()
{
    return "loading arista16 or arista16-hd";
}

//------------------------------------------------------------------
//
// LabelAtlasHD
//
//------------------------------------------------------------------
LabelAtlasHD::LabelAtlasHD()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    // CCLabelBMFont
    CCLabelAtlas *label1 = CCLabelAtlas::create("TESTING RETINA DISPLAY", "fonts/larabie-16.plist");
    label1->setAnchorPoint(ccp(0.5f, 0.5f));

    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

std::string LabelAtlasHD::title()
{
    return "LabelAtlas with Retina Display";
}

std::string LabelAtlasHD::subtitle()
{
    return "loading larabie-16 / larabie-16-hd";
}

//------------------------------------------------------------------
//
// LabelGlyphDesigner
//
//------------------------------------------------------------------
LabelGlyphDesigner::LabelGlyphDesigner()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *layer = CCLayerColor::create(ccc4(128,128,128,255));
    addChild(layer, -10);

    // CCLabelBMFont
    CCLabelBMFont *label1 = CCLabelBMFont::create("Testing Glyph Designer", "fonts/futura-48.fnt");
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

std::string LabelGlyphDesigner::title()
{
    return "Testing Glyph Designer";
}

std::string LabelGlyphDesigner::subtitle()
{
    return "You should see a font with shawdows and outline";
}

void AtlasTestScene::runThisTest()
{
    sceneIdx = -1;
    CCLayer* pLayer = nextAtlasAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}

//------------------------------------------------------------------
//
// LabelTTFTest
//
//------------------------------------------------------------------
LabelTTFTest::LabelTTFTest()
{
    CCSize blockSize = CCSizeMake(200, 160);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *colorLayer = CCLayerColor::create(ccc4(100, 100, 100, 255), blockSize.width, blockSize.height);
    colorLayer->setAnchorPoint(ccp(0,0));
    colorLayer->setPosition(ccp((s.width - blockSize.width) / 2, (s.height - blockSize.height) / 2));

    this->addChild(colorLayer);

    CCMenuItemFont::setFontSize(30);
    CCMenu *menu = CCMenu::create(
		CCMenuItemFont::create("Left", CC_CALLBACK_1(LabelTTFTest::setAlignmentLeft, this)),
		CCMenuItemFont::create("Center", CC_CALLBACK_1(LabelTTFTest::setAlignmentCenter, this)),
		CCMenuItemFont::create("Right", CC_CALLBACK_1(LabelTTFTest::setAlignmentRight, this)),
        NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(ccp(50, s.height / 2 - 20));
    this->addChild(menu);

    menu = CCMenu::create(
		CCMenuItemFont::create("Top", CC_CALLBACK_1(LabelTTFTest::setAlignmentTop, this)),
		CCMenuItemFont::create("Middle", CC_CALLBACK_1(LabelTTFTest::setAlignmentMiddle, this)),
		CCMenuItemFont::create("Bottom", CC_CALLBACK_1(LabelTTFTest::setAlignmentBottom, this)),
		NULL);
    menu->alignItemsVerticallyWithPadding(4);
    menu->setPosition(ccp(s.width - 50, s.height / 2 - 20));
    this->addChild(menu);

    _plabel = NULL;
    _horizAlign = kCCTextAlignmentLeft;
    _vertAlign = kCCVerticalTextAlignmentTop;

    this->updateAlignment();
}

LabelTTFTest::~LabelTTFTest()
{
    CC_SAFE_RELEASE(_plabel);
}

void  LabelTTFTest::updateAlignment()
{
    CCSize blockSize = CCSizeMake(200, 160);
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    if (_plabel)
    {
        _plabel->removeFromParentAndCleanup(true);
    }

    CC_SAFE_RELEASE(_plabel);

    _plabel = CCLabelTTF::create(this->getCurrentAlignment(), "Marker Felt", 32,
                                  blockSize, _horizAlign, _vertAlign);
    _plabel->retain();

    _plabel->setAnchorPoint(ccp(0,0));
    _plabel->setPosition(ccp((s.width - blockSize.width) / 2, (s.height - blockSize.height)/2 ));

    this->addChild(_plabel);
}

void LabelTTFTest::setAlignmentLeft(CCObject* pSender)
{
    _horizAlign = kCCTextAlignmentLeft;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentCenter(CCObject* pSender)
{
    _horizAlign = kCCTextAlignmentCenter;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentRight(CCObject* pSender)
{
    _horizAlign = kCCTextAlignmentRight;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentTop(CCObject* pSender)
{
    _vertAlign = kCCVerticalTextAlignmentTop;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentMiddle(CCObject* pSender)
{
    _vertAlign = kCCVerticalTextAlignmentCenter;
    this->updateAlignment();
}

void LabelTTFTest::setAlignmentBottom(CCObject* pSender)
{
    _vertAlign = kCCVerticalTextAlignmentBottom;
    this->updateAlignment();
}

const char* LabelTTFTest::getCurrentAlignment()
{
    const char* vertical = NULL;
    const char* horizontal = NULL;
    switch (_vertAlign) {
        case kCCVerticalTextAlignmentTop:
            vertical = "Top";
            break;
        case kCCVerticalTextAlignmentCenter:
            vertical = "Middle";
            break;
        case kCCVerticalTextAlignmentBottom:
            vertical = "Bottom";
            break;
    }
    switch (_horizAlign) {
        case kCCTextAlignmentLeft:
            horizontal = "Left";
            break;
        case kCCTextAlignmentCenter:
            horizontal = "Center";
            break;
        case kCCTextAlignmentRight:
            horizontal = "Right";
            break;
    }

    return CCString::createWithFormat("Alignment %s %s", vertical, horizontal)->getCString();
}

string LabelTTFTest::title()
{
    return "Testing CCLabelTTF";
}

string LabelTTFTest::subtitle()
{
    return "Select the buttons on the sides to change alignment";
}

LabelTTFMultiline::LabelTTFMultiline()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *center = CCLabelTTF::create("word wrap \"testing\" (bla0) bla1 'bla2' [bla3] (bla4) {bla5} {bla6} [bla7] (bla8) [bla9] 'bla0' \"bla1\"",
                                            "Paint Boy",
                                            32,
                                            CCSizeMake(s.width/2,200),
                                            kCCTextAlignmentCenter,
                                            kCCVerticalTextAlignmentTop);

    center->setPosition(ccp(s.width / 2, 150));

    addChild(center);
}

string LabelTTFMultiline::title()
{
    return "Testing CCLabelTTF Word Wrap";
}

string LabelTTFMultiline::subtitle()
{
    return "Word wrap using CCLabelTTF and a custom TTF font";
}

LabelTTFChinese::LabelTTFChinese()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF *pLable = CCLabelTTF::create("中国", "Marker Felt", 30);
    pLable->setPosition(ccp(size.width / 2, size.height /2));
    this->addChild(pLable);
}

string LabelTTFChinese::title()
{
    return "Testing CCLabelTTF with Chinese character";
}

LabelBMFontChinese::LabelBMFontChinese()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelBMFont* pLable = CCLabelBMFont::create("中国", "fonts/bitmapFontChinese.fnt");
    pLable->setPosition(ccp(size.width / 2, size.height /2));
    this->addChild(pLable);
}

string LabelBMFontChinese::title()
{
    return "Testing CCLabelBMFont with Chinese character";
}

/// BitmapFontMultiLineAlignment

#define LongSentencesExample "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
#define LineBreaksExample "Lorem ipsum dolor\nsit amet\nconsectetur adipisicing elit\nblah\nblah"
#define MixedExample "ABC\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt\nDEF"

#define ArrowsMax 0.95
#define ArrowsMin 0.7

#define LeftAlign 0
#define CenterAlign 1
#define RightAlign 2

#define LongSentences 0
#define LineBreaks 1
#define Mixed 2

static float alignmentItemPadding = 50;
static float menuItemPaddingCenter = 50;
BitmapFontMultiLineAlignment::BitmapFontMultiLineAlignment()
{
    this->setTouchEnabled(true);

    // ask director the the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // create and initialize a Label
    this->_labelShouldRetain = CCLabelBMFont::create(LongSentencesExample, "fonts/markerFelt.fnt", size.width/1.5, kCCTextAlignmentCenter);
    this->_labelShouldRetain->retain();

    this->_arrowsBarShouldRetain = CCSprite::create("Images/arrowsBar.png");
    this->_arrowsBarShouldRetain->retain();
    this->_arrowsShouldRetain = CCSprite::create("Images/arrows.png");
    this->_arrowsShouldRetain->retain();

    CCMenuItemFont::setFontSize(20);
    CCMenuItemFont *longSentences = CCMenuItemFont::create("Long Flowing Sentences", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    CCMenuItemFont *lineBreaks = CCMenuItemFont::create("Short Sentences With Intentional Line Breaks", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    CCMenuItemFont *mixed = CCMenuItemFont::create("Long Sentences Mixed With Intentional Line Breaks", CC_CALLBACK_1(BitmapFontMultiLineAlignment::stringChanged, this));
    CCMenu *stringMenu = CCMenu::create(longSentences, lineBreaks, mixed, NULL);
    stringMenu->alignItemsVertically();

    longSentences->setColor(ccRED);
    _lastSentenceItem = longSentences;
    longSentences->setTag(LongSentences);
    lineBreaks->setTag(LineBreaks);
    mixed->setTag(Mixed);

    CCMenuItemFont::setFontSize(30);

    CCMenuItemFont *left = CCMenuItemFont::create("Left", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    CCMenuItemFont *center = CCMenuItemFont::create("Center", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    CCMenuItemFont *right = CCMenuItemFont::create("Right", CC_CALLBACK_1(BitmapFontMultiLineAlignment::alignmentChanged, this));
    CCMenu *alignmentMenu = CCMenu::create(left, center, right, NULL);
    alignmentMenu->alignItemsHorizontallyWithPadding(alignmentItemPadding);

    center->setColor(ccRED);
    _lastAlignmentItem = center;
    left->setTag(LeftAlign);
    center->setTag(CenterAlign);
    right->setTag(RightAlign);

    // position the label on the center of the screen
    this->_labelShouldRetain->setPosition(ccp(size.width/2, size.height/2));

    this->_arrowsBarShouldRetain->setVisible(false);

    float arrowsWidth = (ArrowsMax - ArrowsMin) * size.width;
    this->_arrowsBarShouldRetain->setScaleX(arrowsWidth / this->_arrowsBarShouldRetain->getContentSize().width);
    this->_arrowsBarShouldRetain->setPosition(ccp(((ArrowsMax + ArrowsMin) / 2) * size.width, this->_labelShouldRetain->getPosition().y));

    this->snapArrowsToEdge();

    stringMenu->setPosition(ccp(size.width/2, size.height - menuItemPaddingCenter));
    alignmentMenu->setPosition(ccp(size.width/2, menuItemPaddingCenter+15));

    this->addChild(this->_labelShouldRetain);
    this->addChild(this->_arrowsBarShouldRetain);
    this->addChild(this->_arrowsShouldRetain);
    this->addChild(stringMenu);
    this->addChild(alignmentMenu);
}

BitmapFontMultiLineAlignment::~BitmapFontMultiLineAlignment()
{
    this->_labelShouldRetain->release();
    this->_arrowsBarShouldRetain->release();
    this->_arrowsShouldRetain->release();
}

std::string BitmapFontMultiLineAlignment::title()
{
    return "";
}

std::string BitmapFontMultiLineAlignment::subtitle()
{
    return "";
}

void BitmapFontMultiLineAlignment::stringChanged(cocos2d::CCObject *sender)
{
    CCMenuItemFont *item = (CCMenuItemFont*)sender;
    item->setColor(ccRED);
    this->_lastAlignmentItem->setColor(ccWHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LongSentences:
        this->_labelShouldRetain->setString(LongSentencesExample);
        break;
    case LineBreaks:
        this->_labelShouldRetain->setString(LineBreaksExample);
        break;
    case Mixed:
        this->_labelShouldRetain->setString(MixedExample);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::alignmentChanged(cocos2d::CCObject *sender)
{
    CCMenuItemFont *item = (CCMenuItemFont*)sender;
    item->setColor(ccRED);
    this->_lastAlignmentItem->setColor(ccWHITE);
    this->_lastAlignmentItem = item;

    switch(item->getTag())
    {
    case LeftAlign:
        this->_labelShouldRetain->setAlignment(kCCTextAlignmentLeft);
        break;
    case CenterAlign:
        this->_labelShouldRetain->setAlignment(kCCTextAlignmentCenter);
        break;
    case RightAlign:
        this->_labelShouldRetain->setAlignment(kCCTextAlignmentRight);
        break;

    default:
        break;
    }

    this->snapArrowsToEdge();
}

void BitmapFontMultiLineAlignment::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();

    if (this->_arrowsShouldRetain->boundingBox().containsPoint(location))
    {
        _drag = true;
        this->_arrowsBarShouldRetain->setVisible(true);
    }
}

void BitmapFontMultiLineAlignment::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    _drag = false;
    this->snapArrowsToEdge();

    this->_arrowsBarShouldRetain->setVisible(false);
}

void BitmapFontMultiLineAlignment::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (! _drag)
    {
        return;
    }

    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    this->_arrowsShouldRetain->setPosition(ccp(MAX(MIN(location.x, ArrowsMax*winSize.width), ArrowsMin*winSize.width), 
        this->_arrowsShouldRetain->getPosition().y));

    float labelWidth = fabs(this->_arrowsShouldRetain->getPosition().x - this->_labelShouldRetain->getPosition().x) * 2;

    this->_labelShouldRetain->setWidth(labelWidth);
}

void BitmapFontMultiLineAlignment::snapArrowsToEdge()
{
    this->_arrowsShouldRetain->setPosition(ccp(this->_labelShouldRetain->getPosition().x + this->_labelShouldRetain->getContentSize().width/2,
        this->_labelShouldRetain->getPosition().y));
}

/// LabelTTFA8Test
LabelTTFA8Test::LabelTTFA8Test()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLayerColor *layer = CCLayerColor::create(ccc4(128, 128, 128, 255));
    addChild(layer, -10);

    // CCLabelBMFont
    CCLabelTTF *label1 = CCLabelTTF::create("Testing A8 Format", "Marker Felt", 48);
    addChild(label1);
    label1->setColor(ccRED);
    label1->setPosition(ccp(s.width/2, s.height/2));

    CCFadeOut *fadeOut = CCFadeOut::create(2);
    CCFadeIn *fadeIn = CCFadeIn::create(2);
    CCSequence *seq = CCSequence::create(fadeOut, fadeIn, NULL);
    CCRepeatForever *forever = CCRepeatForever::create(seq);
    label1->runAction(forever);
}

std::string LabelTTFA8Test::title()
{
    return "Testing A8 Format";
}

std::string LabelTTFA8Test::subtitle()
{
    return "RED label, fading In and Out in the center of the screen";
}

/// BMFontOneAtlas
BMFontOneAtlas::BMFontOneAtlas()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont *label1 = CCLabelBMFont::create("This is Helvetica", "fonts/helvetica-32.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft, CCPointZero);
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/3*2));

    CCLabelBMFont *label2 = CCLabelBMFont::create("And this is Geneva", "fonts/geneva-32.fnt", kCCLabelAutomaticWidth, kCCTextAlignmentLeft, ccp(0, 128));
    addChild(label2);
    label2->setPosition(ccp(s.width/2, s.height/3*1));
}

std::string BMFontOneAtlas::title()
{
    return "CCLabelBMFont with one texture";
}

std::string BMFontOneAtlas::subtitle()
{
    return "Using 2 .fnt definitions that share the same texture atlas.";
}

/// BMFontUnicode
BMFontUnicode::BMFontUnicode()
{
    CCDictionary *strings = CCDictionary::createWithContentsOfFile("fonts/strings.xml");

    const char *chinese  = ((CCString*)strings->objectForKey("chinese1"))->_string.c_str();
    const char *japanese = ((CCString*)strings->objectForKey("japanese"))->_string.c_str();
    const char *russian  = ((CCString*)strings->objectForKey("russian"))->_string.c_str();
    const char *spanish  = ((CCString*)strings->objectForKey("spanish"))->_string.c_str();


    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont *label1 = CCLabelBMFont::create(spanish, "fonts/arial-unicode-26.fnt", 200, kCCTextAlignmentLeft);
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/5*4));

    CCLabelBMFont *label2 = CCLabelBMFont::create(chinese, "fonts/arial-unicode-26.fnt");
    addChild(label2);
    label2->setPosition(ccp(s.width/2, s.height/5*3));

    CCLabelBMFont *label3 = CCLabelBMFont::create(russian, "fonts/arial-26-en-ru.fnt");
    addChild(label3);
    label3->setPosition(ccp(s.width/2, s.height/5*2));

    CCLabelBMFont *label4 = CCLabelBMFont::create(japanese, "fonts/arial-unicode-26.fnt");
    addChild(label4);
    label4->setPosition(ccp(s.width/2, s.height/5*1));
}

std::string BMFontUnicode::title()
{
    return "CCLabelBMFont with Unicode support";
}

std::string BMFontUnicode::subtitle()
{
    return "You should see 4 differnt labels:\nIn Spanish, Chinese, Russian and Korean";
}

// BMFontInit

BMFontInit::BMFontInit()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* bmFont = new CCLabelBMFont();
    bmFont->init();
    bmFont->autorelease();
    //CCLabelBMFont* bmFont = [CCLabelBMFont create:@"Foo" fntFile:@"arial-unicode-26.fnt"];
    bmFont->setFntFile("fonts/helvetica-32.fnt");
    bmFont->setString("It is working!");
    this->addChild(bmFont);
    bmFont->setPosition(ccp(s.width/2,s.height/4*2));
}

std::string BMFontInit::title()
{
    return "CCLabelBMFont init";
}

std::string BMFontInit::subtitle()
{
    return "Test for support of init method without parameters.";
}

// TTFFontInit

TTFFontInit::TTFFontInit()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* font = new CCLabelTTF();
    font->init();
    font->autorelease();
    font->setFontName("Marker Felt");
    font->setFontSize(48);
    font->setString("It is working!");
    this->addChild(font);
    font->setPosition(ccp(s.width/2,s.height/4*2));
}

std::string TTFFontInit::title()
{
    return "CCLabelTTF init";
}

std::string TTFFontInit::subtitle()
{
    return "Test for support of init method without parameters.";
}

TTFFontShadowAndStroke::TTFFontShadowAndStroke()
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(0,190,0,255));
    addChild(layer, -10);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    ccColor3B tintColorRed      =  { 255, 0, 0   };
    ccColor3B tintColorYellow   =  { 255, 255, 0 };
    ccColor3B tintColorBlue     =  { 0, 0, 255   };
    ccColor3B strokeColor       =  { 0, 10, 255  };
    ccColor3B strokeShadowColor =  { 255, 0, 0   };
    
    CCSize shadowOffset(12.0, 12.0);
    
    ccFontDefinition shadowTextDef;
    shadowTextDef._fontSize = 20;
    shadowTextDef._fontName = std::string("Marker Felt");
    
    shadowTextDef._shadow._shadowEnabled = true;
    shadowTextDef._shadow._shadowOffset  = shadowOffset;
    shadowTextDef._shadow._shadowOpacity = 1.0;
    shadowTextDef._shadow._shadowBlur    = 1.0;
    shadowTextDef._fontFillColor   = tintColorRed;
    
    // shadow only label
    CCLabelTTF* fontShadow = CCLabelTTF::createWithFontDefinition("Shadow Only Red Text", shadowTextDef);
    
    // add label to the scene
    this->addChild(fontShadow);
    fontShadow->setPosition(ccp(s.width/2,s.height/4*2.5));
    
    
    
    // create the stroke only label
    ccFontDefinition strokeTextDef;
    strokeTextDef._fontSize = 20;
    strokeTextDef._fontName = std::string("Marker Felt");
    
    strokeTextDef._stroke._strokeEnabled = true;
    strokeTextDef._stroke._strokeColor   = strokeColor;
    strokeTextDef._stroke._strokeSize    = 1.5;
    
    strokeTextDef._fontFillColor   = tintColorYellow;
    
    // stroke only label
    CCLabelTTF* fontStroke = CCLabelTTF::createWithFontDefinition("Stroke Only Yellow Text", strokeTextDef);
    
    // add label to the scene
    this->addChild(fontStroke);
    fontStroke->setPosition(ccp(s.width/2,s.height/4*1.8));
    
    
    
    // create the label stroke and shadow
    ccFontDefinition strokeShaodwTextDef;
    strokeShaodwTextDef._fontSize = 20;
    strokeShaodwTextDef._fontName = std::string("Marker Felt");
    
    strokeShaodwTextDef._stroke._strokeEnabled = true;
    strokeShaodwTextDef._stroke._strokeColor   = strokeShadowColor;
    strokeShaodwTextDef._stroke._strokeSize    = 1.5;
    
    strokeShaodwTextDef._shadow._shadowEnabled = true;
    strokeShaodwTextDef._shadow._shadowOffset  = shadowOffset;
    strokeShaodwTextDef._shadow._shadowOpacity = 1.0;
    strokeShaodwTextDef._shadow._shadowBlur    = 1.0;
    
    
    strokeShaodwTextDef._fontFillColor   = tintColorBlue;
    
    // shadow + stroke label
    CCLabelTTF* fontStrokeAndShadow = CCLabelTTF::createWithFontDefinition("Stroke & Shadow Blue Text", strokeShaodwTextDef);
    
    // add label to the scene
    this->addChild(fontStrokeAndShadow);
    fontStrokeAndShadow->setPosition(ccp(s.width/2,s.height/4*1.1));
    

    
}

std::string TTFFontShadowAndStroke::title()
{
    return "CCLabelTTF  shadows + stroke";
}

std::string TTFFontShadowAndStroke::subtitle()
{
    return "Test for support of TTF label with stroke and shadow";
}


// Issue1343

Issue1343::Issue1343()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelBMFont* bmFont = new CCLabelBMFont();
    bmFont->init();
    bmFont->setFntFile("fonts/font-issue1343.fnt");
    bmFont->setString("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'");
    this->addChild(bmFont);
    bmFont->release();
    bmFont->setScale(0.3f);

    bmFont->setPosition(ccp(s.width/2,s.height/4*2));
}

std::string Issue1343::title()
{
    return "Issue 1343";
}

std::string Issue1343::subtitle()
{
    return "You should see: ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890abcdefghijklmnopqrstuvwxyz.,'";
}

LabelBMFontBounds::LabelBMFontBounds()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor *layer = CCLayerColor::create(ccc4(128,128,128,255));
    addChild(layer, -10);
    
    // CCLabelBMFont
    label1 = CCLabelBMFont::create("Testing Glyph Designer", "fonts/boundsTestFont.fnt");
    
    
    addChild(label1);
    label1->setPosition(ccp(s.width/2, s.height/2));
}

string LabelBMFontBounds::title()
{
    return "Testing LabelBMFont Bounds";
}

string LabelBMFontBounds::subtitle()
{
    return "You should see string enclosed by a box";
}

void LabelBMFontBounds::draw()
{
    CCSize labelSize = label1->getContentSize();
    CCSize origin = CCDirector::sharedDirector()->getWinSize();
    
    origin.width = origin.width / 2 - (labelSize.width / 2);
    origin.height = origin.height / 2 - (labelSize.height / 2);
    
    CCPoint vertices[4]=
    {
        ccp(origin.width, origin.height),
        ccp(labelSize.width + origin.width, origin.height),
        ccp(labelSize.width + origin.width, labelSize.height + origin.height),
        ccp(origin.width, labelSize.height + origin.height)
    };
    ccDrawPoly(vertices, 4, true);
}

