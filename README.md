MCBCallLambda
=============

Cocos2dx CCCallFunc like action that takes c++11 lambda.<br>
<br>
auto callLater(MCBPlatformSupport::MCBCallLambda::create(\[=\](){<br>
        doSomethingWithCapturedParameters(s);<br>
    }));<br>
<br>
runAction(CCSequence::createWithTwoActions(CCDelayTime::create(.5f), callLater));
<br><br>
Update1: added the factory for the sequence (createWithDelay)
