MCBCallLambda
=============

Cocos2dx CCCallFunc like action that takes c++11 lambda.
<br>
auto callLater(MCBPlatformSupport::MCBCallLambda::create([=](){
        doSomethingWithCapturedParameters(s);
    }));

runAction(CCSequence::createWithTwoActions(CCDelayTime::create(.5f), callLater));